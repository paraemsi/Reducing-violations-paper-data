#include "meetup.h"

#include <cassert>

namespace meetup {

scheduler::scheduler(boost::gregorian::months_of_year month,
                     std::int32_t                     year) noexcept
    : m_year{year},
      m_month{month}
{
}

boost::gregorian::date scheduler::day(const schedule                   sch,
                                      const boost::date_time::weekdays wd) const
{
    using boost::gregorian::date;
    using boost::gregorian::gregorian_calendar;

    auto is_match = [wd](const date& d) noexcept -> bool
    {
        return (d.day_of_week().as_enum() == wd);
    };

    const std::int32_t last_dom =
        static_cast<std::int32_t>(gregorian_calendar::end_of_month_day(
            m_year,
            static_cast<unsigned short>(m_month)));

    switch (sch)
    {
    case schedule::teenth:
    {
        for (std::int32_t day_num{13}; day_num <= 19; ++day_num)
        {
            const date cand{m_year,
                            m_month,
                            static_cast<unsigned short>(day_num)};
            if (is_match(cand))
            {
                return cand;
            }
        }
        break;
    }

    case schedule::first:
    case schedule::second:
    case schedule::third:
    case schedule::fourth:
    {
        std::int32_t target_index{0};
        switch (sch)
        {
        case schedule::first:  { target_index = 1; break; }
        case schedule::second: { target_index = 2; break; }
        case schedule::third:  { target_index = 3; break; }
        case schedule::fourth: { target_index = 4; break; }
        default:               { break; }   /* unreachable */
        }

        std::int32_t count{0};
        for (std::int32_t day_num{1}; day_num <= last_dom; ++day_num)
        {
            const date cand{m_year,
                            m_month,
                            static_cast<unsigned short>(day_num)};
            if (is_match(cand))
            {
                ++count;
                if (count == target_index)
                {
                    return cand;
                }
            }
        }
        break;
    }

    case schedule::last:
    {
        for (std::int32_t day_num{last_dom}; day_num >= 1; --day_num)
        {
            const date cand{m_year,
                            m_month,
                            static_cast<unsigned short>(day_num)};
            if (is_match(cand))
            {
                return cand;
            }
        }
        break;
    }

    default:
    {
        break;   /* should never occur */
    }
    }

    /* should never reach this point; return a not-a-date */
    return boost::gregorian::date{};
}
}

/* ───────────────── convenience wrappers ──────────────────────────────── */
boost::gregorian::date scheduler::monteenth() const { return day(schedule::teenth, boost::date_time::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return day(schedule::teenth, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return day(schedule::teenth, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return day(schedule::teenth, boost::date_time::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return day(schedule::teenth, boost::date_time::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return day(schedule::teenth, boost::date_time::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return day(schedule::teenth, boost::date_time::Sunday); }

/* first */
#define MEETUP_GEN_FIRST(name, wd) \
boost::gregorian::date scheduler::first_##name() const { return day(schedule::first, boost::date_time::wd); }
MEETUP_GEN_FIRST(monday, Monday)
MEETUP_GEN_FIRST(tuesday, Tuesday)
MEETUP_GEN_FIRST(wednesday, Wednesday)
MEETUP_GEN_FIRST(thursday, Thursday)
MEETUP_GEN_FIRST(friday, Friday)
MEETUP_GEN_FIRST(saturday, Saturday)
MEETUP_GEN_FIRST(sunday, Sunday)
#undef MEETUP_GEN_FIRST

/* second */
#define MEETUP_GEN_SECOND(name, wd) \
boost::gregorian::date scheduler::second_##name() const { return day(schedule::second, boost::date_time::wd); }
MEETUP_GEN_SECOND(monday, Monday)
MEETUP_GEN_SECOND(tuesday, Tuesday)
MEETUP_GEN_SECOND(wednesday, Wednesday)
MEETUP_GEN_SECOND(thursday, Thursday)
MEETUP_GEN_SECOND(friday, Friday)
MEETUP_GEN_SECOND(saturday, Saturday)
MEETUP_GEN_SECOND(sunday, Sunday)
#undef MEETUP_GEN_SECOND

/* third */
#define MEETUP_GEN_THIRD(name, wd) \
boost::gregorian::date scheduler::third_##name() const { return day(schedule::third, boost::date_time::wd); }
MEETUP_GEN_THIRD(monday, Monday)
MEETUP_GEN_THIRD(tuesday, Tuesday)
MEETUP_GEN_THIRD(wednesday, Wednesday)
MEETUP_GEN_THIRD(thursday, Thursday)
MEETUP_GEN_THIRD(friday, Friday)
MEETUP_GEN_THIRD(saturday, Saturday)
MEETUP_GEN_THIRD(sunday, Sunday)
#undef MEETUP_GEN_THIRD

/* fourth */
#define MEETUP_GEN_FOURTH(name, wd) \
boost::gregorian::date scheduler::fourth_##name() const { return day(schedule::fourth, boost::date_time::wd); }
MEETUP_GEN_FOURTH(monday, Monday)
MEETUP_GEN_FOURTH(tuesday, Tuesday)
MEETUP_GEN_FOURTH(wednesday, Wednesday)
MEETUP_GEN_FOURTH(thursday, Thursday)
MEETUP_GEN_FOURTH(friday, Friday)
MEETUP_GEN_FOURTH(saturday, Saturday)
MEETUP_GEN_FOURTH(sunday, Sunday)
#undef MEETUP_GEN_FOURTH

/* last */
#define MEETUP_GEN_LAST(name, wd) \
boost::gregorian::date scheduler::last_##name() const { return day(schedule::last, boost::date_time::wd); }
MEETUP_GEN_LAST(monday, Monday)
MEETUP_GEN_LAST(tuesday, Tuesday)
MEETUP_GEN_LAST(wednesday, Wednesday)
MEETUP_GEN_LAST(thursday, Thursday)
MEETUP_GEN_LAST(friday, Friday)
MEETUP_GEN_LAST(saturday, Saturday)
MEETUP_GEN_LAST(sunday, Sunday)
#undef MEETUP_GEN_LAST

}  // namespace meetup
