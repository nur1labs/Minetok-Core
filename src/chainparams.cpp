/***********************************************************************
****************Copyright (c) 2010 Satoshi Nakamoto*********************
***********Copyright (c) 2009-2015 The Bitcoin developers***************
*************Copyright (c) 2014-2015 The Dash developers****************
*************Copyright (c) 2015-2020 The PIVX developers****************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#include "chainparams.h"

#include "chainparamsseeds.h"
#include "consensus/merkle.h"
#include "tinyformat.h"
#include "utilstrencodings.h"

#include <assert.h>

/* 

Lilith Network Is new Light speed system by v8 network mubdi 

Network With Blockstream (Gold)

*/

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.vtx.push_back(std::make_shared<const CTransaction>(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.nVersion = nVersion;
    genesis.nTime    = nTime;
    genesis.nBits    = nBits;
    genesis.nNonce   = nNonce;
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

void CChainParams::UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    assert(IsRegTestNet()); // only available for regtest
    assert(idx > Consensus::BASE_NETWORK && idx < Consensus::MAX_NETWORK_UPGRADES);
    consensus.vUpgrades[idx].nActivationHeight = nActivationHeight;
}

/**
 * Build the genesis block. Note that the output of the genesis coinbase cannot
 * be spent as it did not originally exist in the database.
 *
 * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
 *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
 *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
 *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
 *   vMerkleTree: e0028e
 */
static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "31/05/2010 - Dinar And Dirham will be number one. Become will be used global.";
    const CScript genesisOutputScript = CScript() << ParseHex("042346520305fed849c4646d8179c11951c7214d4f8c358364b65bb0fc721a561a67a81289475ec3a16152e45e0fe04d093f08c2636b0553481e76aee659fa455d") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

/**
 * Main network
 */
/**
 * What makes a good checkpoint block?
 * + Is surrounded by blocks with reasonable timestamps
 *   (no blocks before with a timestamp after, none after with
 *    timestamp before)
 * + Contains no strange transactions
 */
/* start of checkpoint 7 Network */
static MapCheckpoints mapCheckpoints = {
    { 0,   uint256S("f115ea61f4b1c6dd5071634ee64f0590bf31a902e8b01e2d0f7a26d5311ee756")},   //first checkpoint
    { 100,   uint256S("0000000ffd3adf0d93245a433237efab275d1cd7bbdb311652a4b784e020bd57")},   //checkpoint updates for change key from cxau to rci
    { 6000, uint256S("00000001636f9bc5fd1af09f4f43010b623d6567e1661bb0048c8d4477e9dcde")},   //updates of blockchain core & consensus fixed IP
};

static const CCheckpointData data = {
    &mapCheckpoints,
    0,          // * UNIX timestamp of last checkpoint block
    0,          // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the UpdateTip debug.log lines)
    0           // * estimated number of transactions per day after checkpoint
};

static MapCheckpoints mapCheckpointsTestnet = {{0, uint256S("0x001")}};

static const CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    0,
    0,
    0};

