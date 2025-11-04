#include "meetup.h"
#include <chrono>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <stdexcept>
#include <iostream>

namespace meetup {

using namespace std::chrono;

scheduler::scheduler(int year, int month)
    : year_(year), month_(month) {
}

year_month_day scheduler::find_date(const std::string& week, const std::string& weekday) const {
    // Map week strings to indices
    static const std::map<std::string, int> week_map{
        {"first", 0}, {"second", 1}, {"third", 2}, {"fourth", 3}, {"last", -1}, {"teenth", -2}
    };
    
    // Map weekday strings to weekday (chrono uses Sunday=0 to Saturday=6)
    static const std::map<std::string, weekday> weekday_map{
        {"Monday", weekday{1}}, {"Tuesday", weekday{2}}, {"Wednesday", weekday{3}},
        {"Thursday", weekday{4}}, {"Friday", weekday{5}}, {"Saturday", weekday{6}},
        {"Sunday", weekday{0}}
    };
    
    // Get the first day of the month
    auto yml = year{year_} / month{month_} / day{1};
    sys_days current_day = sys_days(yml);
    
    // Find all matching weekdays in the month
    std::vector<year_month_day> matching_days;
    auto current_month = month{month_};
    
    while (year_month_day{current_day}.month() == current_month) {
        weekday current_weekday = year_month_weekday{current_day}.weekday();
        if (current_weekday == weekday_map.at(weekday)) {
            matching_days.push_back(year_month_day{current_day});
        }
        current_day += days{1};
    }
    
    int index = week_map.at(week);
    if (index == -2) {  // teenth
        for (const auto& day : matching_days) {
            unsigned d = static_cast<unsigned>(day.day());
            if ((d >= 13) && (d <= 19)) {
                return day;
            }
        }
    } else if (index >= 0) {
        // Check if the index is valid
        if (index < static_cast<int>(matching_days.size())) {
            return matching_days[index];
        }
    } else {
        if (!matching_days.empty()) {
            return matching_days.back();
        }
    }
    
    throw std::runtime_error("No valid date found");
}

// Implement all the interface functions
// For teenth functions, we need to map to the correct weekday names
#define IMPLEMENT_TEENTH(short_name, full_name) \
    year_month_day scheduler::short_name##teenth() const { \
        return find_date("teenth", full_name); \
    }

#define IMPLEMENT_WEEK(prefix, day_name) \
    year_month_day scheduler::prefix##_##day_name() const { \
        return find_date(#prefix, #day_name); \
    }

IMPLEMENT_TEENTH(mon, "Monday")
IMPLEMENT_TEENTH(tues, "Tuesday")
IMPLEMENT_TEENTH(wednes, "Wednesday")
IMPLEMENT_TEENTH(thurs, "Thursday")
IMPLEMENT_TEENTH(fri, "Friday")
IMPLEMENT_TEENTH(satur, "Saturday")
IMPLEMENT_TEENTH(sun, "Sunday")

IMPLEMENT_WEEK(first, Monday)
IMPLEMENT_WEEK(first, Tuesday)
IMPLEMENT_WEEK(first, Wednesday)
IMPLEMENT_WEEK(first, Thursday)
IMPLEMENT_WEEK(first, Friday)
IMPLEMENT_WEEK(first, Saturday)
IMPLEMENT_WEEK(first, Sunday)

IMPLEMENT_WEEK(second, Monday)
IMPLEMENT_WEEK(second, Tuesday)
IMPLEMENT_WEEK(second, Wednesday)
IMPLEMENT_WEEK(second, Thursday)
IMPLEMENT_WEEK(second, Friday)
IMPLEMENT_WEEK(second, Saturday)
IMPLEMENT_WEEK(second, Sunday)

IMPLEMENT_WEEK(third, Monday)
IMPLEMENT_WEEK(third, Tuesday)
IMPLEMENT_WEEK(third, Wednesday)
IMPLEMENT_WEEK(third, Thursday)
IMPLEMENT_WEEK(third, Friday)
IMPLEMENT_WEEK(third, Saturday)
IMPLEMENT_WEEK(third, Sunday)

IMPLEMENT_WEEK(fourth, Monday)
IMPLEMENT_WEEK(fourth, Tuesday)
IMPLEMENT_WEEK(fourth, Wednesday)
IMPLEMENT_WEEK(fourth, Thursday)
IMPLEMENT_WEEK(fourth, Friday)
IMPLEMENT_WEEK(fourth, Saturday)
IMPLEMENT_WEEK(fourth, Sunday)

IMPLEMENT_WEEK(last, Monday)
IMPLEMENT_WEEK(last, Tuesday)
IMPLEMENT_WEEK(last, Wednesday)
IMPLEMENT_WEEK(last, Thursday)
IMPLEMENT_WEEK(last, Friday)
IMPLEMENT_WEEK(last, Saturday)
IMPLEMENT_WEEK(last, Sunday)

}  // namespace meetup
