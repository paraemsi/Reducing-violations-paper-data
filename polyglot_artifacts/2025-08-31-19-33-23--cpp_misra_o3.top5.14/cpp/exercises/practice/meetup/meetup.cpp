#include "meetup.h"
#include <cstdint>

namespace meetup {

/*----- private free helpers -------------------------------------------------*/

/* Check Gregorian leap-year rule. */
static bool is_leap_year(std::uint32_t year) noexcept
{
    return ((year % 4U) == 0U) && (((year % 100U) != 0U) || ((year % 400U) == 0U));
}

/* Days in month for the supplied Gregorian year/month (1-12). */
static std::uint32_t days_in_month(std::uint32_t year, std::uint32_t month) noexcept
{
    switch (month) {
        case 1U:  return 31U;
        case 2U:  return is_leap_year(year) ? 29U : 28U;
        case 3U:  return 31U;
        case 4U:  return 30U;
        case 5U:  return 31U;
        case 6U:  return 30U;
        case 7U:  return 31U;
        case 8U:  return 31U;
        case 9U:  return 30U;
        case 10U: return 31U;
        case 11U: return 30U;
        case 12U: return 31U;
        default:  return 0U;   /* month out of range – defensive, should not occur */
    }
}

/* Zeller’s congruence – returns 0U = Sunday, …, 6U = Saturday. */
static std::uint8_t weekday_of_date(std::uint32_t year,
                                    std::uint32_t month,
                                    std::uint32_t day) noexcept
{
    /* Shift Jan/Feb to months 13/14 of previous year. */
    std::uint32_t y = year;
    std::uint32_t m = month;
    if (m < 3U) {
        m += 12U;
        --y;
    }

    const std::uint32_t k = (y % 100U);
    const std::uint32_t j = (y / 100U);

    const std::uint32_t h = (day
                             + ((13U * (m + 1U)) / 5U)
                             + k
                             + (k / 4U)
                             + (j / 4U)
                             + (5U * j)) % 7U;

    /* In Zeller: 0 = Saturday … 6 = Friday; convert so 0 = Sunday. */
    const std::uint32_t d = (h + 6U) % 7U;
    return static_cast<std::uint8_t>(d);
}

/*----- scheduler implementation --------------------------------------------*/


/* Return day-of-month fulfilling the requested weekday & schedule. */
std::uint32_t scheduler::day(weekday weekday_in, schedule schedule_in) const
{
    const std::uint8_t target_wd = static_cast<std::uint8_t>(weekday_in);

    if (schedule_in == schedule::teenth) {
        for (std::uint32_t d = 13U; d <= 19U; ++d) {
            if (weekday_of_date(m_year, m_month, d) == target_wd) {
                return d;
            }
        }
    } else if (schedule_in == schedule::last) {
        const std::uint32_t dim = days_in_month(m_year, m_month);
        for (std::uint32_t offset = 0U; offset < 7U; ++offset) {
            const std::uint32_t d = dim - offset;
            if (weekday_of_date(m_year, m_month, d) == target_wd) {
                return d;
            }
        }
    } else { /* first .. fourth */
        const std::uint32_t occurrence = static_cast<std::uint32_t>(schedule_in); /* 0-based */
        std::uint32_t first_candidate = 0U;

        for (std::uint32_t d = 1U; d <= 7U; ++d) {
            if (weekday_of_date(m_year, m_month, d) == target_wd) {
                first_candidate = d;
                break;
            }
        }
        return first_candidate + (occurrence * 7U);
    }

    /* Should never reach here for valid input. */
    return 0U;
}

}  // namespace meetup
