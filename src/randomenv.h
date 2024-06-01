/***********************************************************************
**************Copyright (c) 2009-2010 Satoshi Nakamoto******************
*********Copyright (c) 2009-2019 The Bitcoin Core developers************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_RANDOMENV_H
#define MUBDI_RANDOMENV_H

#include "crypto/sha512.h"

/** Gather non-cryptographic environment data that changes over time. */
void RandAddDynamicEnv(CSHA512& hasher);

/** Gather non-cryptographic environment data that does not change over time. */
void RandAddStaticEnv(CSHA512& hasher);

#endif
