#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <map>
#include <stdexcept>
#include <string>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

boost::gregorian::date scheduler::meetup_day(const std::string& week, const std::string& weekday) const {
    // Map week strings to numbers
    static std::map<std::string, int> week_map = {
        {"first", 1}, {"second", 2}, {"third", 3}, {"fourth", 4}, {"last", 0}, {"teenth", -1}
    };
    
    // Map weekday strings to numbers (Sunday=0, Saturday=6)
    static std::map<std::string, int> weekday_map = {
        {"Sunday", 0}, {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3},
        {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}
    };
    
    int week_num = week_map.at(week);
    int target_wday = weekday_map.at(weekday);
    
    // Start from the first day of the month
    boost::gregorian::date start_date(year_, month_, 1);
    boost::gregorian::date end_date = start_date.end_of_month();
    
    if (week_num == -1) { // teenth
        // Check days 13-19
        for (int day = 13; day <= 19; day++) {
            boost::gregorian::date current(year_, month_, day);
            if (current.day_of_week() == target_wday) {
                return current;
            }
        }
    } else if (week_num > 0) { // first, second, third, fourth
        // Find the first occurrence of the weekday
        int first_occurrence = 1;
        boost::gregorian::date first_day(year_, month_, 1);
        int first_wday = first_day.day_of_week();
        int diff = target_wday - first_wday;
        if (diff < 0) diff += 7;
        first_occurrence += diff;
        
        // Add (week_num - 1) * 7 days
        int target_day = first_occurrence + (week_num - 1) * 7;
        if (target_day > end_date.day()) {
            throw std::runtime_error("Invalid date");
        }
        return boost::gregorian::date(year_, month_, target_day);
    } else if (week_num == 0) { // last
        // Start from the last day of the month and find the last occurrence of the target weekday
        boost::gregorian::date last_day = end_date;
        // Move backwards until we find the matching weekday
        while (last_day.day_of_week() != target_wday) {
            last_day -= boost::gregorian::days(1);
        }
        return last_day;
    }
    
    throw std::runtime_error("Invalid week specification");
}

// Teenth implementations
boost::gregorian::date scheduler::monteenth() const {
    return meetup_day("teenth", "Monday");
}
boost::gregorian::date scheduler::tuesteenth() const {
    return meetup_day("teenth", "Tuesday");
}
boost::gregorian::date scheduler::wednesteenth() const {
    return meetup_day("teenth", "Wednesday");
}
boost::gregorian::date scheduler::thursteenth() const {
    return meetup_day("teenth", "Thursday");
}
boost::gregorian::date scheduler::friteenth() const {
    return meetup_day("teenth", "Friday");
}
boost::gregorian::date scheduler::saturteenth() const {
    return meetup_day("teenth", "Saturday");
}
boost::gregorian::date scheduler::sunteenth() const {
    return meetup_day("teenth", "Sunday");
}

// First week implementations
boost::gregorian::date scheduler::first_monday() const {
    return meetup_day("first", "Monday");
}
boost::gregorian::date scheduler::first_tuesday() const {
    return meetup_day("first", "Tuesday");
}
boost::gregorian::date scheduler::first_wednesday() const {
    return meetup_day("first", "Wednesday");
}
boost::gregorian::date scheduler::first_thursday() const {
    return meetup_day("first", "Thursday");
}
boost::gregorian::date scheduler::first_friday() const {
    return meetup_day("first", "Friday");
}
boost::gregorian::date scheduler::first_saturday() const {
    return meetup_day("first", "Saturday");
}
boost::gregorian::date scheduler::first_sunday() const {
    return meetup_day("first", "Sunday");
}

// Second week implementations
boost::gregorian::date scheduler::second_monday() const {
    return meetup_day("second", "Monday");
}
boost::gregorian::date scheduler::second_tuesday() const {
    return meetup_day("second", "Tuesday");
}
boost::gregorian::date scheduler::second_wednesday() const {
    return meetup_day("second", "Wednesday");
}
boost::gregorian::date scheduler::second_thursday() const {
    return meetup_day("second", "Thursday");
}
boost::gregorian::date scheduler::second_friday() const {
    return meetup_day("second", "Friday");
}
boost::gregorian::date scheduler::second_saturday() const {
    return meetup_day("second", "Saturday");
}
boost::gregorian::date scheduler::second_sunday() const {
    return meetup_day("second", "Sunday");
}

// Third week implementations
boost::gregorian::date scheduler::third_monday() const {
    return meetup_day("third", "Monday");
}
boost::gregorian::date scheduler::third_tuesday() const {
    return meetup_day("third", "Tuesday");
}
boost::gregorian::date scheduler::third_wednesday() const {
    return meetup_day("third", "Wednesday");
}
boost::gregorian::date scheduler::third_thursday() const {
    return meetup_day("third", "Thursday");
}
boost::gregorian::date scheduler::third_friday() const {
    return meetup_day("third", "Friday");
}
boost::gregorian::date scheduler::third_saturday() const {
    return meetup_day("third", "Saturday");
}
boost::gregorian::date scheduler::third_sunday() const {
    return meetup_day("third", "Sunday");
}

// Fourth week implementations
boost::gregorian::date scheduler::fourth_monday() const {
    return meetup_day("fourth", "Monday");
}
boost::gregorian::date scheduler::fourth_tuesday() const {
    return meetup_day("fourth", "Tuesday");
}
boost::gregorian::date scheduler::fourth_wednesday() const {
    return meetup_day("fourth", "Wednesday");
}
boost::gregorian::date scheduler::fourth_thursday() const {
    return meetup_day("fourth", "Thursday");
}
boost::gregorian::date scheduler::fourth_friday() const {
    return meetup_day("fourth", "Friday");
}
boost::gregorian::date scheduler::fourth_saturday() const {
    return meetup_day("fourth", "Saturday");
}
boost::gregorian::date scheduler::fourth_sunday() const {
    return meetup_day("fourth", "Sunday");
}

// Last week implementations
boost::gregorian::date scheduler::last_monday() const {
    return meetup_day("last", "Monday");
}
boost::gregorian::date scheduler::last_tuesday() const {
    return meetup_day("last", "Tuesday");
}
boost::gregorian::date scheduler::last_wednesday() const {
    return meetup_day("last", "Wednesday");
}
boost::gregorian::date scheduler::last_thursday() const {
    return meetup_day("last", "Thursday");
}
boost::gregorian::date scheduler::last_friday() const {
    return meetup_day("last", "Friday");
}
boost::gregorian::date scheduler::last_saturday() const {
    return meetup_day("last", "Saturday");
}
boost::gregorian::date scheduler::last_sunday() const {
    return meetup_day("last", "Sunday");
}

}  // namespace meetup
