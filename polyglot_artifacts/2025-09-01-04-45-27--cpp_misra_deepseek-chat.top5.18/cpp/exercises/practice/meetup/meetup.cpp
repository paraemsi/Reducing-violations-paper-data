#include "meetup.h"
#include <cstdint>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>
#include <array>
#include <unordered_map>

namespace meetup {

namespace {

std::int32_t zeller(std::int32_t year, std::int32_t month, std::int32_t day) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    std::int32_t k = year % 100;
    std::int32_t j = year / 100;
    std::int32_t h = (day + ((13 * (month + 1)) / 5) + k + (k / 4) + (j / 4) + (5 * j)) % 7;
    // Convert to day where 0=Saturday, 1=Sunday, ... 6=Friday
    return ((h + 5) % 7);
}

std::int32_t weekday_to_int(const std::string& weekday) {
    if (weekday == "Monday") return 1;
    if (weekday == "Tuesday") return 2;
    if (weekday == "Wednesday") return 3;
    if (weekday == "Thursday") return 4;
    if (weekday == "Friday") return 5;
    if (weekday == "Saturday") return 6;
    if (weekday == "Sunday") return 0;
    throw std::runtime_error("Invalid weekday");
}

std::vector<std::int32_t> get_days_in_month(std::int32_t year, std::int32_t month) {
    static const std::array<std::int32_t, 13> days_in_month = {
        0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    
    std::int32_t days = days_in_month[month];
    // Check for leap year (February)
    if (month == 2) {
        if (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0))) {
            days = 29;
        }
    }
    std::vector<std::int32_t> result;
    for (std::int32_t day = 1; day <= days; ++day) {
        result.push_back(day);
    }
    return result;
}

}  // namespace

scheduler::scheduler(std::int32_t year, std::int32_t month)
    : year_(year), month_(month) {
}

// Helper function to find the nth occurrence of a weekday
Date scheduler::find_nth_weekday(const std::string& weekday, std::int32_t n) const {
    std::int32_t target_weekday = weekday_to_int(weekday);
    auto days = get_days_in_month(year_, month_);
    std::vector<std::int32_t> matching_days;
    
    for (auto day : days) {
        if ((zeller(year_, month_, day) == target_weekday)) {
            matching_days.push_back(day);
        }
    }
    return Date{year_, month_, matching_days[n - 1]};
}

// Helper function to find teenth day
Date scheduler::find_teenth(const std::string& weekday) const {
    std::int32_t target_weekday = weekday_to_int(weekday);
    auto days = get_days_in_month(year_, month_);
    
    for (auto day : days) {
        if ((day >= 13) && (day <= 19)) {
            if ((zeller(year_, month_, day) == target_weekday)) {
                return Date{year_, month_, day};
            }
        }
    }
    throw std::runtime_error("Teenth day not found");
}

// Helper function to find last occurrence
Date scheduler::find_last(const std::string& weekday) const {
    std::int32_t target_weekday = weekday_to_int(weekday);
    auto days = get_days_in_month(year_, month_);
    std::vector<std::int32_t> matching_days;
    
    for (auto day : days) {
        if ((zeller(year_, month_, day) == target_weekday)) {
            matching_days.push_back(day);
        }
    }
    return Date{year_, month_, matching_days.back()};
}

// Implement all the interface functions
// Teenth implementations
Date scheduler::monteenth() const { return find_teenth("Monday"); }
Date scheduler::tuesteenth() const { return find_teenth("Tuesday"); }
Date scheduler::wednesteenth() const { return find_teenth("Wednesday"); }
Date scheduler::thursteenth() const { return find_teenth("Thursday"); }
Date scheduler::friteenth() const { return find_teenth("Friday"); }
Date scheduler::saturteenth() const { return find_teenth("Saturday"); }
Date scheduler::sunteenth() const { return find_teenth("Sunday"); }

// First implementations
Date scheduler::first_monday() const { return find_nth_weekday("Monday", 1); }
Date scheduler::first_tuesday() const { return find_nth_weekday("Tuesday", 1); }
Date scheduler::first_wednesday() const { return find_nth_weekday("Wednesday", 1); }
Date scheduler::first_thursday() const { return find_nth_weekday("Thursday", 1); }
Date scheduler::first_friday() const { return find_nth_weekday("Friday", 1); }
Date scheduler::first_saturday() const { return find_nth_weekday("Saturday", 1); }
Date scheduler::first_sunday() const { return find_nth_weekday("Sunday", 1); }

// Second implementations
Date scheduler::second_monday() const { return find_nth_weekday("Monday", 2); }
Date scheduler::second_tuesday() const { return find_nth_weekday("Tuesday", 2); }
Date scheduler::second_wednesday() const { return find_nth_weekday("Wednesday", 2); }
Date scheduler::second_thursday() const { return find_nth_weekday("Thursday", 2); }
Date scheduler::second_friday() const { return find_nth_weekday("Friday", 2); }
Date scheduler::second_saturday() const { return find_nth_weekday("Saturday", 2); }
Date scheduler::second_sunday() const { return find_nth_weekday("Sunday", 2); }

// Third implementations
Date scheduler::third_monday() const { return find_nth_weekday("Monday", 3); }
Date scheduler::third_tuesday() const { return find_nth_weekday("Tuesday", 3); }
Date scheduler::third_wednesday() const { return find_nth_weekday("Wednesday", 3); }
Date scheduler::third_thursday() const { return find_nth_weekday("Thursday", 3); }
Date scheduler::third_friday() const { return find_nth_weekday("Friday", 3); }
Date scheduler::third_saturday() const { return find_nth_weekday("Saturday", 3); }
Date scheduler::third_sunday() const { return find_nth_weekday("Sunday", 3); }

// Fourth implementations
Date scheduler::fourth_monday() const { return find_nth_weekday("Monday", 4); }
Date scheduler::fourth_tuesday() const { return find_nth_weekday("Tuesday", 4); }
Date scheduler::fourth_wednesday() const { return find_nth_weekday("Wednesday", 4); }
Date scheduler::fourth_thursday() const { return find_nth_weekday("Thursday", 4); }
Date scheduler::fourth_friday() const { return find_nth_weekday("Friday", 4); }
Date scheduler::fourth_saturday() const { return find_nth_weekday("Saturday", 4); }
Date scheduler::fourth_sunday() const { return find_nth_weekday("Sunday", 4); }

// Last implementations
Date scheduler::last_monday() const { return find_last("Monday"); }
Date scheduler::last_tuesday() const { return find_last("Tuesday"); }
Date scheduler::last_wednesday() const { return find_last("Wednesday"); }
Date scheduler::last_thursday() const { return find_last("Thursday"); }
Date scheduler::last_friday() const { return find_last("Friday"); }
Date scheduler::last_saturday() const { return find_last("Saturday"); }
Date scheduler::last_sunday() const { return find_last("Sunday"); }

}  // namespace meetup
