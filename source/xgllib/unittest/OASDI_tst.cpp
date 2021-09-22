/**
 * \file OASDI_tst.cpp
 *
 * This file is part of the Payroll C++ Library
 *
 * Copyright (c) 2020 Joe Turner.  All rights reserved.
 * Unauthorized copying prohibited.
 */
#include "accounting/payroll/OASDI.h"
#include <gtest/gtest.h>

using namespace accounting::payroll;

//! maximum contribution for 2020 is 6.2% of 137,700
TEST(OASDI_tests, test_max_contribution)
{
    OASDI_TAX_RATE ss;

    ASSERT_EQ(8537.40, ss.max_contribution());
}

//! test case: huge payday, with no previous contributions
//! result should be max contribution
TEST(OASDI_tests, calculate_overmax)
{
    OASDI_TAX_RATE ss;
    double result = ss.calculate(0, 150000);
    ASSERT_EQ(8537.40, result);
}

// Test case: Already hit the contribution cap, the result should be zero.
TEST(OASDI_tests, calculate_already_hit_cap)
{
    OASDI_TAX_RATE ss;
    double result = ss.calculate(8537.40, 150000);
    ASSERT_EQ(0, result);
}

// Test case: Under the contribution cap by 100.00
TEST(OASDI_tests, calculate_close_to_cap)
{
    OASDI_TAX_RATE ss;
    double result = ss.calculate(8437.40, 150000);
    ASSERT_EQ(100, result);
}