#include "meetup.h"
#include <array>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

// ----------------- helpers -------------------------------------------------

// Number of days in each month for a non-leap year.
static constexpr std::array<int, 12> month_lengths{{
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31}};

// Simple leap-year predicate (Gregorian calendar rules).
static constexpr bool is_leap(int year) noexcept
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int days_in_month(int year, unsigned int month)
{
    int days = month_lengths[month - 1];
    if (month == 2 && is_leap(year))
        ++days;
    return days;
}

// ---------------------------------------------------------------------------

scheduler::scheduler(int year, unsigned int month)
    : m_year{year},
      m_month{month}
{
    if (month < 1 || month > 12)
        throw std::invalid_argument{"month must be in the range 1..12"};
}

boost::gregorian::date
scheduler::day(boost::gregorian::greg_weekday wd, schedule s) const
{
    using boost::gregorian::date;

    const int dim = days_in_month(m_year, m_month);

    auto make_date = [&](int d) { return date(m_year, m_month, d); };

    const unsigned req_wd = wd.as_number(); // 0=Sun..6=Sat

    // --- teenth -------------------------------------------------------------
    if (s == schedule::teenth) {
        for (int d = 13; d <= 19; ++d) {
            if (make_date(d).day_of_week().as_number() == req_wd)
                return make_date(d);
        }
        throw std::logic_error{"no teenth day found"};
    }

    // --- first / second / third / fourth ------------------------------------
    const unsigned first_wd = make_date(1).day_of_week().as_number();
    int first_match_offset = static_cast<int>((req_wd + 7 - first_wd) % 7);

    int index = 0;
    switch (s) {
        case schedule::first:  index = 0; break;
        case schedule::second: index = 1; break;
        case schedule::third:  index = 2; break;
        case schedule::fourth: index = 3; break;
        case schedule::last:   index = -1; break; // special-cased below
        default: break;
    }

    if (s != schedule::last) {
        int day_number = 1 + first_match_offset + index * 7;
        if (day_number > dim)
            throw std::logic_error{"requested weekday/schedule does not exist"};
        return make_date(day_number);
    }

    // --- last ---------------------------------------------------------------
    for (int d = dim; d >= dim - 6; --d) {
        if (make_date(d).day_of_week().as_number() == req_wd)
            return make_date(d);
    }

    throw std::logic_error{"requested weekday/schedule does not exist"};
}

}  // namespace meetup
