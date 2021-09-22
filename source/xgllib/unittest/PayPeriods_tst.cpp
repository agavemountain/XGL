#include "accounting/payroll/PayPeriods.h"
#include <gtest/gtest.h>

using namespace accounting::payroll;

TEST(PayPeriod_tests, test_getter_setter)
{
    PayPeriod p;

    p.setPayPeriod(PayPeriod::ePayPeriodMonthly);
    ASSERT_EQ(PayPeriod::ePayPeriodMonthly, p.getPayPeriod());

}
