#include "meetup.h"
#include <map>
#include <stdexcept>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

date scheduler::meetup_day(const std::string& week, const std::string& weekday) const {
    // Map weekday strings to numbers (Sunday=0, Monday=1, etc.)
    static const std::map<std::string, int> weekday_map = {
        {"Sunday", 0}, {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3},
        {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}
    };
    
    int target_weekday = weekday_map.at(weekday);
    
    if (week == "teenth") {
        // Check days 13 to 19
        for (int day = 13; day <= 19; ++day) {
            date current_date(year_, month_, day);
            if (current_date.day_of_week() == target_weekday) {
                return current_date;
            }
        }
    } else {
        // For first, second, third, fourth, last
        // Start from the first day of the month
        date first_day(year_, month_, 1);
        
        // Find the first occurrence of the target weekday
        int first_weekday = first_day.day_of_week();
        int days_to_add = (target_weekday - first_weekday + 7) % 7;
        date base_date = first_day + days(days_to_add);
        
        if (week == "first") {
            return base_date;
        } else if (week == "second") {
            return base_date + days(7);
        } else if (week == "third") {
            return base_date + days(14);
        } else if (week == "fourth") {
            return base_date + days(21);
        } else if (week == "last") {
            // Add 28 days and check if it's still in the same month
            date candidate = base_date + days(28);
            if (candidate.month() == month_) {
                return candidate;
            } else {
                return base_date + days(21);
            }
        }
    }
    throw std::runtime_error("Invalid week specification");
}

// Implement all the required member functions
// Teenth days
date scheduler::monteenth() const { return meetup_day("teenth", "Monday"); }
date scheduler::tuesteenth() const { return meetup_day("teenth", "Tuesday"); }
date scheduler::wednesteenth() const { return meetup_day("teenth", "Wednesday"); }
date scheduler::thursteenth() const { return meetup_day("teenth", "Thursday"); }
date scheduler::friteenth() const { return meetup_day("teenth", "Friday"); }
date scheduler::saturteenth() const { return meetup_day("teenth", "Saturday"); }
date scheduler::sunteenth() const { return meetup_day("teenth", "Sunday"); }

// First week days
date scheduler::first_monday() const { return meetup_day("first", "Monday"); }
date scheduler::first_tuesday() const { return meetup_day("first", "Tuesday"); }
date scheduler::first_wednesday() const { return meetup_day("first", "Wednesday"); }
date scheduler::first_thursday() const { return meetup_day("first", "Thursday"); }
date scheduler::first_friday() const { return meetup_day("first", "Friday"); }
date scheduler::first_saturday() const { return meetup_day("first", "Saturday"); }
date scheduler::first_sunday() const { return meetup_day("first", "Sunday"); }

// Second week days
date scheduler::second_monday() const { return meetup_day("second", "Monday"); }
date scheduler::second_tuesday() const { return meetup_day("second", "Tuesday"); }
date scheduler::second_wednesday() const { return meetup_day("second", "Wednesday"); }
date scheduler::second_thursday() const { return meetup_day("second", "Thursday"); }
date scheduler::second_friday() const { return meetup_day("second", "Friday"); }
date scheduler::second_saturday() const { return meetup_day("second", "Saturday"); }
date scheduler::second_sunday() const { return meetup_day("second", "Sunday"); }

// Third week days
date scheduler::third_monday() const { return meetup_day("third", "Monday"); }
date scheduler::third_tuesday() const { return meetup_day("third", "Tuesday"); }
date scheduler::third_wednesday() const { return meetup_day("third", "Wednesday"); }
date scheduler::third_thursday() const { return meetup_day("third", "Thursday"); }
date scheduler::third_friday() const { return meetup_day("third", "Friday"); }
date scheduler::third_saturday() const { return meetup_day("third", "Saturday"); }
date scheduler::third_sunday() const { return meetup_day("third", "Sunday"); }

// Fourth week days
date scheduler::fourth_monday() const { return meetup_day("fourth", "Monday"); }
date scheduler::fourth_tuesday() const { return meetup_day("fourth", "Tuesday"); }
date scheduler::fourth_wednesday() const { return meetup_day("fourth", "Wednesday"); }
date scheduler::fourth_thursday() const { return meetup_day("fourth", "Thursday"); }
date scheduler::fourth_friday() const { return meetup_day("fourth", "Friday"); }
date scheduler::fourth_saturday() const { return meetup_day("fourth", "Saturday"); }
date scheduler::fourth_sunday() const { return meetup_day("fourth", "Sunday"); }

// Last week days
date scheduler::last_monday() const { return meetup_day("last", "Monday"); }
date scheduler::last_tuesday() const { return meetup_day("last", "Tuesday"); }
date scheduler::last_wednesday() const { return meetup_day("last", "Wednesday"); }
date scheduler::last_thursday() const { return meetup_day("last", "Thursday"); }
date scheduler::last_friday() const { return meetup_day("last", "Friday"); }
date scheduler::last_saturday() const { return meetup_day("last", "Saturday"); }
date scheduler::last_sunday() const { return meetup_day("last", "Sunday"); }

}  // namespace meetup
