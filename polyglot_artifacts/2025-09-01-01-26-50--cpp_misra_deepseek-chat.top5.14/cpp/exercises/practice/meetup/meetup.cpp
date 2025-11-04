#include "meetup.h"
#include <ctime>
#include <string>
#include <map>
#include <functional>
#include <vector>
#include <cstdint>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

std::tm scheduler::find_impl(const std::string& week, const std::string& weekday) const {
    // Map weekdays to tm_wday values (Sunday = 0)
    std::map<std::string, int32_t> weekday_map = {
        {"Sunday", 0}, {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3},
        {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}
    };
    
    // Get the target weekday
    int32_t target_wday = weekday_map[weekday];
    
    // Helper function to check if a day matches the target weekday
    std::function<bool(int32_t)> is_target_weekday = [&](int32_t day) -> bool {
        std::tm time_in = {};
        time_in.tm_year = year_ - 1900;
        time_in.tm_mon = month_ - 1;
        time_in.tm_mday = static_cast<int>(day);
        time_in.tm_hour = 12;
        std::mktime(&time_in);
        return (time_in.tm_wday == target_wday);
    };
    
    // Handle teenth case
    if (week == "teenth") {
        for (int32_t day = 13; day <= 19; ++day) {
            if (is_target_weekday(day)) {
                std::tm result = {};
                result.tm_year = year_ - 1900;
                result.tm_mon = month_ - 1;
                result.tm_mday = static_cast<int>(day);
                return result;
            }
        }
    }
    
    // For first, second, third, fourth, last
    // Find all matching weekdays in the month
    std::vector<int32_t> matching_days;
    // Check up to 31 days
    for (int32_t day = 1; day <= 31; ++day) {
        std::tm time_in = {};
        time_in.tm_year = year_ - 1900;
        time_in.tm_mon = month_ - 1;
        time_in.tm_mday = static_cast<int>(day);
        time_in.tm_hour = 12;
        // Normalize the time
        std::mktime(&time_in);
        // Check if we're still in the same month
        if (time_in.tm_mon != (month_ - 1)) {
            break;
        }
        if (time_in.tm_wday == target_wday) {
            matching_days.push_back(day);
        }
    }
    
    std::map<std::string, int32_t> week_index_map = {
        {"first", 0}, {"second", 1}, {"third", 2}, {"fourth", 3}
    };
    
    int32_t index;
    if (week == "last") {
        index = static_cast<int32_t>(matching_days.size()) - 1;
    } else {
        index = week_index_map[week];
    }
    int32_t result_day = matching_days.at(index);
    
    std::tm result = {};
    result.tm_year = year_ - 1900;
    result.tm_mon = month_ - 1;
    result.tm_mday = static_cast<int>(result_day);
    return result;
}

// Teenth methods
std::tm scheduler::monteenth() const { return find_impl("teenth", "Monday"); }
std::tm scheduler::tuesteenth() const { return find_impl("teenth", "Tuesday"); }
std::tm scheduler::wednesteenth() const { return find_impl("teenth", "Wednesday"); }
std::tm scheduler::thursteenth() const { return find_impl("teenth", "Thursday"); }
std::tm scheduler::friteenth() const { return find_impl("teenth", "Friday"); }
std::tm scheduler::saturteenth() const { return find_impl("teenth", "Saturday"); }
std::tm scheduler::sunteenth() const { return find_impl("teenth", "Sunday"); }

// First week methods
std::tm scheduler::first_monday() const { return find_impl("first", "Monday"); }
std::tm scheduler::first_tuesday() const { return find_impl("first", "Tuesday"); }
std::tm scheduler::first_wednesday() const { return find_impl("first", "Wednesday"); }
std::tm scheduler::first_thursday() const { return find_impl("first", "Thursday"); }
std::tm scheduler::first_friday() const { return find_impl("first", "Friday"); }
std::tm scheduler::first_saturday() const { return find_impl("first", "Saturday"); }
std::tm scheduler::first_sunday() const { return find_impl("first", "Sunday"); }

// Second week methods
std::tm scheduler::second_monday() const { return find_impl("second", "Monday"); }
std::tm scheduler::second_tuesday() const { return find_impl("second", "Tuesday"); }
std::tm scheduler::second_wednesday() const { return find_impl("second", "Wednesday"); }
std::tm scheduler::second_thursday() const { return find_impl("second", "Thursday"); }
std::tm scheduler::second_friday() const { return find_impl("second", "Friday"); }
std::tm scheduler::second_saturday() const { return find_impl("second", "Saturday"); }
std::tm scheduler::second_sunday() const { return find_impl("second", "Sunday"); }

// Third week methods
std::tm scheduler::third_monday() const { return find_impl("third", "Monday"); }
std::tm scheduler::third_tuesday() const { return find_impl("third", "Tuesday"); }
std::tm scheduler::third_wednesday() const { return find_impl("third", "Wednesday"); }
std::tm scheduler::third_thursday() const { return find_impl("third", "Thursday"); }
std::tm scheduler::third_friday() const { return find_impl("third", "Friday"); }
std::tm scheduler::third_saturday() const { return find_impl("third", "Saturday"); }
std::tm scheduler::third_sunday() const { return find_impl("third", "Sunday"); }

// Fourth week methods
std::tm scheduler::fourth_monday() const { return find_impl("fourth", "Monday"); }
std::tm scheduler::fourth_tuesday() const { return find_impl("fourth", "Tuesday"); }
std::tm scheduler::fourth_wednesday() const { return find_impl("fourth", "Wednesday"); }
std::tm scheduler::fourth_thursday() const { return find_impl("fourth", "Thursday"); }
std::tm scheduler::fourth_friday() const { return find_impl("fourth", "Friday"); }
std::tm scheduler::fourth_saturday() const { return find_impl("fourth", "Saturday"); }
std::tm scheduler::fourth_sunday() const { return find_impl("fourth", "Sunday"); }

// Last week methods
std::tm scheduler::last_monday() const { return find_impl("last", "Monday"); }
std::tm scheduler::last_tuesday() const { return find_impl("last", "Tuesday"); }
std::tm scheduler::last_wednesday() const { return find_impl("last", "Wednesday"); }
std::tm scheduler::last_thursday() const { return find_impl("last", "Thursday"); }
std::tm scheduler::last_friday() const { return find_impl("last", "Friday"); }
std::tm scheduler::last_saturday() const { return find_impl("last", "Saturday"); }
std::tm scheduler::last_sunday() const { return find_impl("last", "Sunday"); }

}  // namespace meetup
