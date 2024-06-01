/***********************************************************************
**************Copyright (c) 2009-2010 Satoshi Nakamoto******************
***********Copyright (c) 2009-2014 The Bitcoin developers***************
*************Copyright (c) 2016-2020 The PIVX developers****************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT/X11 software license, see the accompanying
>file COPYING or https://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_MINER_H
#define MUBDI_MINER_H

#include "primitives/block.h"

#include <stdint.h>

class CBlock;
class CBlockHeader;
class CBlockIndex;
class CStakeableOutput;
class CReserveKey;
class CScript;
class CWallet;

struct CBlockTemplate;

static const bool DEFAULT_PRINTPRIORITY = false;

/** Generate a new block, without valid proof-of-work */
CBlockTemplate* CreateNewBlock(const CScript& scriptPubKeyIn, CWallet* pwallet, bool fProofOfStake, std::vector<CStakeableOutput>* availableCoins = nullptr);
/** Modify the extranonce in a block */
void IncrementExtraNonce(std::shared_ptr<CBlock>& pblock, CBlockIndex* pindexPrev, unsigned int& nExtraNonce);
/** Check mined block */
void UpdateTime(CBlockHeader* block, const CBlockIndex* pindexPrev);

#ifdef ENABLE_WALLET
    /** Run the miner threads */
    void GenerateMuBdIs(bool fGenerate, CWallet* pwallet, int nThreads);
    /** Generate a new PoW block, without valid proof-of-work */
    CBlockTemplate* CreateNewBlockWithKey(std::unique_ptr<CReserveKey>& reservekey, CWallet* pwallet);
    CBlockTemplate* CreateNewBlockWithScript(const CScript& coinbaseScript, CWallet* pwallet);

    void MuBdIMiner(CWallet* pwallet, bool fProofOfStake);
    void ThreadStakeMinter();
#endif // ENABLE_WALLET

extern double dHashesPerSec;
extern int64_t nHPSTimerStart;

#endif /* MUBDI_MINER_H */
