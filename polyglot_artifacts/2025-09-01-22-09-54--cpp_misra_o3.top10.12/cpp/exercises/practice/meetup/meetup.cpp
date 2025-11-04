#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

scheduler::scheduler(boost::gregorian::months_of_year month,
                     std::int32_t                     year) noexcept
    : month_{month}, year_{year}
{
}

boost::gregorian::date
scheduler::get_teenth(boost::date_time::weekdays weekday) const noexcept
{
    for (std::uint8_t d = 13U; d <= 19U; ++d)
    {
        const boost::gregorian::date current{
            year_, month_, static_cast<std::uint16_t>(d)};
        if (current.day_of_week() == weekday)
        {
            return current;
        }
    }
    /* Unreachable for valid input – return a deterministic value */
    return boost::gregorian::date{year_, month_, 13U};
}

boost::gregorian::date
scheduler::get_nth(std::uint8_t                  nth,
                   boost::date_time::weekdays    weekday) const noexcept
{
    const boost::gregorian::date first{year_, month_, 1U};
    const std::uint8_t diff{static_cast<std::uint8_t>(
        (static_cast<int>(weekday) + 7 -
         static_cast<int>(first.day_of_week())) %
        7)};

    const std::uint16_t day{static_cast<std::uint16_t>(
        (1U + static_cast<std::uint16_t>(diff)) +
        static_cast<std::uint16_t>(7U * static_cast<std::uint8_t>(nth - 1U)))};

    return boost::gregorian::date{year_, month_, day};
}

boost::gregorian::date
scheduler::get_last(boost::date_time::weekdays weekday) const noexcept
{
    const std::uint16_t end_of_month{static_cast<std::uint16_t>(
        boost::gregorian::gregorian_calendar::end_of_month_day(year_, month_))};

    boost::gregorian::date current{year_, month_, end_of_month};

    while (current.day_of_week() != weekday)
    {
        current -= boost::gregorian::days{1};
    }
    return current;
}

/* ---------- teenth helpers ---------- */
#define DEFINE_TEENTH(method, weekdayEnum)                                  \
    boost::gregorian::date scheduler::method() const noexcept               \
    {                                                                       \
        return get_teenth(boost::date_time::weekdayEnum);                   \
    }

DEFINE_TEENTH(monteenth, Monday)
DEFINE_TEENTH(tuesteenth, Tuesday)
DEFINE_TEENTH(wednesteenth, Wednesday)
DEFINE_TEENTH(thursteenth, Thursday)
DEFINE_TEENTH(friteenth, Friday)
DEFINE_TEENTH(saturteenth, Saturday)
DEFINE_TEENTH(sunteenth, Sunday)

#undef DEFINE_TEENTH

/* ---------- nth helpers ---------- */
#define DEFINE_NTH(prefix, nthIndex, methodSuffix, weekdayEnum)             \
    boost::gregorian::date scheduler::prefix##_##methodSuffix()             \
        const noexcept                                                      \
    {                                                                       \
        return get_nth(static_cast<std::uint8_t>(nthIndex),                 \
                       boost::date_time::weekdayEnum);                      \
    }

/* first */
DEFINE_NTH(first, 1U, monday,    Monday)
DEFINE_NTH(first, 1U, tuesday,   Tuesday)
DEFINE_NTH(first, 1U, wednesday, Wednesday)
DEFINE_NTH(first, 1U, thursday,  Thursday)
DEFINE_NTH(first, 1U, friday,    Friday)
DEFINE_NTH(first, 1U, saturday,  Saturday)
DEFINE_NTH(first, 1U, sunday,    Sunday)

/* second */
DEFINE_NTH(second, 2U, monday,    Monday)
DEFINE_NTH(second, 2U, tuesday,   Tuesday)
DEFINE_NTH(second, 2U, wednesday, Wednesday)
DEFINE_NTH(second, 2U, thursday,  Thursday)
DEFINE_NTH(second, 2U, friday,    Friday)
DEFINE_NTH(second, 2U, saturday,  Saturday)
DEFINE_NTH(second, 2U, sunday,    Sunday)

/* third */
DEFINE_NTH(third, 3U, monday,    Monday)
DEFINE_NTH(third, 3U, tuesday,   Tuesday)
DEFINE_NTH(third, 3U, wednesday, Wednesday)
DEFINE_NTH(third, 3U, thursday,  Thursday)
DEFINE_NTH(third, 3U, friday,    Friday)
DEFINE_NTH(third, 3U, saturday,  Saturday)
DEFINE_NTH(third, 3U, sunday,    Sunday)

/* fourth */
DEFINE_NTH(fourth, 4U, monday,    Monday)
DEFINE_NTH(fourth, 4U, tuesday,   Tuesday)
DEFINE_NTH(fourth, 4U, wednesday, Wednesday)
DEFINE_NTH(fourth, 4U, thursday,  Thursday)
DEFINE_NTH(fourth, 4U, friday,    Friday)
DEFINE_NTH(fourth, 4U, saturday,  Saturday)
DEFINE_NTH(fourth, 4U, sunday,    Sunday)

#undef DEFINE_NTH

/* ---------- last helpers ---------- */
#define DEFINE_LAST(methodSuffix, weekdayEnum)                              \
    boost::gregorian::date scheduler::last_##methodSuffix() const noexcept  \
    {                                                                       \
        return get_last(boost::date_time::weekdayEnum);                     \
    }

DEFINE_LAST(monday,    Monday)
DEFINE_LAST(tuesday,   Tuesday)
DEFINE_LAST(wednesday, Wednesday)
DEFINE_LAST(thursday,  Thursday)
DEFINE_LAST(friday,    Friday)
DEFINE_LAST(saturday,  Saturday)
DEFINE_LAST(sunday,    Sunday)

#undef DEFINE_LAST

}  // namespace meetup
