#include "meetup.h"
#include <string>
#include <ctime>
#include <map>
#include <stdexcept>
#include <vector>
#include <algorithm>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper function to find a specific occurrence
std::tm scheduler::find_occurrence(const std::string& week, int target_wday) const {
    // Find all dates that match the target weekday in the month
    std::vector<int> matching_days;
    
    // Start from the first day of the month
    std::tm timeinfo = {};
    timeinfo.tm_year = year_ - 1900;
    timeinfo.tm_mon = month_ - 1;
    timeinfo.tm_mday = 1;
    timeinfo.tm_hour = 0;
    timeinfo.tm_min = 0;
    timeinfo.tm_sec = 0;
    timeinfo.tm_isdst = -1;
    
    // Normalize to get the weekday of the first day
    std::mktime(&timeinfo);
    
    // Iterate through all days in the month
    int original_month = month_ - 1;
    while (timeinfo.tm_mon == original_month) {
        if (timeinfo.tm_wday == target_wday) {
            matching_days.push_back(timeinfo.tm_mday);
        }
        // Move to next day
        timeinfo.tm_mday++;
        std::mktime(&timeinfo);
    }
    
    // Determine which day to pick based on the week parameter
    int selected_day;
    if (week == "first") {
        selected_day = matching_days[0];
    } else if (week == "second") {
        selected_day = matching_days[1];
    } else if (week == "third") {
        selected_day = matching_days[2];
    } else if (week == "fourth") {
        selected_day = matching_days[3];
    } else if (week == "last") {
        selected_day = matching_days.back();
    } else if (week == "teenth") {
        // Find the day that's between 13 and 19 inclusive
        for (int day : matching_days) {
            if (day >= 13 && day <= 19) {
                selected_day = day;
                break;
            }
        }
    } else {
        throw std::invalid_argument("Invalid week specification");
    }
    
    // Create the result tm struct
    std::tm result = {};
    result.tm_year = year_ - 1900;
    result.tm_mon = month_ - 1;
    result.tm_mday = selected_day;
    result.tm_hour = 0;
    result.tm_min = 0;
    result.tm_sec = 0;
    result.tm_isdst = -1;
    std::mktime(&result);
    
    return result;
}

// Teenth functions
std::tm scheduler::monteenth() const { return find_occurrence("teenth", 1); }
std::tm scheduler::tuesteenth() const { return find_occurrence("teenth", 2); }
std::tm scheduler::wednesteenth() const { return find_occurrence("teenth", 3); }
std::tm scheduler::thursteenth() const { return find_occurrence("teenth", 4); }
std::tm scheduler::friteenth() const { return find_occurrence("teenth", 5); }
std::tm scheduler::saturteenth() const { return find_occurrence("teenth", 6); }
std::tm scheduler::sunteenth() const { return find_occurrence("teenth", 0); }

// First week functions
std::tm scheduler::first_monday() const { return find_occurrence("first", 1); }
std::tm scheduler::first_tuesday() const { return find_occurrence("first", 2); }
std::tm scheduler::first_wednesday() const { return find_occurrence("first", 3); }
std::tm scheduler::first_thursday() const { return find_occurrence("first", 4); }
std::tm scheduler::first_friday() const { return find_occurrence("first", 5); }
std::tm scheduler::first_saturday() const { return find_occurrence("first", 6); }
std::tm scheduler::first_sunday() const { return find_occurrence("first", 0); }

// Second week functions
std::tm scheduler::second_monday() const { return find_occurrence("second", 1); }
std::tm scheduler::second_tuesday() const { return find_occurrence("second", 2); }
std::tm scheduler::second_wednesday() const { return find_occurrence("second", 3); }
std::tm scheduler::second_thursday() const { return find_occurrence("second", 4); }
std::tm scheduler::second_friday() const { return find_occurrence("second", 5); }
std::tm scheduler::second_saturday() const { return find_occurrence("second", 6); }
std::tm scheduler::second_sunday() const { return find_occurrence("second", 0); }

// Third week functions
std::tm scheduler::third_monday() const { return find_occurrence("third", 1); }
std::tm scheduler::third_tuesday() const { return find_occurrence("third", 2); }
std::tm scheduler::third_wednesday() const { return find_occurrence("third", 3); }
std::tm scheduler::third_thursday() const { return find_occurrence("third", 4); }
std::tm scheduler::third_friday() const { return find_occurrence("third", 5); }
std::tm scheduler::third_saturday() const { return find_occurrence("third", 6); }
std::tm scheduler::third_sunday() const { return find_occurrence("third", 0); }

// Fourth week functions
std::tm scheduler::fourth_monday() const { return find_occurrence("fourth", 1); }
std::tm scheduler::fourth_tuesday() const { return find_occurrence("fourth", 2); }
std::tm scheduler::fourth_wednesday() const { return find_occurrence("fourth", 3); }
std::tm scheduler::fourth_thursday() const { return find_occurrence("fourth", 4); }
std::tm scheduler::fourth_friday() const { return find_occurrence("fourth", 5); }
std::tm scheduler::fourth_saturday() const { return find_occurrence("fourth", 6); }
std::tm scheduler::fourth_sunday() const { return find_occurrence("fourth", 0); }

// Last week functions
std::tm scheduler::last_monday() const { return find_occurrence("last", 1); }
std::tm scheduler::last_tuesday() const { return find_occurrence("last", 2); }
std::tm scheduler::last_wednesday() const { return find_occurrence("last", 3); }
std::tm scheduler::last_thursday() const { return find_occurrence("last", 4); }
std::tm scheduler::last_friday() const { return find_occurrence("last", 5); }
std::tm scheduler::last_saturday() const { return find_occurrence("last", 6); }
std::tm scheduler::last_sunday() const { return find_occurrence("last", 0); }

}  // namespace meetup
