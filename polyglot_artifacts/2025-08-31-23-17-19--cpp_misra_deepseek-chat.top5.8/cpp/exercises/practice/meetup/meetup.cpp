#include "meetup.h"
#include <string>
#include <ctime>
#include <map>
#include <stdexcept>
#include <iostream>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

std::tm scheduler::find_day(const std::string& week, const std::string& weekday) const {
    // Map weekdays to tm_wday values (Sunday = 0)
    std::map<std::string, int> weekday_map = {
        {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3},
        {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}, {"Sunday", 0}
    };
    
    // Get the target weekday
    int target_wday = weekday_map.at(weekday);
    
    std::tm result = {};
    
    if (week == "teenth") {
        // Check each day from 13 to 19 to find the one that matches the target weekday
        for (int day = 13; day <= 19; day++) {
            std::tm time_in = {};
            time_in.tm_year = year_ - 1900;
            time_in.tm_mon = month_ - 1;
            time_in.tm_mday = day;
            time_in.tm_hour = 12;
            time_in.tm_min = 0;
            time_in.tm_sec = 0;
            time_in.tm_isdst = -1;
            
            std::mktime(&time_in);
            if (time_in.tm_wday == target_wday) {
                result = time_in;
                break;
            }
        }
    } else {
        // Handle first, second, third, fourth, last
        // Start from the first day of the month
        std::tm time_in = {};
        time_in.tm_year = year_ - 1900;
        time_in.tm_mon = month_ - 1;
        time_in.tm_mday = 1;
        time_in.tm_hour = 12;
        time_in.tm_min = 0;
        time_in.tm_sec = 0;
        time_in.tm_isdst = -1;
        
        std::mktime(&time_in);
        
        // Find the first occurrence of the target weekday
        int day_delta = (target_wday - time_in.tm_wday + 7) % 7;
        int target_day = 1 + day_delta;
        
        if (week == "first") {
            // target_day is correct
        } else if (week == "second") {
            target_day += 7;
        } else if (week == "third") {
            target_day += 14;
        } else if (week == "fourth") {
            target_day += 21;
        } else if (week == "last") {
            // Find the last occurrence by checking if adding 28, 35, etc. days is valid
            // First, find the last day of the month
            std::tm next_month = time_in;
            next_month.tm_mon += 1;
            next_month.tm_mday = 0;
            std::mktime(&next_month);
            int last_day = next_month.tm_mday;
            
            // Start from the fourth occurrence and move back if necessary
            target_day += 28;
            if (target_day > last_day) {
                target_day -= 7;
            }
        } else {
            throw std::runtime_error("Invalid week specification");
        }
        
        // Set result
        result.tm_year = year_ - 1900;
        result.tm_mon = month_ - 1;
        result.tm_mday = target_day;
        result.tm_hour = 12;
        result.tm_min = 0;
        result.tm_sec = 0;
        result.tm_isdst = -1;
        std::mktime(&result);
    }
    
    return result;
}

// Implement all the member functions
// For teenth days, we need to map to the correct weekday names
#define IMPLEMENT_TEENTH(day, weekday_name) \
    std::tm scheduler::day##teenth() const { return find_day("teenth", weekday_name); }
IMPLEMENT_TEENTH(mon, "Monday")
IMPLEMENT_TEENTH(tues, "Tuesday")
IMPLEMENT_TEENTH(wednes, "Wednesday")
IMPLEMENT_TEENTH(thurs, "Thursday")
IMPLEMENT_TEENTH(fri, "Friday")
IMPLEMENT_TEENTH(satur, "Saturday")
IMPLEMENT_TEENTH(sun, "Sunday")

#define IMPLEMENT_FIRST(day, weekday_name) \
    std::tm scheduler::first_##day() const { return find_day("first", weekday_name); }
IMPLEMENT_FIRST(monday, "Monday")
IMPLEMENT_FIRST(tuesday, "Tuesday")
IMPLEMENT_FIRST(wednesday, "Wednesday")
IMPLEMENT_FIRST(thursday, "Thursday")
IMPLEMENT_FIRST(friday, "Friday")
IMPLEMENT_FIRST(saturday, "Saturday")
IMPLEMENT_FIRST(sunday, "Sunday")

#define IMPLEMENT_SECOND(day, weekday_name) \
    std::tm scheduler::second_##day() const { return find_day("second", weekday_name); }
IMPLEMENT_SECOND(monday, "Monday")
IMPLEMENT_SECOND(tuesday, "Tuesday")
IMPLEMENT_SECOND(wednesday, "Wednesday")
IMPLEMENT_SECOND(thursday, "Thursday")
IMPLEMENT_SECOND(friday, "Friday")
IMPLEMENT_SECOND(saturday, "Saturday")
IMPLEMENT_SECOND(sunday, "Sunday")

#define IMPLEMENT_THIRD(day, weekday_name) \
    std::tm scheduler::third_##day() const { return find_day("third", weekday_name); }
IMPLEMENT_THIRD(monday, "Monday")
IMPLEMENT_THIRD(tuesday, "Tuesday")
IMPLEMENT_THIRD(wednesday, "Wednesday")
IMPLEMENT_THIRD(thursday, "Thursday")
IMPLEMENT_THIRD(friday, "Friday")
IMPLEMENT_THIRD(saturday, "Saturday")
IMPLEMENT_THIRD(sunday, "Sunday")

#define IMPLEMENT_FOURTH(day, weekday_name) \
    std::tm scheduler::fourth_##day() const { return find_day("fourth", weekday_name); }
IMPLEMENT_FOURTH(monday, "Monday")
IMPLEMENT_FOURTH(tuesday, "Tuesday")
IMPLEMENT_FOURTH(wednesday, "Wednesday")
IMPLEMENT_FOURTH(thursday, "Thursday")
IMPLEMENT_FOURTH(friday, "Friday")
IMPLEMENT_FOURTH(saturday, "Saturday")
IMPLEMENT_FOURTH(sunday, "Sunday")

#define IMPLEMENT_LAST(day, weekday_name) \
    std::tm scheduler::last_##day() const { return find_day("last", weekday_name); }
IMPLEMENT_LAST(monday, "Monday")
IMPLEMENT_LAST(tuesday, "Tuesday")
IMPLEMENT_LAST(wednesday, "Wednesday")
IMPLEMENT_LAST(thursday, "Thursday")
IMPLEMENT_LAST(friday, "Friday")
IMPLEMENT_LAST(saturday, "Saturday")
IMPLEMENT_LAST(sunday, "Sunday")

}  // namespace meetup