static MapCheckpoints mapCheckpointsRegtest = {{0, uint256S("0x001")}};
static const CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    0,
    0,
    0};

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        strNetworkID = "lilith";

        genesis = CreateGenesisBlock(1716867241, 150717, 0x1e0ffff0, 1, 100 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0xf115ea61f4b1c6dd5071634ee64f0590bf31a902e8b01e2d0f7a26d5311ee756"));
        assert(genesis.hashMerkleRoot == uint256S("0x97262e036c937048e5ce823299ac5486582fdf636b8b27a5197b9447651eb460"));

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.powLimit   = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV1 = uint256S("0x000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV2 = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nBudgetCycleBlocks = 43200;       // approx. 1 every 30 days
        consensus.nBudgetFeeConfirmations = 6;      // Number of confirmations for the finalization fee
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 2500000 * COIN;
        consensus.nMNCollateralAmt = 1000 * COIN;
        consensus.Premine = 100000;                 //premine at block 5
        consensus.AnchorSupply = 1000000;            //premine at block 1
        consensus.nProposalEstablishmentTime = 60 * 60 * 24;    // must be at least a day old to make it into a budget
        consensus.nStakeMinAge = 10 * 60;           // 10 minutes
        consensus.nStakeMinDepth = 300;             // depth set 300 prevent stake fast | 300 confirmation to active PoS
        consensus.nTargetTimespan = 1 * 30;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 30;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 6;

        // spork keys
        consensus.strSporkPubKey = "04e0e3443668a549effa9549d9a31428009364c17ec7ee743573e2846d2c520864a2055cfa79ec79ead55252a76d9e690ec7282443b49008e1694482b227572270";
        consensus.strSporkPubKeyOld = "04de56c0b1541fe85af32594aa51adc1bbfc36ec034626d6c70f7b108c6360db48a8ce3d3774f3378e12ec7e166c655aa136f5994dc046d9d5324a7e0658853c30";
        consensus.nTime_EnforceNewSporkKey = 1711943762;    //!> Sporks signed after  must use the new spork key
        consensus.nTime_RejectOldSporkKey = 1653955200;     //!> Fully reject old spork key after Tue, 31 May 2022 00:00:00 GMT

        // validation by-pass
        consensus.nMuBdIBadBlockTime = 1471401614;    // Skip nBit validation of Block 259201 per PR #915
        consensus.nMuBdIBadBlockBits = 0x1c056dac;    // Skip nBit validation of Block 259201 per PR #915

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_HYBRID].nActivationHeight        = 100;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 500000;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 1000000;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = 1500000;
        consensus.vUpgrades[Consensus::UPGRADE_V2].nActivationHeight            = 2000000;
        consensus.vUpgrades[Consensus::UPGRADE_V3].nActivationHeight            = 2500000;
        consensus.vUpgrades[Consensus::UPGRADE_V4].nActivationHeight            = 3000000;
        consensus.vUpgrades[Consensus::UPGRADE_V5].nActivationHeight            = 3500000;
        consensus.vUpgrades[Consensus::UPGRADE_V6].nActivationHeight            = 4000000;
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        consensus.vUpgrades[Consensus::UPGRADE_HYBRID].hashActivationBlock =
                uint256S("0x0000000ffd3adf0d93245a433237efab275d1cd7bbdb311652a4b784e020bd57");
 
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x7c;
        pchMessageStart[1] = 0x70;
        pchMessageStart[2] = 0x0a;
        pchMessageStart[3] = 0x01;
        nDefaultPort = 41031;

        // Note that of those with the service bits flag, most only support a subset of possible options
        vSeeds.emplace_back("45.76.8.103", true);            // seed-main
        vSeeds.emplace_back("seed07.urcoin.cc", false);      // seed-second
        vSeeds.emplace_back("149.28.45.189", false);         // seed-third
        vSeeds.emplace_back("149.28.235.170", false);        // seed-fourth
        vSeeds.emplace_back("92.205.236.136", false);        // seed-fifth

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 110);      // m
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 23);      // A
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 110);    // starting with 'm'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 38);         // G(Gold Network)
        base58Prefixes[EXT_PUBLIC_KEY] = {0x01, 0x49, 0x70, 0xca};
        base58Prefixes[EXT_SECRET_KEY] = {0x01, 0x06, 0x18, 0x5f};
        // BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = {0x01, 0x45, 0xb1, 0x82};

        vFixedSeeds = std::vector<uint8_t>(std::begin(chainparams_seed_main), std::end(chainparams_seed_main));

        // Reject non-standard transactions by default
        fRequireStandard = true;
    }

    const CCheckpointData& Checkpoints() const
    {
        return data;
    }

};

/**
 * Testnet (v5)
 */
