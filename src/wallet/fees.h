/***********************************************************************
**************Copyright (c) 2009-2010 Satoshi Nakamoto******************
*********Copyright (c) 2009-2017 The Bitcoin Core developers************
***************Copyright (c) 2021 The PIVX developers*******************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_WALLET_FEES_H
#define MUBDI_WALLET_FEES_H

#include "amount.h"

class CTxMemPool;

/**
 * Return the minimum required fee taking into account the
 * floating relay fee and user set minimum transaction fee
 */
CAmount GetRequiredFee(unsigned int nTxBytes);

/**
 * Estimate the minimum fee considering user set parameters
 * and the required fee
 */
CAmount GetMinimumFee(unsigned int nTxBytes, unsigned int nConfirmTarget, const CTxMemPool& pool);


#endif /* MUBDI_WALLET_FEES_H */
