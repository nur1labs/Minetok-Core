/***********************************************************************
*********Copyright (c) 2016-2021 The Bitcoin Core developers************
************Copyright (c) 2020-2021 The PIVX developers*****************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_WALLET_TEST_FIXTURE_H
#define MUBDI_WALLET_TEST_FIXTURE_H

#include "test/test_mubdi.h"
#include "wallet/wallet.h"


/** Testing setup and teardown for wallet.
 */
struct WalletTestingSetup : public TestingSetup
{
    WalletTestingSetup(const std::string& chainName = CBaseChainParams::MAIN);
    ~WalletTestingSetup();

    CWallet m_wallet;
};

struct WalletRegTestingSetup : public WalletTestingSetup
{
    WalletRegTestingSetup() : WalletTestingSetup(CBaseChainParams::REGTEST) {}
};

#endif /* MUBDI_WALLET_TEST_FIXTURE_H */

