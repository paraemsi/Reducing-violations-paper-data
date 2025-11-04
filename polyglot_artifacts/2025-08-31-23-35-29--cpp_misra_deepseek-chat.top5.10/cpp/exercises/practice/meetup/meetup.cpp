#include "meetup.h"
#include <chrono>
#include <string>
#include <stdexcept>
#include <memory>

namespace meetup {

using namespace std::chrono;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

std::chrono::year_month_day scheduler::find_day(const std::string& descriptor, 
                                                const std::chrono::weekday& wd) const {
    if (descriptor == "first") {
        // Find the first occurrence
        auto first_day = year_month_day{year{year_}, month{month_}, day{1}};
        sys_days first_sys = first_day;
        weekday first_weekday = year_month_weekday{first_sys}.weekday();
        // Calculate days to add to reach the first occurrence of the target weekday
        int days_to_add = (wd.c_encoding() - first_weekday.c_encoding() + 7) % 7;
        sys_days target = first_sys + days{days_to_add};
        return year_month_day{target};
    } else if (descriptor == "second") {
        auto first = find_day("first", wd);
        sys_days first_sys = first;
        sys_days target = first_sys + days{7};
        return year_month_day{target};
    } else if (descriptor == "third") {
        auto first = find_day("first", wd);
        sys_days first_sys = first;
        sys_days target = first_sys + days{14};
        return year_month_day{target};
    } else if (descriptor == "fourth") {
        auto first = find_day("first", wd);
        sys_days first_sys = first;
        sys_days target = first_sys + days{21};
        return year_month_day{target};
    } else if (descriptor == "last") {
        // Find the last day of the month
        auto last_day = year_month_day_last{year{year_}, month_day_last{month{month_}}};
        sys_days last_sys = last_day;
        weekday last_weekday = year_month_weekday{last_sys}.weekday();
        // Calculate days to subtract to reach the last occurrence of the target weekday
        int days_to_subtract = (last_weekday.c_encoding() - wd.c_encoding() + 7) % 7;
        sys_days target = last_sys - days{days_to_subtract};
        return year_month_day{target};
    } else if (descriptor == "teenth") {
        // Check days 13-19
        for (int d = 13; d <= 19; d++) {
            auto current = year_month_day{year{year_}, month{month_}, day{d}};
            sys_days current_sys = current;
            if (weekday{current_sys} == wd) {
                return current;
            }
        }
        throw std::runtime_error("Teenth not found");
    }
    throw std::invalid_argument("Invalid descriptor");
}

// Teenth methods
std::chrono::year_month_day scheduler::monteenth() const {
    return find_day("teenth", std::chrono::Monday);
}

std::chrono::year_month_day scheduler::tuesteenth() const {
    return find_day("teenth", std::chrono::Tuesday);
}

std::chrono::year_month_day scheduler::wednesteenth() const {
    return find_day("teenth", std::chrono::Wednesday);
}

std::chrono::year_month_day scheduler::thursteenth() const {
    return find_day("teenth", std::chrono::Thursday);
}

std::chrono::year_month_day scheduler::friteenth() const {
    return find_day("teenth", std::chrono::Friday);
}

std::chrono::year_month_day scheduler::saturteenth() const {
    return find_day("teenth", std::chrono::Saturday);
}

std::chrono::year_month_day scheduler::sunteenth() const {
    return find_day("teenth", std::chrono::Sunday);
}

// First methods
std::chrono::year_month_day scheduler::first_monday() const {
    return find_day("first", std::chrono::Monday);
}

std::chrono::year_month_day scheduler::first_tuesday() const {
    return find_day("first", std::chrono::Tuesday);
}

std::chrono::year_month_day scheduler::first_wednesday() const {
    return find_day("first", std::chrono::Wednesday);
}

std::chrono::year_month_day scheduler::first_thursday() const {
    return find_day("first", std::chrono::Thursday);
}

std::chrono::year_month_day scheduler::first_friday() const {
    return find_day("first", std::chrono::Friday);
}

std::chrono::year_month_day scheduler::first_saturday() const {
    return find_day("first", std::chrono::Saturday);
}

std::chrono::year_month_day scheduler::first_sunday() const {
    return find_day("first", std::chrono::Sunday);
}

// Second methods
std::chrono::year_month_day scheduler::second_monday() const {
    return find_day("second", std::chrono::Monday);
}

std::chrono::year_month_day scheduler::second_tuesday() const {
    return find_day("second", std::chrono::Tuesday);
}

std::chrono::year_month_day scheduler::second_wednesday() const {
    return find_day("second", std::chrono::Wednesday);
}

std::chrono::year_month_day scheduler::second_thursday() const {
    return find_day("second", std::chrono::Thursday);
}

std::chrono::year_month_day scheduler::second_friday() const {
    return find_day("second", std::chrono::Friday);
}

std::chrono::year_month_day scheduler::second_saturday() const {
    return find_day("second", std::chrono::Saturday);
}

std::chrono::year_month_day scheduler::second_sunday() const {
    return find_day("second", std::chrono::Sunday);
}

// Third methods
std::chrono::year_month_day scheduler::third_monday() const {
    return find_day("third", std::chrono::Monday);
}

std::chrono::year_month_day scheduler::third_tuesday() const {
    return find_day("third", std::chrono::Tuesday);
}

std::chrono::year_month_day scheduler::third_wednesday() const {
    return find_day("third", std::chrono::Wednesday);
}

std::chrono::year_month_day scheduler::third_thursday() const {
    return find_day("third", std::chrono::Thursday);
}

std::chrono::year_month_day scheduler::third_friday() const {
    return find_day("third", std::chrono::Friday);
}

std::chrono::year_month_day scheduler::third_saturday() const {
    return find_day("third", std::chrono::Saturday);
}

std::chrono::year_month_day scheduler::third_sunday() const {
    return find_day("third", std::chrono::Sunday);
}

// Fourth methods
std::chrono::year_month_day scheduler::fourth_monday() const {
    return find_day("fourth", std::chrono::Monday);
}

std::chrono::year_month_day scheduler::fourth_tuesday() const {
    return find_day("fourth", std::chrono::Tuesday);
}

std::chrono::year_month_day scheduler::fourth_wednesday() const {
    return find_day("fourth", std::chrono::Wednesday);
}

std::chrono::year_month_day scheduler::fourth_thursday() const {
    return find_day("fourth", std::chrono::Thursday);
}

std::chrono::year_month_day scheduler::fourth_friday() const {
    return find_day("fourth", std::chrono::Friday);
}

std::chrono::year_month_day scheduler::fourth_saturday() const {
    return find_day("fourth", std::chrono::Saturday);
}

std::chrono::year_month_day scheduler::fourth_sunday() const {
    return find_day("fourth", std::chrono::Sunday);
}

// Last methods
std::chrono::year_month_day scheduler::last_monday() const {
    return find_day("last", std::chrono::Monday);
}

std::chrono::year_month_day scheduler::last_tuesday() const {
    return find_day("last", std::chrono::Tuesday);
}

std::chrono::year_month_day scheduler::last_wednesday() const {
    return find_day("last", std::chrono::Wednesday);
}

std::chrono::year_month_day scheduler::last_thursday() const {
    return find_day("last", std::chrono::Thursday);
}

std::chrono::year_month_day scheduler::last_friday() const {
    return find_day("last", std::chrono::Friday);
}

std::chrono::year_month_day scheduler::last_saturday() const {
    return find_day("last", std::chrono::Saturday);
}

std::chrono::year_month_day scheduler::last_sunday() const {
    return find_day("last", std::chrono::Sunday);
}

}  // namespace meetup
