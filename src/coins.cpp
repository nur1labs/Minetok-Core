/***********************************************************************
***********Copyright (c) 2012-2014 The Bitcoin developers***************
*************Copyright (c) 2015-2020 The PIVX developers****************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#include "coins.h"

#include "consensus/consensus.h"
#include "policy/fees.h"
#include "logging.h"
#include "random.h"
#include "version.h"

#include <assert.h>

bool CCoinsView::GetCoin(const COutPoint& outpoint, Coin& coin) const { return false; }
bool CCoinsView::HaveCoin(const COutPoint& outpoint) const { return false; }
uint256 CCoinsView::GetBestBlock() const { return UINT256_ZERO; }
std::vector<uint256> CCoinsView::GetHeadBlocks() const { return std::vector<uint256>(); }
CCoinsViewCursor *CCoinsView::Cursor() const { return 0; }

bool CCoinsView::BatchWrite(CCoinsMap& mapCoins,
                            const uint256& hashBlock) { return false; }

CCoinsViewBacked::CCoinsViewBacked(CCoinsView* viewIn) : base(viewIn) {}
bool CCoinsViewBacked::GetCoin(const COutPoint& outpoint, Coin& coin) const { return base->GetCoin(outpoint, coin); }
bool CCoinsViewBacked::HaveCoin(const COutPoint& outpoint) const { return base->HaveCoin(outpoint); }
uint256 CCoinsViewBacked::GetBestBlock() const { return base->GetBestBlock(); }
std::vector<uint256> CCoinsViewBacked::GetHeadBlocks() const { return base->GetHeadBlocks(); }
void CCoinsViewBacked::SetBackend(CCoinsView& viewIn) { base = &viewIn; }
CCoinsViewCursor *CCoinsViewBacked::Cursor() const { return base->Cursor(); }
size_t CCoinsViewBacked::EstimateSize() const { return base->EstimateSize(); }

bool CCoinsViewBacked::BatchWrite(CCoinsMap& mapCoins,
                                  const uint256& hashBlock)
{ return base->BatchWrite(mapCoins, hashBlock); }

SaltedOutpointHasher::SaltedOutpointHasher() : k0(GetRand(std::numeric_limits<uint64_t>::max())), k1(GetRand(std::numeric_limits<uint64_t>::max())) {}
SaltedIdHasher::SaltedIdHasher() : k0(GetRand(std::numeric_limits<uint64_t>::max())), k1(GetRand(std::numeric_limits<uint64_t>::max())) {}

CCoinsViewCache::CCoinsViewCache(CCoinsView *baseIn) : CCoinsViewBacked(baseIn), cachedCoinsUsage(0) {}

size_t CCoinsViewCache::DynamicMemoryUsage() const {
    return memusage::DynamicUsage(cacheCoins) +
           cachedCoinsUsage;
}

CCoinsMap::iterator CCoinsViewCache::FetchCoin(const COutPoint& outpoint) const
{
    CCoinsMap::iterator it = cacheCoins.find(outpoint);
    if (it != cacheCoins.end())
        return it;
    Coin tmp;
    if (!base->GetCoin(outpoint, tmp))
        return cacheCoins.end();
    CCoinsMap::iterator ret = cacheCoins.emplace(std::piecewise_construct, std::forward_as_tuple(outpoint), std::forward_as_tuple(std::move(tmp))).first;
    if (ret->second.coin.IsSpent()) {
        // The parent only has an empty entry for this outpoint; we can consider our
        // version as fresh.
        ret->second.flags = CCoinsCacheEntry::FRESH;
    }
    cachedCoinsUsage += memusage::DynamicUsage(ret->second.coin);
    return ret;
}

bool CCoinsViewCache::GetCoin(const COutPoint& outpoint, Coin& coin) const
{
    CCoinsMap::const_iterator it = FetchCoin(outpoint);
    if (it != cacheCoins.end()) {
        coin = it->second.coin;
        return true;
    }
    return false;
}

void CCoinsViewCache::AddCoin(const COutPoint& outpoint, Coin&& coin, bool possible_overwrite) {
    assert(!coin.IsSpent());
    if (coin.out.scriptPubKey.IsUnspendable()) return;
    CCoinsMap::iterator it;
    bool inserted;
    std::tie(it, inserted) = cacheCoins.emplace(std::piecewise_construct, std::forward_as_tuple(outpoint), std::tuple<>());
    bool fresh = false;
    if (!inserted) {
        cachedCoinsUsage -= it->second.coin.DynamicMemoryUsage();
    }
    if (!possible_overwrite) {
        if (!it->second.coin.IsSpent()) {
            throw std::logic_error("Adding new coin that replaces non-pruned entry");
        }
        fresh = !(it->second.flags & CCoinsCacheEntry::DIRTY);
    }
    it->second.coin = std::move(coin);
    it->second.flags |= CCoinsCacheEntry::DIRTY | (fresh ? CCoinsCacheEntry::FRESH : 0);
    cachedCoinsUsage += it->second.coin.DynamicMemoryUsage();
}

void AddCoins(CCoinsViewCache& cache, const CTransaction& tx, int nHeight, bool check)
{
    bool fCoinbase = tx.IsCoinBase();
    bool fCoinstake = tx.IsCoinStake();
    const uint256& txid = tx.GetHash();
    for (size_t i = 0; i < tx.vout.size(); ++i) {
        const COutPoint out(txid, i);
        bool overwrite = check && cache.HaveCoin(out);
        cache.AddCoin(out, Coin(tx.vout[i], nHeight, fCoinbase, fCoinstake), overwrite);
    }
}

void CCoinsViewCache::SpendCoin(const COutPoint& outpoint, Coin* moveout)
{
    CCoinsMap::iterator it = FetchCoin(outpoint);
    if (it == cacheCoins.end()) return;
    cachedCoinsUsage -= it->second.coin.DynamicMemoryUsage();
    if (moveout) {
        *moveout = std::move(it->second.coin);
    }
    if (it->second.flags & CCoinsCacheEntry::FRESH) {
        cacheCoins.erase(it);
    } else {
        it->second.flags |= CCoinsCacheEntry::DIRTY;
        it->second.coin.Clear();
    }
}

static const Coin coinEmpty;

const Coin& CCoinsViewCache::AccessCoin(const COutPoint& outpoint) const
{
    CCoinsMap::const_iterator it = FetchCoin(outpoint);
    if (it == cacheCoins.end()) {
        return coinEmpty;
    } else {
        return it->second.coin;
    }
}

bool CCoinsViewCache::HaveCoin(const COutPoint& outpoint) const
{
    CCoinsMap::const_iterator it = FetchCoin(outpoint);
    return (it != cacheCoins.end() && !it->second.coin.IsSpent());
}

bool CCoinsViewCache::HaveCoinInCache(const COutPoint& outpoint) const
{
    CCoinsMap::const_iterator it = cacheCoins.find(outpoint);
    return it != cacheCoins.end();
}

uint256 CCoinsViewCache::GetBestBlock() const
{
    if (hashBlock.IsNull())
        hashBlock = base->GetBestBlock();
    return hashBlock;
}

void CCoinsViewCache::SetBestBlock(const uint256& hashBlockIn)
{
    hashBlock = hashBlockIn;
}

template<typename Map, typename MapIterator, typename MapEntry>
void BatchWriteAnchors(
        Map &mapAnchors,
        Map &cacheAnchors,
        size_t &cachedCoinsUsage
)
{
    for (MapIterator child_it = mapAnchors.begin(); child_it != mapAnchors.end();)
    {
        if (child_it->second.flags & MapEntry::DIRTY) {
            MapIterator parent_it = cacheAnchors.find(child_it->first);

            if (parent_it == cacheAnchors.end()) {
                MapEntry& entry = cacheAnchors[child_it->first];
                entry.entered = child_it->second.entered;
                entry.tree = child_it->second.tree;
                entry.flags = MapEntry::DIRTY;

                cachedCoinsUsage += entry.tree.DynamicMemoryUsage();
            } else {
                if (parent_it->second.entered != child_it->second.entered) {
                    // The parent may have removed the entry.
                    parent_it->second.entered = child_it->second.entered;
                    parent_it->second.flags |= MapEntry::DIRTY;
                }
            }
        }

        MapIterator itOld = child_it++;
        mapAnchors.erase(itOld);
    }
}

bool CCoinsViewCache::BatchWrite(CCoinsMap& mapCoins,
                                 const uint256& hashBlockIn)
{
    for (CCoinsMap::iterator it = mapCoins.begin(); it != mapCoins.end(); it = mapCoins.erase(it)) {
        // Ignore non-dirty entries (optimization).
        if (!(it->second.flags & CCoinsCacheEntry::DIRTY)) {
            continue;
        }
        CCoinsMap::iterator itUs = cacheCoins.find(it->first);
        if (itUs == cacheCoins.end()) {
            // The parent cache does not have an entry, while the child does
            // We can ignore it if it's both FRESH and pruned in the child
            if (!(it->second.flags & CCoinsCacheEntry::FRESH && it->second.coin.IsSpent())) {
                // Otherwise we will need to create it in the parent
                // and move the data up and mark it as dirty
                CCoinsCacheEntry& entry = cacheCoins[it->first];
                entry.coin = std::move(it->second.coin);
                cachedCoinsUsage += memusage::DynamicUsage(entry.coin);
                entry.flags = CCoinsCacheEntry::DIRTY;
                // We can mark it FRESH in the parent if it was FRESH in the child
                // Otherwise it might have just been flushed from the parent's cache
                // and already exist in the grandparent
                if (it->second.flags & CCoinsCacheEntry::FRESH) {
                    entry.flags |= CCoinsCacheEntry::FRESH;
                }
            }
        } else {
            // Assert that the child cache entry was not marked FRESH if the
            // parent cache entry has unspent outputs. If this ever happens,
            // it means the FRESH flag was misapplied and there is a logic
            // error in the calling code.
            if ((it->second.flags & CCoinsCacheEntry::FRESH) && !itUs->second.coin.IsSpent()) {
                throw std::logic_error("FRESH flag misapplied to cache entry for base transaction with spendable outputs");
            }

            // Found the entry in the parent cache
            if ((itUs->second.flags & CCoinsCacheEntry::FRESH) && it->second.coin.IsSpent()) {
                // The grandparent does not have an entry, and the child is
                // modified and being pruned. This means we can just delete
                // it from the parent.
                cachedCoinsUsage -= memusage::DynamicUsage(itUs->second.coin);
                cacheCoins.erase(itUs);
            } else {
                // A normal modification.
                cachedCoinsUsage -= memusage::DynamicUsage(itUs->second.coin);
                itUs->second.coin = std::move(it->second.coin);
                cachedCoinsUsage += memusage::DynamicUsage(itUs->second.coin);
                itUs->second.flags |= CCoinsCacheEntry::DIRTY;
                // NOTE: It is possible the child has a FRESH flag here in
                // the event the entry we found in the parent is pruned. But
                // we must not copy that FRESH flag to the parent as that
                // pruned state likely still needs to be communicated to the
                // grandparent.
            }
        }
    }
    hashBlock = hashBlockIn;
    return true;
}

bool CCoinsViewCache::Flush()
{
    bool fOk = base->BatchWrite(cacheCoins,
            hashBlock);
    cacheCoins.clear();
    cachedCoinsUsage = 0;
    return fOk;
}

void CCoinsViewCache::Uncache(const COutPoint& outpoint)
{
    CCoinsMap::iterator it = cacheCoins.find(outpoint);
    if (it != cacheCoins.end() && it->second.flags == 0) {
        cachedCoinsUsage -= it->second.coin.DynamicMemoryUsage();
        cacheCoins.erase(it);
    }
}

unsigned int CCoinsViewCache::GetCacheSize() const
{
    return cacheCoins.size();
}

CAmount CCoinsViewCache::GetValueIn(const CTransaction& tx) const
{
    if (tx.IsCoinBase())
        return 0;

    CAmount nResult = 0;
    for (const CTxIn& in : tx.vin) {
        nResult += AccessCoin(in.prevout).out.nValue;
    }

    return nResult;
}

bool CCoinsViewCache::HaveInputs(const CTransaction& tx) const
{
    if (!tx.IsCoinBase() && !tx.HasZerocoinSpendInputs()) {
        for (unsigned int i = 0; i < tx.vin.size(); i++) {
            if (!HaveCoin(tx.vin[i].prevout)) {
                return false;
            }
        }
    }
    return true;
}

double CCoinsViewCache::GetPriority(const CTransaction& tx, int nHeight, CAmount &inChainInputValue) const
{
    inChainInputValue = 0;
    if (tx.IsCoinBase() || tx.IsCoinStake())
        return 0.0;
    double dResult = 0.0;
    for (const CTxIn& txin : tx.vin) {
        const Coin& coin = AccessCoin(txin.prevout);
        if (coin.IsSpent()) continue;
        if (coin.nHeight <= (unsigned)nHeight) {
            dResult += coin.out.nValue * (nHeight - coin.nHeight);
            inChainInputValue += coin.out.nValue;
        }
    }
    return tx.ComputePriority(dResult);
}

int CCoinsViewCache::GetCoinDepthAtHeight(const COutPoint& output, int nHeight) const
{
    const Coin& coin = AccessCoin(output);
    if (!coin.IsSpent())
        return nHeight - coin.nHeight + 1;
    return -1;
}

CAmount CCoinsViewCache::GetTotalAmount() const
{
    CAmount nTotal = 0;

    std::unique_ptr<CCoinsViewCursor> pcursor(Cursor());
    while (pcursor->Valid()) {
        Coin coin;
        if (pcursor->GetValue(coin) && !coin.IsSpent()) {
            nTotal += coin.out.nValue;
        }
        pcursor->Next();
    }

    return nTotal;
}

static const size_t MAX_OUTPUTS_PER_BLOCK = MAX_BLOCK_SIZE_CURRENT /  ::GetSerializeSize(CTxOut(), PROTOCOL_VERSION); // TODO: merge with similar definition in undo.h.

const Coin& AccessByTxid(const CCoinsViewCache& view, const uint256& txid)
{
    COutPoint iter(txid, 0);
    while (iter.n < MAX_OUTPUTS_PER_BLOCK) {
        const Coin& alternate = view.AccessCoin(iter);
        if (!alternate.IsSpent()) return alternate;
        ++iter.n;
    }
    return coinEmpty;
}
