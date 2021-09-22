//! \brief Federal Unemployment (FUTA) Tax
//! \file FUTA.hpp
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
#ifndef _FUTA_H_
#define _FUTA_H_

namespace accounting {
namespace payroll {

    /** @defgroup FUTA Federal Unemployment Tax
    * \brief Employer's FUTA tax liability
    * 
    * The Federal Unemployment Tax Act (FUTA) is a payroll tax paid by employers on employee wages. 
    * The tax is 6.0% on the first $7,000 an employee earns; any earnings beyond $7,000 are not taxed. 
    * In practice, the actual percentage paid is usually 0.6%. FUTA requires that employers contribute 
    * to the federal unemployment pool which covers employees who qualify for unemployment benefits. 
    * If you have at least one employee who works at least 20 weeks out of the year or have paid 
    * employees at least $1,500 in any quarter, you are responsible for paying FUTA taxes.
    * 
    * The magic number is $7,000. If you are required to pay FUTA based on the criteria above, the 
    * amount you are responsible for paying equals 6% of the first $7,000 your employee makes each calendar 
    * year. After you pay on that, anything earned after $7,000 does not need to account for FUTA.
    * 
    * FUTA Tax Credit. Raise your hand if you like tax credits. The good news is, if you pay SUTA (State 
    * Unemployment Tax Act) on time, you are eligible for a FUTA tax credit. This credit can be up to 5.4%, 
    * meaning your FUTA liability is 0.6%.
    * 
    * Payments are due quarterly. In the tax world, it’s common to have quarterly tax deadlines. The same 
    * applies for FUTA with deadlines of: April 30th, July 31st, October 31st and January 31st. Make 
    * sure you pay on time or else you could face a penalty between 2% and 15%.
    * 
    * Employees do not pay FUTA. There are some payroll taxes that employees contribute to, like Social 
    * Security and Medicare taxes but FUTA is one that the sole responsibility falls on the employer.
    *  @{
    */

    //! \brief Federal Unemployment Tax
    //!
    //! \note This applies to all employees.
    struct FUTA_RATE {

        //! \brief FUTA tax rate for 2020
        //!
        //! "For 2020, the FUTA tax rate is 6.0%. The tax applies to the first $7,000 you pay to each
        //! employee as wages during the year."
        double tax_rate;
        double wage_cap;

        // \brief 2020 Tax rates
        void fy2020()
        {
            //! "For 2020, the FUTA tax rate is 6.0%. The tax applies to the first $7,000 you pay to each
            //! employee as wages during the year."
            tax_rate = 0.06;
            wage_cap = 7000.00;
        }

        //! \brief Default Constructor
        FUTA_RATE()
        {
            fy2020();
        }
    };

    //! \brief FUTA tax rate for 2020
    //!
    //! "For 2020, the FUTA tax rate is 6.0%. The tax applies to the first $7,000 you pay to each
    //! employee as wages during the year."
    const double FUTA_TAX_RATE_2020 = 0.06;
    const double FUTA_TAX_CEILING_2020 = 7000.00;

    //! \brief Calculate FUTA tax for an employee
    double calc_FUTA(double federal_wage_base);

    /** @} */ // end of group1
}
}
#endif