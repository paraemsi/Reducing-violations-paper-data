#include "meetup.h"
#include <map>
#include <stdexcept>
#include <string>
#include <cstdint>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

std::tm scheduler::find_date(int week_num, int target_weekday) const {
    std::tm time_in = {};
    time_in.tm_year = year_ - 1900;
    time_in.tm_mon = month_ - 1;
    time_in.tm_mday = 1;
    time_in.tm_hour = 12;
    time_in.tm_isdst = -1;
    
    // Normalize to get the weekday of the first day of the month
    std::mktime(&time_in);
    
    // Find the first occurrence of the target weekday
    int day_delta = (target_weekday - time_in.tm_wday + 7) % 7;
    time_in.tm_mday += day_delta;
    std::mktime(&time_in);
    
    if (week_num == 5) { // teenth
        // Ensure the date is between 13-19
        if (time_in.tm_mday < 13) {
            time_in.tm_mday += 7;
            std::mktime(&time_in);
        }
        // It should now be between 13-19
    } else if (week_num >= 0 && week_num <= 3) { // first through fourth
        time_in.tm_mday += week_num * 7;
        std::mktime(&time_in);
    } else if (week_num == 4) { // last
        // Start from the last day of the month
        // First, find the number of days in the month
        // Move to next month, then set day to 0 to get last day of current month
        std::tm temp = time_in;
        temp.tm_mon = month_; // Next month
        temp.tm_mday = 0;
        std::mktime(&temp);
        int last_day = temp.tm_mday;
        
        // Find the last occurrence which is within 6 days of the last day
        // Start from the last day and find the target weekday
        temp.tm_mday = last_day;
        std::mktime(&temp);
        int delta = (temp.tm_wday - target_weekday + 7) % 7;
        temp.tm_mday -= delta;
        std::mktime(&temp);
        return temp;
    }
    
    // Make sure the date is valid and in the correct month
    // For cases where adding weeks might push into the next month, we need to adjust
    // For example, if the first occurrence is on the 7th, adding 7*3=21 days would be the 28th which may be valid
    // But if the month has fewer days, it could be invalid
    std::mktime(&time_in);
    
    // Check if we're still in the same month
    if (time_in.tm_mon != month_ - 1) {
        // For non-last cases, this shouldn't happen according to the problem statement
        // Adjust to find the correct date
        // For teenth, it's always between 13-19, so it should be in the same month
        // For first through fourth, we need to find a valid approach
        // Let's find the last occurrence in the month
        std::tm temp = time_in;
        temp.tm_mon = month_; // Next month
        temp.tm_mday = 0;
        std::mktime(&temp);
        int last_day = temp.tm_mday;
        
        // Find the target weekday on or before the last day
        temp.tm_mday = last_day;
        std::mktime(&temp);
        int delta = (temp.tm_wday - target_weekday + 7) % 7;
        temp.tm_mday -= delta;
        std::mktime(&temp);
        return temp;
    }
    return time_in;
}

// Implement all the member functions
// Teenth functions
std::tm scheduler::monteenth() const { return find_date(5, 1); }
std::tm scheduler::tuesteenth() const { return find_date(5, 2); }
std::tm scheduler::wednesteenth() const { return find_date(5, 3); }
std::tm scheduler::thursteenth() const { return find_date(5, 4); }
std::tm scheduler::friteenth() const { return find_date(5, 5); }
std::tm scheduler::saturteenth() const { return find_date(5, 6); }
std::tm scheduler::sunteenth() const { return find_date(5, 0); }

// First week
std::tm scheduler::first_monday() const { return find_date(0, 1); }
std::tm scheduler::first_tuesday() const { return find_date(0, 2); }
std::tm scheduler::first_wednesday() const { return find_date(0, 3); }
std::tm scheduler::first_thursday() const { return find_date(0, 4); }
std::tm scheduler::first_friday() const { return find_date(0, 5); }
std::tm scheduler::first_saturday() const { return find_date(0, 6); }
std::tm scheduler::first_sunday() const { return find_date(0, 0); }

// Second week
std::tm scheduler::second_monday() const { return find_date(1, 1); }
std::tm scheduler::second_tuesday() const { return find_date(1, 2); }
std::tm scheduler::second_wednesday() const { return find_date(1, 3); }
std::tm scheduler::second_thursday() const { return find_date(1, 4); }
std::tm scheduler::second_friday() const { return find_date(1, 5); }
std::tm scheduler::second_saturday() const { return find_date(1, 6); }
std::tm scheduler::second_sunday() const { return find_date(1, 0); }

// Third week
std::tm scheduler::third_monday() const { return find_date(2, 1); }
std::tm scheduler::third_tuesday() const { return find_date(2, 2); }
std::tm scheduler::third_wednesday() const { return find_date(2, 3); }
std::tm scheduler::third_thursday() const { return find_date(2, 4); }
std::tm scheduler::third_friday() const { return find_date(2, 5); }
std::tm scheduler::third_saturday() const { return find_date(2, 6); }
std::tm scheduler::third_sunday() const { return find_date(2, 0); }

// Fourth week
std::tm scheduler::fourth_monday() const { return find_date(3, 1); }
std::tm scheduler::fourth_tuesday() const { return find_date(3, 2); }
std::tm scheduler::fourth_wednesday() const { return find_date(3, 3); }
std::tm scheduler::fourth_thursday() const { return find_date(3, 4); }
std::tm scheduler::fourth_friday() const { return find_date(3, 5); }
std::tm scheduler::fourth_saturday() const { return find_date(3, 6); }
std::tm scheduler::fourth_sunday() const { return find_date(3, 0); }

// Last week
std::tm scheduler::last_monday() const { return find_date(4, 1); }
std::tm scheduler::last_tuesday() const { return find_date(4, 2); }
std::tm scheduler::last_wednesday() const { return find_date(4, 3); }
std::tm scheduler::last_thursday() const { return find_date(4, 4); }
std::tm scheduler::last_friday() const { return find_date(4, 5); }
std::tm scheduler::last_saturday() const { return find_date(4, 6); }
std::tm scheduler::last_sunday() const { return find_date(4, 0); }

}  // namespace meetup
