/***********************************************************************
**********Copyright (c) 2017 The Bitcoin Core developers****************
******************Copyright (c) 2010-2022 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_WALLET_UTIL_H
#define MUBDI_WALLET_UTIL_H

#include "fs.h"
#include "operationresult.h"

//! Get the path of the wallet directory.
fs::path GetWalletDir();
//! Verify the wallet db's path
OperationResult VerifyWalletPath(const std::string& walletFile);

#endif /* MUBDI_WALLET_UTIL_H */
