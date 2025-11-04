#include "meetup.h"

#include <cassert>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

// Helper: number of days in the given month / year
static constexpr std::chrono::day
days_in_month(const std::chrono::year & year, const std::chrono::month & month) noexcept
{
    return (year / month / std::chrono::last).day();
}

std::chrono::year_month_day meetup_day(const std::chrono::year & year,
                                       const std::chrono::month & month,
                                       const std::chrono::weekday & weekday,
                                       const schedule sched) noexcept
{
    // Verify that the supplied (year, month) combination is valid.
    assert(year.ok());
    assert(month.ok());

    // Common calculations use unsigned arithmetic to avoid signed/unsigned mixing.
    const std::uint32_t weekday_target {static_cast<std::uint32_t>(weekday.c_encoding())};

    switch (sched) {
        case schedule::teenth:
        {
            // Search the 13th-19th.
            for (std::uint32_t d {13U}; d <= 19U; ++d) {
                const std::chrono::year_month_day current {year, month, std::chrono::day{d}};
                const std::uint32_t wd {static_cast<std::uint32_t>(std::chrono::weekday{std::chrono::sys_days{current}}.c_encoding())};
                if (wd == weekday_target) {
                    return current;
                }
            }
            break; // defensive – should never reach
        }

        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth:
        {
            const std::uint32_t ordinal {static_cast<std::uint32_t>(sched)}; // 0-based
            const std::chrono::year_month_day first_of_month {year, month, std::chrono::day{1}};
            const std::uint32_t first_wd {static_cast<std::uint32_t>(std::chrono::weekday{std::chrono::sys_days{first_of_month}}.c_encoding())};

            const std::uint32_t offset {(weekday_target + 7U - first_wd) % 7U};
            const std::uint32_t day_value {1U + offset + (ordinal * 7U)};

            return std::chrono::year_month_day{year, month, std::chrono::day{day_value}};
        }

        case schedule::last:
        {
            const std::chrono::day dim {days_in_month(year, month)};
            const std::chrono::year_month_day last_day {year, month, dim};
            const std::uint32_t last_wd {static_cast<std::uint32_t>(std::chrono::weekday{std::chrono::sys_days{last_day}}.c_encoding())};

            const std::uint32_t backward {(last_wd + 7U - weekday_target) % 7U};
            const std::uint32_t day_value {static_cast<std::uint32_t>(dim) - backward};

            return std::chrono::year_month_day{year, month, std::chrono::day{day_value}};
        }

        default:
            break;
    }

    // Should never reach here; return a sentinel date for release builds.
    return std::chrono::year_month_day{};
}

}  // namespace meetup
