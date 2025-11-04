#include "meetup.h"
#include <ctime>
#include <cstring>
#include <stdexcept>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

int scheduler::find_day(const char* descriptor, const char* day_of_week) const {
    // Convert day of week to number (0-6, Sunday=0)
    int target_dow;
    if (std::strcmp(day_of_week, "Sunday") == 0) target_dow = 0;
    else if (std::strcmp(day_of_week, "Monday") == 0) target_dow = 1;
    else if (std::strcmp(day_of_week, "Tuesday") == 0) target_dow = 2;
    else if (std::strcmp(day_of_week, "Wednesday") == 0) target_dow = 3;
    else if (std::strcmp(day_of_week, "Thursday") == 0) target_dow = 4;
    else if (std::strcmp(day_of_week, "Friday") == 0) target_dow = 5;
    else if (std::strcmp(day_of_week, "Saturday") == 0) target_dow = 6;
    else throw std::runtime_error("Invalid day of week");
    
    // Handle teenth case
    if (std::strcmp(descriptor, "teenth") == 0) {
        for (int day = 13; day <= 19; ++day) {
            std::tm time_in = {};
            time_in.tm_year = year_ - 1900;
            time_in.tm_mon = month_ - 1;
            time_in.tm_mday = day;
            time_in.tm_isdst = -1;
            
            std::mktime(&time_in);
            if (time_in.tm_wday == target_dow) {
                return day;
            }
        }
    }
    
    // Handle first, second, third, fourth, last
    int week_index;
    if (std::strcmp(descriptor, "first") == 0) week_index = 0;
    else if (std::strcmp(descriptor, "second") == 0) week_index = 1;
    else if (std::strcmp(descriptor, "third") == 0) week_index = 2;
    else if (std::strcmp(descriptor, "fourth") == 0) week_index = 3;
    else if (std::strcmp(descriptor, "last") == 0) week_index = -1;
    else throw std::runtime_error("Invalid descriptor");
    
    if (week_index >= 0) {
        int count = 0;
        for (int day = 1; day <= 31; ++day) {
            std::tm time_in = {};
            time_in.tm_year = year_ - 1900;
            time_in.tm_mon = month_ - 1;
            time_in.tm_mday = day;
            time_in.tm_isdst = -1;
            
            std::mktime(&time_in);
            // Check if we're still in the same month
            if (time_in.tm_mon != month_ - 1) {
                break;
            }
            if (time_in.tm_wday == target_dow) {
                if (count == week_index) {
                    return day;
                }
                count++;
            }
        }
    } else {
        int last_found = -1;
        for (int day = 31; day >= 1; --day) {
            std::tm time_in = {};
            time_in.tm_year = year_ - 1900;
            time_in.tm_mon = month_ - 1;
            time_in.tm_mday = day;
            time_in.tm_isdst = -1;
            
            std::mktime(&time_in);
            // Check if we're still in the same month
            if (time_in.tm_mon == month_ - 1) {
                if (time_in.tm_wday == target_dow) {
                    last_found = day;
                    break;
                }
            }
        }
        if (last_found != -1) {
            return last_found;
        }
    }
    
    throw std::runtime_error("No valid date found");
}

// Implement all the required member functions
// Teenth days
int scheduler::monteenth() const { return find_day("teenth", "Monday"); }
int scheduler::tuesteenth() const { return find_day("teenth", "Tuesday"); }
int scheduler::wednesteenth() const { return find_day("teenth", "Wednesday"); }
int scheduler::thursteenth() const { return find_day("teenth", "Thursday"); }
int scheduler::friteenth() const { return find_day("teenth", "Friday"); }
int scheduler::saturteenth() const { return find_day("teenth", "Saturday"); }
int scheduler::sunteenth() const { return find_day("teenth", "Sunday"); }

// First days
int scheduler::first_monday() const { return find_day("first", "Monday"); }
int scheduler::first_tuesday() const { return find_day("first", "Tuesday"); }
int scheduler::first_wednesday() const { return find_day("first", "Wednesday"); }
int scheduler::first_thursday() const { return find_day("first", "Thursday"); }
int scheduler::first_friday() const { return find_day("first", "Friday"); }
int scheduler::first_saturday() const { return find_day("first", "Saturday"); }
int scheduler::first_sunday() const { return find_day("first", "Sunday"); }

// Second days
int scheduler::second_monday() const { return find_day("second", "Monday"); }
int scheduler::second_tuesday() const { return find_day("second", "Tuesday"); }
int scheduler::second_wednesday() const { return find_day("second", "Wednesday"); }
int scheduler::second_thursday() const { return find_day("second", "Thursday"); }
int scheduler::second_friday() const { return find_day("second", "Friday"); }
int scheduler::second_saturday() const { return find_day("second", "Saturday"); }
int scheduler::second_sunday() const { return find_day("second", "Sunday"); }

// Third days
int scheduler::third_monday() const { return find_day("third", "Monday"); }
int scheduler::third_tuesday() const { return find_day("third", "Tuesday"); }
int scheduler::third_wednesday() const { return find_day("third", "Wednesday"); }
int scheduler::third_thursday() const { return find_day("third", "Thursday"); }
int scheduler::third_friday() const { return find_day("third", "Friday"); }
int scheduler::third_saturday() const { return find_day("third", "Saturday"); }
int scheduler::third_sunday() const { return find_day("third", "Sunday"); }

// Fourth days
int scheduler::fourth_monday() const { return find_day("fourth", "Monday"); }
int scheduler::fourth_tuesday() const { return find_day("fourth", "Tuesday"); }
int scheduler::fourth_wednesday() const { return find_day("fourth", "Wednesday"); }
int scheduler::fourth_thursday() const { return find_day("fourth", "Thursday"); }
int scheduler::fourth_friday() const { return find_day("fourth", "Friday"); }
int scheduler::fourth_saturday() const { return find_day("fourth", "Saturday"); }
int scheduler::fourth_sunday() const { return find_day("fourth", "Sunday"); }

// Last days
int scheduler::last_monday() const { return find_day("last", "Monday"); }
int scheduler::last_tuesday() const { return find_day("last", "Tuesday"); }
int scheduler::last_wednesday() const { return find_day("last", "Wednesday"); }
int scheduler::last_thursday() const { return find_day("last", "Thursday"); }
int scheduler::last_friday() const { return find_day("last", "Friday"); }
int scheduler::last_saturday() const { return find_day("last", "Saturday"); }
int scheduler::last_sunday() const { return find_day("last", "Sunday"); }

}  // namespace meetup
