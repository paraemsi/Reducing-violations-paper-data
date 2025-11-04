#include "meetup.h"
#include <ctime>
#include <string>
#include <array>

namespace meetup {

namespace {
    // Helper: map weekday string to tm_wday (0=Sunday, 1=Monday, ..., 6=Saturday)
    constexpr std::array<const char*, 7> weekday_names = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };

    meetup::day_t days_in_month(meetup::year_t year, meetup::month_t month) noexcept {
        static const meetup::day_t days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        meetup::day_t d = days[static_cast<std::size_t>(month) - 1];
        if((month == 2) && (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0)))) {
            d = 29;
        }
        return d;
    }

    std::uint8_t calc_wday(meetup::year_t year, meetup::month_t month, meetup::day_t day) noexcept {
        std::tm time_in = {};
        time_in.tm_year = static_cast<int>(year) - 1900;
        time_in.tm_mon = static_cast<int>(month) - 1;
        time_in.tm_mday = static_cast<int>(day);
        time_in.tm_hour = 12;
        std::mktime(&time_in);
        return static_cast<std::uint8_t>(time_in.tm_wday);
    }
}

scheduler::scheduler(month_t month, year_t year) noexcept
    : m_month(month), m_year(year) {}

meetup::day_t scheduler::weekday_to_num(const std::string& weekday) noexcept {
    for(std::size_t i = 0; i < weekday_names.size(); ++i) {
        if(weekday == weekday_names[i]) {
            return static_cast<meetup::day_t>(i);
        }
    }
    return -1;
}

meetup::day_t scheduler::find(const std::string& weekday, const std::string& schedule) const noexcept {
    const meetup::day_t target_wd = weekday_to_num(weekday);
    if(target_wd < 0) return -1;

    if(schedule == "teenth") {
        for(meetup::day_t d = 13; d <= 19; ++d) {
            if(calc_wday(m_year, m_month, d) == static_cast<std::uint8_t>(target_wd)) {
                return d;
            }
        }
    } else if(schedule == "last") {
        meetup::day_t last_day = days_in_month(m_year, m_month);
        for(meetup::day_t d = last_day; d >= (last_day - 6); --d) {
            if(calc_wday(m_year, m_month, d) == static_cast<std::uint8_t>(target_wd)) {
                return d;
            }
        }
    } else {
        std::size_t week_num = 0;
        if(schedule == "first") {
            week_num = 1;
        } else if(schedule == "second") {
            week_num = 2;
        } else if(schedule == "third") {
            week_num = 3;
        } else if(schedule == "fourth") {
            week_num = 4;
        } else {
            return -1;
        }
        meetup::day_t count = 0;
        meetup::day_t days = days_in_month(m_year, m_month);
        for(meetup::day_t d = 1; d <= days; ++d) {
            if(calc_wday(m_year, m_month, d) == static_cast<std::uint8_t>(target_wd)) {
                ++count;
                if(count == static_cast<meetup::day_t>(week_num)) {
                    return d;
                }
            }
        }
    }
    return -1;
}

// Teenth
meetup::day_t scheduler::monteenth() const noexcept { return find("Monday", "teenth"); }
meetup::day_t scheduler::tuesteenth() const noexcept { return find("Tuesday", "teenth"); }
meetup::day_t scheduler::wednesteenth() const noexcept { return find("Wednesday", "teenth"); }
meetup::day_t scheduler::thursteenth() const noexcept { return find("Thursday", "teenth"); }
meetup::day_t scheduler::friteenth() const noexcept { return find("Friday", "teenth"); }
meetup::day_t scheduler::saturteenth() const noexcept { return find("Saturday", "teenth"); }
meetup::day_t scheduler::sunteenth() const noexcept { return find("Sunday", "teenth"); }

// First
meetup::day_t scheduler::first_monday() const noexcept { return find("Monday", "first"); }
meetup::day_t scheduler::first_tuesday() const noexcept { return find("Tuesday", "first"); }
meetup::day_t scheduler::first_wednesday() const noexcept { return find("Wednesday", "first"); }
meetup::day_t scheduler::first_thursday() const noexcept { return find("Thursday", "first"); }
meetup::day_t scheduler::first_friday() const noexcept { return find("Friday", "first"); }
meetup::day_t scheduler::first_saturday() const noexcept { return find("Saturday", "first"); }
meetup::day_t scheduler::first_sunday() const noexcept { return find("Sunday", "first"); }

// Second
meetup::day_t scheduler::second_monday() const noexcept { return find("Monday", "second"); }
meetup::day_t scheduler::second_tuesday() const noexcept { return find("Tuesday", "second"); }
meetup::day_t scheduler::second_wednesday() const noexcept { return find("Wednesday", "second"); }
meetup::day_t scheduler::second_thursday() const noexcept { return find("Thursday", "second"); }
meetup::day_t scheduler::second_friday() const noexcept { return find("Friday", "second"); }
meetup::day_t scheduler::second_saturday() const noexcept { return find("Saturday", "second"); }
meetup::day_t scheduler::second_sunday() const noexcept { return find("Sunday", "second"); }

// Third
meetup::day_t scheduler::third_monday() const noexcept { return find("Monday", "third"); }
meetup::day_t scheduler::third_tuesday() const noexcept { return find("Tuesday", "third"); }
meetup::day_t scheduler::third_wednesday() const noexcept { return find("Wednesday", "third"); }
meetup::day_t scheduler::third_thursday() const noexcept { return find("Thursday", "third"); }
meetup::day_t scheduler::third_friday() const noexcept { return find("Friday", "third"); }
meetup::day_t scheduler::third_saturday() const noexcept { return find("Saturday", "third"); }
meetup::day_t scheduler::third_sunday() const noexcept { return find("Sunday", "third"); }

// Fourth
meetup::day_t scheduler::fourth_monday() const noexcept { return find("Monday", "fourth"); }
meetup::day_t scheduler::fourth_tuesday() const noexcept { return find("Tuesday", "fourth"); }
meetup::day_t scheduler::fourth_wednesday() const noexcept { return find("Wednesday", "fourth"); }
meetup::day_t scheduler::fourth_thursday() const noexcept { return find("Thursday", "fourth"); }
meetup::day_t scheduler::fourth_friday() const noexcept { return find("Friday", "fourth"); }
meetup::day_t scheduler::fourth_saturday() const noexcept { return find("Saturday", "fourth"); }
meetup::day_t scheduler::fourth_sunday() const noexcept { return find("Sunday", "fourth"); }

// Last
meetup::day_t scheduler::last_monday() const noexcept { return find("Monday", "last"); }
meetup::day_t scheduler::last_tuesday() const noexcept { return find("Tuesday", "last"); }
meetup::day_t scheduler::last_wednesday() const noexcept { return find("Wednesday", "last"); }
meetup::day_t scheduler::last_thursday() const noexcept { return find("Thursday", "last"); }
meetup::day_t scheduler::last_friday() const noexcept { return find("Friday", "last"); }
meetup::day_t scheduler::last_saturday() const noexcept { return find("Saturday", "last"); }
meetup::day_t scheduler::last_sunday() const noexcept { return find("Sunday", "last"); }

}  // namespace meetup
