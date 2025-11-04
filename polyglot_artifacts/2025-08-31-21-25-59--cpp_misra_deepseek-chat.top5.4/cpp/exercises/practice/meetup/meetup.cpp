#include "meetup.h"
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <map>
#include <stdexcept>

namespace meetup {

namespace {

int day_of_week(int year, int month, int day) {
    // Adjust month and year for Zeller's congruence
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int century = year / 100;
    int year_of_century = year % 100;
    // Zeller's congruence calculation
    int h = (day + (13 * (month + 1)) / 5 + year_of_century + (year_of_century / 4) + (century / 4) + (5 * century)) % 7;
    // Convert result to our mapping where 0=Saturday, 1=Sunday, 2=Monday, ... 6=Friday
    // We need to map to 0=Monday, 1=Tuesday, ... 6=Sunday
    // So adjust: (h + 5) % 7
    // Let's test: January 1, 2018 is Monday -> should return 0
    int result = (h + 5) % 7;
    // Ensure it's between 0-6
    if (result < 0) {
        result += 7;
    }
    return result % 7;
}

const std::map<std::string, int> weekday_map = {
    {"Monday", 0},
    {"Tuesday", 1},
    {"Wednesday", 2},
    {"Thursday", 3},
    {"Friday", 4},
    {"Saturday", 5},
    {"Sunday", 6}
};

}  // namespace

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Teenth implementations
Date scheduler::monteenth() const { return find_date("teenth", "Monday"); }
Date scheduler::tuesteenth() const { return find_date("teenth", "Tuesday"); }
Date scheduler::wednesteenth() const { return find_date("teenth", "Wednesday"); }
Date scheduler::thursteenth() const { return find_date("teenth", "Thursday"); }
Date scheduler::friteenth() const { return find_date("teenth", "Friday"); }
Date scheduler::saturteenth() const { return find_date("teenth", "Saturday"); }
Date scheduler::sunteenth() const { return find_date("teenth", "Sunday"); }

// First week implementations
Date scheduler::first_monday() const { return find_date("first", "Monday"); }
Date scheduler::first_tuesday() const { return find_date("first", "Tuesday"); }
Date scheduler::first_wednesday() const { return find_date("first", "Wednesday"); }
Date scheduler::first_thursday() const { return find_date("first", "Thursday"); }
Date scheduler::first_friday() const { return find_date("first", "Friday"); }
Date scheduler::first_saturday() const { return find_date("first", "Saturday"); }
Date scheduler::first_sunday() const { return find_date("first", "Sunday"); }

// Second week implementations
Date scheduler::second_monday() const { return find_date("second", "Monday"); }
Date scheduler::second_tuesday() const { return find_date("second", "Tuesday"); }
Date scheduler::second_wednesday() const { return find_date("second", "Wednesday"); }
Date scheduler::second_thursday() const { return find_date("second", "Thursday"); }
Date scheduler::second_friday() const { return find_date("second", "Friday"); }
Date scheduler::second_saturday() const { return find_date("second", "Saturday"); }
Date scheduler::second_sunday() const { return find_date("second", "Sunday"); }

// Third week implementations
Date scheduler::third_monday() const { return find_date("third", "Monday"); }
Date scheduler::third_tuesday() const { return find_date("third", "Tuesday"); }
Date scheduler::third_wednesday() const { return find_date("third", "Wednesday"); }
Date scheduler::third_thursday() const { return find_date("third", "Thursday"); }
Date scheduler::third_friday() const { return find_date("third", "Friday"); }
Date scheduler::third_saturday() const { return find_date("third", "Saturday"); }
Date scheduler::third_sunday() const { return find_date("third", "Sunday"); }

// Fourth week implementations
Date scheduler::fourth_monday() const { return find_date("fourth", "Monday"); }
Date scheduler::fourth_tuesday() const { return find_date("fourth", "Tuesday"); }
Date scheduler::fourth_wednesday() const { return find_date("fourth", "Wednesday"); }
Date scheduler::fourth_thursday() const { return find_date("fourth", "Thursday"); }
Date scheduler::fourth_friday() const { return find_date("fourth", "Friday"); }
Date scheduler::fourth_saturday() const { return find_date("fourth", "Saturday"); }
Date scheduler::fourth_sunday() const { return find_date("fourth", "Sunday"); }

// Last week implementations
Date scheduler::last_monday() const { return find_date("last", "Monday"); }
Date scheduler::last_tuesday() const { return find_date("last", "Tuesday"); }
Date scheduler::last_wednesday() const { return find_date("last", "Wednesday"); }
Date scheduler::last_thursday() const { return find_date("last", "Thursday"); }
Date scheduler::last_friday() const { return find_date("last", "Friday"); }
Date scheduler::last_saturday() const { return find_date("last", "Saturday"); }
Date scheduler::last_sunday() const { return find_date("last", "Sunday"); }

Date scheduler::find_date(const std::string& week, const std::string& weekday) const {
    int target_weekday = weekday_map.at(weekday);
    
    // Find all days that match the target weekday
    std::vector<int> matching_days;
    
    // Determine number of days in the month
    // Simple approach: for months with 31,30,28,29 days
    int days_in_month;
    if (month_ == 2) {
        // Check for leap year
        if ((year_ % 4 == 0 && year_ % 100 != 0) || (year_ % 400 == 0)) {
            days_in_month = 29;
        } else {
            days_in_month = 28;
        }
    } else if (month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11) {
        days_in_month = 30;
    } else {
        days_in_month = 31;
    }
    
    // Find all matching weekdays
    for (int day = 1; day <= days_in_month; ++day) {
        if (day_of_week(year_, month_, day) == target_weekday) {
            matching_days.push_back(day);
        }
    }
    
    int selected_day = 0;
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
        // Find the day between 13-19 that's in matching_days
        for (int day : matching_days) {
            if ((day >= 13) && (day <= 19)) {
                selected_day = day;
                break;
            }
        }
    } else {
        throw std::runtime_error("Invalid week specification");
    }
    
    return Date{year_, month_, selected_day};
}

}  // namespace meetup
