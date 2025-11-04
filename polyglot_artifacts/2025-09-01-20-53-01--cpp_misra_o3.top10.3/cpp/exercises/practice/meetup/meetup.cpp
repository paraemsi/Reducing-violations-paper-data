#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

scheduler::scheduler(std::int32_t year, std::uint32_t month) noexcept
    : m_year{year},
      m_month{month}
{
}

boost::gregorian::date scheduler::day(const boost::date_time::weekdays weekday_req,
                                      const schedule schedule_req) const noexcept
{
    using boost::gregorian::date;
    using boost::gregorian::gregorian_calendar;
    using boost::date_time::weekdays;

    const std::int32_t  y{m_year};
    const std::uint32_t m{m_month};

    if(schedule_req == schedule::teenth)
    {
        for(std::uint32_t d = 13U; d <= 19U; ++d)
        {
            const date cur{static_cast<long>(y),
                           static_cast<unsigned short>(m),
                           static_cast<unsigned short>(d)};
            if(cur.day_of_week().as_enum() == weekday_req)
            {
                return cur;
            }
        }
    }
    else if(schedule_req != schedule::last)
    {
        const date first_of_month{static_cast<long>(y),
                                  static_cast<unsigned short>(m),
                                  1U};

        const weekdays first_dow{first_of_month.day_of_week().as_enum()};

        const std::uint32_t diff{static_cast<std::uint32_t>(
            (static_cast<std::uint32_t>(weekday_req) + 7U -
             static_cast<std::uint32_t>(first_dow)) % 7U)};

        const std::uint32_t week_idx{static_cast<std::uint32_t>(schedule_req) - 1U};

        const std::uint32_t day_val{1U + diff + (7U * week_idx)};

        return date{static_cast<long>(y),
                    static_cast<unsigned short>(m),
                    static_cast<unsigned short>(day_val)};
    }
    else
    {
        const std::uint32_t last_dom{static_cast<std::uint32_t>(
            gregorian_calendar::end_of_month_day(static_cast<int>(y),
                                                 static_cast<int>(m)))};

        const date last_of_month{static_cast<long>(y),
                                 static_cast<unsigned short>(m),
                                 static_cast<unsigned short>(last_dom)};

        const weekdays last_dow{last_of_month.day_of_week().as_enum()};

        const std::uint32_t back_diff{static_cast<std::uint32_t>(
            (static_cast<std::uint32_t>(last_dow) + 7U -
             static_cast<std::uint32_t>(weekday_req)) % 7U)};

        const std::uint32_t day_val{last_dom - back_diff};

        return date{static_cast<long>(y),
                    static_cast<unsigned short>(m),
                    static_cast<unsigned short>(day_val)};
    }

    /* fallback */
    return boost::gregorian::date{};
}

/* ---------- teenth ---------- */
boost::gregorian::date scheduler::monteenth() const noexcept
{
    return day(boost::date_time::Monday, schedule::teenth);
}

boost::gregorian::date scheduler::tuesteenth() const noexcept
{
    return day(boost::date_time::Tuesday, schedule::teenth);
}

boost::gregorian::date scheduler::wednesteenth() const noexcept
{
    return day(boost::date_time::Wednesday, schedule::teenth);
}

boost::gregorian::date scheduler::thursteenth() const noexcept
{
    return day(boost::date_time::Thursday, schedule::teenth);
}

boost::gregorian::date scheduler::friteenth() const noexcept
{
    return day(boost::date_time::Friday, schedule::teenth);
}

boost::gregorian::date scheduler::saturteenth() const noexcept
{
    return day(boost::date_time::Saturday, schedule::teenth);
}

boost::gregorian::date scheduler::sunteenth() const noexcept
{
    return day(boost::date_time::Sunday, schedule::teenth);
}

/* ---------- helper macro (undef after use) ---------- */
#define MEETUP_GEN(ordinal, sched_enum)                                              \
    boost::gregorian::date scheduler::ordinal##_monday() const noexcept              \
    {                                                                                \
        return day(boost::date_time::Monday, sched_enum);                            \
    }                                                                                \
    boost::gregorian::date scheduler::ordinal##_tuesday() const noexcept             \
    {                                                                                \
        return day(boost::date_time::Tuesday, sched_enum);                           \
    }                                                                                \
    boost::gregorian::date scheduler::ordinal##_wednesday() const noexcept           \
    {                                                                                \
        return day(boost::date_time::Wednesday, sched_enum);                         \
    }                                                                                \
    boost::gregorian::date scheduler::ordinal##_thursday() const noexcept            \
    {                                                                                \
        return day(boost::date_time::Thursday, sched_enum);                          \
    }                                                                                \
    boost::gregorian::date scheduler::ordinal##_friday() const noexcept              \
    {                                                                                \
        return day(boost::date_time::Friday, sched_enum);                            \
    }                                                                                \
    boost::gregorian::date scheduler::ordinal##_saturday() const noexcept            \
    {                                                                                \
        return day(boost::date_time::Saturday, sched_enum);                          \
    }                                                                                \
    boost::gregorian::date scheduler::ordinal##_sunday() const noexcept              \
    {                                                                                \
        return day(boost::date_time::Sunday, sched_enum);                            \
    }

MEETUP_GEN(first,  schedule::first)
MEETUP_GEN(second, schedule::second)
MEETUP_GEN(third,  schedule::third)
MEETUP_GEN(fourth, schedule::fourth)
MEETUP_GEN(last,   schedule::last)

#undef MEETUP_GEN

}  // namespace meetup
