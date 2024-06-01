/***********************************************************************
*************Copyright (c) 2014-2016 The Dash developers****************
*************Copyright (c) 2015-2020 The PIVX developers****************
******************Copyright (c) 2010-2022 Nur1Labs**********************
>Distributed under the MIT/X11 software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef ACTIVEMASTERNODE_H
#define ACTIVEMASTERNODE_H

#include "key.h"
#include "net.h"
#include "operationresult.h"
#include "sync.h"
#include "validationinterface.h"
#include "validation.h"

class CBLSPublicKey;
class CBLSSecretKey;

#define ACTIVE_MASTERNODE_INITIAL 0 // initial state
#define ACTIVE_MASTERNODE_SYNC_IN_PROCESS 1
#define ACTIVE_MASTERNODE_NOT_CAPABLE 3
#define ACTIVE_MASTERNODE_STARTED 4

struct CActiveMasternodeInfo
{
    // Keys for the active Masternode
    CBLSPublicKey pubKeyOperator;
    CBLSSecretKey keyOperator;
    // Initialized while registering Masternode
    uint256 proTxHash{UINT256_ZERO};
    CService service;
};

// Responsible for initializing the masternode
OperationResult initMasternode(const std::string& strMasterNodePrivKey, const std::string& strMasterNodeAddr, bool isFromInit);


// Responsible for activating the Masternode and pinging the network (legacy MN list)
class CActiveMasternode
{
private:
    int status{ACTIVE_MASTERNODE_INITIAL};
    std::string notCapableReason;

public:
    CActiveMasternode() = default;

    // Initialized by init.cpp
    // Keys for the main Masternode
    CPubKey pubKeyMasternode;
    CKey privKeyMasternode;

    // Initialized while registering Masternode
    Optional<CTxIn> vin{nullopt};
    CService service;

    /// Manage status of main Masternode
    void ManageStatus();
    void ResetStatus();
    std::string GetStatusMessage() const;
    int GetStatus() const { return status; }

    /// Ping Masternode
    bool SendMasternodePing(std::string& errorMessage);
    /// Enable cold wallet mode (run a Masternode with no funds)
    bool EnableHotColdMasterNode(CTxIn& vin, CService& addr);

    void GetKeys(CKey& privKeyMasternode, CPubKey& pubKeyMasternode);
};

// Compatibility code: get vin and keys for either legacy or deterministic masternode
bool GetActiveMasternodeKeys(CTxIn& vin, Optional<CKey>& key, CBLSSecretKey& blsKey);

#endif
