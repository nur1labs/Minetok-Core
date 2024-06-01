/***********************************************************************
**************Copyright (c) 2020 The PIVX developers********************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or https://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#include "destination_io.h"
#include "key_io.h"

namespace Standard {

    std::string EncodeDestination(const CWDestination &address, const CChainParams::Base58Type addrType) {
        const CTxDestination *dest = boost::get<CTxDestination>(&address);

        return EncodeDestination(*dest, addrType);
    };

    CWDestination DecodeDestination(const std::string& strAddress)
    {
        bool isStaking = false;
        return DecodeDestination(strAddress, isStaking);
    }

    CWDestination DecodeDestination(const std::string& strAddress, bool& isStaking)
    {
        CWDestination dest;
        CTxDestination regDest = ::DecodeDestination(strAddress, isStaking);
        
        return regDest;

    }

    bool IsValidDestination(const CWDestination& address)
    {
        // Only regular base58 addresses accepted here for now
        const CTxDestination *dest = boost::get<CTxDestination>(&address);
        return dest && ::IsValidDestination(*dest);
    }

    const CTxDestination* GetTransparentDestination(const CWDestination& dest)
    {
        return boost::get<CTxDestination>(&dest);
    }

} // End Standard namespace

Destination& Destination::operator=(const Destination& from)
{
    this->dest = from.dest;
    this->isP2CS = from.isP2CS;
    return *this;
}

// Returns the key ID if Destination is a transparent "regular" destination
const CKeyID* Destination::getKeyID()
{
    const CTxDestination* regDest = Standard::GetTransparentDestination(dest);
    return (regDest) ? boost::get<CKeyID>(regDest) : nullptr;
}

std::string Destination::ToString() const
{
    if (!Standard::IsValidDestination(dest)) {
        // Invalid address
        return "";
    }
    return Standard::EncodeDestination(dest, isP2CS ? CChainParams::STAKING_ADDRESS : CChainParams::PUBKEY_ADDRESS);
}

