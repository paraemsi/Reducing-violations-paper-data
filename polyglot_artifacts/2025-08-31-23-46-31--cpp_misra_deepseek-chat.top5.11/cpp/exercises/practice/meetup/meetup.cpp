#include "meetup.h"
#include <ctime>
#include <cstring>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {
}

std::tm scheduler::find(const std::string& week, const std::string& weekday) const {
    // Parse weekday
    int target_wday;
    if (weekday == "Monday") {
        target_wday = 1;
    } else if (weekday == "Tuesday") {
        target_wday = 2;
    } else if (weekday == "Wednesday") {
        target_wday = 3;
    } else if (weekday == "Thursday") {
        target_wday = 4;
    } else if (weekday == "Friday") {
        target_wday = 5;
    } else if (weekday == "Saturday") {
        target_wday = 6;
    } else if (weekday == "Sunday") {
        target_wday = 0;
    } else {
        throw std::invalid_argument("Invalid weekday");
    }
    
    if (week == "teenth") {
        // Teenth days are always between 13 and 19
        for (int day = 13; day <= 19; day++) {
            std::tm time_in = {};
            time_in.tm_year = year_ - 1900;
            time_in.tm_mon = month_ - 1;
            time_in.tm_mday = day;
            time_in.tm_isdst = -1;
            std::mktime(&time_in);
            if (time_in.tm_wday == target_wday) {
                return time_in;
            }
        }
    } else {
        // For other cases, find the first occurrence of the target weekday
        std::tm first_day = {};
        first_day.tm_year = year_ - 1900;
        first_day.tm_mon = month_ - 1;
        first_day.tm_mday = 1;
        first_day.tm_isdst = -1;
        std::mktime(&first_day);
        
        // Find the first target weekday
        int first_occurrence = 1 + (target_wday - first_day.tm_wday + 7) % 7;
        
        if (week == "first") {
            std::tm result = {};
            result.tm_year = year_ - 1900;
            result.tm_mon = month_ - 1;
            result.tm_mday = first_occurrence;
            result.tm_isdst = -1;
            std::mktime(&result);
            return result;
        } else if (week == "second") {
            std::tm result = {};
            result.tm_year = year_ - 1900;
            result.tm_mon = month_ - 1;
            result.tm_mday = first_occurrence + 7;
            result.tm_isdst = -1;
            std::mktime(&result);
            return result;
        } else if (week == "third") {
            std::tm result = {};
            result.tm_year = year_ - 1900;
            result.tm_mon = month_ - 1;
            result.tm_mday = first_occurrence + 14;
            result.tm_isdst = -1;
            std::mktime(&result);
            return result;
        } else if (week == "fourth") {
            std::tm result = {};
            result.tm_year = year_ - 1900;
            result.tm_mon = month_ - 1;
            result.tm_mday = first_occurrence + 21;
            result.tm_isdst = -1;
            std::mktime(&result);
            return result;
        } else if (week == "last") {
            // Start from the end of the month and work backwards to find the last occurrence
            // Get the last day of the month by going to the next month and setting day to 0
            std::tm last = {};
            last.tm_year = year_ - 1900;
            last.tm_mon = month_;
            last.tm_mday = 0;
            last.tm_isdst = -1;
            std::mktime(&last);
            
            int last_day = last.tm_mday;
            // Find the last target weekday by checking backwards from the last day
            for (int day = last_day; day > 0; day--) {
                std::tm temp = {};
                temp.tm_year = year_ - 1900;
                temp.tm_mon = month_ - 1;
                temp.tm_mday = day;
                temp.tm_isdst = -1;
                std::mktime(&temp);
                if (temp.tm_wday == target_wday) {
                    return temp;
                }
            }
        } else {
            throw std::invalid_argument("Invalid week");
        }
    }
    // According to the problem statement, this should never be reached
    // But to satisfy the compiler, return a default value
    std::tm default_tm = {};
    return default_tm;
}

// Teenth implementations
std::tm scheduler::monteenth() const { return find("teenth", "Monday"); }
std::tm scheduler::tuesteenth() const { return find("teenth", "Tuesday"); }
std::tm scheduler::wednesteenth() const { return find("teenth", "Wednesday"); }
std::tm scheduler::thursteenth() const { return find("teenth", "Thursday"); }
std::tm scheduler::friteenth() const { return find("teenth", "Friday"); }
std::tm scheduler::saturteenth() const { return find("teenth", "Saturday"); }
std::tm scheduler::sunteenth() const { return find("teenth", "Sunday"); }

// First implementations
std::tm scheduler::first_monday() const { return find("first", "Monday"); }
std::tm scheduler::first_tuesday() const { return find("first", "Tuesday"); }
std::tm scheduler::first_wednesday() const { return find("first", "Wednesday"); }
std::tm scheduler::first_thursday() const { return find("first", "Thursday"); }
std::tm scheduler::first_friday() const { return find("first", "Friday"); }
std::tm scheduler::first_saturday() const { return find("first", "Saturday"); }
std::tm scheduler::first_sunday() const { return find("first", "Sunday"); }

// Second implementations
std::tm scheduler::second_monday() const { return find("second", "Monday"); }
std::tm scheduler::second_tuesday() const { return find("second", "Tuesday"); }
std::tm scheduler::second_wednesday() const { return find("second", "Wednesday"); }
std::tm scheduler::second_thursday() const { return find("second", "Thursday"); }
std::tm scheduler::second_friday() const { return find("second", "Friday"); }
std::tm scheduler::second_saturday() const { return find("second", "Saturday"); }
std::tm scheduler::second_sunday() const { return find("second", "Sunday"); }

// Third implementations
std::tm scheduler::third_monday() const { return find("third", "Monday"); }
std::tm scheduler::third_tuesday() const { return find("third", "Tuesday"); }
std::tm scheduler::third_wednesday() const { return find("third", "Wednesday"); }
std::tm scheduler::third_thursday() const { return find("third", "Thursday"); }
std::tm scheduler::third_friday() const { return find("third", "Friday"); }
std::tm scheduler::third_saturday() const { return find("third", "Saturday"); }
std::tm scheduler::third_sunday() const { return find("third", "Sunday"); }

// Fourth implementations
std::tm scheduler::fourth_monday() const { return find("fourth", "Monday"); }
std::tm scheduler::fourth_tuesday() const { return find("fourth", "Tuesday"); }
std::tm scheduler::fourth_wednesday() const { return find("fourth", "Wednesday"); }
std::tm scheduler::fourth_thursday() const { return find("fourth", "Thursday"); }
std::tm scheduler::fourth_friday() const { return find("fourth", "Friday"); }
std::tm scheduler::fourth_saturday() const { return find("fourth", "Saturday"); }
std::tm scheduler::fourth_sunday() const { return find("fourth", "Sunday"); }

// Last implementations
std::tm scheduler::last_monday() const { return find("last", "Monday"); }
std::tm scheduler::last_tuesday() const { return find("last", "Tuesday"); }
std::tm scheduler::last_wednesday() const { return find("last", "Wednesday"); }
std::tm scheduler::last_thursday() const { return find("last", "Thursday"); }
std::tm scheduler::last_friday() const { return find("last", "Friday"); }
std::tm scheduler::last_saturday() const { return find("last", "Saturday"); }
std::tm scheduler::last_sunday() const { return find("last", "Sunday"); }

}  // namespace meetup
