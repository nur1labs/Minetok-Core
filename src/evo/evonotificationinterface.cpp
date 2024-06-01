/***********************************************************************
**********Copyright (c) 2014-2019 The Dash Core developers**************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#include "evo/evonotificationinterface.h"

#include "validation.h"

void EvoNotificationInterface::InitializeCurrentBlockTip()
{
    LOCK(cs_main);
    UpdatedBlockTip(chainActive.Tip(), nullptr, IsInitialBlockDownload());
}

void EvoNotificationInterface::UpdatedBlockTip(const CBlockIndex *pindexNew, const CBlockIndex *pindexFork, bool fInitialDownload)
{
    const CBlockIndex* pindex;
    const CBlockIndex* tipIndex;
    tipIndex = pindex;
}
