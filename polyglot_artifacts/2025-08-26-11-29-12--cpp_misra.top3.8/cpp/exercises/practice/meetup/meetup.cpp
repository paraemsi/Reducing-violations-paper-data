#include "meetup.h"
#include <array>
#include <stdexcept>

namespace meetup {

namespace {

constexpr std::array<const char*, 7U> WEEKDAYS = {{"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"}};

std::uint8_t weekday_to_index(const std::string& weekday)
{
    for(std::uint8_t i = 0U; i < 7U; ++i)
    {
        if(weekday == WEEKDAYS[i])
        {
            return i;
        }
    }
    throw std::invalid_argument("Invalid weekday: " + weekday);
}

std::uint8_t days_in_month(meetup::year_t year, meetup::month_t month)
{
    if(month == 2U)
    {
        if(((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0)))
        {
            return 29U;
        }
        else
        {
            return 28U;
        }
    }
    if((month == 4U) || (month == 6U) || (month == 9U) || (month == 11U))
    {
        return 30U;
    }
    return 31U;
}

// 0=Monday, ..., 6=Sunday
std::uint8_t get_weekday(meetup::year_t year, meetup::month_t month, meetup::day_t day)
{
    // Zeller's congruence, but adjust for Monday=0
    std::int32_t y = year;
    std::uint8_t m = month;
    if(m < 3U)
    {
        m = static_cast<std::uint8_t>(m + 12U);
        y = y - 1;
    }
    std::int32_t K = y % 100;
    std::int32_t J = y / 100;
    std::int32_t h = (day + (13 * (m + 1U)) / 5 + K + (K / 4) + (J / 4) + (5 * J));
    h = h % 7;
    // Zeller's: 0=Saturday, 1=Sunday, ..., 6=Friday
    // We want: 0=Monday, ..., 6=Sunday
    std::uint8_t d = static_cast<std::uint8_t>(((h + 5) % 7));
    return d;
}

meetup::day_t nth_weekday(meetup::year_t year, meetup::month_t month, std::uint8_t weekday, std::uint8_t n)
{
    std::uint8_t days = days_in_month(year, month);
    std::uint8_t count = 0U;
    for(meetup::day_t d = 1U; d <= days; ++d)
    {
        if(get_weekday(year, month, d) == weekday)
        {
            if(count == n)
            {
                return d;
            }
            count = static_cast<std::uint8_t>(count + 1U);
        }
    }
    throw std::logic_error("No matching day found");
}

meetup::day_t last_weekday(meetup::year_t year, meetup::month_t month, std::uint8_t weekday)
{
    std::uint8_t days = days_in_month(year, month);
    for(meetup::day_t d = days; d >= 1U; --d)
    {
        if(get_weekday(year, month, d) == weekday)
        {
            return d;
        }
    }
    throw std::logic_error("No matching day found");
}

meetup::day_t teenth_weekday(meetup::year_t year, meetup::month_t month, std::uint8_t weekday)
{
    for(meetup::day_t d = 13U; d <= 19U; ++d)
    {
        if(get_weekday(year, month, d) == weekday)
        {
            return d;
        }
    }
    throw std::logic_error("No matching day found");
}

} // anonymous namespace

// Implementation of scheduler class

scheduler::scheduler(year_t year, month_t month)
    : m_month(month), m_year(year)
{}

#define MEETUP_IMPL(NAME, N) \
meetup::day_t scheduler::NAME() const { \
    return nth_weekday(m_year, m_month, weekday_to_index(#NAME + 0), N); \
}

#define MEETUP_IMPL_WEEKDAY(NAME, IDX, N) \
meetup::day_t scheduler::NAME() const { \
    return nth_weekday(m_year, m_month, IDX, N); \
}

#define MEETUP_IMPL_TEENTH(NAME, IDX) \
meetup::day_t scheduler::NAME() const { \
    return teenth_weekday(m_year, m_month, IDX); \
}

#define MEETUP_IMPL_LAST(NAME, IDX) \
meetup::day_t scheduler::NAME() const { \
    return last_weekday(m_year, m_month, IDX); \
}

/* teenth */
meetup::day_t scheduler::monteenth() const { return teenth_weekday(m_year, m_month, 0U); }
meetup::day_t scheduler::tuesteenth() const { return teenth_weekday(m_year, m_month, 1U); }
meetup::day_t scheduler::wednesteenth() const { return teenth_weekday(m_year, m_month, 2U); }
meetup::day_t scheduler::thursteenth() const { return teenth_weekday(m_year, m_month, 3U); }
meetup::day_t scheduler::friteenth() const { return teenth_weekday(m_year, m_month, 4U); }
meetup::day_t scheduler::saturteenth() const { return teenth_weekday(m_year, m_month, 5U); }
meetup::day_t scheduler::sunteenth() const { return teenth_weekday(m_year, m_month, 6U); }

/* first */
meetup::day_t scheduler::first_monday() const { return nth_weekday(m_year, m_month, 0U, 0U); }
meetup::day_t scheduler::first_tuesday() const { return nth_weekday(m_year, m_month, 1U, 0U); }
meetup::day_t scheduler::first_wednesday() const { return nth_weekday(m_year, m_month, 2U, 0U); }
meetup::day_t scheduler::first_thursday() const { return nth_weekday(m_year, m_month, 3U, 0U); }
meetup::day_t scheduler::first_friday() const { return nth_weekday(m_year, m_month, 4U, 0U); }
meetup::day_t scheduler::first_saturday() const { return nth_weekday(m_year, m_month, 5U, 0U); }
meetup::day_t scheduler::first_sunday() const { return nth_weekday(m_year, m_month, 6U, 0U); }

/* second */
meetup::day_t scheduler::second_monday() const { return nth_weekday(m_year, m_month, 0U, 1U); }
meetup::day_t scheduler::second_tuesday() const { return nth_weekday(m_year, m_month, 1U, 1U); }
meetup::day_t scheduler::second_wednesday() const { return nth_weekday(m_year, m_month, 2U, 1U); }
meetup::day_t scheduler::second_thursday() const { return nth_weekday(m_year, m_month, 3U, 1U); }
meetup::day_t scheduler::second_friday() const { return nth_weekday(m_year, m_month, 4U, 1U); }
meetup::day_t scheduler::second_saturday() const { return nth_weekday(m_year, m_month, 5U, 1U); }
meetup::day_t scheduler::second_sunday() const { return nth_weekday(m_year, m_month, 6U, 1U); }

/* third */
meetup::day_t scheduler::third_monday() const { return nth_weekday(m_year, m_month, 0U, 2U); }
meetup::day_t scheduler::third_tuesday() const { return nth_weekday(m_year, m_month, 1U, 2U); }
meetup::day_t scheduler::third_wednesday() const { return nth_weekday(m_year, m_month, 2U, 2U); }
meetup::day_t scheduler::third_thursday() const { return nth_weekday(m_year, m_month, 3U, 2U); }
meetup::day_t scheduler::third_friday() const { return nth_weekday(m_year, m_month, 4U, 2U); }
meetup::day_t scheduler::third_saturday() const { return nth_weekday(m_year, m_month, 5U, 2U); }
meetup::day_t scheduler::third_sunday() const { return nth_weekday(m_year, m_month, 6U, 2U); }

/* fourth */
meetup::day_t scheduler::fourth_monday() const { return nth_weekday(m_year, m_month, 0U, 3U); }
meetup::day_t scheduler::fourth_tuesday() const { return nth_weekday(m_year, m_month, 1U, 3U); }
meetup::day_t scheduler::fourth_wednesday() const { return nth_weekday(m_year, m_month, 2U, 3U); }
meetup::day_t scheduler::fourth_thursday() const { return nth_weekday(m_year, m_month, 3U, 3U); }
meetup::day_t scheduler::fourth_friday() const { return nth_weekday(m_year, m_month, 4U, 3U); }
meetup::day_t scheduler::fourth_saturday() const { return nth_weekday(m_year, m_month, 5U, 3U); }
meetup::day_t scheduler::fourth_sunday() const { return nth_weekday(m_year, m_month, 6U, 3U); }

/* last */
meetup::day_t scheduler::last_monday() const { return last_weekday(m_year, m_month, 0U); }
meetup::day_t scheduler::last_tuesday() const { return last_weekday(m_year, m_month, 1U); }
meetup::day_t scheduler::last_wednesday() const { return last_weekday(m_year, m_month, 2U); }
meetup::day_t scheduler::last_thursday() const { return last_weekday(m_year, m_month, 3U); }
meetup::day_t scheduler::last_friday() const { return last_weekday(m_year, m_month, 4U); }
meetup::day_t scheduler::last_saturday() const { return last_weekday(m_year, m_month, 5U); }
meetup::day_t scheduler::last_sunday() const { return last_weekday(m_year, m_month, 6U); }

}  // namespace meetup
