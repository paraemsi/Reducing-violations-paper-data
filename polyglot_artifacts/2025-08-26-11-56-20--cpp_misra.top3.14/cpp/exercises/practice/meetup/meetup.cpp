#include "meetup.h"
#include <ctime>
#include <stdexcept>

namespace meetup {

namespace {

constexpr day_t days_in_month(year_t year, month_t month)
{
    switch(month) {
        case 1U: case 3U: case 5U: case 7U: case 8U: case 10U: case 12U:
            return static_cast<day_t>(31);
        case 4U: case 6U: case 9U: case 11U:
            return static_cast<day_t>(30);
        case 2U:
            if(((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0))) {
                return static_cast<day_t>(29);
            } else {
                return static_cast<day_t>(28);
            }
        default:
            throw std::invalid_argument("Invalid month");
    }
}

// Returns 0=Sunday, 1=Monday, ..., 6=Saturday
std::uint8_t weekday_of(year_t year, month_t month, day_t day)
{
    year_t y = year;
    month_t m = month;
    if(m < static_cast<month_t>(3U)) {
        m = static_cast<month_t>(m + 12U);
        y = static_cast<year_t>(y - 1);
    }
    std::int32_t K = static_cast<std::int32_t>(y % 100);
    std::int32_t J = static_cast<std::int32_t>(y / 100);
    std::int32_t h = (static_cast<std::int32_t>(day) + ((13 * (static_cast<std::int32_t>(m) + 1)) / 5)
        + K + (K / 4) + (J / 4) + (5 * J));
    h = h % 7;
    std::uint8_t wd = static_cast<std::uint8_t>((h + 6) % 7);
    return wd;
}

day_t find_day(year_t year, month_t month, std::uint8_t target_wd, int which)
{
    day_t dim = days_in_month(year, month);
    if(which == 0) { // teenth
        for(day_t d = 13U; d <= 19U; ++d) {
            if(weekday_of(year, month, d) == target_wd) {
                return d;
            }
        }
    } else if(which == -1) { // last
        for(day_t d = dim; d >= 1U; --d) {
            if(weekday_of(year, month, d) == target_wd) {
                return d;
            }
        }
    } else { // 1=first, 2=second, 3=third, 4=fourth
        day_t count = 0U;
        for(day_t d = 1U; d <= dim; ++d) {
            if(weekday_of(year, month, d) == target_wd) {
                ++count;
                if(count == static_cast<day_t>(which)) {
                    return d;
                }
            }
        }
    }
    throw std::domain_error("No such meetup day in this month");
}

} // anonymous namespace

// Helper macro to generate methods for each schedule/weekday combination
#define MEETUP_METHOD(NAME, WD, WHICH) \
    day_t scheduler::NAME() const { return find_day(m_year, m_month, static_cast<std::uint8_t>(Weekday::WD), WHICH); }

MEETUP_METHOD(monteenth, Monday, 0)
MEETUP_METHOD(tuesteenth, Tuesday, 0)
MEETUP_METHOD(wednesteenth, Wednesday, 0)
MEETUP_METHOD(thursteenth, Thursday, 0)
MEETUP_METHOD(friteenth, Friday, 0)
MEETUP_METHOD(saturteenth, Saturday, 0)
MEETUP_METHOD(sunteenth, Sunday, 0)

MEETUP_METHOD(first_monday, Monday, 1)
MEETUP_METHOD(first_tuesday, Tuesday, 1)
MEETUP_METHOD(first_wednesday, Wednesday, 1)
MEETUP_METHOD(first_thursday, Thursday, 1)
MEETUP_METHOD(first_friday, Friday, 1)
MEETUP_METHOD(first_saturday, Saturday, 1)
MEETUP_METHOD(first_sunday, Sunday, 1)

MEETUP_METHOD(second_monday, Monday, 2)
MEETUP_METHOD(second_tuesday, Tuesday, 2)
MEETUP_METHOD(second_wednesday, Wednesday, 2)
MEETUP_METHOD(second_thursday, Thursday, 2)
MEETUP_METHOD(second_friday, Friday, 2)
MEETUP_METHOD(second_saturday, Saturday, 2)
MEETUP_METHOD(second_sunday, Sunday, 2)

MEETUP_METHOD(third_monday, Monday, 3)
MEETUP_METHOD(third_tuesday, Tuesday, 3)
MEETUP_METHOD(third_wednesday, Wednesday, 3)
MEETUP_METHOD(third_thursday, Thursday, 3)
MEETUP_METHOD(third_friday, Friday, 3)
MEETUP_METHOD(third_saturday, Saturday, 3)
MEETUP_METHOD(third_sunday, Sunday, 3)

MEETUP_METHOD(fourth_monday, Monday, 4)
MEETUP_METHOD(fourth_tuesday, Tuesday, 4)
MEETUP_METHOD(fourth_wednesday, Wednesday, 4)
MEETUP_METHOD(fourth_thursday, Thursday, 4)
MEETUP_METHOD(fourth_friday, Friday, 4)
MEETUP_METHOD(fourth_saturday, Saturday, 4)
MEETUP_METHOD(fourth_sunday, Sunday, 4)

MEETUP_METHOD(last_monday, Monday, -1)
MEETUP_METHOD(last_tuesday, Tuesday, -1)
MEETUP_METHOD(last_wednesday, Wednesday, -1)
MEETUP_METHOD(last_thursday, Thursday, -1)
MEETUP_METHOD(last_friday, Friday, -1)
MEETUP_METHOD(last_saturday, Saturday, -1)
MEETUP_METHOD(last_sunday, Sunday, -1)

#undef MEETUP_METHOD

}  // namespace meetup
