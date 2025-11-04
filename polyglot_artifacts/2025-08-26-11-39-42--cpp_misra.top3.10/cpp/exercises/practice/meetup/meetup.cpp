#include "meetup.h"

namespace meetup {

namespace {

constexpr day_t days_in_month(year_t year, month_t month)
{
    switch(month) {
        case 1U: return 31U;
        case 2U: {
            if(((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0))) {
                return 29U;
            } else {
                return 28U;
            }
        }
        case 3U: return 31U;
        case 4U: return 30U;
        case 5U: return 31U;
        case 6U: return 30U;
        case 7U: return 31U;
        case 8U: return 31U;
        case 9U: return 30U;
        case 10U: return 31U;
        case 11U: return 30U;
        case 12U: return 31U;
        default: return 0U;
    }
}

// Returns 0=Sunday, 1=Monday, ..., 6=Saturday
constexpr std::uint8_t weekday_of(year_t year, month_t month, day_t day)
{
    year_t y = year;
    month_t m = month;
    if(m < 3U) {
        m = static_cast<month_t>(m + 12U);
        y = static_cast<year_t>(y - 1);
    }
    std::uint8_t K = static_cast<std::uint8_t>(y % 100);
    std::uint8_t J = static_cast<std::uint8_t>(y / 100);
    std::uint8_t h = static_cast<std::uint8_t>(
        (day + (13U * (m + 1U)) / 5U + K + (K / 4U) + (J / 4U) + (5U * J)) % 7U
    );
    // h: 0=Saturday, 1=Sunday, ..., 6=Friday
    return static_cast<std::uint8_t>((h + 6U) % 7U);
}

} // anonymous namespace

scheduler::scheduler(month_t month, year_t year) noexcept
    : m_month(month), m_year(year)
{
}

day_t scheduler::get_day(std::uint8_t weekday, std::uint8_t n) const noexcept
{
    day_t d = 1U;
    day_t count = 0U;
    day_t dim = days_in_month(m_year, m_month);
    for(; d <= dim; ++d) {
        if(weekday_of(m_year, m_month, d) == weekday) {
            if(count == n) {
                return d;
            }
            count = static_cast<day_t>(count + 1U);
        }
    }
    return 0U;
}

day_t scheduler::get_teenth(std::uint8_t weekday) const noexcept
{
    for(day_t d = 13U; d <= 19U; ++d) {
        if(weekday_of(m_year, m_month, d) == weekday) {
            return d;
        }
    }
    return 0U;
}

day_t scheduler::get_last(std::uint8_t weekday) const noexcept
{
    day_t dim = days_in_month(m_year, m_month);
    for(day_t d = dim; d >= 1U; --d) {
        if(weekday_of(m_year, m_month, d) == weekday) {
            return d;
        }
    }
    return 0U;
}

// Teenth
day_t scheduler::monteenth() const noexcept { return get_teenth(1U); }
day_t scheduler::tuesteenth() const noexcept { return get_teenth(2U); }
day_t scheduler::wednesteenth() const noexcept { return get_teenth(3U); }
day_t scheduler::thursteenth() const noexcept { return get_teenth(4U); }
day_t scheduler::friteenth() const noexcept { return get_teenth(5U); }
day_t scheduler::saturteenth() const noexcept { return get_teenth(6U); }
day_t scheduler::sunteenth() const noexcept { return get_teenth(0U); }

// First
day_t scheduler::first_monday() const noexcept { return get_day(1U, 0U); }
day_t scheduler::first_tuesday() const noexcept { return get_day(2U, 0U); }
day_t scheduler::first_wednesday() const noexcept { return get_day(3U, 0U); }
day_t scheduler::first_thursday() const noexcept { return get_day(4U, 0U); }
day_t scheduler::first_friday() const noexcept { return get_day(5U, 0U); }
day_t scheduler::first_saturday() const noexcept { return get_day(6U, 0U); }
day_t scheduler::first_sunday() const noexcept { return get_day(0U, 0U); }

// Second
day_t scheduler::second_monday() const noexcept { return get_day(1U, 1U); }
day_t scheduler::second_tuesday() const noexcept { return get_day(2U, 1U); }
day_t scheduler::second_wednesday() const noexcept { return get_day(3U, 1U); }
day_t scheduler::second_thursday() const noexcept { return get_day(4U, 1U); }
day_t scheduler::second_friday() const noexcept { return get_day(5U, 1U); }
day_t scheduler::second_saturday() const noexcept { return get_day(6U, 1U); }
day_t scheduler::second_sunday() const noexcept { return get_day(0U, 1U); }

// Third
day_t scheduler::third_monday() const noexcept { return get_day(1U, 2U); }
day_t scheduler::third_tuesday() const noexcept { return get_day(2U, 2U); }
day_t scheduler::third_wednesday() const noexcept { return get_day(3U, 2U); }
day_t scheduler::third_thursday() const noexcept { return get_day(4U, 2U); }
day_t scheduler::third_friday() const noexcept { return get_day(5U, 2U); }
day_t scheduler::third_saturday() const noexcept { return get_day(6U, 2U); }
day_t scheduler::third_sunday() const noexcept { return get_day(0U, 2U); }

// Fourth
day_t scheduler::fourth_monday() const noexcept { return get_day(1U, 3U); }
day_t scheduler::fourth_tuesday() const noexcept { return get_day(2U, 3U); }
day_t scheduler::fourth_wednesday() const noexcept { return get_day(3U, 3U); }
day_t scheduler::fourth_thursday() const noexcept { return get_day(4U, 3U); }
day_t scheduler::fourth_friday() const noexcept { return get_day(5U, 3U); }
day_t scheduler::fourth_saturday() const noexcept { return get_day(6U, 3U); }
day_t scheduler::fourth_sunday() const noexcept { return get_day(0U, 3U); }

// Last
day_t scheduler::last_monday() const noexcept { return get_last(1U); }
day_t scheduler::last_tuesday() const noexcept { return get_last(2U); }
day_t scheduler::last_wednesday() const noexcept { return get_last(3U); }
day_t scheduler::last_thursday() const noexcept { return get_last(4U); }
day_t scheduler::last_friday() const noexcept { return get_last(5U); }
day_t scheduler::last_saturday() const noexcept { return get_last(6U); }
day_t scheduler::last_sunday() const noexcept { return get_last(0U); }

} // namespace meetup