class CTestNetParams : public CChainParams
{
public:
    CTestNetParams()
    {
        strNetworkID = "test";

        genesis = CreateGenesisBlock(1620401973, 686001, 0x1e0ffff0, 1, 10 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0xf115ea61f4b1c6dd5071634ee64f0590bf31a902e8b01e2d0f7a26d5311ee756"));
        //assert(genesis.hashMerkleRoot == uint256S("0xafa5537df767ffbd36168609fc42f44bd53152f8844fad002ed3921e18c41795"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = false;
        consensus.powLimit   = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV1 = uint256S("0x000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV2 = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on testnet)
        consensus.nCoinbaseMaturity = 15;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 21000000 * COIN;
        consensus.nMNCollateralAmt = 10000 * COIN;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 60 * 60;
        consensus.nStakeMinDepth = 100;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 20;

        // spork keys
        consensus.strSporkPubKey = "04677c34726c491117265f4b1c83cef085684f36c8df5a97a3a42fc499316d0c4e63959c9eca0dba239d9aaaf72011afffeb3ef9f51b9017811dec686e412eb504";
        consensus.strSporkPubKeyOld = "04E88BB455E2A04E65FCC41D88CD367E9CCE1F5A409BE94D8C2B4B35D223DED9C8E2F4E061349BA3A38839282508066B6DC4DB72DD432AC4067991E6BF20176127";
        consensus.nTime_EnforceNewSporkKey = 1608512400;    //!> December 21, 2020 01:00:00 AM GMT
        consensus.nTime_RejectOldSporkKey = 1614560400;     //!> March 1, 2021 01:00:00 AM GMT


        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_HYBRID].nActivationHeight        = 100;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 200;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 500000;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = 1500000;
        consensus.vUpgrades[Consensus::UPGRADE_V2].nActivationHeight            = 2000000;
        consensus.vUpgrades[Consensus::UPGRADE_V3].nActivationHeight            = 4000000;
        consensus.vUpgrades[Consensus::UPGRADE_V4].nActivationHeight            = 2500000;
        consensus.vUpgrades[Consensus::UPGRADE_V5].nActivationHeight            = 3000000;
        consensus.vUpgrades[Consensus::UPGRADE_V6].nActivationHeight            = 3500000;
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0xc4;
        pchMessageStart[1] = 0x5e;
        pchMessageStart[2] = 0xb3;
        pchMessageStart[3] = 0x01;
        nDefaultPort = 46100;

        // nodes with support for servicebits filtering should be at the top
        vSeeds.emplace_back("66.175.236.170", true);       // seed-main
        vSeeds.emplace_back("107.155.116.230", true);      // seed-second

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 90);  // Testnet MuBdI addresses start with 'd'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 41);  // Testnet MuBdI script addresses start with 'H'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73); // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 110);     // Testnet private keys start with 'm' (MuBdI defaults)
        // Testnet mubdi BIP32 pubkeys start with 'DINV'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x00, 0xbb, 0x20, 0xdd};
        // Testnet mubdi BIP32 prvkeys start with 'DHMP'
        base58Prefixes[EXT_SECRET_KEY] = {0x00, 0x65, 0xbc, 0x9d};
        // Testnet mubdi BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = {0x00, 0xcf, 0xcc, 0xa4};

        vFixedSeeds = std::vector<uint8_t>(std::begin(chainparams_seed_test), std::end(chainparams_seed_test));

        fRequireStandard = false;
    }

    const CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};

/**
 * Regression test
 */
