#include "meetup.h"

namespace meetup {

bool scheduler::is_leap_year(std::int32_t year) noexcept
{
    return ((year % static_cast<std::int32_t>(4)) == 0) &&
           (((year % static_cast<std::int32_t>(100)) != 0) ||
            ((year % static_cast<std::int32_t>(400)) == 0));
}

std::uint32_t scheduler::days_in_month(std::int32_t year, std::int32_t month) noexcept
{
    switch (month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return static_cast<std::uint32_t>(31U);
        case 4:
        case 6:
        case 9:
        case 11:
            return static_cast<std::uint32_t>(30U);
        case 2:
        default:
            {
                return is_leap_year(year) ? static_cast<std::uint32_t>(29U)
                                          : static_cast<std::uint32_t>(28U);
            }
    }
}

weekday scheduler::weekday_of(std::int32_t year,
                              std::int32_t month,
                              std::uint32_t day) noexcept
{
    std::int32_t adjusted_year = year;
    std::int32_t adjusted_month = month;

    if (adjusted_month < 3)
    {
        adjusted_month = static_cast<std::int32_t>(adjusted_month + 12);
        adjusted_year = static_cast<std::int32_t>(adjusted_year - 1);
    }

    const std::int32_t K = static_cast<std::int32_t>(adjusted_year % static_cast<std::int32_t>(100));
    const std::int32_t J = static_cast<std::int32_t>(adjusted_year / static_cast<std::int32_t>(100));

    const std::int32_t h = static_cast<std::int32_t>(
        (static_cast<std::int32_t>(day) +
         ((static_cast<std::int32_t>(13) * (adjusted_month + 1)) / static_cast<std::int32_t>(5)) +
         K +
         (K / static_cast<std::int32_t>(4)) +
         (J / static_cast<std::int32_t>(4)) +
         (static_cast<std::int32_t>(5) * J)) %
        static_cast<std::int32_t>(7));

    /* Convert Zeller’s result to 0 = Sunday, … 6 = Saturday */
    const std::int32_t d = static_cast<std::int32_t>((h + static_cast<std::int32_t>(6)) % static_cast<std::int32_t>(7));

    return static_cast<weekday>(d);
}

std::uint32_t scheduler::day(weekday target_weekday, schedule target_schedule) const
{
    const std::uint32_t dim = days_in_month(m_year, m_month);

    if (target_schedule == schedule::teenth)
    {
        for (std::uint32_t d = static_cast<std::uint32_t>(13U); d <= static_cast<std::uint32_t>(19U); ++d)
        {
            if (weekday_of(m_year, m_month, d) == target_weekday)
            {
                return d;
            }
        }
    }
    else if (target_schedule == schedule::last)
    {
        for (std::int32_t d = static_cast<std::int32_t>(dim); d >= static_cast<std::int32_t>(1); --d)
        {
            if (weekday_of(m_year, m_month, static_cast<std::uint32_t>(d)) == target_weekday)
            {
                return static_cast<std::uint32_t>(d);
            }
        }
    }
    else
    {
        std::uint32_t occurrence_index = static_cast<std::uint32_t>(0U);

        switch (target_schedule)
        {
            case schedule::first:
                occurrence_index = static_cast<std::uint32_t>(0U);
                break;
            case schedule::second:
                occurrence_index = static_cast<std::uint32_t>(1U);
                break;
            case schedule::third:
                occurrence_index = static_cast<std::uint32_t>(2U);
                break;
            case schedule::fourth:
                occurrence_index = static_cast<std::uint32_t>(3U);
                break;
            case schedule::fifth:
                occurrence_index = static_cast<std::uint32_t>(4U);
                break;
            default:
                break; /* handled above */
        }

        for (std::uint32_t d = static_cast<std::uint32_t>(1U); d <= static_cast<std::uint32_t>(7U); ++d)
        {
            if (weekday_of(m_year, m_month, d) == target_weekday)
            {
                const std::uint32_t candidate = static_cast<std::uint32_t>(d + (occurrence_index * static_cast<std::uint32_t>(7U)));
                if (candidate <= dim)
                {
                    return candidate;
                }
                else
                {
                    break;
                }
            }
        }
    }

    throw std::domain_error("Requested meetup date does not exist in specified month.");
}

}  // namespace meetup
