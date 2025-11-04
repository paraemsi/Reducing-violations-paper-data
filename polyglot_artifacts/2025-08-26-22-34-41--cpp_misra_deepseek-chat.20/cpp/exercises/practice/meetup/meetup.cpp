#include "meetup.h"
#include <ctime>
#include <cstring>
#include <string>
#include <stdexcept>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {
}

std::tm scheduler::find(const char* week, const char* weekday) const {
    // Map weekdays to numbers (Sunday=0, Monday=1, etc.)
    int target_wday;
    if (std::strcmp(weekday, "Sunday") == 0) target_wday = 0;
    else if (std::strcmp(weekday, "Monday") == 0) target_wday = 1;
    else if (std::strcmp(weekday, "Tuesday") == 0) target_wday = 2;
    else if (std::strcmp(weekday, "Wednesday") == 0) target_wday = 3;
    else if (std::strcmp(weekday, "Thursday") == 0) target_wday = 4;
    else if (std::strcmp(weekday, "Friday") == 0) target_wday = 5;
    else if (std::strcmp(weekday, "Saturday") == 0) target_wday = 6;
    else throw std::runtime_error("Invalid weekday");
    
    // Initialize a tm struct for the first day of the month
    std::tm time_in = {};
    time_in.tm_year = year_ - 1900;
    time_in.tm_mon = month_ - 1;
    time_in.tm_mday = 1;
    time_in.tm_hour = 0;
    time_in.tm_min = 0;
    time_in.tm_sec = 0;
    time_in.tm_isdst = -1;
    
    // Normalize the time
    std::mktime(&time_in);
    
    // Find the first occurrence of the target weekday
    int day = 1;
    if (std::strcmp(week, "teenth") == 0) {
        // Check days 13 to 19
        for (day = 13; day <= 19; day++) {
            std::tm temp = time_in;
            temp.tm_mday = day;
            std::mktime(&temp);
            if (temp.tm_wday == target_wday) {
                return temp;
            }
        }
        // According to the problem, each weekday has exactly one teenth day, so this should never be reached
        throw std::runtime_error("No teenth day found");
    } else {
        // Find the offset to the first target weekday
        int wday_diff = (target_wday - time_in.tm_wday + 7) % 7;
        int base_day = 1 + wday_diff;
        
        if (std::strcmp(week, "first") == 0) {
            day = base_day;
        } else if (std::strcmp(week, "second") == 0) {
            day = base_day + 7;
        } else if (std::strcmp(week, "third") == 0) {
            day = base_day + 14;
        } else if (std::strcmp(week, "fourth") == 0) {
            day = base_day + 21;
        } else if (std::strcmp(week, "last") == 0) {
            // Start from the end of the month
            // Get the last day of the month by going to the next month and subtracting one day
            std::tm next_month = time_in;
            next_month.tm_mon += 1;
            next_month.tm_mday = 0;
            std::mktime(&next_month);
            int last_day = next_month.tm_mday;
            
            // Find the last occurrence of the target weekday
            for (day = last_day; day > 0; day--) {
                std::tm temp = time_in;
                temp.tm_mday = day;
                std::mktime(&temp);
                if (temp.tm_wday == target_wday) {
                    break;
                }
            }
        } else {
            throw std::runtime_error("Invalid week specification");
        }
        
        // Verify the day is within the current month
        std::tm temp = time_in;
        temp.tm_mday = day;
        std::mktime(&temp);
        // If the month changed, then the day is not valid
        if (temp.tm_mon != time_in.tm_mon) {
            // This should not happen according to the problem statement, but let's handle it
            throw std::runtime_error("Invalid date found");
        }
        return temp;
    }
}

// Teenth implementations
std::tm scheduler::monteenth() const { return find("teenth", "Monday"); }
std::tm scheduler::tuesteenth() const { return find("teenth", "Tuesday"); }
std::tm scheduler::wednesteenth() const { return find("teenth", "Wednesday"); }
std::tm scheduler::thursteenth() const { return find("teenth", "Thursday"); }
std::tm scheduler::friteenth() const { return find("teenth", "Friday"); }
std::tm scheduler::saturteenth() const { return find("teenth", "Saturday"); }
std::tm scheduler::sunteenth() const { return find("teenth", "Sunday"); }

// First week implementations
std::tm scheduler::first_monday() const { return find("first", "Monday"); }
std::tm scheduler::first_tuesday() const { return find("first", "Tuesday"); }
std::tm scheduler::first_wednesday() const { return find("first", "Wednesday"); }
std::tm scheduler::first_thursday() const { return find("first", "Thursday"); }
std::tm scheduler::first_friday() const { return find("first", "Friday"); }
std::tm scheduler::first_saturday() const { return find("first", "Saturday"); }
std::tm scheduler::first_sunday() const { return find("first", "Sunday"); }

// Second week implementations
std::tm scheduler::second_monday() const { return find("second", "Monday"); }
std::tm scheduler::second_tuesday() const { return find("second", "Tuesday"); }
std::tm scheduler::second_wednesday() const { return find("second", "Wednesday"); }
std::tm scheduler::second_thursday() const { return find("second", "Thursday"); }
std::tm scheduler::second_friday() const { return find("second", "Friday"); }
std::tm scheduler::second_saturday() const { return find("second", "Saturday"); }
std::tm scheduler::second_sunday() const { return find("second", "Sunday"); }

// Third week implementations
std::tm scheduler::third_monday() const { return find("third", "Monday"); }
std::tm scheduler::third_tuesday() const { return find("third", "Tuesday"); }
std::tm scheduler::third_wednesday() const { return find("third", "Wednesday"); }
std::tm scheduler::third_thursday() const { return find("third", "Thursday"); }
std::tm scheduler::third_friday() const { return find("third", "Friday"); }
std::tm scheduler::third_saturday() const { return find("third", "Saturday"); }
std::tm scheduler::third_sunday() const { return find("third", "Sunday"); }

// Fourth week implementations
std::tm scheduler::fourth_monday() const { return find("fourth", "Monday"); }
std::tm scheduler::fourth_tuesday() const { return find("fourth", "Tuesday"); }
std::tm scheduler::fourth_wednesday() const { return find("fourth", "Wednesday"); }
std::tm scheduler::fourth_thursday() const { return find("fourth", "Thursday"); }
std::tm scheduler::fourth_friday() const { return find("fourth", "Friday"); }
std::tm scheduler::fourth_saturday() const { return find("fourth", "Saturday"); }
std::tm scheduler::fourth_sunday() const { return find("fourth", "Sunday"); }

// Last week implementations
std::tm scheduler::last_monday() const { return find("last", "Monday"); }
std::tm scheduler::last_tuesday() const { return find("last", "Tuesday"); }
std::tm scheduler::last_wednesday() const { return find("last", "Wednesday"); }
std::tm scheduler::last_thursday() const { return find("last", "Thursday"); }
std::tm scheduler::last_friday() const { return find("last", "Friday"); }
std::tm scheduler::last_saturday() const { return find("last", "Saturday"); }
std::tm scheduler::last_sunday() const { return find("last", "Sunday"); }

}  // namespace meetup
