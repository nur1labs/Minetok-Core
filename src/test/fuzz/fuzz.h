/***********************************************************************
********Copyright (c) 2009-2019 The Bitcoin Core developers*************
******************Copyright (c) 2010-2023 Nur1Labs**********************
>Distributed under the MIT software license, see the accompanying
>file COPYING or http://www.opensource.org/licenses/mit-license.php.
************************************************************************/

#ifndef MUBDI_TEST_FUZZ_FUZZ_H
#define MUBDI_TEST_FUZZ_FUZZ_H

#include <functional>
#include <stdint.h>
#include <vector>


const std::function<std::string(const char*)> G_TRANSLATION_FUN = nullptr;

void test_one_input(std::vector<uint8_t> buffer);

#endif /* MUBDI_TEST_FUZZ_FUZZ_H */
