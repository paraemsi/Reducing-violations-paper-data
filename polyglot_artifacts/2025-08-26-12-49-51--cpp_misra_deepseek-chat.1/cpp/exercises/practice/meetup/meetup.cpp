#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <stdexcept>
#include <map>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

boost::gregorian::date scheduler::find_date(int week_day, const std::string& desc) const {
    using namespace boost::gregorian;
    
    if (desc == "teenth") {
        // Check each day from 13 to 19 to find the one that matches the target weekday
        for (int day = 13; day <= 19; ++day) {
            date current(year_, month_, day);
            if (current.day_of_week() == week_day) {
                return current;
            }
        }
    } else {
        // For first, second, third, fourth
        // Start from the first day of the month
        date first_of_month(year_, month_, 1);
        
        // Find the first occurrence of the target weekday
        // The number of days to add to reach the first target weekday
        int days_to_add = (week_day - first_of_month.day_of_week() + 7) % 7;
        date first_occurrence = first_of_month + days(days_to_add);
        
        if (desc == "first") {
            return first_occurrence;
        } else if (desc == "second") {
            return first_occurrence + weeks(1);
        } else if (desc == "third") {
            return first_occurrence + weeks(2);
        } else if (desc == "fourth") {
            return first_occurrence + weeks(3);
        } else if (desc == "last") {
            // For last, find the last occurrence which could be the 4th or 5th instance
            // Start from the end of the month and work backwards
            date last_of_month = first_of_month.end_of_month();
            
            // Calculate days to subtract to reach the last occurrence of the target weekday
            int days_to_subtract = (last_of_month.day_of_week() - week_day + 7) % 7;
            date last_occurrence = last_of_month - days(days_to_subtract);
            
            // Make sure we're still in the same month
            if (last_occurrence.month() != month_) {
                last_occurrence -= weeks(1);
            }
            return last_occurrence;
        }
    }
    throw std::runtime_error("No date found");
}

// Teenth functions
boost::gregorian::date scheduler::monteenth() const { return find_date(1, "teenth"); }
boost::gregorian::date scheduler::tuesteenth() const { return find_date(2, "teenth"); }
boost::gregorian::date scheduler::wednesteenth() const { return find_date(3, "teenth"); }
boost::gregorian::date scheduler::thursteenth() const { return find_date(4, "teenth"); }
boost::gregorian::date scheduler::friteenth() const { return find_date(5, "teenth"); }
boost::gregorian::date scheduler::saturteenth() const { return find_date(6, "teenth"); }
boost::gregorian::date scheduler::sunteenth() const { return find_date(0, "teenth"); }

// First week functions
boost::gregorian::date scheduler::first_monday() const { return find_date(1, "first"); }
boost::gregorian::date scheduler::first_tuesday() const { return find_date(2, "first"); }
boost::gregorian::date scheduler::first_wednesday() const { return find_date(3, "first"); }
boost::gregorian::date scheduler::first_thursday() const { return find_date(4, "first"); }
boost::gregorian::date scheduler::first_friday() const { return find_date(5, "first"); }
boost::gregorian::date scheduler::first_saturday() const { return find_date(6, "first"); }
boost::gregorian::date scheduler::first_sunday() const { return find_date(0, "first"); }

// Second week functions
boost::gregorian::date scheduler::second_monday() const { return find_date(1, "second"); }
boost::gregorian::date scheduler::second_tuesday() const { return find_date(2, "second"); }
boost::gregorian::date scheduler::second_wednesday() const { return find_date(3, "second"); }
boost::gregorian::date scheduler::second_thursday() const { return find_date(4, "second"); }
boost::gregorian::date scheduler::second_friday() const { return find_date(5, "second"); }
boost::gregorian::date scheduler::second_saturday() const { return find_date(6, "second"); }
boost::gregorian::date scheduler::second_sunday() const { return find_date(0, "second"); }

// Third week functions
boost::gregorian::date scheduler::third_monday() const { return find_date(1, "third"); }
boost::gregorian::date scheduler::third_tuesday() const { return find_date(2, "third"); }
boost::gregorian::date scheduler::third_wednesday() const { return find_date(3, "third"); }
boost::gregorian::date scheduler::third_thursday() const { return find_date(4, "third"); }
boost::gregorian::date scheduler::third_friday() const { return find_date(5, "third"); }
boost::gregorian::date scheduler::third_saturday() const { return find_date(6, "third"); }
boost::gregorian::date scheduler::third_sunday() const { return find_date(0, "third"); }

// Fourth week functions
boost::gregorian::date scheduler::fourth_monday() const { return find_date(1, "fourth"); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_date(2, "fourth"); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_date(3, "fourth"); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_date(4, "fourth"); }
boost::gregorian::date scheduler::fourth_friday() const { return find_date(5, "fourth"); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_date(6, "fourth"); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_date(0, "fourth"); }

// Last week functions
boost::gregorian::date scheduler::last_monday() const { return find_date(1, "last"); }
boost::gregorian::date scheduler::last_tuesday() const { return find_date(2, "last"); }
boost::gregorian::date scheduler::last_wednesday() const { return find_date(3, "last"); }
boost::gregorian::date scheduler::last_thursday() const { return find_date(4, "last"); }
boost::gregorian::date scheduler::last_friday() const { return find_date(5, "last"); }
boost::gregorian::date scheduler::last_saturday() const { return find_date(6, "last"); }
boost::gregorian::date scheduler::last_sunday() const { return find_date(0, "last"); }

}  // namespace meetup
