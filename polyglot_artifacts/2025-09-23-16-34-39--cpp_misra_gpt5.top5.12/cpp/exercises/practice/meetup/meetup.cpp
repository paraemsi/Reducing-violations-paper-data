#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <sstream>
#include <iomanip>
#include <string>

namespace meetup {

namespace {

// Gregorian leap year check
inline bool is_leap_year(std::uint16_t year) noexcept
{
    // Leap if divisible by 400, or divisible by 4 and not by 100.
    const std::uint16_t y = year;
    const bool div_by_400 = ((static_cast<std::uint32_t>(y) % static_cast<std::uint32_t>(400U)) == static_cast<std::uint32_t>(0U));
    const bool div_by_100 = ((static_cast<std::uint32_t>(y) % static_cast<std::uint32_t>(100U)) == static_cast<std::uint32_t>(0U));
    const bool div_by_4   = ((static_cast<std::uint32_t>(y) % static_cast<std::uint32_t>(4U)) == static_cast<std::uint32_t>(0U));

    return (div_by_400 || (div_by_4 && (!div_by_100)));
}

inline std::uint8_t days_in_month(std::uint16_t year, std::uint8_t month)
{
    if ((month == static_cast<std::uint8_t>(1U)) ||
        (month == static_cast<std::uint8_t>(3U)) ||
        (month == static_cast<std::uint8_t>(5U)) ||
        (month == static_cast<std::uint8_t>(7U)) ||
        (month == static_cast<std::uint8_t>(8U)) ||
        (month == static_cast<std::uint8_t>(10U)) ||
        (month == static_cast<std::uint8_t>(12U)))
    {
        return static_cast<std::uint8_t>(31U);
    }

    if ((month == static_cast<std::uint8_t>(4U)) ||
        (month == static_cast<std::uint8_t>(6U)) ||
        (month == static_cast<std::uint8_t>(9U)) ||
        (month == static_cast<std::uint8_t>(11U)))
    {
        return static_cast<std::uint8_t>(30U);
    }

    // February
    if (month == static_cast<std::uint8_t>(2U))
    {
        return is_leap_year(year) ? static_cast<std::uint8_t>(29U) : static_cast<std::uint8_t>(28U);
    }

    throw std::out_of_range("month must be in 1..12");
}

// Zeller's congruence (Gregorian) to get weekday index for Y-M-D.
// Returns 0=Sunday, 1=Monday, ..., 6=Saturday
inline std::uint8_t weekday_index(std::uint16_t year, std::uint8_t month, std::uint8_t day)
{
    if ((month < static_cast<std::uint8_t>(1U)) || (month > static_cast<std::uint8_t>(12U)))
    {
        throw std::out_of_range("month must be in 1..12");
    }

    const std::uint8_t dim = days_in_month(year, month);
    if ((day < static_cast<std::uint8_t>(1U)) || (day > dim))
    {
        throw std::out_of_range("day out of range for month");
    }

    std::uint32_t y = static_cast<std::uint32_t>(year);
    std::uint32_t m = static_cast<std::uint32_t>(month);
    const std::uint32_t d = static_cast<std::uint32_t>(day);

    if (m <= static_cast<std::uint32_t>(2U))
    {
        m = static_cast<std::uint32_t>(m + static_cast<std::uint32_t>(12U));
        y = static_cast<std::uint32_t>(y - static_cast<std::uint32_t>(1U));
    }

    const std::uint32_t K = static_cast<std::uint32_t>(y % static_cast<std::uint32_t>(100U));
    const std::uint32_t J = static_cast<std::uint32_t>(y / static_cast<std::uint32_t>(100U));

    const std::uint32_t term1 = d;
    const std::uint32_t term2 = static_cast<std::uint32_t>((static_cast<std::uint32_t>(13U) * (m + static_cast<std::uint32_t>(1U))) / static_cast<std::uint32_t>(5U));
    const std::uint32_t term3 = K;
    const std::uint32_t term4 = static_cast<std::uint32_t>(K / static_cast<std::uint32_t>(4U));
    const std::uint32_t term5 = static_cast<std::uint32_t>(J / static_cast<std::uint32_t>(4U));
    const std::uint32_t term6 = static_cast<std::uint32_t>(5U) * J;

    const std::uint32_t h = static_cast<std::uint32_t>((term1 + term2 + term3 + term4 + term5 + term6) % static_cast<std::uint32_t>(7U));
    // Convert h (0=Sat, 1=Sun, 2=Mon, ..., 6=Fri) to 0=Sun..6=Sat
    const std::uint32_t w = static_cast<std::uint32_t>((h + static_cast<std::uint32_t>(6U)) % static_cast<std::uint32_t>(7U));

    return static_cast<std::uint8_t>(w);
}

} // anonymous namespace

scheduler::scheduler(std::uint16_t year, std::uint8_t month) noexcept
    : m_year{year}, m_month{month}
{
    // no validation here; validated in member functions
}

scheduler::scheduler(std::uint8_t month, std::uint16_t year) noexcept
    : m_year{year}, m_month{month}
{
    // no validation here; validated in member functions
}

scheduler::scheduler(std::int32_t month, std::int32_t year) noexcept
    : m_year{static_cast<std::uint16_t>(year)}, m_month{static_cast<std::uint8_t>(month)}
{
    // Parameters validated later in member functions; ensure tests construct without narrowing
}


std::uint8_t scheduler::day(weekday which_weekday, schedule which_schedule) const
{
    if ((m_month < static_cast<std::uint8_t>(1U)) || (m_month > static_cast<std::uint8_t>(12U)))
    {
        throw std::out_of_range("month must be in 1..12");
    }

    const std::uint8_t last_day = days_in_month(m_year, m_month);
    const std::uint8_t target_w = static_cast<std::uint8_t>(which_weekday); // 0..6

    if (which_schedule == schedule::teenth)
    {
        for (std::uint32_t d = static_cast<std::uint32_t>(13U); d <= static_cast<std::uint32_t>(19U); d = static_cast<std::uint32_t>(d + static_cast<std::uint32_t>(1U)))
        {
            const std::uint8_t w = weekday_index(m_year, m_month, static_cast<std::uint8_t>(d));
            if (w == target_w)
            {
                return static_cast<std::uint8_t>(d);
            }
        }
        throw std::runtime_error("No teenth day found"); // defensive; logically unreachable
    }

    if (which_schedule == schedule::last)
    {
        const std::uint8_t last_w = weekday_index(m_year, m_month, last_day);
        const std::uint8_t delta_back = static_cast<std::uint8_t>((static_cast<std::uint32_t>(last_w + static_cast<std::uint8_t>(7U) - target_w)) % static_cast<std::uint32_t>(7U));
        const std::uint32_t result = static_cast<std::uint32_t>(last_day) - static_cast<std::uint32_t>(delta_back);

        if ((result < static_cast<std::uint32_t>(1U)) || (result > static_cast<std::uint32_t>(last_day)))
        {
            throw std::runtime_error("Computed day out of range");
        }
        return static_cast<std::uint8_t>(result);
    }

    // first..fourth
    std::uint8_t n = static_cast<std::uint8_t>(0U);
    if (which_schedule == schedule::first)
    {
        n = static_cast<std::uint8_t>(1U);
    }
    else if (which_schedule == schedule::second)
    {
        n = static_cast<std::uint8_t>(2U);
    }
    else if (which_schedule == schedule::third)
    {
        n = static_cast<std::uint8_t>(3U);
    }
    else if (which_schedule == schedule::fourth)
    {
        n = static_cast<std::uint8_t>(4U);
    }
    else
    {
        throw std::invalid_argument("Unsupported schedule");
    }

    const std::uint8_t w_first = weekday_index(m_year, m_month, static_cast<std::uint8_t>(1U));
    const std::uint8_t delta_fwd = static_cast<std::uint8_t>((static_cast<std::uint32_t>(target_w + static_cast<std::uint8_t>(7U) - w_first)) % static_cast<std::uint32_t>(7U));

    const std::uint32_t base = static_cast<std::uint32_t>(1U) + static_cast<std::uint32_t>(delta_fwd);
    const std::uint32_t result = static_cast<std::uint32_t>(base + (static_cast<std::uint32_t>(n - static_cast<std::uint8_t>(1U)) * static_cast<std::uint32_t>(7U)));

    if ((result < static_cast<std::uint32_t>(1U)) || (result > static_cast<std::uint32_t>(last_day)))
    {
        throw std::runtime_error("Computed day out of range");
    }

    return static_cast<std::uint8_t>(result);
}

// Helpers to build Boost date safely without numeric narrowing
namespace {

inline std::string iso_ymd(std::uint16_t year, std::uint8_t month, std::uint8_t day)
{
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << static_cast<std::uint32_t>(year);
    oss << std::setw(2) << std::setfill('0') << static_cast<std::uint32_t>(month);
    oss << std::setw(2) << std::setfill('0') << static_cast<std::uint32_t>(day);
    return oss.str();
}

inline boost::gregorian::date make_date(std::uint16_t year, std::uint8_t month, std::uint8_t day)
{
    const std::string iso = iso_ymd(year, month, day);
    return boost::gregorian::date_from_iso_string(iso);
}

} // anonymous namespace

// Teenth
boost::gregorian::date scheduler::monteenth() const
{
    const std::uint8_t d = day(weekday::monday, schedule::teenth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::tuesteenth() const
{
    const std::uint8_t d = day(weekday::tuesday, schedule::teenth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::wednesteenth() const
{
    const std::uint8_t d = day(weekday::wednesday, schedule::teenth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::thursteenth() const
{
    const std::uint8_t d = day(weekday::thursday, schedule::teenth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::friteenth() const
{
    const std::uint8_t d = day(weekday::friday, schedule::teenth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::saturteenth() const
{
    const std::uint8_t d = day(weekday::saturday, schedule::teenth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::sunteenth() const
{
    const std::uint8_t d = day(weekday::sunday, schedule::teenth);
    return make_date(m_year, m_month, d);
}

// First
boost::gregorian::date scheduler::first_monday() const
{
    const std::uint8_t d = day(weekday::monday, schedule::first);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::first_tuesday() const
{
    const std::uint8_t d = day(weekday::tuesday, schedule::first);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::first_wednesday() const
{
    const std::uint8_t d = day(weekday::wednesday, schedule::first);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::first_thursday() const
{
    const std::uint8_t d = day(weekday::thursday, schedule::first);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::first_friday() const
{
    const std::uint8_t d = day(weekday::friday, schedule::first);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::first_saturday() const
{
    const std::uint8_t d = day(weekday::saturday, schedule::first);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::first_sunday() const
{
    const std::uint8_t d = day(weekday::sunday, schedule::first);
    return make_date(m_year, m_month, d);
}

// Second
boost::gregorian::date scheduler::second_monday() const
{
    const std::uint8_t d = day(weekday::monday, schedule::second);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::second_tuesday() const
{
    const std::uint8_t d = day(weekday::tuesday, schedule::second);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::second_wednesday() const
{
    const std::uint8_t d = day(weekday::wednesday, schedule::second);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::second_thursday() const
{
    const std::uint8_t d = day(weekday::thursday, schedule::second);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::second_friday() const
{
    const std::uint8_t d = day(weekday::friday, schedule::second);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::second_saturday() const
{
    const std::uint8_t d = day(weekday::saturday, schedule::second);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::second_sunday() const
{
    const std::uint8_t d = day(weekday::sunday, schedule::second);
    return make_date(m_year, m_month, d);
}

// Third
boost::gregorian::date scheduler::third_monday() const
{
    const std::uint8_t d = day(weekday::monday, schedule::third);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::third_tuesday() const
{
    const std::uint8_t d = day(weekday::tuesday, schedule::third);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::third_wednesday() const
{
    const std::uint8_t d = day(weekday::wednesday, schedule::third);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::third_thursday() const
{
    const std::uint8_t d = day(weekday::thursday, schedule::third);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::third_friday() const
{
    const std::uint8_t d = day(weekday::friday, schedule::third);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::third_saturday() const
{
    const std::uint8_t d = day(weekday::saturday, schedule::third);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::third_sunday() const
{
    const std::uint8_t d = day(weekday::sunday, schedule::third);
    return make_date(m_year, m_month, d);
}

// Fourth
boost::gregorian::date scheduler::fourth_monday() const
{
    const std::uint8_t d = day(weekday::monday, schedule::fourth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::fourth_tuesday() const
{
    const std::uint8_t d = day(weekday::tuesday, schedule::fourth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::fourth_wednesday() const
{
    const std::uint8_t d = day(weekday::wednesday, schedule::fourth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::fourth_thursday() const
{
    const std::uint8_t d = day(weekday::thursday, schedule::fourth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::fourth_friday() const
{
    const std::uint8_t d = day(weekday::friday, schedule::fourth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::fourth_saturday() const
{
    const std::uint8_t d = day(weekday::saturday, schedule::fourth);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::fourth_sunday() const
{
    const std::uint8_t d = day(weekday::sunday, schedule::fourth);
    return make_date(m_year, m_month, d);
}

// Last
boost::gregorian::date scheduler::last_monday() const
{
    const std::uint8_t d = day(weekday::monday, schedule::last);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::last_tuesday() const
{
    const std::uint8_t d = day(weekday::tuesday, schedule::last);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::last_wednesday() const
{
    const std::uint8_t d = day(weekday::wednesday, schedule::last);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::last_thursday() const
{
    const std::uint8_t d = day(weekday::thursday, schedule::last);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::last_friday() const
{
    const std::uint8_t d = day(weekday::friday, schedule::last);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::last_saturday() const
{
    const std::uint8_t d = day(weekday::saturday, schedule::last);
    return make_date(m_year, m_month, d);
}

boost::gregorian::date scheduler::last_sunday() const
{
    const std::uint8_t d = day(weekday::sunday, schedule::last);
    return make_date(m_year, m_month, d);
}

}  // namespace meetup
