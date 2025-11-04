#include "meetup.h"
#include <string>
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace meetup {

namespace {

bool is_leap_year(int year) {
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    return (year % 400 == 0);
}

int days_in_month(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return is_leap_year(year) ? 29 : 28;
        default:
            throw std::runtime_error("Invalid month");
    }
}

// Zeller's Congruence to find the day of the week for a given date
int day_of_week(int day, int month, int year) {
    if (month < 3) {
        month += 12;
        year -= 1;
    }
    int k = year % 100;
    int j = year / 100;
    int h = (day + (13 * (month + 1)) / 5 + k + (k / 4) + (j / 4) + (5 * j)) % 7;
    return (h + 5) % 7; // Convert to 0=Sunday, 1=Monday, ..., 6=Saturday
}

}  // namespace

int scheduler::find_day(int target_weekday, const std::string& week) const {
    int num_days = days_in_month(month_, year_);
    
    // Find all dates that match the target weekday
    std::vector<int> matching_days;
    for (int day = 1; day <= num_days; day++) {
        if (day_of_week(day, month_, year_) == target_weekday) {
            matching_days.push_back(day);
        }
    }
    
    // Determine which day to pick based on the week specification
    if (week == "first") {
        return matching_days[0];
    } else if (week == "second") {
        return matching_days[1];
    } else if (week == "third") {
        return matching_days[2];
    } else if (week == "fourth") {
        return matching_days[3];
    } else if (week == "last") {
        return matching_days.back();
    } else if (week == "teenth") {
        for (int day : matching_days) {
            if (day >= 13 && day <= 19) {
                return day;
            }
        }
    }
    throw std::runtime_error("Invalid week specification");
}

// Implement all the member functions
int scheduler::monteenth() const { return find_day(1, "teenth"); }
int scheduler::tuesteenth() const { return find_day(2, "teenth"); }
int scheduler::wednesteenth() const { return find_day(3, "teenth"); }
int scheduler::thursteenth() const { return find_day(4, "teenth"); }
int scheduler::friteenth() const { return find_day(5, "teenth"); }
int scheduler::saturteenth() const { return find_day(6, "teenth"); }
int scheduler::sunteenth() const { return find_day(0, "teenth"); }

int scheduler::first_monday() const { return find_day(1, "first"); }
int scheduler::first_tuesday() const { return find_day(2, "first"); }
int scheduler::first_wednesday() const { return find_day(3, "first"); }
int scheduler::first_thursday() const { return find_day(4, "first"); }
int scheduler::first_friday() const { return find_day(5, "first"); }
int scheduler::first_saturday() const { return find_day(6, "first"); }
int scheduler::first_sunday() const { return find_day(0, "first"); }

int scheduler::second_monday() const { return find_day(1, "second"); }
int scheduler::second_tuesday() const { return find_day(2, "second"); }
int scheduler::second_wednesday() const { return find_day(3, "second"); }
int scheduler::second_thursday() const { return find_day(4, "second"); }
int scheduler::second_friday() const { return find_day(5, "second"); }
int scheduler::second_saturday() const { return find_day(6, "second"); }
int scheduler::second_sunday() const { return find_day(0, "second"); }

int scheduler::third_monday() const { return find_day(1, "third"); }
int scheduler::third_tuesday() const { return find_day(2, "third"); }
int scheduler::third_wednesday() const { return find_day(3, "third"); }
int scheduler::third_thursday() const { return find_day(4, "third"); }
int scheduler::third_friday() const { return find_day(5, "third"); }
int scheduler::third_saturday() const { return find_day(6, "third"); }
int scheduler::third_sunday() const { return find_day(0, "third"); }

int scheduler::fourth_monday() const { return find_day(1, "fourth"); }
int scheduler::fourth_tuesday() const { return find_day(2, "fourth"); }
int scheduler::fourth_wednesday() const { return find_day(3, "fourth"); }
int scheduler::fourth_thursday() const { return find_day(4, "fourth"); }
int scheduler::fourth_friday() const { return find_day(5, "fourth"); }
int scheduler::fourth_saturday() const { return find_day(6, "fourth"); }
int scheduler::fourth_sunday() const { return find_day(0, "fourth"); }

int scheduler::last_monday() const { return find_day(1, "last"); }
int scheduler::last_tuesday() const { return find_day(2, "last"); }
int scheduler::last_wednesday() const { return find_day(3, "last"); }
int scheduler::last_thursday() const { return find_day(4, "last"); }
int scheduler::last_friday() const { return find_day(5, "last"); }
int scheduler::last_saturday() const { return find_day(6, "last"); }
int scheduler::last_sunday() const { return find_day(0, "last"); }

}  // namespace meetup
