#include "meetup.h"
#include <ctime>
#include <string>
#include <stdexcept>
#include <map>
#include <functional>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

std::tm scheduler::find_date(int week_offset, int target_weekday) const {
    // Get the first day of the month
    std::tm timeinfo = {};
    timeinfo.tm_year = year_ - 1900;
    timeinfo.tm_mon = month_ - 1;
    timeinfo.tm_mday = 1;
    timeinfo.tm_hour = 12;
    timeinfo.tm_isdst = -1;
    mktime(&timeinfo);
    
    // Find the first occurrence of the target weekday
    int day_delta = (target_weekday - timeinfo.tm_wday + 7) % 7;
    int dayOfMonth = 1 + day_delta;
    
    if (week_offset >= 0) {
        // For first, second, third, fourth weeks
        dayOfMonth += week_offset * 7;
        // Check if the day is in the current month
        std::tm test = timeinfo;
        test.tm_mday = dayOfMonth;
        mktime(&test);
        if (test.tm_mon != timeinfo.tm_mon) {
            // Adjust to the previous week if necessary
            dayOfMonth -= 7;
        }
    } else if (week_offset == -1) { // last
        // Get the last day of the month
        std::tm lastDay = timeinfo;
        lastDay.tm_mon++;
        lastDay.tm_mday = 0;
        mktime(&lastDay);
        
        // Find the last occurrence of the target weekday
        int last_day_delta = (lastDay.tm_wday - target_weekday + 7) % 7;
        dayOfMonth = lastDay.tm_mday - last_day_delta;
        if (dayOfMonth <= 0) {
            dayOfMonth += 7;
        }
    } else if (week_offset == -2) { // teenth
        // Teenth days are always between 13 and 19, so find the first occurrence on or after the 13th
        if (dayOfMonth < 13) {
            dayOfMonth += 7;
        }
        // It should now be between 13 and 19
    }
    
    // Create and return the result
    std::tm result = {};
    result.tm_year = year_ - 1900;
    result.tm_mon = month_ - 1;
    result.tm_mday = dayOfMonth;
    result.tm_hour = 12;
    result.tm_isdst = -1;
    mktime(&result);
    return result;
}

// Teenth implementations
std::tm scheduler::monteenth() const { return find_date(-2, 1); }
std::tm scheduler::tuesteenth() const { return find_date(-2, 2); }
std::tm scheduler::wednesteenth() const { return find_date(-2, 3); }
std::tm scheduler::thursteenth() const { return find_date(-2, 4); }
std::tm scheduler::friteenth() const { return find_date(-2, 5); }
std::tm scheduler::saturteenth() const { return find_date(-2, 6); }
std::tm scheduler::sunteenth() const { return find_date(-2, 0); }

// First week implementations
std::tm scheduler::first_monday() const { return find_date(0, 1); }
std::tm scheduler::first_tuesday() const { return find_date(0, 2); }
std::tm scheduler::first_wednesday() const { return find_date(0, 3); }
std::tm scheduler::first_thursday() const { return find_date(0, 4); }
std::tm scheduler::first_friday() const { return find_date(0, 5); }
std::tm scheduler::first_saturday() const { return find_date(0, 6); }
std::tm scheduler::first_sunday() const { return find_date(0, 0); }

// Second week implementations
std::tm scheduler::second_monday() const { return find_date(1, 1); }
std::tm scheduler::second_tuesday() const { return find_date(1, 2); }
std::tm scheduler::second_wednesday() const { return find_date(1, 3); }
std::tm scheduler::second_thursday() const { return find_date(1, 4); }
std::tm scheduler::second_friday() const { return find_date(1, 5); }
std::tm scheduler::second_saturday() const { return find_date(1, 6); }
std::tm scheduler::second_sunday() const { return find_date(1, 0); }

// Third week implementations
std::tm scheduler::third_monday() const { return find_date(2, 1); }
std::tm scheduler::third_tuesday() const { return find_date(2, 2); }
std::tm scheduler::third_wednesday() const { return find_date(2, 3); }
std::tm scheduler::third_thursday() const { return find_date(2, 4); }
std::tm scheduler::third_friday() const { return find_date(2, 5); }
std::tm scheduler::third_saturday() const { return find_date(2, 6); }
std::tm scheduler::third_sunday() const { return find_date(2, 0); }

// Fourth week implementations
std::tm scheduler::fourth_monday() const { return find_date(3, 1); }
std::tm scheduler::fourth_tuesday() const { return find_date(3, 2); }
std::tm scheduler::fourth_wednesday() const { return find_date(3, 3); }
std::tm scheduler::fourth_thursday() const { return find_date(3, 4); }
std::tm scheduler::fourth_friday() const { return find_date(3, 5); }
std::tm scheduler::fourth_saturday() const { return find_date(3, 6); }
std::tm scheduler::fourth_sunday() const { return find_date(3, 0); }

// Last week implementations
std::tm scheduler::last_monday() const { return find_date(-1, 1); }
std::tm scheduler::last_tuesday() const { return find_date(-1, 2); }
std::tm scheduler::last_wednesday() const { return find_date(-1, 3); }
std::tm scheduler::last_thursday() const { return find_date(-1, 4); }
std::tm scheduler::last_friday() const { return find_date(-1, 5); }
std::tm scheduler::last_saturday() const { return find_date(-1, 6); }
std::tm scheduler::last_sunday() const { return find_date(-1, 0); }

}  // namespace meetup
