#include "meetup.h"

#include <stdexcept>

namespace meetup {

scheduler::scheduler(boost::gregorian::greg_month month,
                     std::int32_t                  year) noexcept
    : m_month(month),
      m_year(year)
{
}

boost::gregorian::date scheduler::find_nth_weekday(boost::date_time::weekdays wd,
                                                   std::int32_t              nth) const
{
    using boost::gregorian::date;
    using boost::gregorian::days;
    using boost::gregorian::gregorian_calendar;

    /* teenth calculation */
    if (nth == static_cast<std::int32_t>(5))
    {
        date const start{ m_year,
                          static_cast<unsigned short>(m_month.as_number()),
                          static_cast<unsigned short>(13U) };

        for (std::int32_t offset = static_cast<std::int32_t>(0);
             offset <= static_cast<std::int32_t>(6);
             ++offset)
        {
            date const candidate = start + days(offset);
            if (candidate.day_of_week() == wd)
            {
                return candidate;
            }
        }
    }
    /* last-week calculation */
    else if (nth == static_cast<std::int32_t>(0))
    {
        unsigned short const last_dom = static_cast<unsigned short>(
            gregorian_calendar::end_of_month_day(
                m_year,
                static_cast<unsigned short>(m_month.as_number())));

        date d{ m_year,
                static_cast<unsigned short>(m_month.as_number()),
                last_dom };

        while (d.day_of_week() != wd)
        {
            d -= days(1);
        }
        return d;
    }
    /* first-fourth week calculation */
    else
    {
        date const first{ m_year,
                          static_cast<unsigned short>(m_month.as_number()),
                          static_cast<unsigned short>(1U) };

        std::int32_t diff = static_cast<std::int32_t>(wd) -
                            static_cast<std::int32_t>(first.day_of_week());

        if (diff < static_cast<std::int32_t>(0))
        {
            diff += static_cast<std::int32_t>(7);
        }

        std::int32_t const day =
            diff + static_cast<std::int32_t>(1) +
            (static_cast<std::int32_t>(7) *
             (nth - static_cast<std::int32_t>(1)));

        return date{ m_year,
                     static_cast<unsigned short>(m_month.as_number()),
                     static_cast<unsigned short>(day) };
    }

    throw std::logic_error("Invalid meetup calculation");
}

/* ---------- teenth helpers ---------- */
boost::gregorian::date scheduler::monteenth() const
{
    return find_nth_weekday(boost::gregorian::Monday,
                            static_cast<std::int32_t>(5));
}

boost::gregorian::date scheduler::tuesteenth() const
{
    return find_nth_weekday(boost::gregorian::Tuesday,
                            static_cast<std::int32_t>(5));
}

boost::gregorian::date scheduler::wednesteenth() const
{
    return find_nth_weekday(boost::gregorian::Wednesday,
                            static_cast<std::int32_t>(5));
}

boost::gregorian::date scheduler::thursteenth() const
{
    return find_nth_weekday(boost::gregorian::Thursday,
                            static_cast<std::int32_t>(5));
}

boost::gregorian::date scheduler::friteenth() const
{
    return find_nth_weekday(boost::gregorian::Friday,
                            static_cast<std::int32_t>(5));
}

boost::gregorian::date scheduler::saturteenth() const
{
    return find_nth_weekday(boost::gregorian::Saturday,
                            static_cast<std::int32_t>(5));
}

boost::gregorian::date scheduler::sunteenth() const
{
    return find_nth_weekday(boost::gregorian::Sunday,
                            static_cast<std::int32_t>(5));
}

/* ---------- repeating boiler-plate generators ---------- */
#define MEETUP_IMPL(NTH, VALUE)                                                         \
    boost::gregorian::date scheduler::NTH##_monday() const                              \
    {                                                                                   \
        return find_nth_weekday(boost::gregorian::Monday,                               \
                                static_cast<std::int32_t>(VALUE));                      \
    }                                                                                   \
    boost::gregorian::date scheduler::NTH##_tuesday() const                             \
    {                                                                                   \
        return find_nth_weekday(boost::gregorian::Tuesday,                              \
                                static_cast<std::int32_t>(VALUE));                      \
    }                                                                                   \
    boost::gregorian::date scheduler::NTH##_wednesday() const                           \
    {                                                                                   \
        return find_nth_weekday(boost::gregorian::Wednesday,                            \
                                static_cast<std::int32_t>(VALUE));                      \
    }                                                                                   \
    boost::gregorian::date scheduler::NTH##_thursday() const                            \
    {                                                                                   \
        return find_nth_weekday(boost::gregorian::Thursday,                             \
                                static_cast<std::int32_t>(VALUE));                      \
    }                                                                                   \
    boost::gregorian::date scheduler::NTH##_friday() const                              \
    {                                                                                   \
        return find_nth_weekday(boost::gregorian::Friday,                               \
                                static_cast<std::int32_t>(VALUE));                      \
    }                                                                                   \
    boost::gregorian::date scheduler::NTH##_saturday() const                            \
    {                                                                                   \
        return find_nth_weekday(boost::gregorian::Saturday,                             \
                                static_cast<std::int32_t>(VALUE));                      \
    }                                                                                   \
    boost::gregorian::date scheduler::NTH##_sunday() const                              \
    {                                                                                   \
        return find_nth_weekday(boost::gregorian::Sunday,                               \
                                static_cast<std::int32_t>(VALUE));                      \
    }

MEETUP_IMPL(first,  1)
MEETUP_IMPL(second, 2)
MEETUP_IMPL(third,  3)
MEETUP_IMPL(fourth, 4)
MEETUP_IMPL(last,   0)

#undef MEETUP_IMPL

}  // namespace meetup
