#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <ctime>

namespace meetup {

namespace {

// ------------------------------------------------------------------
// Helper utilities
// ------------------------------------------------------------------

// Leap-year check (Gregorian calendar rules)
constexpr bool is_leap(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Number of days in the given month of the given year.
constexpr unsigned int days_in_month(int year, unsigned int month)
{
    constexpr unsigned int table[]{31, 28, 31, 30, 31, 30,
                                   31, 31, 30, 31, 30, 31};

    if (month == 2)
        return is_leap(year) ? 29 : 28;

    return table[month - 1];
}

} // namespace (anon)

// ------------------------------------------------------------------
// scheduler implementation
// ------------------------------------------------------------------
scheduler::scheduler(int year, unsigned int month)
    : m_year{year}
    , m_month{month}
{
    if (month == 0 || month > 12)
        throw std::invalid_argument("month must be in the range 1-12");
}

boost::gregorian::date
scheduler::get_day(int target_wd, schedule sch) const
{
    // target_wd: 0 = Sunday, 1 = Monday, … 6 = Saturday

    // Weekday of the first day of the month
    const int wd_first = [&] {
        std::tm tm{};
        tm.tm_year = m_year - 1900;
        tm.tm_mon  = m_month - 1;
        tm.tm_mday = 1;
        std::mktime(&tm);
        return tm.tm_wday; // 0..6
    }();

    const unsigned offset =
        static_cast<unsigned>((target_wd - wd_first + 7) % 7);

    unsigned day_number{0};

    switch (sch)
    {
    case schedule::first:
    case schedule::second:
    case schedule::third:
    case schedule::fourth: {
        const unsigned nth = static_cast<unsigned>(sch); // 0,1,2,3
        day_number         = 1 + offset + 7 * nth;
        break;
    }

    case schedule::teenth: {
        for (unsigned d = 13; d <= 19; ++d)
        {
            boost::gregorian::date candidate(m_year, m_month, d);
            if (candidate.day_of_week().as_number() == target_wd)
            {
                day_number = d;
                break;
            }
        }
        break;
    }

    case schedule::last: {
        const unsigned dim = days_in_month(m_year, m_month);
        boost::gregorian::date last_day(m_year, m_month, dim);
        const unsigned wd_last = last_day.day_of_week().as_number();

        const unsigned diff = (wd_last + 7 - static_cast<unsigned>(target_wd)) % 7;

        day_number = dim - diff;
        break;
    }

    default:
        throw std::invalid_argument("unknown schedule value");
    }

    return boost::gregorian::date(m_year, m_month, day_number);
}

#define MEETUP_DEFINE_METHOD(name, wd, sch) \
    boost::gregorian::date scheduler::name() const { return get_day(wd, sch); }

// “teenth”
MEETUP_DEFINE_METHOD(monteenth,      1, schedule::teenth)
MEETUP_DEFINE_METHOD(tuesteenth,     2, schedule::teenth)
MEETUP_DEFINE_METHOD(wednesteenth,   3, schedule::teenth)
MEETUP_DEFINE_METHOD(thursteenth,    4, schedule::teenth)
MEETUP_DEFINE_METHOD(friteenth,      5, schedule::teenth)
MEETUP_DEFINE_METHOD(saturteenth,    6, schedule::teenth)
MEETUP_DEFINE_METHOD(sunteenth,      0, schedule::teenth)

// first
MEETUP_DEFINE_METHOD(first_monday,    1, schedule::first)
MEETUP_DEFINE_METHOD(first_tuesday,   2, schedule::first)
MEETUP_DEFINE_METHOD(first_wednesday, 3, schedule::first)
MEETUP_DEFINE_METHOD(first_thursday,  4, schedule::first)
MEETUP_DEFINE_METHOD(first_friday,    5, schedule::first)
MEETUP_DEFINE_METHOD(first_saturday,  6, schedule::first)
MEETUP_DEFINE_METHOD(first_sunday,    0, schedule::first)

// second
MEETUP_DEFINE_METHOD(second_monday,    1, schedule::second)
MEETUP_DEFINE_METHOD(second_tuesday,   2, schedule::second)
MEETUP_DEFINE_METHOD(second_wednesday, 3, schedule::second)
MEETUP_DEFINE_METHOD(second_thursday,  4, schedule::second)
MEETUP_DEFINE_METHOD(second_friday,    5, schedule::second)
MEETUP_DEFINE_METHOD(second_saturday,  6, schedule::second)
MEETUP_DEFINE_METHOD(second_sunday,    0, schedule::second)

// third
MEETUP_DEFINE_METHOD(third_monday,    1, schedule::third)
MEETUP_DEFINE_METHOD(third_tuesday,   2, schedule::third)
MEETUP_DEFINE_METHOD(third_wednesday, 3, schedule::third)
MEETUP_DEFINE_METHOD(third_thursday,  4, schedule::third)
MEETUP_DEFINE_METHOD(third_friday,    5, schedule::third)
MEETUP_DEFINE_METHOD(third_saturday,  6, schedule::third)
MEETUP_DEFINE_METHOD(third_sunday,    0, schedule::third)

// fourth
MEETUP_DEFINE_METHOD(fourth_monday,    1, schedule::fourth)
MEETUP_DEFINE_METHOD(fourth_tuesday,   2, schedule::fourth)
MEETUP_DEFINE_METHOD(fourth_wednesday, 3, schedule::fourth)
MEETUP_DEFINE_METHOD(fourth_thursday,  4, schedule::fourth)
MEETUP_DEFINE_METHOD(fourth_friday,    5, schedule::fourth)
MEETUP_DEFINE_METHOD(fourth_saturday,  6, schedule::fourth)
MEETUP_DEFINE_METHOD(fourth_sunday,    0, schedule::fourth)

// last
MEETUP_DEFINE_METHOD(last_monday,    1, schedule::last)
MEETUP_DEFINE_METHOD(last_tuesday,   2, schedule::last)
MEETUP_DEFINE_METHOD(last_wednesday, 3, schedule::last)
MEETUP_DEFINE_METHOD(last_thursday,  4, schedule::last)
MEETUP_DEFINE_METHOD(last_friday,    5, schedule::last)
MEETUP_DEFINE_METHOD(last_saturday,  6, schedule::last)
MEETUP_DEFINE_METHOD(last_sunday,    0, schedule::last)

#undef MEETUP_DEFINE_METHOD

}  // namespace meetup
