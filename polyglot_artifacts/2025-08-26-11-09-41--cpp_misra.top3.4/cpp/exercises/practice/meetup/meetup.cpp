#include "meetup.h"
#include <ctime>
#include <stdexcept>

namespace meetup {

scheduler::scheduler(month_t month, year_t year)
    : m_year(year), m_month(month)
{
}

day_t scheduler::monteenth() const
{
    return day(m_year, m_month, weekday::Monday, schedule::teenth);
}
day_t scheduler::tuesteenth() const
{
    return day(m_year, m_month, weekday::Tuesday, schedule::teenth);
}
day_t scheduler::wednesteenth() const
{
    return day(m_year, m_month, weekday::Wednesday, schedule::teenth);
}
day_t scheduler::thursteenth() const
{
    return day(m_year, m_month, weekday::Thursday, schedule::teenth);
}
day_t scheduler::friteenth() const
{
    return day(m_year, m_month, weekday::Friday, schedule::teenth);
}
day_t scheduler::saturteenth() const
{
    return day(m_year, m_month, weekday::Saturday, schedule::teenth);
}
day_t scheduler::sunteenth() const
{
    return day(m_year, m_month, weekday::Sunday, schedule::teenth);
}

day_t scheduler::first_monday() const
{
    return day(m_year, m_month, weekday::Monday, schedule::first);
}
day_t scheduler::first_tuesday() const
{
    return day(m_year, m_month, weekday::Tuesday, schedule::first);
}
day_t scheduler::first_wednesday() const
{
    return day(m_year, m_month, weekday::Wednesday, schedule::first);
}
day_t scheduler::first_thursday() const
{
    return day(m_year, m_month, weekday::Thursday, schedule::first);
}
day_t scheduler::first_friday() const
{
    return day(m_year, m_month, weekday::Friday, schedule::first);
}
day_t scheduler::first_saturday() const
{
    return day(m_year, m_month, weekday::Saturday, schedule::first);
}
day_t scheduler::first_sunday() const
{
    return day(m_year, m_month, weekday::Sunday, schedule::first);
}

day_t scheduler::second_monday() const
{
    return day(m_year, m_month, weekday::Monday, schedule::second);
}
day_t scheduler::second_tuesday() const
{
    return day(m_year, m_month, weekday::Tuesday, schedule::second);
}
day_t scheduler::second_wednesday() const
{
    return day(m_year, m_month, weekday::Wednesday, schedule::second);
}
day_t scheduler::second_thursday() const
{
    return day(m_year, m_month, weekday::Thursday, schedule::second);
}
day_t scheduler::second_friday() const
{
    return day(m_year, m_month, weekday::Friday, schedule::second);
}
day_t scheduler::second_saturday() const
{
    return day(m_year, m_month, weekday::Saturday, schedule::second);
}
day_t scheduler::second_sunday() const
{
    return day(m_year, m_month, weekday::Sunday, schedule::second);
}

day_t scheduler::third_monday() const
{
    return day(m_year, m_month, weekday::Monday, schedule::third);
}
day_t scheduler::third_tuesday() const
{
    return day(m_year, m_month, weekday::Tuesday, schedule::third);
}
day_t scheduler::third_wednesday() const
{
    return day(m_year, m_month, weekday::Wednesday, schedule::third);
}
day_t scheduler::third_thursday() const
{
    return day(m_year, m_month, weekday::Thursday, schedule::third);
}
day_t scheduler::third_friday() const
{
    return day(m_year, m_month, weekday::Friday, schedule::third);
}
day_t scheduler::third_saturday() const
{
    return day(m_year, m_month, weekday::Saturday, schedule::third);
}
day_t scheduler::third_sunday() const
{
    return day(m_year, m_month, weekday::Sunday, schedule::third);
}

day_t scheduler::fourth_monday() const
{
    return day(m_year, m_month, weekday::Monday, schedule::fourth);
}
day_t scheduler::fourth_tuesday() const
{
    return day(m_year, m_month, weekday::Tuesday, schedule::fourth);
}
day_t scheduler::fourth_wednesday() const
{
    return day(m_year, m_month, weekday::Wednesday, schedule::fourth);
}
day_t scheduler::fourth_thursday() const
{
    return day(m_year, m_month, weekday::Thursday, schedule::fourth);
}
day_t scheduler::fourth_friday() const
{
    return day(m_year, m_month, weekday::Friday, schedule::fourth);
}
day_t scheduler::fourth_saturday() const
{
    return day(m_year, m_month, weekday::Saturday, schedule::fourth);
}
day_t scheduler::fourth_sunday() const
{
    return day(m_year, m_month, weekday::Sunday, schedule::fourth);
}

day_t scheduler::last_monday() const
{
    return day(m_year, m_month, weekday::Monday, schedule::last);
}
day_t scheduler::last_tuesday() const
{
    return day(m_year, m_month, weekday::Tuesday, schedule::last);
}
day_t scheduler::last_wednesday() const
{
    return day(m_year, m_month, weekday::Wednesday, schedule::last);
}
day_t scheduler::last_thursday() const
{
    return day(m_year, m_month, weekday::Thursday, schedule::last);
}
day_t scheduler::last_friday() const
{
    return day(m_year, m_month, weekday::Friday, schedule::last);
}
day_t scheduler::last_saturday() const
{
    return day(m_year, m_month, weekday::Saturday, schedule::last);
}
day_t scheduler::last_sunday() const
{
    return day(m_year, m_month, weekday::Sunday, schedule::last);
}

namespace {
    // Helper: Return true if y is a leap year
    bool is_leap_year(meetup::year_t y)
    {
        return (((y % 4) == 0) && (((y % 100) != 0) || ((y % 400) == 0)));
    }

