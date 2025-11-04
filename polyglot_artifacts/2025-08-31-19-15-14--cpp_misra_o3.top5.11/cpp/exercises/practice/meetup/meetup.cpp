#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::greg_month;
using boost::gregorian::gregorian_calendar;

// ─────────────────────────────────────────────────────────────────────────────
// scheduler implementation
// ─────────────────────────────────────────────────────────────────────────────

scheduler::scheduler(greg_month month, std::int32_t year) noexcept
    : m_month(month),
      m_year(year)
{
}

date scheduler::compute_date(schedule selector,
                             std::uint8_t weekday_index) const
{
    const std::uint32_t eom =
        static_cast<std::uint32_t>(
            gregorian_calendar::end_of_month_day(
                m_year, static_cast<unsigned short>(m_month.as_number())));

    /* Teenth calculation */
    if (selector == schedule::teenth)
    {
        for (std::uint8_t day = 13U; day <= 19U; ++day)
        {
            const date current{static_cast<unsigned short>(m_year),
                               static_cast<unsigned short>(m_month.as_number()),
                               static_cast<unsigned short>(day)};
            if (static_cast<std::uint8_t>(current.day_of_week()) == weekday_index)
            {
                return current;
            }
        }
    }

    /* First – Fourth */
    if ((selector == schedule::first)  || (selector == schedule::second) ||
        (selector == schedule::third)  || (selector == schedule::fourth))
    {
        const std::uint8_t target =
            static_cast<std::uint8_t>(selector) - 1U;   /* 0-based */
        std::uint8_t found = 0U;

        for (std::uint32_t day = 1U; day <= eom; ++day)
        {
            const date current{static_cast<unsigned short>(m_year),
                               static_cast<unsigned short>(m_month.as_number()),
                               static_cast<unsigned short>(day)};
            if (static_cast<std::uint8_t>(current.day_of_week()) == weekday_index)
            {
                if (found == target)
                {
                    return current;
                }
                ++found;
            }
        }
    }

    /* Last */
    if (selector == schedule::last)
    {
        for (std::int32_t day = static_cast<std::int32_t>(eom); day >= 1; --day)
        {
            const date current{static_cast<unsigned short>(m_year),
                               static_cast<unsigned short>(m_month.as_number()),
                               static_cast<unsigned short>(day)};
            if (static_cast<std::uint8_t>(current.day_of_week()) == weekday_index)
            {
                return current;
            }
        }
    }

    /* Defensive fallback – should never be reached */
    return date{static_cast<unsigned short>(m_year),
                static_cast<unsigned short>(m_month.as_number()),
                static_cast<unsigned short>(1U)};
}

/* Helper macro to create the thin wrappers */
#define MEETUP_DEF(fn_name, sched, wday)                      \
    date scheduler::fn_name() const                           \
    {                                                         \
        return compute_date(schedule::sched, wday);           \
    }

MEETUP_DEF(monteenth,   teenth, 1U)
MEETUP_DEF(tuesteenth,  teenth, 2U)
MEETUP_DEF(wednesteenth,teenth, 3U)
MEETUP_DEF(thursteenth, teenth, 4U)
MEETUP_DEF(friteenth,   teenth, 5U)
MEETUP_DEF(saturteenth, teenth, 6U)
MEETUP_DEF(sunteenth,   teenth, 0U)

MEETUP_DEF(first_monday,     first, 1U)
MEETUP_DEF(first_tuesday,    first, 2U)
MEETUP_DEF(first_wednesday,  first, 3U)
MEETUP_DEF(first_thursday,   first, 4U)
MEETUP_DEF(first_friday,     first, 5U)
MEETUP_DEF(first_saturday,   first, 6U)
MEETUP_DEF(first_sunday,     first, 0U)

MEETUP_DEF(second_monday,    second, 1U)
MEETUP_DEF(second_tuesday,   second, 2U)
MEETUP_DEF(second_wednesday, second, 3U)
MEETUP_DEF(second_thursday,  second, 4U)
MEETUP_DEF(second_friday,    second, 5U)
MEETUP_DEF(second_saturday,  second, 6U)
MEETUP_DEF(second_sunday,    second, 0U)

MEETUP_DEF(third_monday,     third, 1U)
MEETUP_DEF(third_tuesday,    third, 2U)
MEETUP_DEF(third_wednesday,  third, 3U)
MEETUP_DEF(third_thursday,   third, 4U)
MEETUP_DEF(third_friday,     third, 5U)
MEETUP_DEF(third_saturday,   third, 6U)
MEETUP_DEF(third_sunday,     third, 0U)

MEETUP_DEF(fourth_monday,    fourth, 1U)
MEETUP_DEF(fourth_tuesday,   fourth, 2U)
MEETUP_DEF(fourth_wednesday, fourth, 3U)
MEETUP_DEF(fourth_thursday,  fourth, 4U)
MEETUP_DEF(fourth_friday,    fourth, 5U)
MEETUP_DEF(fourth_saturday,  fourth, 6U)
MEETUP_DEF(fourth_sunday,    fourth, 0U)

MEETUP_DEF(last_monday,      last, 1U)
MEETUP_DEF(last_tuesday,     last, 2U)
MEETUP_DEF(last_wednesday,   last, 3U)
MEETUP_DEF(last_thursday,    last, 4U)
MEETUP_DEF(last_friday,      last, 5U)
MEETUP_DEF(last_saturday,    last, 6U)
MEETUP_DEF(last_sunday,      last, 0U)

#undef MEETUP_DEF

}  // namespace meetup
