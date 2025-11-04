#include "meetup.h"
#include <ctime>
#include <string>
#include <stdexcept>
#include <cstring>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper function to find the day
std::tm scheduler::find_day(int year, int month, const char* weekday, const char* which) const {
    // Parse which
    int week_offset;
    bool is_teenth = (std::string(which) == "teenth");
    
    if (is_teenth) {
        week_offset = 1; // We'll search between days 13-19
    } else if (std::string(which) == "first") {
        week_offset = 0;
    } else if (std::string(which) == "second") {
        week_offset = 1;
    } else if (std::string(which) == "third") {
        week_offset = 2;
    } else if (std::string(which) == "fourth") {
        week_offset = 3;
    } else if (std::string(which) == "last") {
        week_offset = 4; // Handle last separately
    } else {
        throw std::runtime_error("Invalid week specification");
    }
    
    // Parse weekday
    int target_wday;
    if (std::strcmp(weekday, "Monday") == 0) target_wday = 1;
    else if (std::strcmp(weekday, "Tuesday") == 0) target_wday = 2;
    else if (std::strcmp(weekday, "Wednesday") == 0) target_wday = 3;
    else if (std::strcmp(weekday, "Thursday") == 0) target_wday = 4;
    else if (std::strcmp(weekday, "Friday") == 0) target_wday = 5;
    else if (std::strcmp(weekday, "Saturday") == 0) target_wday = 6;
    else if (std::strcmp(weekday, "Sunday") == 0) target_wday = 0;
    else throw std::runtime_error("Invalid weekday");
    
    // Set up initial date
    std::tm time_in = {0};
    time_in.tm_year = year - 1900;
    time_in.tm_mon = month - 1;
    time_in.tm_mday = 1;
    time_in.tm_isdst = -1;
    
    // Normalize and get the first day of the month
    std::mktime(&time_in);
    
    // Find the first occurrence of the target weekday
    int days_to_add = (target_wday - time_in.tm_wday + 7) % 7;
    time_in.tm_mday += days_to_add;
    
    if (is_teenth) {
        // Adjust until day is between 13-19
        while (time_in.tm_mday < 13) {
            time_in.tm_mday += 7;
        }
    } else if (std::string(which) == "last") {
        // Move to the last week
        time_in.tm_mday += 28; // Move to potential last occurrence
        std::mktime(&time_in);
        // If we're in the next month, step back 7 days
        if (time_in.tm_mon != month - 1) {
            time_in.tm_mday -= 7;
        }
        std::mktime(&time_in);
    } else {
        // Add weeks according to the offset
        time_in.tm_mday += 7 * week_offset;
        std::mktime(&time_in);
        // Check if we're still in the same month
        if (time_in.tm_mon != month - 1) {
            throw std::runtime_error("Invalid date found");
        }
    }
    
    return time_in;
}

// Implement all interface methods
// Teenth days
std::tm scheduler::monteenth() const { return find_day(year_, month_, "Monday", "teenth"); }
std::tm scheduler::tuesteenth() const { return find_day(year_, month_, "Tuesday", "teenth"); }
std::tm scheduler::wednesteenth() const { return find_day(year_, month_, "Wednesday", "teenth"); }
std::tm scheduler::thursteenth() const { return find_day(year_, month_, "Thursday", "teenth"); }
std::tm scheduler::friteenth() const { return find_day(year_, month_, "Friday", "teenth"); }
std::tm scheduler::saturteenth() const { return find_day(year_, month_, "Saturday", "teenth"); }
std::tm scheduler::sunteenth() const { return find_day(year_, month_, "Sunday", "teenth"); }

// First week days
std::tm scheduler::first_monday() const { return find_day(year_, month_, "Monday", "first"); }
std::tm scheduler::first_tuesday() const { return find_day(year_, month_, "Tuesday", "first"); }
std::tm scheduler::first_wednesday() const { return find_day(year_, month_, "Wednesday", "first"); }
std::tm scheduler::first_thursday() const { return find_day(year_, month_, "Thursday", "first"); }
std::tm scheduler::first_friday() const { return find_day(year_, month_, "Friday", "first"); }
std::tm scheduler::first_saturday() const { return find_day(year_, month_, "Saturday", "first"); }
std::tm scheduler::first_sunday() const { return find_day(year_, month_, "Sunday", "first"); }

// Second week days
std::tm scheduler::second_monday() const { return find_day(year_, month_, "Monday", "second"); }
std::tm scheduler::second_tuesday() const { return find_day(year_, month_, "Tuesday", "second"); }
std::tm scheduler::second_wednesday() const { return find_day(year_, month_, "Wednesday", "second"); }
std::tm scheduler::second_thursday() const { return find_day(year_, month_, "Thursday", "second"); }
std::tm scheduler::second_friday() const { return find_day(year_, month_, "Friday", "second"); }
std::tm scheduler::second_saturday() const { return find_day(year_, month_, "Saturday", "second"); }
std::tm scheduler::second_sunday() const { return find_day(year_, month_, "Sunday", "second"); }

// Third week days
std::tm scheduler::third_monday() const { return find_day(year_, month_, "Monday", "third"); }
std::tm scheduler::third_tuesday() const { return find_day(year_, month_, "Tuesday", "third"); }
std::tm scheduler::third_wednesday() const { return find_day(year_, month_, "Wednesday", "third"); }
std::tm scheduler::third_thursday() const { return find_day(year_, month_, "Thursday", "third"); }
std::tm scheduler::third_friday() const { return find_day(year_, month_, "Friday", "third"); }
std::tm scheduler::third_saturday() const { return find_day(year_, month_, "Saturday", "third"); }
std::tm scheduler::third_sunday() const { return find_day(year_, month_, "Sunday", "third"); }

// Fourth week days
std::tm scheduler::fourth_monday() const { return find_day(year_, month_, "Monday", "fourth"); }
std::tm scheduler::fourth_tuesday() const { return find_day(year_, month_, "Tuesday", "fourth"); }
std::tm scheduler::fourth_wednesday() const { return find_day(year_, month_, "Wednesday", "fourth"); }
std::tm scheduler::fourth_thursday() const { return find_day(year_, month_, "Thursday", "fourth"); }
std::tm scheduler::fourth_friday() const { return find_day(year_, month_, "Friday", "fourth"); }
std::tm scheduler::fourth_saturday() const { return find_day(year_, month_, "Saturday", "fourth"); }
std::tm scheduler::fourth_sunday() const { return find_day(year_, month_, "Sunday", "fourth"); }

// Last week days
std::tm scheduler::last_monday() const { return find_day(year_, month_, "Monday", "last"); }
std::tm scheduler::last_tuesday() const { return find_day(year_, month_, "Tuesday", "last"); }
std::tm scheduler::last_wednesday() const { return find_day(year_, month_, "Wednesday", "last"); }
std::tm scheduler::last_thursday() const { return find_day(year_, month_, "Thursday", "last"); }
std::tm scheduler::last_friday() const { return find_day(year_, month_, "Friday", "last"); }
std::tm scheduler::last_saturday() const { return find_day(year_, month_, "Saturday", "last"); }
std::tm scheduler::last_sunday() const { return find_day(year_, month_, "Sunday", "last"); }

}  // namespace meetup
