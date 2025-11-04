#include "meetup.h"
#include <ctime>
#include <string>
#include <stdexcept>
#include <cstring>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper functions
std::tm scheduler::make_time(int day) const {
    std::tm time_struct = {};
    time_struct.tm_year = year_ - 1900;
    time_struct.tm_mon = month_ - 1;
    time_struct.tm_mday = day;
    time_struct.tm_hour = 12;
    time_struct.tm_isdst = -1;
    return time_struct;
}

bool scheduler::is_weekday(const std::tm& time_struct, const char* target) const {
    // Make a copy to avoid modifying the original
    std::tm temp = time_struct;
    std::mktime(&temp);
    switch (temp.tm_wday) {
        case 0: return std::strcmp(target, "Sunday") == 0;
        case 1: return std::strcmp(target, "Monday") == 0;
        case 2: return std::strcmp(target, "Tuesday") == 0;
        case 3: return std::strcmp(target, "Wednesday") == 0;
        case 4: return std::strcmp(target, "Thursday") == 0;
        case 5: return std::strcmp(target, "Friday") == 0;
        case 6: return std::strcmp(target, "Saturday") == 0;
        default: return false;
    }
}

std::tm scheduler::find_nth_weekday(int n, const char* weekday) const {
    int count = 0;
    for (int day = 1; day <= 31; day++) {
        std::tm time_struct = make_time(day);
        std::mktime(&time_struct);
        // Check if still in the same month
        if (time_struct.tm_mon != month_ - 1) {
            break;
        }
        if (is_weekday(time_struct, weekday)) {
            count++;
            if (count == n) {
                return time_struct;
            }
        }
    }
    throw std::runtime_error("Date not found");
}

std::tm scheduler::find_teenth(const char* weekday) const {
    for (int day = 13; day <= 19; day++) {
        std::tm time_struct = make_time(day);
        std::mktime(&time_struct);
        if (is_weekday(time_struct, weekday)) {
            return time_struct;
        }
    }
    throw std::runtime_error("Date not found");
}

std::tm scheduler::find_last(const char* weekday) const {
    // Find last day of the month
    std::tm time_struct = make_time(1);
    time_struct.tm_mon += 1;
    std::mktime(&time_struct);
    time_struct.tm_mday = 0;
    std::mktime(&time_struct);
    
    int last_day = time_struct.tm_mday;
    for (int day = last_day; day >= 1; day--) {
        std::tm current = make_time(day);
        std::mktime(&current);
        if (is_weekday(current, weekday)) {
            return current;
        }
    }
    throw std::runtime_error("Date not found");
}

// Implement all the interface methods
// Teenth methods
std::tm scheduler::monteenth() const { return find_teenth("Monday"); }
std::tm scheduler::tuesteenth() const { return find_teenth("Tuesday"); }
std::tm scheduler::wednesteenth() const { return find_teenth("Wednesday"); }
std::tm scheduler::thursteenth() const { return find_teenth("Thursday"); }
std::tm scheduler::friteenth() const { return find_teenth("Friday"); }
std::tm scheduler::saturteenth() const { return find_teenth("Saturday"); }
std::tm scheduler::sunteenth() const { return find_teenth("Sunday"); }

// First week
std::tm scheduler::first_monday() const { return find_nth_weekday(1, "Monday"); }
std::tm scheduler::first_tuesday() const { return find_nth_weekday(1, "Tuesday"); }
std::tm scheduler::first_wednesday() const { return find_nth_weekday(1, "Wednesday"); }
std::tm scheduler::first_thursday() const { return find_nth_weekday(1, "Thursday"); }
std::tm scheduler::first_friday() const { return find_nth_weekday(1, "Friday"); }
std::tm scheduler::first_saturday() const { return find_nth_weekday(1, "Saturday"); }
std::tm scheduler::first_sunday() const { return find_nth_weekday(1, "Sunday"); }

// Second week
std::tm scheduler::second_monday() const { return find_nth_weekday(2, "Monday"); }
std::tm scheduler::second_tuesday() const { return find_nth_weekday(2, "Tuesday"); }
std::tm scheduler::second_wednesday() const { return find_nth_weekday(2, "Wednesday"); }
std::tm scheduler::second_thursday() const { return find_nth_weekday(2, "Thursday"); }
std::tm scheduler::second_friday() const { return find_nth_weekday(2, "Friday"); }
std::tm scheduler::second_saturday() const { return find_nth_weekday(2, "Saturday"); }
std::tm scheduler::second_sunday() const { return find_nth_weekday(2, "Sunday"); }

// Third week
std::tm scheduler::third_monday() const { return find_nth_weekday(3, "Monday"); }
std::tm scheduler::third_tuesday() const { return find_nth_weekday(3, "Tuesday"); }
std::tm scheduler::third_wednesday() const { return find_nth_weekday(3, "Wednesday"); }
std::tm scheduler::third_thursday() const { return find_nth_weekday(3, "Thursday"); }
std::tm scheduler::third_friday() const { return find_nth_weekday(3, "Friday"); }
std::tm scheduler::third_saturday() const { return find_nth_weekday(3, "Saturday"); }
std::tm scheduler::third_sunday() const { return find_nth_weekday(3, "Sunday"); }

// Fourth week
std::tm scheduler::fourth_monday() const { return find_nth_weekday(4, "Monday"); }
std::tm scheduler::fourth_tuesday() const { return find_nth_weekday(4, "Tuesday"); }
std::tm scheduler::fourth_wednesday() const { return find_nth_weekday(4, "Wednesday"); }
std::tm scheduler::fourth_thursday() const { return find_nth_weekday(4, "Thursday"); }
std::tm scheduler::fourth_friday() const { return find_nth_weekday(4, "Friday"); }
std::tm scheduler::fourth_saturday() const { return find_nth_weekday(4, "Saturday"); }
std::tm scheduler::fourth_sunday() const { return find_nth_weekday(4, "Sunday"); }

// Last week
std::tm scheduler::last_monday() const { return find_last("Monday"); }
std::tm scheduler::last_tuesday() const { return find_last("Tuesday"); }
std::tm scheduler::last_wednesday() const { return find_last("Wednesday"); }
std::tm scheduler::last_thursday() const { return find_last("Thursday"); }
std::tm scheduler::last_friday() const { return find_last("Friday"); }
std::tm scheduler::last_saturday() const { return find_last("Saturday"); }
std::tm scheduler::last_sunday() const { return find_last("Sunday"); }

}  // namespace meetup
