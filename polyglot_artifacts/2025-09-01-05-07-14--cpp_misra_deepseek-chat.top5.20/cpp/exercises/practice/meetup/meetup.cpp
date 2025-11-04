#include "meetup.h"
#include <map>
#include <string>
#include <stdexcept>
#include <ctime>
#include <iostream>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month), day_(1) {
}

scheduler::scheduler(int year, int month, int day) : year_(year), month_(month), day_(day) {
}

int scheduler::day() const {
    return day_;
}

int scheduler::month() const {
    return month_;
}

int scheduler::year() const {
    return year_;
}

// Helper function implementations
scheduler scheduler::find_nth_weekday(int target_weekday, int week_num) const {
    // Initialize tm struct properly
    struct tm first_day;
    first_day.tm_year = year_ - 1900;
    first_day.tm_mon = month_ - 1;
    first_day.tm_mday = 1;
    first_day.tm_hour = 0;
    first_day.tm_min = 0;
    first_day.tm_sec = 0;
    first_day.tm_isdst = -1; // Let mktime determine DST
    mktime(&first_day);
    
    int count = 0;
    struct tm current_date = first_day;
    while (current_date.tm_mon == month_ - 1) {
        if (current_date.tm_wday == target_weekday) {
            count++;
            if (count == week_num) {
                return scheduler(year_, month_, current_date.tm_mday);
            }
        }
        current_date.tm_mday++;
        current_date.tm_hour = 0;
        current_date.tm_min = 0;
        current_date.tm_sec = 0;
        current_date.tm_isdst = -1;
        mktime(&current_date);
    }
    throw std::runtime_error("No valid date found");
}

scheduler scheduler::find_teenth_weekday(int target_weekday) const {
    // Check days 13-19
    for (int day = 13; day <= 19; day++) {
        struct tm current_date;
        current_date.tm_year = year_ - 1900;
        current_date.tm_mon = month_ - 1;
        current_date.tm_mday = day;
        current_date.tm_hour = 0;
        current_date.tm_min = 0;
        current_date.tm_sec = 0;
        current_date.tm_isdst = -1;
        mktime(&current_date);
        if (current_date.tm_wday == target_weekday) {
            return scheduler(year_, month_, day);
        }
    }
    throw std::runtime_error("No valid date found");
}

scheduler scheduler::find_last_weekday(int target_weekday) const {
    // Prepare a tm struct for the first day of the next month, then go back
    struct tm next_month;
    next_month.tm_year = year_ - 1900;
    next_month.tm_mon = month_; // Next month
    next_month.tm_mday = 0;     // Last day of current month
    next_month.tm_hour = 0;
    next_month.tm_min = 0;
    next_month.tm_sec = 0;
    next_month.tm_isdst = -1;
    mktime(&next_month);
    
    // Start from the last day of the month
    struct tm current_date = next_month;
    while (current_date.tm_mon == month_ - 1) {
        if (current_date.tm_wday == target_weekday) {
            return scheduler(year_, month_, current_date.tm_mday);
        }
        current_date.tm_mday--;
        current_date.tm_hour = 0;
        current_date.tm_min = 0;
        current_date.tm_sec = 0;
        current_date.tm_isdst = -1;
        mktime(&current_date);
    }
    throw std::runtime_error("No valid date found");
}

// Implement all the required member functions
// Teenth functions
scheduler scheduler::monteenth() const { return find_teenth_weekday(1); }
scheduler scheduler::tuesteenth() const { return find_teenth_weekday(2); }
scheduler scheduler::wednesteenth() const { return find_teenth_weekday(3); }
scheduler scheduler::thursteenth() const { return find_teenth_weekday(4); }
scheduler scheduler::friteenth() const { return find_teenth_weekday(5); }
scheduler scheduler::saturteenth() const { return find_teenth_weekday(6); }
scheduler scheduler::sunteenth() const { return find_teenth_weekday(0); }

// First week functions
scheduler scheduler::first_monday() const { return find_nth_weekday(1, 1); }
scheduler scheduler::first_tuesday() const { return find_nth_weekday(2, 1); }
scheduler scheduler::first_wednesday() const { return find_nth_weekday(3, 1); }
scheduler scheduler::first_thursday() const { return find_nth_weekday(4, 1); }
scheduler scheduler::first_friday() const { return find_nth_weekday(5, 1); }
scheduler scheduler::first_saturday() const { return find_nth_weekday(6, 1); }
scheduler scheduler::first_sunday() const { return find_nth_weekday(0, 1); }

// Second week functions
scheduler scheduler::second_monday() const { return find_nth_weekday(1, 2); }
scheduler scheduler::second_tuesday() const { return find_nth_weekday(2, 2); }
scheduler scheduler::second_wednesday() const { return find_nth_weekday(3, 2); }
scheduler scheduler::second_thursday() const { return find_nth_weekday(4, 2); }
scheduler scheduler::second_friday() const { return find_nth_weekday(5, 2); }
scheduler scheduler::second_saturday() const { return find_nth_weekday(6, 2); }
scheduler scheduler::second_sunday() const { return find_nth_weekday(0, 2); }

// Third week functions
scheduler scheduler::third_monday() const { return find_nth_weekday(1, 3); }
scheduler scheduler::third_tuesday() const { return find_nth_weekday(2, 3); }
scheduler scheduler::third_wednesday() const { return find_nth_weekday(3, 3); }
scheduler scheduler::third_thursday() const { return find_nth_weekday(4, 3); }
scheduler scheduler::third_friday() const { return find_nth_weekday(5, 3); }
scheduler scheduler::third_saturday() const { return find_nth_weekday(6, 3); }
scheduler scheduler::third_sunday() const { return find_nth_weekday(0, 3); }

// Fourth week functions
scheduler scheduler::fourth_monday() const { return find_nth_weekday(1, 4); }
scheduler scheduler::fourth_tuesday() const { return find_nth_weekday(2, 4); }
scheduler scheduler::fourth_wednesday() const { return find_nth_weekday(3, 4); }
scheduler scheduler::fourth_thursday() const { return find_nth_weekday(4, 4); }
scheduler scheduler::fourth_friday() const { return find_nth_weekday(5, 4); }
scheduler scheduler::fourth_saturday() const { return find_nth_weekday(6, 4); }
scheduler scheduler::fourth_sunday() const { return find_nth_weekday(0, 4); }

// Last week functions
scheduler scheduler::last_monday() const { return find_last_weekday(1); }
scheduler scheduler::last_tuesday() const { return find_last_weekday(2); }
scheduler scheduler::last_wednesday() const { return find_last_weekday(3); }
scheduler scheduler::last_thursday() const { return find_last_weekday(4); }
scheduler scheduler::last_friday() const { return find_last_weekday(5); }
scheduler scheduler::last_saturday() const { return find_last_weekday(6); }
scheduler scheduler::last_sunday() const { return find_last_weekday(0); }

}  // namespace meetup
