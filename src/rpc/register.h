/***********************************************************************
*******Copyright (c) 2009-2016 The Bitcoin Core developers**************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_RPCREGISTER_H
#define MUBDI_RPCREGISTER_H

/** These are in one header file to avoid creating tons of single-function
 * headers for everything under src/rpc/ */
class CRPCTable;

/** Register block chain RPC commands */
void RegisterBlockchainRPCCommands(CRPCTable& tableRPC);
/** Register P2P networking RPC commands */
void RegisterNetRPCCommands(CRPCTable& tableRPC);
/** Register miscellaneous RPC commands */
void RegisterMiscRPCCommands(CRPCTable& tableRPC);
/** Register mining RPC commands */
void RegisterMiningRPCCommands(CRPCTable& tableRPC);
/** Register raw transaction RPC commands */
void RegisterRawTransactionRPCCommands(CRPCTable& tableRPC);
/** Register masternode RPC commands */
void RegisterMasternodeRPCCommands(CRPCTable& tableRPC);
/** Register budget RPC commands */
void RegisterBudgetRPCCommands(CRPCTable& tableRPC);

static inline void RegisterAllCoreRPCCommands(CRPCTable& tableRPC)
{
    RegisterBlockchainRPCCommands(tableRPC);
    RegisterNetRPCCommands(tableRPC);
    RegisterMiscRPCCommands(tableRPC);
    RegisterMiningRPCCommands(tableRPC);
    RegisterRawTransactionRPCCommands(tableRPC);
    RegisterMasternodeRPCCommands(tableRPC);
    RegisterBudgetRPCCommands(tableRPC);
}

#endif