    // Helper: Return number of days in a month
    meetup::day_t days_in_month(meetup::year_t y, meetup::month_t m)
    {
        static const meetup::day_t days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if ((m == 2U) && is_leap_year(y)) {
            return 29U;
        }
        return days[m - 1U];
    }

    // Helper: Zeller's congruence to get weekday (0=Sunday, 1=Monday, ..., 6=Saturday)
    meetup::weekday calc_weekday(meetup::year_t y, meetup::month_t m, meetup::day_t d)
    {
        meetup::year_t year = y;
        meetup::month_t month = m;
        if (month < 3U) {
            month = static_cast<meetup::month_t>(month + 12U);
            year = static_cast<meetup::year_t>(year - 1);
        }
        std::int32_t K = static_cast<std::int32_t>(year % 100);
        std::int32_t J = static_cast<std::int32_t>(year / 100);
        std::int32_t h = (d + (13 * (month + 1) / 5) + K + (K / 4) + (J / 4) + (5 * J));
        h = h % 7;
        // Zeller's: 0=Saturday, 1=Sunday, ..., 6=Friday
        // We want: 0=Sunday, 1=Monday, ..., 6=Saturday
        std::int32_t zeller_to_sunday = (h + 6) % 7;
        return static_cast<meetup::weekday>(zeller_to_sunday);
    }
}

meetup::day_t day(meetup::year_t year, meetup::month_t month, meetup::weekday wd, meetup::schedule sched)
{
    meetup::day_t result = 0U;
    meetup::day_t dim = days_in_month(year, month);

    if (sched == meetup::schedule::teenth) {
        for (meetup::day_t d = 13U; d <= 19U; ++d) {
            if (calc_weekday(year, month, d) == wd) {
                result = d;
                break;
            }
        }
    } else if (sched == meetup::schedule::last) {
        for (meetup::day_t d = dim; d >= 1U; --d) {
            if (calc_weekday(year, month, d) == wd) {
                result = d;
                break;
            }
        }
    } else {
        // first=0, second=1, third=2, fourth=3
        std::uint8_t week_offset = 0U;
        if (sched == meetup::schedule::first) {
            week_offset = 0U;
        } else if (sched == meetup::schedule::second) {
            week_offset = 1U;
        } else if (sched == meetup::schedule::third) {
            week_offset = 2U;
        } else if (sched == meetup::schedule::fourth) {
            week_offset = 3U;
        } else {
            throw std::invalid_argument("Invalid schedule");
        }
        // Find first day of month with correct weekday
        for (meetup::day_t d = 1U; d <= 7U; ++d) {
            if (calc_weekday(year, month, d) == wd) {
                result = static_cast<meetup::day_t>(d + (week_offset * 7U));
                break;
            }
        }
        // If result is out of month, throw
        if ((result < 1U) || (result > dim)) {
            throw std::out_of_range("No such day in month");
        }
    }
    return result;
}

}  // namespace meetup
