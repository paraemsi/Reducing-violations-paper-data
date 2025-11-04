#include "meetup.h"
#include <stdexcept>

namespace meetup {

namespace {

constexpr meetup::day_t days_in_month(meetup::year_t year, meetup::month_t month)
{
    switch (month) {
        case 1U: case 3U: case 5U: case 7U: case 8U: case 10U: case 12U:
            return static_cast<meetup::day_t>(31);
        case 4U: case 6U: case 9U: case 11U:
            return static_cast<meetup::day_t>(30);
        case 2U:
            if (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0))) {
                return static_cast<meetup::day_t>(29);
            } else {
                return static_cast<meetup::day_t>(28);
            }
        default:
            throw std::invalid_argument("Invalid month");
    }
}

// Returns 0=Sunday, 1=Monday, ..., 6=Saturday
std::uint8_t weekday_of(meetup::year_t year, meetup::month_t month, meetup::day_t day)
{
    meetup::year_t y = year;
    meetup::month_t m = month;
    if (m < static_cast<meetup::month_t>(3U)) {
        m = static_cast<meetup::month_t>(m + 12U);
        y = static_cast<meetup::year_t>(y - 1);
    }
    std::int32_t K = static_cast<std::int32_t>(y % 100);
    std::int32_t J = static_cast<std::int32_t>(y / 100);
    std::int32_t d = static_cast<std::int32_t>(day);
    std::int32_t h = (d + ((13 * (static_cast<std::int32_t>(m) + 1)) / 5) + K + (K / 4) + (J / 4) + (5 * J));
    h = h % 7;
    std::uint8_t result = static_cast<std::uint8_t>((h + 6) % 7);
    return result;
}

} // anonymous namespace

scheduler::scheduler(month_t month, year_t year)
    : m_month(month), m_year(year)
{
}

day_t scheduler::find_day(std::uint8_t weekday, std::uint8_t n) const
{
    // n = 1 (first), 2 (second), 3 (third), 4 (fourth)
    day_t start = static_cast<day_t>(1U + (n - 1U) * 7U);
    day_t end = static_cast<day_t>(start + 6U);
    day_t dim = days_in_month(m_year, m_month);
    if (end > dim) {
        end = dim;
    }
    for (day_t d = start; d <= end; d = static_cast<day_t>(d + 1U)) {
        if (weekday_of(m_year, m_month, d) == weekday) {
            return d;
        }
    }
    throw std::domain_error("No such meetup day in this month");
}

day_t scheduler::find_teenth(std::uint8_t weekday) const
{
    for (day_t d = 13U; d <= 19U; d = static_cast<day_t>(d + 1U)) {
        if (weekday_of(m_year, m_month, d) == weekday) {
            return d;
        }
    }
    throw std::domain_error("No such teenth day in this month");
}

day_t scheduler::find_last(std::uint8_t weekday) const
{
    day_t dim = days_in_month(m_year, m_month);
    for (day_t d = dim; d >= static_cast<day_t>(1U); d = static_cast<day_t>(d - 1U)) {
        if (weekday_of(m_year, m_month, d) == weekday) {
            return d;
        }
    }
    throw std::domain_error("No such last day in this month");
}

// "teenth" methods
day_t scheduler::monteenth() const { return find_teenth(1U); }
day_t scheduler::tuesteenth() const { return find_teenth(2U); }
day_t scheduler::wednesteenth() const { return find_teenth(3U); }
day_t scheduler::thursteenth() const { return find_teenth(4U); }
day_t scheduler::friteenth() const { return find_teenth(5U); }
day_t scheduler::saturteenth() const { return find_teenth(6U); }
day_t scheduler::sunteenth() const { return find_teenth(0U); }

// "first" methods
day_t scheduler::first_monday() const { return find_day(1U, 1U); }
day_t scheduler::first_tuesday() const { return find_day(2U, 1U); }
day_t scheduler::first_wednesday() const { return find_day(3U, 1U); }
day_t scheduler::first_thursday() const { return find_day(4U, 1U); }
day_t scheduler::first_friday() const { return find_day(5U, 1U); }
day_t scheduler::first_saturday() const { return find_day(6U, 1U); }
day_t scheduler::first_sunday() const { return find_day(0U, 1U); }

// "second" methods
day_t scheduler::second_monday() const { return find_day(1U, 2U); }
day_t scheduler::second_tuesday() const { return find_day(2U, 2U); }
day_t scheduler::second_wednesday() const { return find_day(3U, 2U); }
day_t scheduler::second_thursday() const { return find_day(4U, 2U); }
day_t scheduler::second_friday() const { return find_day(5U, 2U); }
day_t scheduler::second_saturday() const { return find_day(6U, 2U); }
day_t scheduler::second_sunday() const { return find_day(0U, 2U); }

// "third" methods
day_t scheduler::third_monday() const { return find_day(1U, 3U); }
day_t scheduler::third_tuesday() const { return find_day(2U, 3U); }
day_t scheduler::third_wednesday() const { return find_day(3U, 3U); }
day_t scheduler::third_thursday() const { return find_day(4U, 3U); }
day_t scheduler::third_friday() const { return find_day(5U, 3U); }
day_t scheduler::third_saturday() const { return find_day(6U, 3U); }
day_t scheduler::third_sunday() const { return find_day(0U, 3U); }

// "fourth" methods
day_t scheduler::fourth_monday() const { return find_day(1U, 4U); }
day_t scheduler::fourth_tuesday() const { return find_day(2U, 4U); }
day_t scheduler::fourth_wednesday() const { return find_day(3U, 4U); }
day_t scheduler::fourth_thursday() const { return find_day(4U, 4U); }
day_t scheduler::fourth_friday() const { return find_day(5U, 4U); }
day_t scheduler::fourth_saturday() const { return find_day(6U, 4U); }
day_t scheduler::fourth_sunday() const { return find_day(0U, 4U); }

// "last" methods
day_t scheduler::last_monday() const { return find_last(1U); }
day_t scheduler::last_tuesday() const { return find_last(2U); }
day_t scheduler::last_wednesday() const { return find_last(3U); }
day_t scheduler::last_thursday() const { return find_last(4U); }
day_t scheduler::last_friday() const { return find_last(5U); }
day_t scheduler::last_saturday() const { return find_last(6U); }
day_t scheduler::last_sunday() const { return find_last(0U); }

}  // namespace meetup
