//! \file OSADI.h
//! \brief The "Old-Age, Survivors and Disability Insurance program (OASDI) tax"
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
#ifndef _OSADI_H_
#define _OSADI_H_

/** @defgroup OSADI The Old-Age, Survivors and Disability Insurance program (OASDI) tax
 * \brief The Social Security Taxes
 * 
 * The OASDI tax -- more commonly called the Social Security Tax began in 1937. At that 
 * time, the employee rate was 1%. It has steadily risen over the years, reaching 3% in 
 * 1960 and 5% in 1978. In 1990, the employee portion increased from 6.06 to 6.2% 
 * but has held steady ever since—with the exception of 2011 and 2012.
 *
 * The Social Security Tax aggregates:
 * 
 * - The employee's calculated tax which is witheld from a paycheck; and
 * - The employer's calculated tax with is paid; and 
 * - a tax cap defining the maximum annual employee contribution.
 * 
 * The tax cap has existed since the inception of the program in 1937 and 
 * remained at $3,000 until the Social Security Amendments Act of 1950.1. It was 
 * then raised to $3,600 with expanded benefits and coverage. Additional increases 
 * in the tax cap in 1955, 1959, and 1965 were designed to address the difference 
 * in benefits between low-wage and high-wage earners.
 * 
 *  @{
 */
namespace accounting {
namespace payroll {

    //! \brief Social Security Tax Rate for a given year
    //!
    //! This structure contains:
    //! - The employee's calculated tax rate which is witheld from a paycheck; and
    //! - The employer's calculated tax with is paid; and
    //! - a tax cap defining the maximum annual employee contribution.
    //!
    struct OASDI_TAX_RATE {

        //! \brief Employee's Social Security tax rate
        double employee_tax_rate;

        //! \brief Business's Social Security tax rate
        double business_tax_rate;

        //! \brief Social Security Maximum Annual Contribution
        //!
        //! This is a limit to the taxable wages.  Note if there
        //! is an overpayment, the employee will get a tax refund,
        //! but the business will not.
        double wage_limit;

        //! \brief Maximum employee contribution
        double maximum_contribution;

        //! \brief Financial Year 2020 Tax Rates for Social Security
        //!
        //! Per IRS Pub 15:
        //!     "For 2020, the social security tax rate is 6.2% (amount
        //!     withheld) each for the employer and employee (12.4% total). The
        //!     social security wage base limit is $137,700."
        //!
        void fy2020()
        {
            employee_tax_rate = 0.062;
            business_tax_rate = 0.062;
            wage_limit = 137700;
        }

        //! \brief Financial Year 2019 Tax Rates for Social Security
        void fy2019()
        {
            employee_tax_rate = 0.062;
            business_tax_rate = 0.062;
            wage_limit = 132900;
        }

        //! \brief Financial Year 2018 Tax Rates for Social Security
        void fy2018()
        {
            employee_tax_rate = 0.062;
            business_tax_rate = 0.062;
            wage_limit = 128400;
        }

        //! \brief Financial Year 2017 Tax Rates for Social Security
        void fy2017()
        {
            employee_tax_rate = 0.062;
            business_tax_rate = 0.062;
            wage_limit = 127200;
        }

        //! \brief Returns the maximum annual contribution
        //!
        //! \returns
        //! This returns the maximum annual contribution.
        double max_contribution()
        {
            static double max = 0;
            if (!max)
            {
                max = wage_limit * employee_tax_rate;
            }
            return max;
        }
        
        //! \brief Calculate social security contribution for this paycheck
        //!
        //! This function will calculate the social security tax due for
        //! this employee, checking to see if we have reached the contribution
        //! limit, so we don't calculate an over payment.
        //!
        //! \param a_accumulated_contributions  
        //! This is the amount of money that has been collected year to date, 
        //! (previous to this payroll run).  This is used to make sure we don't
        //! overpay social security tax.
        //!
        //! \param a_wages
        //! This is the amount of base wages, used to calculate the tax.
        //
        double calculate(double a_accumulated_contributions, double a_wages)
        {
            double max = max_contribution();
            double contribution = 0;

            // no sense in calculating if we have already hit the cap.
            if (a_accumulated_contributions < max) {
                contribution = a_wages * employee_tax_rate;

                // edge case: check to see if this pushes over the cap and reduce
                // the contribution. 
                if ((a_accumulated_contributions + contribution) > max)
                {
                    contribution = max - a_accumulated_contributions;
                }
            }

            return contribution;
        }

        //! \brief Default constructor
        //!
        //! By default, the current year's tax rate is used.
        OASDI_TAX_RATE()
        {
            fy2020();
        }
    };

}
}

/** @} */ // end of group1

#endif