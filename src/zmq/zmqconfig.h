/***********************************************************************
**********Copyright (c) 2015 The Bitcoin Core developers****************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_ZMQ_ZMQCONFIG_H
#define MUBDI_ZMQ_ZMQCONFIG_H

#if defined(HAVE_CONFIG_H)
#include "config/mubdi-config.h"
#endif

#include <stdarg.h>
#include <string>

#if ENABLE_ZMQ
#include <zmq.h>
#endif

#include "primitives/block.h"
#include "primitives/transaction.h"

void zmqError(const char *str);

#endif /* MUBDI_ZMQ_ZMQCONFIG_H */
