#include "meetup.h"

#include <optional>
#include <stdexcept>

namespace meetup {

namespace {

/* Convert custom weekday enum to std::chrono::weekday index (0 = Sunday) */
constexpr std::uint8_t to_chrono_index(weekday wd) noexcept
{
    switch (wd) {
    case weekday::Sunday:    return 0U;
    case weekday::Monday:    return 1U;
    case weekday::Tuesday:   return 2U;
    case weekday::Wednesday: return 3U;
    case weekday::Thursday:  return 4U;
    case weekday::Friday:    return 5U;
    case weekday::Saturday:  return 6U;
    default:                 return 0U;             /* Unreachable – keeps MISRA happy */
    }
}

/* Safely build a year_month_day; return std::nullopt when the day is invalid */
std::optional<std::chrono::year_month_day> make_ymd(const std::chrono::year &y,
                                                    const std::chrono::month &m,
                                                    std::uint32_t d) noexcept
{
    const std::chrono::day dd{d};
    const std::chrono::year_month_day ymd{y, m, dd};
    if (ymd.ok()) {
        return ymd;
    } else {
        return std::nullopt;
    }
}

}   /* anonymous namespace */

scheduler::scheduler(std::int32_t year, std::uint32_t month) noexcept
    : m_year(year), m_month(month)
{
}

std::chrono::year_month_day scheduler::get_day(weekday day_of_week,
                                               schedule sched) const
{
    const std::chrono::year  y{m_year};
    const std::chrono::month m{static_cast<std::uint32_t>(m_month)};
    const std::chrono::weekday target_wd{to_chrono_index(day_of_week)};

    if (sched == schedule::teenth) {
        for (std::uint32_t d = 13U; d <= 19U; ++d) {
            const auto ymd_opt = make_ymd(y, m, d);
            if (ymd_opt.has_value()) {
                const std::chrono::weekday wd{std::chrono::sys_days{ymd_opt.value()}};
                if (wd == target_wd) {
                    return ymd_opt.value();
                }
            }
        }
    } else if ((sched == schedule::first)  || (sched == schedule::second) ||
               (sched == schedule::third)  || (sched == schedule::fourth)) {

        const std::uint8_t ordinal   = static_cast<std::uint8_t>(sched);   /* 0 – 3 */
        const std::uint32_t start_d  = static_cast<std::uint32_t>(1U + (ordinal * 7U));
        const std::uint32_t finish_d = static_cast<std::uint32_t>(start_d + 6U);

        for (std::uint32_t d = start_d; d <= finish_d; ++d) {
            const auto ymd_opt = make_ymd(y, m, d);
            if (ymd_opt.has_value()) {
                const std::chrono::weekday wd{std::chrono::sys_days{ymd_opt.value()}};
                if (wd == target_wd) {
                    return ymd_opt.value();
                }
            }
        }
    } else if (sched == schedule::last) {

        std::uint32_t last_day = 31U;
        for (; last_day >= 28U; --last_day) {
            const auto ymd_opt = make_ymd(y, m, last_day);
            if (ymd_opt.has_value()) {
                break;          /* last_day is now the last valid day of the month */
            }
        }

        for (std::uint32_t off = 0U; off < 7U; ++off) {
            const std::uint32_t cur_d = static_cast<std::uint32_t>(last_day - off);
            const auto ymd_opt = make_ymd(y, m, cur_d);
            if (ymd_opt.has_value()) {
                const std::chrono::weekday wd{std::chrono::sys_days{ymd_opt.value()}};
                if (wd == target_wd) {
                    return ymd_opt.value();
                }
            }
        }
    }

    throw std::logic_error("Requested meetup day does not exist");
}

}  // namespace meetup
