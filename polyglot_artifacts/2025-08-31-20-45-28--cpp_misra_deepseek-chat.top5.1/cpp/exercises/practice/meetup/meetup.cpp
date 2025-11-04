#include "meetup.h"
#include <string>
#include <map>
#include <stdexcept>
#include <vector>
#include <functional>

namespace meetup {

namespace {

int day_of_week(int year, int month, int day) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int k = year % 100;
    int j = year / 100;
    int h = (day + 13*(month + 1)/5 + k + k/4 + j/4 + 5*j) % 7;
    // Convert to 0=Saturday, 1=Sunday, 2=Monday, ... 6=Friday
    // We want to map to 0=Sunday, 1=Monday, ... 6=Saturday
    return (h + 6) % 7;
}

int days_in_month(int year, int month) {
    static const std::vector<int> days = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    if (month != 2) {
        return days[month - 1];
    }
    // Check for leap year
    if (year % 4 == 0) {
        if (year % 100 == 0) {
            if (year % 400 == 0) {
                return 29;
            }
            return 28;
        }
        return 29;
    }
    return 28;
}

} // namespace

Date scheduler::find_date(const std::string& week, const std::string& day_of_week_str) const {
    // Map day names to numbers (0=Sunday, 1=Monday, ..., 6=Saturday)
    static std::map<std::string, int> day_map = {
        {"Sunday", 0},
        {"Monday", 1},
        {"Tuesday", 2},
        {"Wednesday", 3},
        {"Thursday", 4},
        {"Friday", 5},
        {"Saturday", 6}
    };
    
    int target_dow = day_map.at(day_of_week_str);
    
    // Find first day of the month's day of the week
    int first_day_dow = day_of_week(year_, month_, 1);
    
    // Calculate the offset to the first occurrence of the target day of the week
    int day_offset = (target_dow - first_day_dow + 7) % 7;
    int first_occurrence = 1 + day_offset;
    
    int result_day;
    if (week == "first") {
        result_day = first_occurrence;
    } else if (week == "second") {
        result_day = first_occurrence + 7;
    } else if (week == "third") {
        result_day = first_occurrence + 14;
    } else if (week == "fourth") {
        result_day = first_occurrence + 21;
    } else if (week == "last") {
        // Start from the last day of the month and work backwards to find the target weekday
        int last_day = days_in_month(year_, month_);
        int last_day_dow = day_of_week(year_, month_, last_day);
        // Calculate offset to target day of the week
        int offset = (last_day_dow - target_dow + 7) % 7;
        result_day = last_day - offset;
    } else if (week == "teenth") {
        // Teenth days are between 13-19
        // Find the first occurrence that falls in this range
        while (first_occurrence < 13) {
            first_occurrence += 7;
        }
        result_day = first_occurrence;
    } else {
        throw std::invalid_argument("Invalid week specification");
    }
    
    // Validate the result day is within the number of days in the month
    int max_days = days_in_month(year_, month_);
    if (result_day < 1 || result_day > max_days) {
        throw std::runtime_error("Calculated day is out of range");
    }
    
    return Date{year_, month_, result_day};
}

// Implement all the member functions by providing the correct day names
Date scheduler::monteenth() const { return find_date("teenth", "Monday"); }
Date scheduler::tuesteenth() const { return find_date("teenth", "Tuesday"); }
Date scheduler::wednesteenth() const { return find_date("teenth", "Wednesday"); }
Date scheduler::thursteenth() const { return find_date("teenth", "Thursday"); }
Date scheduler::friteenth() const { return find_date("teenth", "Friday"); }
Date scheduler::saturteenth() const { return find_date("teenth", "Saturday"); }
Date scheduler::sunteenth() const { return find_date("teenth", "Sunday"); }

Date scheduler::first_monday() const { return find_date("first", "Monday"); }
Date scheduler::first_tuesday() const { return find_date("first", "Tuesday"); }
Date scheduler::first_wednesday() const { return find_date("first", "Wednesday"); }
Date scheduler::first_thursday() const { return find_date("first", "Thursday"); }
Date scheduler::first_friday() const { return find_date("first", "Friday"); }
Date scheduler::first_saturday() const { return find_date("first", "Saturday"); }
Date scheduler::first_sunday() const { return find_date("first", "Sunday"); }

Date scheduler::second_monday() const { return find_date("second", "Monday"); }
Date scheduler::second_tuesday() const { return find_date("second", "Tuesday"); }
Date scheduler::second_wednesday() const { return find_date("second", "Wednesday"); }
Date scheduler::second_thursday() const { return find_date("second", "Thursday"); }
Date scheduler::second_friday() const { return find_date("second", "Friday"); }
Date scheduler::second_saturday() const { return find_date("second", "Saturday"); }
Date scheduler::second_sunday() const { return find_date("second", "Sunday"); }

Date scheduler::third_monday() const { return find_date("third", "Monday"); }
Date scheduler::third_tuesday() const { return find_date("third", "Tuesday"); }
Date scheduler::third_wednesday() const { return find_date("third", "Wednesday"); }
Date scheduler::third_thursday() const { return find_date("third", "Thursday"); }
Date scheduler::third_friday() const { return find_date("third", "Friday"); }
Date scheduler::third_saturday() const { return find_date("third", "Saturday"); }
Date scheduler::third_sunday() const { return find_date("third", "Sunday"); }

Date scheduler::fourth_monday() const { return find_date("fourth", "Monday"); }
Date scheduler::fourth_tuesday() const { return find_date("fourth", "Tuesday"); }
Date scheduler::fourth_wednesday() const { return find_date("fourth", "Wednesday"); }
Date scheduler::fourth_thursday() const { return find_date("fourth", "Thursday"); }
Date scheduler::fourth_friday() const { return find_date("fourth", "Friday"); }
Date scheduler::fourth_saturday() const { return find_date("fourth", "Saturday"); }
Date scheduler::fourth_sunday() const { return find_date("fourth", "Sunday"); }

Date scheduler::last_monday() const { return find_date("last", "Monday"); }
Date scheduler::last_tuesday() const { return find_date("last", "Tuesday"); }
Date scheduler::last_wednesday() const { return find_date("last", "Wednesday"); }
Date scheduler::last_thursday() const { return find_date("last", "Thursday"); }
Date scheduler::last_friday() const { return find_date("last", "Friday"); }
Date scheduler::last_saturday() const { return find_date("last", "Saturday"); }
Date scheduler::last_sunday() const { return find_date("last", "Sunday"); }

}  // namespace meetup
