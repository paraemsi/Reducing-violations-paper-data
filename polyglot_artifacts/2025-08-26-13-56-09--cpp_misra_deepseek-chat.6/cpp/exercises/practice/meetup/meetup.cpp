#include "meetup.h"
#include <chrono>
#include <string>
#include <functional>
#include <map>
#include <stdexcept>
#include <array>

using namespace std::chrono;

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper function implementation
std::chrono::year_month_day scheduler::find_date(const std::string& week, const std::string& weekday) const {
    // Map weekdays to their chrono weekday values
    static const std::map<std::string, unsigned> weekday_map = {
        {"Monday", 1},
        {"Tuesday", 2},
        {"Wednesday", 3},
        {"Thursday", 4},
        {"Friday", 5},
        {"Saturday", 6},
        {"Sunday", 7}
    };
    
    // Find the target weekday number
    auto target_weekday_it = weekday_map.find(weekday);
    if (target_weekday_it == weekday_map.end()) {
        throw std::invalid_argument("Invalid weekday");
    }
    unsigned target_weekday_num = target_weekday_it->second;
    
    // Handle teenth case
    if (week == "teenth") {
        for (int day = 13; day <= 19; day++) {
            auto candidate = year_month_day{year{year_}/month{month_}/day};
            auto wd = weekday{candidate};
            if (wd.iso_encoding() == target_weekday_num) {
                return candidate;
            }
        }
    } else {
        // Start from the first day of the month
        auto first_day = year_month_day{year{year_}/month{month_}/1};
        sys_days current = sys_days(first_day);
        
        // Find the first occurrence of the target weekday
        while (weekday{current}.iso_encoding() != target_weekday_num) {
            current += days{1};
        }
        
        // Handle first, second, third, fourth
        if (week == "first") {
            return year_month_day{current};
        } else if (week == "second") {
            return year_month_day{current + days{7}};
        } else if (week == "third") {
            return year_month_day{current + days{14}};
        } else if (week == "fourth") {
            return year_month_day{current + days{21}};
        } else if (week == "last") {
            // Move to the fourth occurrence and check if it's still in the same month
            auto fourth_occurrence = current + days{21};
            auto next_month_first = year_month_day{year{year_}/month{month_ + 1}/1};
            sys_days next_month_start = sys_days(next_month_first);
            
            // If fourth occurrence is in the next month, use third occurrence
            if (fourth_occurrence >= next_month_start) {
                return year_month_day{current + days{14}};
            } else {
                // Check if fifth occurrence is in the same month
                auto fifth_occurrence = fourth_occurrence + days{7};
                if (fifth_occurrence < next_month_start) {
                    return year_month_day{fifth_occurrence};
                } else {
                    return year_month_day{fourth_occurrence};
                }
            }
        } else {
            throw std::invalid_argument("Invalid week specifier");
        }
    }
    throw std::runtime_error("No valid date found");
}

// Implement all the interface functions
// Teenth functions
year_month_day scheduler::monteenth() const { return find_date("teenth", "Monday"); }
year_month_day scheduler::tuesteenth() const { return find_date("teenth", "Tuesday"); }
year_month_day scheduler::wednesteenth() const { return find_date("teenth", "Wednesday"); }
year_month_day scheduler::thursteenth() const { return find_date("teenth", "Thursday"); }
year_month_day scheduler::friteenth() const { return find_date("teenth", "Friday"); }
year_month_day scheduler::saturteenth() const { return find_date("teenth", "Saturday"); }
year_month_day scheduler::sunteenth() const { return find_date("teenth", "Sunday"); }

// First week functions
year_month_day scheduler::first_monday() const { return find_date("first", "Monday"); }
year_month_day scheduler::first_tuesday() const { return find_date("first", "Tuesday"); }
year_month_day scheduler::first_wednesday() const { return find_date("first", "Wednesday"); }
year_month_day scheduler::first_thursday() const { return find_date("first", "Thursday"); }
year_month_day scheduler::first_friday() const { return find_date("first", "Friday"); }
year_month_day scheduler::first_saturday() const { return find_date("first", "Saturday"); }
year_month_day scheduler::first_sunday() const { return find_date("first", "Sunday"); }

// Second week functions
year_month_day scheduler::second_monday() const { return find_date("second", "Monday"); }
year_month_day scheduler::second_tuesday() const { return find_date("second", "Tuesday"); }
year_month_day scheduler::second_wednesday() const { return find_date("second", "Wednesday"); }
year_month_day scheduler::second_thursday() const { return find_date("second", "Thursday"); }
year_month_day scheduler::second_friday() const { return find_date("second", "Friday"); }
year_month_day scheduler::second_saturday() const { return find_date("second", "Saturday"); }
year_month_day scheduler::second_sunday() const { return find_date("second", "Sunday"); }

// Third week functions
year_month_day scheduler::third_monday() const { return find_date("third", "Monday"); }
year_month_day scheduler::third_tuesday() const { return find_date("third", "Tuesday"); }
year_month_day scheduler::third_wednesday() const { return find_date("third", "Wednesday"); }
year_month_day scheduler::third_thursday() const { return find_date("third", "Thursday"); }
year_month_day scheduler::third_friday() const { return find_date("third", "Friday"); }
year_month_day scheduler::third_saturday() const { return find_date("third", "Saturday"); }
year_month_day scheduler::third_sunday() const { return find_date("third", "Sunday"); }

// Fourth week functions
year_month_day scheduler::fourth_monday() const { return find_date("fourth", "Monday"); }
year_month_day scheduler::fourth_tuesday() const { return find_date("fourth", "Tuesday"); }
year_month_day scheduler::fourth_wednesday() const { return find_date("fourth", "Wednesday"); }
year_month_day scheduler::fourth_thursday() const { return find_date("fourth", "Thursday"); }
year_month_day scheduler::fourth_friday() const { return find_date("fourth", "Friday"); }
year_month_day scheduler::fourth_saturday() const { return find_date("fourth", "Saturday"); }
year_month_day scheduler::fourth_sunday() const { return find_date("fourth", "Sunday"); }

// Last week functions
year_month_day scheduler::last_monday() const { return find_date("last", "Monday"); }
year_month_day scheduler::last_tuesday() const { return find_date("last", "Tuesday"); }
year_month_day scheduler::last_wednesday() const { return find_date("last", "Wednesday"); }
year_month_day scheduler::last_thursday() const { return find_date("last", "Thursday"); }
year_month_day scheduler::last_friday() const { return find_date("last", "Friday"); }
year_month_day scheduler::last_saturday() const { return find_date("last", "Saturday"); }
year_month_day scheduler::last_sunday() const { return find_date("last", "Sunday"); }

}  // namespace meetup
