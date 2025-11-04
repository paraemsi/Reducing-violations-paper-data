#include "meetup.h"

#include <chrono>
#include <stdexcept>

namespace meetup {

using namespace std::chrono;

/* Helper: number of days in the supplied month */
static auto days_in_month(const year_month& ym) -> std::uint32_t
{
    const sys_days first_next_month{ (ym + months{1}) / day{1} };
    const sys_days last_this_month{ first_next_month - days{1} };
    const year_month_day ymd_last{ last_this_month };

    /*  year_month_day::day() returns a std::chrono::day.
     *  The explicit cast to unsigned then to uint32_t avoids narrowing.
     */
    return static_cast<std::uint32_t>(
        static_cast<unsigned>(ymd_last.day()));
}

auto day(const year_month& ym,
         const weekday&    wd,
         const schedule    recurrence) -> year_month_day
{
    switch (recurrence) {
    case schedule::teenth:
    {
        for (std::uint32_t d{13U}; d <= 19U; ++d) {
            const year_month_day current{ ym / day{ static_cast<unsigned>(d) } };
            if (weekday{ current } == wd) {
                return current;
            }
        }
        break;          /*  Logic guarantees return in loop – defensive   */
    }
    case schedule::first:
    case schedule::second:
    case schedule::third:
    case schedule::fourth:
    {
        const std::uint32_t index{
            static_cast<std::uint32_t>(recurrence) /* 0-3 for first-fourth */
        };

        const year_month_day first_of_month{ ym / day{1} };
        weekday weekday_of_first{ first_of_month };

        days diff_days{ wd - weekday_of_first };
        if (diff_days < days{0}) {
            diff_days += days{7};
        }

        const sys_days first_occurrence{
            sys_days{ first_of_month } + diff_days +
            days{ static_cast<std::int64_t>(index) * 7 }
        };

        return year_month_day{ first_occurrence };
    }
    case schedule::last:
    {
        const std::uint32_t dim{ days_in_month(ym) };
        sys_days current_sys{ ym / day{ static_cast<unsigned>(dim) } };

        while (weekday{ current_sys } != wd) {
            current_sys -= days{1};
        }
        return year_month_day{ current_sys };
    }
    default:
        break;          /*  Should be unreachable – keeps compiler happy  */
    }

    throw std::logic_error("Invalid schedule supplied to meetup::day");
}

}  // namespace meetup
