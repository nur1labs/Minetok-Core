/***********************************************************************
**************Copyright (c) 2021 The PIVX developers********************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or https://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_BLOCKSUTIL_H
#define MUBDI_BLOCKSUTIL_H

#include "primitives/block.h"
#include <memory>

// Process block and boost_check for the specific rejection reason.
void ProcessBlockAndCheckRejectionReason(std::shared_ptr<CBlock>& pblock,
                                         const std::string& blockRejectionReason,
                                         int expectedChainHeight);

#endif /* MUBDI_BLOCKSUTIL_H */
