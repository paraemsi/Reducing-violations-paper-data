#include "meetup.h"
#include <ctime>
#include <stdexcept>
#include <string>
#include <iostream>

namespace meetup {

namespace {

int get_wday(int year, int month, int day) {
    std::tm time_in = {0};
    time_in.tm_year = year - 1900;
    time_in.tm_mon = month - 1;
    time_in.tm_mday = day;
    time_in.tm_hour = 12;  // Avoid issues with DST by setting to noon
    std::mktime(&time_in);
    return time_in.tm_wday;
}

std::tm find_date(int year, int month, const std::string& which, int target_wday) {
    std::tm result = {0};
    result.tm_hour = 12;  // Set to noon to avoid DST issues
    
    if (which == "teenth") {
        for (int day = 13; day <= 19; day++) {
            if (get_wday(year, month, day) == target_wday) {
                result.tm_mday = day;
                result.tm_mon = month - 1;
                result.tm_year = year - 1900;
                // Normalize the tm structure
                std::mktime(&result);
                return result;
            }
        }
    } else if (which == "first") {
        for (int day = 1; day <= 7; day++) {
            if (get_wday(year, month, day) == target_wday) {
                result.tm_mday = day;
                result.tm_mon = month - 1;
                result.tm_year = year - 1900;
                std::mktime(&result);
                return result;
            }
        }
    } else if (which == "second") {
        for (int day = 8; day <= 14; day++) {
            if (get_wday(year, month, day) == target_wday) {
                result.tm_mday = day;
                result.tm_mon = month - 1;
                result.tm_year = year - 1900;
                std::mktime(&result);
                return result;
            }
        }
    } else if (which == "third") {
        for (int day = 15; day <= 21; day++) {
            if (get_wday(year, month, day) == target_wday) {
                result.tm_mday = day;
                result.tm_mon = month - 1;
                result.tm_year = year - 1900;
                std::mktime(&result);
                return result;
            }
        }
    } else if (which == "fourth") {
        for (int day = 22; day <= 28; day++) {
            if (get_wday(year, month, day) == target_wday) {
                result.tm_mday = day;
                result.tm_mon = month - 1;
                result.tm_year = year - 1900;
                std::mktime(&result);
                return result;
            }
        }
    } else if (which == "last") {
        // To find the last occurrence, start from the last day of the month and go backwards
        // Get the number of days in the month by finding the first day of the next month and subtracting 1
        std::tm tmp = {0};
        tmp.tm_year = year - 1900;
        tmp.tm_mon = month;  // Next month (0-based, so month is already 1-based, thus month is next)
        tmp.tm_mday = 1;
        std::mktime(&tmp);
        
        // The day before the first of next month is the last day of current month
        tmp.tm_mday = 0;
        std::mktime(&tmp);
        int last_day = tmp.tm_mday;
        
        // Find the last occurrence of the target weekday
        for (int day = last_day; day > last_day - 7; day--) {
            if (day < 1) break;
            if (get_wday(year, month, day) == target_wday) {
                result.tm_mday = day;
                result.tm_mon = month - 1;
                result.tm_year = year - 1900;
                std::mktime(&result);
                return result;
            }
        }
    }
    throw std::runtime_error("Date not found");
}

} // namespace

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Implement all interface functions
#define IMPLEMENT_TEENTH(day_name, wday) \
    std::tm scheduler::day_name##teenth() const { \
        return find_date(year_, month_, "teenth", wday); \
    }
    
#define IMPLEMENT_WEEK(prefix, day_name, wday, which) \
    std::tm scheduler::prefix##_##day_name() const { \
        return find_date(year_, month_, which, wday); \
    }

IMPLEMENT_TEENTH(mon, 1)
IMPLEMENT_TEENTH(tues, 2)
IMPLEMENT_TEENTH(wednes, 3)
IMPLEMENT_TEENTH(thurs, 4)
IMPLEMENT_TEENTH(fri, 5)
IMPLEMENT_TEENTH(satur, 6)
IMPLEMENT_TEENTH(sun, 0)

// First week
IMPLEMENT_WEEK(first, monday, 1, "first")
IMPLEMENT_WEEK(first, tuesday, 2, "first")
IMPLEMENT_WEEK(first, wednesday, 3, "first")
IMPLEMENT_WEEK(first, thursday, 4, "first")
IMPLEMENT_WEEK(first, friday, 5, "first")
IMPLEMENT_WEEK(first, saturday, 6, "first")
IMPLEMENT_WEEK(first, sunday, 0, "first")

// Second week
IMPLEMENT_WEEK(second, monday, 1, "second")
IMPLEMENT_WEEK(second, tuesday, 2, "second")
IMPLEMENT_WEEK(second, wednesday, 3, "second")
IMPLEMENT_WEEK(second, thursday, 4, "second")
IMPLEMENT_WEEK(second, friday, 5, "second")
IMPLEMENT_WEEK(second, saturday, 6, "second")
IMPLEMENT_WEEK(second, sunday, 0, "second")

// Third week
IMPLEMENT_WEEK(third, monday, 1, "third")
IMPLEMENT_WEEK(third, tuesday, 2, "third")
IMPLEMENT_WEEK(third, wednesday, 3, "third")
IMPLEMENT_WEEK(third, thursday, 4, "third")
IMPLEMENT_WEEK(third, friday, 5, "third")
IMPLEMENT_WEEK(third, saturday, 6, "third")
IMPLEMENT_WEEK(third, sunday, 0, "third")

// Fourth week
IMPLEMENT_WEEK(fourth, monday, 1, "fourth")
IMPLEMENT_WEEK(fourth, tuesday, 2, "fourth")
IMPLEMENT_WEEK(fourth, wednesday, 3, "fourth")
IMPLEMENT_WEEK(fourth, thursday, 4, "fourth")
IMPLEMENT_WEEK(fourth, friday, 5, "fourth")
IMPLEMENT_WEEK(fourth, saturday, 6, "fourth")
IMPLEMENT_WEEK(fourth, sunday, 0, "fourth")

// Last week
IMPLEMENT_WEEK(last, monday, 1, "last")
IMPLEMENT_WEEK(last, tuesday, 2, "last")
IMPLEMENT_WEEK(last, wednesday, 3, "last")
IMPLEMENT_WEEK(last, thursday, 4, "last")
IMPLEMENT_WEEK(last, friday, 5, "last")
IMPLEMENT_WEEK(last, saturday, 6, "last")
IMPLEMENT_WEEK(last, sunday, 0, "last")

}  // namespace meetup
