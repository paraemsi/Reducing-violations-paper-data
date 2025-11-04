#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

using boost::gregorian::date;
using boost::date_time::weekdays;

scheduler::scheduler(boost::gregorian::months_of_year month,
                     std::int32_t year) noexcept
    : m_month(month)
    , m_year(year)
{
    /* Constructor body intentionally blank */
}

date scheduler::day(weekdays wd, schedule spec) const
{
    date const first{m_year, m_month, 1};

    if (spec == schedule::teenth) {
        for (std::uint32_t d = 13U; d <= 19U; ++d) {
            date const cur{m_year, m_month, static_cast<unsigned short>(d)};
            if (cur.day_of_week() == wd) {
                return cur;
            }
        }
    } else if ((spec == schedule::first) || (spec == schedule::second) ||
               (spec == schedule::third) || (spec == schedule::fourth)) {

        std::int32_t diff =
            static_cast<std::int32_t>(wd) -
            static_cast<std::int32_t>(first.day_of_week());
        if ((diff < 0)) {
            diff += 7;
        }
        std::uint32_t const delta = static_cast<std::uint32_t>(diff);

        std::uint32_t week_index = 0U;
        if (spec == schedule::second) {
            week_index = 1U;
        } else if (spec == schedule::third) {
            week_index = 2U;
        } else if (spec == schedule::fourth) {
            week_index = 3U;
        }

        std::uint32_t const target_day =
            static_cast<std::uint32_t>(1U + delta + (week_index * 7U));

        return date{m_year, m_month,
                    static_cast<unsigned short>(target_day)};
    } else { /* schedule::last */
        unsigned short const last_dom =
            boost::gregorian::gregorian_calendar::end_of_month_day(
                static_cast<unsigned>(m_year),
                static_cast<unsigned>(m_month));

        date const last_date{m_year, m_month, last_dom};

        std::int32_t diff =
            static_cast<std::int32_t>(last_date.day_of_week()) -
            static_cast<std::int32_t>(wd);
        if ((diff < 0)) {
            diff += 7;
        }
        std::uint32_t const back_delta = static_cast<std::uint32_t>(diff);

        return last_date -
               boost::gregorian::days{static_cast<std::int64_t>(back_delta)};
    }

    return first; /* unreachable */
}

/* Helper macro to reduce boilerplate */
#define MEETUP_BUILD_FUNC(name, wd_enum, sched_enum) \
    date scheduler::name() const {                  \
        return day(boost::date_time::wd_enum, schedule::sched_enum); \
    }

/* Teenth helpers */
MEETUP_BUILD_FUNC(monteenth, Monday, teenth)
MEETUP_BUILD_FUNC(tuesteenth, Tuesday, teenth)
MEETUP_BUILD_FUNC(wednesteenth, Wednesday, teenth)
MEETUP_BUILD_FUNC(thursteenth, Thursday, teenth)
MEETUP_BUILD_FUNC(friteenth, Friday, teenth)
MEETUP_BUILD_FUNC(saturteenth, Saturday, teenth)
MEETUP_BUILD_FUNC(sunteenth, Sunday, teenth)

/* First */
MEETUP_BUILD_FUNC(first_monday, Monday, first)
MEETUP_BUILD_FUNC(first_tuesday, Tuesday, first)
MEETUP_BUILD_FUNC(first_wednesday, Wednesday, first)
MEETUP_BUILD_FUNC(first_thursday, Thursday, first)
MEETUP_BUILD_FUNC(first_friday, Friday, first)
MEETUP_BUILD_FUNC(first_saturday, Saturday, first)
MEETUP_BUILD_FUNC(first_sunday, Sunday, first)

/* Second */
MEETUP_BUILD_FUNC(second_monday, Monday, second)
MEETUP_BUILD_FUNC(second_tuesday, Tuesday, second)
MEETUP_BUILD_FUNC(second_wednesday, Wednesday, second)
MEETUP_BUILD_FUNC(second_thursday, Thursday, second)
MEETUP_BUILD_FUNC(second_friday, Friday, second)
MEETUP_BUILD_FUNC(second_saturday, Saturday, second)
MEETUP_BUILD_FUNC(second_sunday, Sunday, second)

/* Third */
MEETUP_BUILD_FUNC(third_monday, Monday, third)
MEETUP_BUILD_FUNC(third_tuesday, Tuesday, third)
MEETUP_BUILD_FUNC(third_wednesday, Wednesday, third)
MEETUP_BUILD_FUNC(third_thursday, Thursday, third)
MEETUP_BUILD_FUNC(third_friday, Friday, third)
MEETUP_BUILD_FUNC(third_saturday, Saturday, third)
MEETUP_BUILD_FUNC(third_sunday, Sunday, third)

/* Fourth */
MEETUP_BUILD_FUNC(fourth_monday, Monday, fourth)
MEETUP_BUILD_FUNC(fourth_tuesday, Tuesday, fourth)
MEETUP_BUILD_FUNC(fourth_wednesday, Wednesday, fourth)
MEETUP_BUILD_FUNC(fourth_thursday, Thursday, fourth)
MEETUP_BUILD_FUNC(fourth_friday, Friday, fourth)
MEETUP_BUILD_FUNC(fourth_saturday, Saturday, fourth)
MEETUP_BUILD_FUNC(fourth_sunday, Sunday, fourth)

/* Last */
MEETUP_BUILD_FUNC(last_monday, Monday, last)
MEETUP_BUILD_FUNC(last_tuesday, Tuesday, last)
MEETUP_BUILD_FUNC(last_wednesday, Wednesday, last)
MEETUP_BUILD_FUNC(last_thursday, Thursday, last)
MEETUP_BUILD_FUNC(last_friday, Friday, last)
MEETUP_BUILD_FUNC(last_saturday, Saturday, last)
MEETUP_BUILD_FUNC(last_sunday, Sunday, last)

#undef MEETUP_BUILD_FUNC

} // namespace meetup
