//! \file PayPeriods.cpp
//!
//! \copyright Copyright (C) 2021 IO Industrial Holdings, LLC; All Rights Reserved.
//!
//! This program is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 3 of the License, or
//! (at your option) any later version.
//!
//! This program is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "accounting/payroll/PayPeriods.h"

namespace accounting {
namespace payroll {

int PayPeriod::getPayPeriodsInYear() const
{
    int periods_in_year = 0;
    switch (_pay_period)
    {
        case ePayPeriodWeekly:
            periods_in_year = 52;
            break;
        
        case ePayPeriodBiweekly:
            // \todo leap year.  extra check or 27 periods.
            periods_in_year = 26;
            break;

        case ePayPeriodSemimonthly:
            periods_in_year = 24;
            break;

        case ePayPeriodMonthly:
            periods_in_year = 12;
            break;

        case ePayPeriodQuarterly:
            periods_in_year = 4;
            break;

        case ePayPeriodSemiannually:
            periods_in_year = 2;
            break;

        default:
            periods_in_year = 365;
            break;
    }

    return periods_in_year;
}

double PayPeriod::calculateGrossSalaryWages(double const annual_wage)
{
    return (annual_wage / getPayPeriodsInYear());
}

}
}
