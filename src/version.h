/***********************************************************************
***********Copyright (c) 2012-2014 The Bitcoin developers***************
*************Copyright (c) 2014-2015 The Dash developers****************
*************Copyright (c) 2015-2020 The PIVX developers****************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_VERSION_H
#define MUBDI_VERSION_H

/**
 * network protocol versioning
 */

static const int PROTOCOL_VERSION = 71110;

//! initial proto version, to be increased after version/verack negotiation
static const int INIT_PROTO_VERSION = 211;

//! disconnect from peers older than this proto version
static const int MIN_PEER_PROTO_VERSION_BEFORE_ENFORCEMENT = 71108;
static const int MIN_PEER_PROTO_VERSION_AFTER_ENFORCEMENT = 71110;

//! Version where BIP155 was introduced
static const int MIN_BIP155_PROTOCOL_VERSION = 71110;

// Make sure that none of the values above collide with
// `ADDRV2_FORMAT`.

#endif /* MUBDI_VERSION_H */
