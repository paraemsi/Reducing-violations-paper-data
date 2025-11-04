#include "meetup.h"
#include <ctime>
#include <stdexcept>

namespace meetup {

namespace {

constexpr day_t days_in_month(year_t year, month_t month)
{
    // Months: Jan=1, Feb=2, ..., Dec=12
    switch(month) {
        case 1U: case 3U: case 5U: case 7U: case 8U: case 10U: case 12U:
            return 31U;
        case 4U: case 6U: case 9U: case 11U:
            return 30U;
        case 2U:
            // Leap year check
            if(((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0))) {
                return 29U;
            } else {
                return 28U;
            }
        default:
            throw std::invalid_argument("Invalid month");
    }
}

// Returns 0=Sunday, 1=Monday, ..., 6=Saturday
std::uint8_t weekday_of(year_t year, month_t month, day_t day)
{
    std::tm timeinfo = {};
    timeinfo.tm_year = static_cast<int>(year - 1900);
    timeinfo.tm_mon = static_cast<int>(month - 1U);
    timeinfo.tm_mday = static_cast<int>(day);
    timeinfo.tm_hour = 12; // avoid DST issues

    // Use timegm if available, else mktime (local time)
    std::time_t t = std::mktime(&timeinfo);
    if(t == static_cast<std::time_t>(-1)) {
        throw std::runtime_error("Invalid date");
    }
    // tm_wday: 0=Sunday, ..., 6=Saturday
    return static_cast<std::uint8_t>(timeinfo.tm_wday);
}

} // anonymous namespace

scheduler::scheduler(month_t month, year_t year)
    : m_month(month), m_year(year)
{
}

day_t scheduler::get_day(Weekday weekday, Schedule schedule) const
{
    return day(m_year, m_month, weekday, schedule);
}

#define MEETUP_IMPL_METHOD(NAME, WEEKDAY, SCHEDULE) \
    day_t scheduler::NAME() const { return get_day(Weekday::WEEKDAY, Schedule::SCHEDULE); }

MEETUP_IMPL_METHOD(monteenth, Monday, Teenth)
MEETUP_IMPL_METHOD(tuesteenth, Tuesday, Teenth)
MEETUP_IMPL_METHOD(wednesteenth, Wednesday, Teenth)
MEETUP_IMPL_METHOD(thursteenth, Thursday, Teenth)
MEETUP_IMPL_METHOD(friteenth, Friday, Teenth)
MEETUP_IMPL_METHOD(saturteenth, Saturday, Teenth)
MEETUP_IMPL_METHOD(sunteenth, Sunday, Teenth)

MEETUP_IMPL_METHOD(first_monday, Monday, First)
MEETUP_IMPL_METHOD(first_tuesday, Tuesday, First)
MEETUP_IMPL_METHOD(first_wednesday, Wednesday, First)
MEETUP_IMPL_METHOD(first_thursday, Thursday, First)
MEETUP_IMPL_METHOD(first_friday, Friday, First)
MEETUP_IMPL_METHOD(first_saturday, Saturday, First)
MEETUP_IMPL_METHOD(first_sunday, Sunday, First)

MEETUP_IMPL_METHOD(second_monday, Monday, Second)
MEETUP_IMPL_METHOD(second_tuesday, Tuesday, Second)
MEETUP_IMPL_METHOD(second_wednesday, Wednesday, Second)
MEETUP_IMPL_METHOD(second_thursday, Thursday, Second)
MEETUP_IMPL_METHOD(second_friday, Friday, Second)
MEETUP_IMPL_METHOD(second_saturday, Saturday, Second)
MEETUP_IMPL_METHOD(second_sunday, Sunday, Second)

MEETUP_IMPL_METHOD(third_monday, Monday, Third)
MEETUP_IMPL_METHOD(third_tuesday, Tuesday, Third)
MEETUP_IMPL_METHOD(third_wednesday, Wednesday, Third)
MEETUP_IMPL_METHOD(third_thursday, Thursday, Third)
MEETUP_IMPL_METHOD(third_friday, Friday, Third)
MEETUP_IMPL_METHOD(third_saturday, Saturday, Third)
MEETUP_IMPL_METHOD(third_sunday, Sunday, Third)

MEETUP_IMPL_METHOD(fourth_monday, Monday, Fourth)
MEETUP_IMPL_METHOD(fourth_tuesday, Tuesday, Fourth)
MEETUP_IMPL_METHOD(fourth_wednesday, Wednesday, Fourth)
MEETUP_IMPL_METHOD(fourth_thursday, Thursday, Fourth)
MEETUP_IMPL_METHOD(fourth_friday, Friday, Fourth)
MEETUP_IMPL_METHOD(fourth_saturday, Saturday, Fourth)
MEETUP_IMPL_METHOD(fourth_sunday, Sunday, Fourth)

MEETUP_IMPL_METHOD(last_monday, Monday, Last)
MEETUP_IMPL_METHOD(last_tuesday, Tuesday, Last)
MEETUP_IMPL_METHOD(last_wednesday, Wednesday, Last)
MEETUP_IMPL_METHOD(last_thursday, Thursday, Last)
MEETUP_IMPL_METHOD(last_friday, Friday, Last)
MEETUP_IMPL_METHOD(last_saturday, Saturday, Last)
MEETUP_IMPL_METHOD(last_sunday, Sunday, Last)

#undef MEETUP_IMPL_METHOD

}  // namespace meetup
