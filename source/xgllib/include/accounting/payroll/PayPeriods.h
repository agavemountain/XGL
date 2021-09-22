//! \file PayPeriods.h
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
#ifndef _PAY_PERIODS_H_
#define _PAY_PERIODS_H_

namespace accounting {
namespace payroll {

    //! \brief PayPeriod
    //!
    //! A pay period is a period of time that we caculate taxes and withholding.
    class PayPeriod {
    public:
        //! \brief Pay Period enumeration
        //!
        //! A pay period is a recurring length of time over which employee time
        //! is recorded and paid. Examples of pay periods are weekly, bi-weekly,
        //! semi-monthly, and monthly.
        //!
        //! \note Some years have an extra pay period for some employees. This is called
        //! a "pay period leap year." This phenomenon only affects salaried
        //! employees who are paid on a bi-weekly basis. Depending on when the
        //! last pay period falls in the year, it's possible to have a 27th pay
        //! period in the year. If you can catch the issue early enough, you can
        //! divide the employee's annual salary by 27, instead of 26. If you can't
        //! catch it in time, you'll have to make some adjustments.
        //!
        //! \note Federal and state laws also come into play when determining pay periods.
        //! Although the IRS does not regulate the frequency of pay periods, some states
        //! do.
        //!
        //! Prorating Salary (Exempt employees)
        //! 
        //! - If an employee starts work in the middle of a pay period, after working a week in the hole or more, 
        //!   count the actual number of days worked to calculate prorated salary. Take the amount from dividing 
        //!   the yearly salary by the number of pay periods, and divide it by the number of working days in the 
        //!   pay period. The result is the daily rate. Multiply the daily rate by the number of days worked to finish 
        //!   calculating the first paycheck. For example, a new employee with an annual salary of $50,000, paid 
        //!   bi-weekly in a non-leap year, works four days. $50,000 is divided by 26 and the result is divided 
        //!   by 10 (the number of working days in the pay period) to get the daily rate of $192.31. The daily rate 
        //!   is multiplied by 4 and the gross pay is $769.24.
        //!
        //! - You may prorate a terminated exempt employee's pay if she does not work the entire pay period.
        //! 
        enum ePAY_PERIOD {

            //! \brief Undefined Pay Period
            //!
            //! The pay period hasn't been defined.  This should be an error state.
            ePayPeriodUndefined,

            //! \brief Daily Pay Period
            //!
            //! Employee is paid on a daily basis.
            //!
            //! No regular payroll period. When you don't have a regular payroll period,
            //! withhold the tax as if you paid wages for a daily or miscellaneous payroll period.
            //! Figure the number of days (including Sundays and holidays) in the period covered
            //! by the wage payment. If the wages are unrelated to a specific length of time
            //! (for example, commissions paid on completion of a sale), count back the number
            //! of days from the payment period to the latest of:
            //! - The last wage payment made during the same calendar year;
            //! - The date employment began, if during the same calendar year; or
            //! - January 1 of the same year.
            ePayPeriodDaily,

            //! \brief Weekly Pay Period
            //!
            //! A weekly pay period results in 52 paychecks in a year. Hourly employees
            //! are often paid weekly. Sometimes these employees are paid a week in arrears.
            //! That is, they record and turn in their time sheets at the end of one week and
            //! are paid for that time a week later. This gives the payroll clerk time to
            //! calculate pay for these employees.
            //!
            //! Employees receive 52 paychecks per year – one for every week of the year.
            //! Payroll is usually scheduled to run on the same day every week, most often on
            //! Thursday or Friday.
            ePayPeriodWeekly,

            //! \brief Bi-Weekly Pay Period
            //!
            //! A bi-weekly (every other week) pay period results in 26 paychecks in a year.
            //! Some hourly employees are paid bi-weekly, and some salaried employees are too.
            //!
            //! Employees receive 26 paychecks per year. Because bi-weekly pay periods occur
            //! once every two weeks, some months will have three pay periods. To further
            //! complicate matters, every decade or so the extra day from leap years wreaks bi-weekly
            //! pay havoc by necessitating a 27th paycheck.
            //!
            //! \note In some years, a bi-weekly payroll system might result in an additional
            //! pay period and it can result in overpaying employees.
            ePayPeriodBiweekly,

            //! \brief Semi-Monthly Pay Period
            //!
            //! A semi-monthly (twice a month) pay period results in 24 paychecks in a year.
            //! Usually, salaried employees are paid semi-monthly.
            //!
            //! Employees receive 24 paychecks per year, 2 per month. Employers typically
            //! issue checks on the 1st and 15th of the month, or the 15th and the last day
            //! of the month. You do have the option of scheduling recurring payments on any
            //! two dates in a month that are spread equally apart.
            ePayPeriodSemimonthly,

            //! \brief Monthly Pay Period
            //!
            //! A monthly pay period results in 12 paychecks in a year. Almost all monthly pay
            //! periods are for salaried employees.
            //!
            //! Employees receive 12 paychecks per year, issued on the same date every month,
            //! usually the first or last day the month.
            ePayPeriodMonthly,

            //! \brief Quarterly Pay Period
            //!
            //! A quarterly pay period results in 4 paychecks a year.
            ePayPeriodQuarterly,

            //! \brief Semiannual Pay Period
            //!
            //! A semiannual pay period results in 2 paychecks a year.
            ePayPeriodSemiannually,
        };

        //! \brief Get the number of periods in the year
        //!
        //! \returns
        //!     returns the number of pay periods in a year.
        int getPayPeriodsInYear() const;

        //! \brief Get the current pay period
        //! \returns
        //! Returns the current pay period. \see ePAY_PERIOD.
        ePAY_PERIOD getPayPeriod() const { return _pay_period; }

        //! \brief Set the current pay period
        //!
        //! \param period       The pay period
        void setPayPeriod(const ePAY_PERIOD period) { _pay_period = period; }

        //! \brief Calculate Gross Salary Wages for this pay period
        //!
        //! For salaried employees, they are assigned an annual wage; or the 
        //! total wages for the year.  They are paid a portion of that wage
        //! for each pay period.  This function calculates the wages for this
        //! period.
        double calculateGrossSalaryWages(double const annual_wage);

        //! \brief Calculate prorated check based on partial employement
        //!
        //! Calculate the prorated check based on partial employment (i.e,
        //! employee starts mid pay period, or is terminated mid pay-period).
        //!
        double calculateGrossSalaryWages(double const annual_wage, int days_worked);

        private:

        //! \brief Get the number of days in this pay period
        //!
        //! \returns 
        //! The function returns the number of days inside the pay period.
        int getDaysInPeriod();
        
        ePAY_PERIOD _pay_period;
    };
}
}

#endif 