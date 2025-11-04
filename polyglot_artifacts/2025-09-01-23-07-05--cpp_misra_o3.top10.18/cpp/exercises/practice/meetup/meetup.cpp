#include "meetup.h"

#include <cassert>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::days;
using boost::gregorian::greg_weekday;

scheduler::scheduler(boost::gregorian::months_of_year month,
                     std::int32_t                       year)
    : m_year{year}, m_month{month}
{
    /* No further validation required: boost::date will throw if invalid */
}

date scheduler::nth_weekday(greg_weekday weekday, std::uint32_t nth) const
{
    /* nth is 1-based */
    const date first_day{m_year, m_month, 1};
    const std::int32_t first_dow =
        static_cast<std::int32_t>(first_day.day_of_week().as_number());
    const std::int32_t desired_dow =
        static_cast<std::int32_t>(weekday.as_number());

    const std::int32_t delta =
        (desired_dow - first_dow + 7) % 7;

    const std::int32_t offset =
        (delta) + ((static_cast<std::int32_t>(nth) - 1) * 7);

    return first_day + days{offset};
}

date scheduler::teenth(greg_weekday weekday) const
{
    date current{m_year, m_month, 13};
    for(std::uint32_t i = 0U; i < 7U; ++i)
    {
        if(current.day_of_week() == weekday)
        {
            return current;
        }
        current += days{1};
    }
    /* Unreachable because exactly one weekday falls in teenth range */
    assert(false);
    return current;
}

date scheduler::last_weekday(greg_weekday weekday) const
{
    const unsigned short last_dom =
        boost::gregorian::gregorian_calendar::end_of_month_day(
            static_cast<unsigned short>(m_year),
            static_cast<unsigned short>(m_month));

    date current{m_year, m_month, static_cast<unsigned short>(last_dom)};
    while(current.day_of_week() != weekday)
    {
        current -= days{1};
    }
    return current;
}

date scheduler::get_day(greg_weekday weekday, schedule which) const
{
    switch(which)
    {
        case schedule::first:
            return nth_weekday(weekday, 1U);
        case schedule::second:
            return nth_weekday(weekday, 2U);
        case schedule::third:
            return nth_weekday(weekday, 3U);
        case schedule::fourth:
            return nth_weekday(weekday, 4U);
        case schedule::last:
            return last_weekday(weekday);
        case schedule::teenth:
            return teenth(weekday);
        default:
            assert(false);
            return date{};
    }
}

/* teenth helpers */
#define MEETUP_DEFINE_TEENTH(fname, weekdayConst) \
    date scheduler::fname() const \
    { \
        return teenth(greg_weekday{boost::date_time::weekdayConst}); \
    }

MEETUP_DEFINE_TEENTH(monteenth, Monday)
MEETUP_DEFINE_TEENTH(tuesteenth, Tuesday)
MEETUP_DEFINE_TEENTH(wednesteenth, Wednesday)
MEETUP_DEFINE_TEENTH(thursteenth, Thursday)
MEETUP_DEFINE_TEENTH(friteenth, Friday)
MEETUP_DEFINE_TEENTH(saturteenth, Saturday)
MEETUP_DEFINE_TEENTH(sunteenth, Sunday)

#undef MEETUP_DEFINE_TEENTH

/* nth weekday helpers */
#define MEETUP_DEFINE_NTH(prefix, nth, fname, weekdayConst)                     \
    date scheduler::prefix##_##fname() const                                    \
    {                                                                           \
        return nth_weekday(                                                     \
            greg_weekday{boost::date_time::weekdayConst},                       \
            static_cast<std::uint32_t>(nth));                                   \
    }

#define MEETUP_DEFINE_GROUP(prefix, nth)               \
    MEETUP_DEFINE_NTH(prefix, nth, monday, Monday)     \
    MEETUP_DEFINE_NTH(prefix, nth, tuesday, Tuesday)   \
    MEETUP_DEFINE_NTH(prefix, nth, wednesday, Wednesday)\
    MEETUP_DEFINE_NTH(prefix, nth, thursday, Thursday) \
    MEETUP_DEFINE_NTH(prefix, nth, friday, Friday)     \
    MEETUP_DEFINE_NTH(prefix, nth, saturday, Saturday) \
    MEETUP_DEFINE_NTH(prefix, nth, sunday, Sunday)

/* first-fourth */
MEETUP_DEFINE_GROUP(first, 1)
MEETUP_DEFINE_GROUP(second, 2)
MEETUP_DEFINE_GROUP(third, 3)
MEETUP_DEFINE_GROUP(fourth, 4)

/* last */
#define MEETUP_DEFINE_LAST(fname, weekdayConst)                  \
    date scheduler::last_##fname() const                         \
    {                                                            \
        return last_weekday(greg_weekday{boost::date_time::weekdayConst}); \
    }

MEETUP_DEFINE_LAST(monday, Monday)
MEETUP_DEFINE_LAST(tuesday, Tuesday)
MEETUP_DEFINE_LAST(wednesday, Wednesday)
MEETUP_DEFINE_LAST(thursday, Thursday)
MEETUP_DEFINE_LAST(friday, Friday)
MEETUP_DEFINE_LAST(saturday, Saturday)
MEETUP_DEFINE_LAST(sunday, Sunday)

#undef MEETUP_DEFINE_LAST
#undef MEETUP_DEFINE_GROUP
#undef MEETUP_DEFINE_NTH

}  // namespace meetup
