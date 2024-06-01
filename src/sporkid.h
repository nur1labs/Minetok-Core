/***********************************************************************
*************Copyright (c) 2014-2016 The Dash developers**************
*************Copyright (c) 2016-2020 The PIVX developers****************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT/X11 software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef SPORKID_H
#define SPORKID_H

/*
    Don't ever reuse these IDs for other sporks
    - This would result in old clients getting confused about which spork is for what
*/

enum SporkId : int32_t {
    SPORK_0_SWIFTTX                             = 10001,        // Deprecated in v6.5
    SPORK_1_SWIFTTX_BLOCK_FILTERING             = 10002,	// Deprecated in v6.5
    SPORK_2_MAX_VALUE                           = 10003,
    SPORK_3_MASTERNODE_PAYMENT_ENFORCEMENT      = 10004,
    SPORK_4_MASTERNODE_BUDGET_ENFORCEMENT       = 10005,
    SPORK_5_ENABLE_SUPERBLOCKS                  = 10006,
    SPORK_6_NEW_PROTOCOL_ENFORCEMENT            = 10007,
    SPORK_7_NEW_PROTOCOL_ENFORCEMENT_2          = 10008,
    SPORK_8_COLDSTAKING_ENFORCEMENT             = 10009,	// Deprecated in v6.5
    SPORK_9_COLDSTAKING_MAINTENANCE             = 10010,
    SPORK_10_BLOCKSTREAM_ENCHANCEMENT           = 10011,
    SPORK_11_GENESIS_ENCHANCEMENT               = 10012,
    SPORK_12_LEGACY_MNS_MAX_HEIGHT              = 10013,

    SPORK_INVALID                               = -1
};

// Default values
struct CSporkDef
{
    CSporkDef(): sporkId(SPORK_INVALID), defaultValue(0) {}
    CSporkDef(SporkId id, int64_t val, std::string n): sporkId(id), defaultValue(val), name(n) {}
    SporkId sporkId;
    int64_t defaultValue;
    std::string name;
};

#endif
