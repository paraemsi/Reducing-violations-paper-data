#include "meetup.h"
#include <ctime>
#include <cstring>
#include <stdexcept>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

int scheduler::find_day(const char* week, const char* day_of_week) const {
    // Map day names to tm_wday values (Sunday = 0)
    int target_dow;
    if (std::strcmp(day_of_week, "Sunday") == 0) { 
        target_dow = 0; 
    } else if (std::strcmp(day_of_week, "Monday") == 0) { 
        target_dow = 1; 
    } else if (std::strcmp(day_of_week, "Tuesday") == 0) { 
        target_dow = 2; 
    } else if (std::strcmp(day_of_week, "Wednesday") == 0) { 
        target_dow = 3; 
    } else if (std::strcmp(day_of_week, "Thursday") == 0) { 
        target_dow = 4; 
    } else if (std::strcmp(day_of_week, "Friday") == 0) { 
        target_dow = 5; 
    } else if (std::strcmp(day_of_week, "Saturday") == 0) { 
        target_dow = 6; 
    } else { 
        throw std::invalid_argument("Invalid day of week"); 
    }
    
    // Handle teenth case
    if (std::strcmp(week, "teenth") == 0) {
        for (int day = 13; day <= 19; day++) {
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
    
    // Get the first day of the month
    std::tm first_day = {};
    first_day.tm_year = year_ - 1900;
    first_day.tm_mon = month_ - 1;
    first_day.tm_mday = 1;
    first_day.tm_isdst = -1;
    std::mktime(&first_day);
    
    // Find the first occurrence of the target day
    int day_offset = (target_dow - first_day.tm_wday + 7) % 7;
    int first_occurrence = 1 + day_offset;
    
    // Handle first, second, third, fourth
    if (std::strcmp(week, "first") == 0) {
        return first_occurrence;
    } else if (std::strcmp(week, "second") == 0) {
        return first_occurrence + 7;
    } else if (std::strcmp(week, "third") == 0) {
        return first_occurrence + 14;
    } else if (std::strcmp(week, "fourth") == 0) {
        return first_occurrence + 21;
    } else if (std::strcmp(week, "last") == 0) {
        // To find the last occurrence, start from the end of the month
        // Get the number of days in the month by going to the next month and subtracting
        std::tm next_month = {};
        next_month.tm_year = year_ - 1900;
        next_month.tm_mon = month_;
        next_month.tm_mday = 0;
        next_month.tm_isdst = -1;
        std::mktime(&next_month);
        int last_day = next_month.tm_mday;
        
        // Find the last occurrence of the target day
        std::tm last_day_tm = {};
        last_day_tm.tm_year = year_ - 1900;
        last_day_tm.tm_mon = month_ - 1;
        last_day_tm.tm_mday = last_day;
        last_day_tm.tm_isdst = -1;
        std::mktime(&last_day_tm);
        
        int last_dow = last_day_tm.tm_wday;
        int days_to_subtract = (last_dow - target_dow + 7) % 7;
        int result = last_day - days_to_subtract;
        return result;
    } else {
        throw std::invalid_argument("Invalid week specification");
    }
}

// Implement all the member functions
int scheduler::monteenth() const { return find_day("teenth", "Monday"); }
int scheduler::tuesteenth() const { return find_day("teenth", "Tuesday"); }
int scheduler::wednesteenth() const { return find_day("teenth", "Wednesday"); }
int scheduler::thursteenth() const { return find_day("teenth", "Thursday"); }
int scheduler::friteenth() const { return find_day("teenth", "Friday"); }
int scheduler::saturteenth() const { return find_day("teenth", "Saturday"); }
int scheduler::sunteenth() const { return find_day("teenth", "Sunday"); }

int scheduler::first_monday() const { return find_day("first", "Monday"); }
int scheduler::first_tuesday() const { return find_day("first", "Tuesday"); }
int scheduler::first_wednesday() const { return find_day("first", "Wednesday"); }
int scheduler::first_thursday() const { return find_day("first", "Thursday"); }
int scheduler::first_friday() const { return find_day("first", "Friday"); }
int scheduler::first_saturday() const { return find_day("first", "Saturday"); }
int scheduler::first_sunday() const { return find_day("first", "Sunday"); }

int scheduler::second_monday() const { return find_day("second", "Monday"); }
int scheduler::second_tuesday() const { return find_day("second", "Tuesday"); }
int scheduler::second_wednesday() const { return find_day("second", "Wednesday"); }
int scheduler::second_thursday() const { return find_day("second", "Thursday"); }
int scheduler::second_friday() const { return find_day("second", "Friday"); }
int scheduler::second_saturday() const { return find_day("second", "Saturday"); }
int scheduler::second_sunday() const { return find_day("second", "Sunday"); }

int scheduler::third_monday() const { return find_day("third", "Monday"); }
int scheduler::third_tuesday() const { return find_day("third", "Tuesday"); }
int scheduler::third_wednesday() const { return find_day("third", "Wednesday"); }
int scheduler::third_thursday() const { return find_day("third", "Thursday"); }
int scheduler::third_friday() const { return find_day("third", "Friday"); }
int scheduler::third_saturday() const { return find_day("third", "Saturday"); }
int scheduler::third_sunday() const { return find_day("third", "Sunday"); }

int scheduler::fourth_monday() const { return find_day("fourth", "Monday"); }
int scheduler::fourth_tuesday() const { return find_day("fourth", "Tuesday"); }
int scheduler::fourth_wednesday() const { return find_day("fourth", "Wednesday"); }
int scheduler::fourth_thursday() const { return find_day("fourth", "Thursday"); }
int scheduler::fourth_friday() const { return find_day("fourth", "Friday"); }
int scheduler::fourth_saturday() const { return find_day("fourth", "Saturday"); }
int scheduler::fourth_sunday() const { return find_day("fourth", "Sunday"); }

int scheduler::last_monday() const { return find_day("last", "Monday"); }
int scheduler::last_tuesday() const { return find_day("last", "Tuesday"); }
int scheduler::last_wednesday() const { return find_day("last", "Wednesday"); }
int scheduler::last_thursday() const { return find_day("last", "Thursday"); }
int scheduler::last_friday() const { return find_day("last", "Friday"); }
int scheduler::last_saturday() const { return find_day("last", "Saturday"); }
int scheduler::last_sunday() const { return find_day("last", "Sunday"); }

}  // namespace meetup