class CRegTestParams : public CChainParams
{
public:
    CRegTestParams()
    {
        strNetworkID = "regtest";

        genesis = CreateGenesisBlock(1620401973, 686001, 0x1e0ffff0, 1, 10 * COIN);
        consensus.hashGenesisBlock = genesis.GetHash();
        //assert(consensus.hashGenesisBlock == uint256S("0xf115ea61f4b1c6dd5071634ee64f0590bf31a902e8b01e2d0f7a26d5311ee756"));
        //assert(genesis.hashMerkleRoot == uint256S("0xafa5537df767ffbd36168609fc42f44bd53152f8844fad002ed3921e18c41795"));

        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.powLimit   = uint256S("0x7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV1 = uint256S("0x000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.posLimitV2 = uint256S("0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nBudgetCycleBlocks = 144;         // approx 10 cycles per day
        consensus.nBudgetFeeConfirmations = 3;      // (only 8-blocks window for finalization on regtest)
        consensus.nCoinbaseMaturity = 100;
        consensus.nFutureTimeDriftPoW = 7200;
        consensus.nFutureTimeDriftPoS = 180;
        consensus.nMaxMoneyOut = 43199500 * COIN;
        consensus.nMNCollateralAmt = 100 * COIN;
        consensus.nProposalEstablishmentTime = 60 * 5;  // at least 5 min old to make it into a budget
        consensus.nStakeMinAge = 0;
        consensus.nStakeMinDepth = 20;
        consensus.nTargetTimespan = 40 * 60;
        consensus.nTargetTimespanV2 = 30 * 60;
        consensus.nTargetSpacing = 1 * 60;
        consensus.nTimeSlotLength = 15;
        consensus.nMaxProposalPayments = 20;

        /* Spork Key for RegTest:
        WIF private key: 932HEevBSujW2ud7RfB1YF91AFygbBRQj3de3LyaCRqNzKKgWXi
        private key hex: bd4960dcbd9e7f2223f24e7164ecb6f1fe96fc3a416f5d3a830ba5720c84b8ca
        Address: yCvUVd72w7xpimf981m114FSFbmAmne7j9
        */
        consensus.strSporkPubKey = "04de56c0b1541fe85af32594aa51adc1bbfc36ec034626d6c70f7b108c6360db48a8ce3d3774f3378e12ec7e166c655aa136f5994dc046d9d5324a7e0658853c30";
        consensus.strSporkPubKeyOld = "";
        consensus.nTime_EnforceNewSporkKey = 0;
        consensus.nTime_RejectOldSporkKey = 0;

        // Network upgrades
        consensus.vUpgrades[Consensus::BASE_NETWORK].nActivationHeight =
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_TESTDUMMY].nActivationHeight =
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;
        consensus.vUpgrades[Consensus::UPGRADE_HYBRID].nActivationHeight        = 100;
        consensus.vUpgrades[Consensus::UPGRADE_POS].nActivationHeight           = 200;
        consensus.vUpgrades[Consensus::UPGRADE_POS_V2].nActivationHeight        = 500000;
        consensus.vUpgrades[Consensus::UPGRADE_BIP65].nActivationHeight         = 1500000;
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_V2].nActivationHeight            = 2000000;
        consensus.vUpgrades[Consensus::UPGRADE_V3].nActivationHeight            = 2500000;
        consensus.vUpgrades[Consensus::UPGRADE_V4].nActivationHeight            = 3000000;
                Consensus::NetworkUpgrade::ALWAYS_ACTIVE;
        consensus.vUpgrades[Consensus::UPGRADE_V5].nActivationHeight            = 3500000;
        consensus.vUpgrades[Consensus::UPGRADE_V6].nActivationHeight            = 4000000;
                Consensus::NetworkUpgrade::NO_ACTIVATION_HEIGHT;

        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x4b;
        pchMessageStart[1] = 0x9b;
        pchMessageStart[2] = 0x13;
        pchMessageStart[3] = 0x01;
        nDefaultPort = 47000;

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 139); // Testnet pivx addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 19);  // Testnet pivx script addresses start with '8' or '9'
        base58Prefixes[STAKING_ADDRESS] = std::vector<unsigned char>(1, 73);     // starting with 'W'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet pivx BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = {0x3a, 0x80, 0x61, 0xa0};
        // Testnet pivx BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = {0x3a, 0x80, 0x58, 0x37};
        // Testnet pivx BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = {0x80, 0x00, 0x00, 0x01};

        // Reject non-standard transactions by default
        fRequireStandard = true;
    }

    const CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams &Params()
{
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateNetworkUpgradeParameters(Consensus::UpgradeIndex idx, int nActivationHeight)
{
    globalChainParams->UpdateNetworkUpgradeParameters(idx, nActivationHeight);
}
