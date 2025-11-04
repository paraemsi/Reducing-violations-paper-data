#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

scheduler::scheduler(std::int32_t year, std::int32_t month) noexcept
    : m_year{year},
      m_month{month}
{
}

boost::gregorian::date
scheduler::day(schedule week, boost::gregorian::greg_weekday weekday) const
{
    return find_date(week, weekday);
}

boost::gregorian::date
scheduler::find_date(schedule week, boost::gregorian::greg_weekday weekday) const
{
    using boost::gregorian::date;
    using boost::gregorian::days;
    using boost::gregorian::gregorian_calendar;
    using std::uint32_t;

    if (week == schedule::teenth) {
        date current{m_year, m_month, static_cast<unsigned short>(13U)};
        while (current.day_of_week() != weekday) {
            current += days{1};
        }
        return current;
    }

    if (week == schedule::last) {
        const unsigned short last_dom{static_cast<unsigned short>(
            gregorian_calendar::end_of_month_day(m_year, m_month))};

        date current{m_year, m_month, last_dom};
        while (current.day_of_week() != weekday) {
            current -= days{1};
        }
        return current;
    }

    uint32_t nth{1U};
    switch (week) {
        case schedule::first:  { nth = 1U; break; }
        case schedule::second: { nth = 2U; break; }
        case schedule::third:  { nth = 3U; break; }
        case schedule::fourth: { nth = 4U; break; }
        default:               { break; }
    }

    date current{m_year, m_month, static_cast<unsigned short>(1U)};
    while (current.day_of_week() != weekday) {
        current += days{1};
    }
    const std::int32_t offset_days{
        static_cast<std::int32_t>((nth - 1U) * 7U)};
    current += days{offset_days};
    return current;
}

/* Teenth helpers */
boost::gregorian::date scheduler::monteenth() const {
    return find_date(schedule::teenth,
                     boost::gregorian::greg_weekday(boost::date_time::Monday));
}
boost::gregorian::date scheduler::tuesteenth() const {
    return find_date(schedule::teenth,
                     boost::gregorian::greg_weekday(boost::date_time::Tuesday));
}
boost::gregorian::date scheduler::wednesteenth() const {
    return find_date(schedule::teenth,
                     boost::gregorian::greg_weekday(boost::date_time::Wednesday));
}
boost::gregorian::date scheduler::thursteenth() const {
    return find_date(schedule::teenth,
                     boost::gregorian::greg_weekday(boost::date_time::Thursday));
}
boost::gregorian::date scheduler::friteenth() const {
    return find_date(schedule::teenth,
                     boost::gregorian::greg_weekday(boost::date_time::Friday));
}
boost::gregorian::date scheduler::saturteenth() const {
    return find_date(schedule::teenth,
                     boost::gregorian::greg_weekday(boost::date_time::Saturday));
}
boost::gregorian::date scheduler::sunteenth() const {
    return find_date(schedule::teenth,
                     boost::gregorian::greg_weekday(boost::date_time::Sunday));
}

/* First */
boost::gregorian::date scheduler::first_monday() const {
    return find_date(schedule::first,
                     boost::gregorian::greg_weekday(boost::date_time::Monday));
}
boost::gregorian::date scheduler::first_tuesday() const {
    return find_date(schedule::first,
                     boost::gregorian::greg_weekday(boost::date_time::Tuesday));
}
boost::gregorian::date scheduler::first_wednesday() const {
    return find_date(schedule::first,
                     boost::gregorian::greg_weekday(boost::date_time::Wednesday));
}
boost::gregorian::date scheduler::first_thursday() const {
    return find_date(schedule::first,
                     boost::gregorian::greg_weekday(boost::date_time::Thursday));
}
boost::gregorian::date scheduler::first_friday() const {
    return find_date(schedule::first,
                     boost::gregorian::greg_weekday(boost::date_time::Friday));
}
boost::gregorian::date scheduler::first_saturday() const {
    return find_date(schedule::first,
                     boost::gregorian::greg_weekday(boost::date_time::Saturday));
}
boost::gregorian::date scheduler::first_sunday() const {
    return find_date(schedule::first,
                     boost::gregorian::greg_weekday(boost::date_time::Sunday));
}

/* Second */
boost::gregorian::date scheduler::second_monday() const {
    return find_date(schedule::second,
                     boost::gregorian::greg_weekday(boost::date_time::Monday));
}
boost::gregorian::date scheduler::second_tuesday() const {
    return find_date(schedule::second,
                     boost::gregorian::greg_weekday(boost::date_time::Tuesday));
}
boost::gregorian::date scheduler::second_wednesday() const {
    return find_date(schedule::second,
                     boost::gregorian::greg_weekday(boost::date_time::Wednesday));
}
boost::gregorian::date scheduler::second_thursday() const {
    return find_date(schedule::second,
                     boost::gregorian::greg_weekday(boost::date_time::Thursday));
}
boost::gregorian::date scheduler::second_friday() const {
    return find_date(schedule::second,
                     boost::gregorian::greg_weekday(boost::date_time::Friday));
}
boost::gregorian::date scheduler::second_saturday() const {
    return find_date(schedule::second,
                     boost::gregorian::greg_weekday(boost::date_time::Saturday));
}
boost::gregorian::date scheduler::second_sunday() const {
    return find_date(schedule::second,
                     boost::gregorian::greg_weekday(boost::date_time::Sunday));
}

/* Third */
boost::gregorian::date scheduler::third_monday() const {
    return find_date(schedule::third,
                     boost::gregorian::greg_weekday(boost::date_time::Monday));
}
boost::gregorian::date scheduler::third_tuesday() const {
    return find_date(schedule::third,
                     boost::gregorian::greg_weekday(boost::date_time::Tuesday));
}
boost::gregorian::date scheduler::third_wednesday() const {
    return find_date(schedule::third,
                     boost::gregorian::greg_weekday(boost::date_time::Wednesday));
}
boost::gregorian::date scheduler::third_thursday() const {
    return find_date(schedule::third,
                     boost::gregorian::greg_weekday(boost::date_time::Thursday));
}
boost::gregorian::date scheduler::third_friday() const {
    return find_date(schedule::third,
                     boost::gregorian::greg_weekday(boost::date_time::Friday));
}
boost::gregorian::date scheduler::third_saturday() const {
    return find_date(schedule::third,
                     boost::gregorian::greg_weekday(boost::date_time::Saturday));
}
boost::gregorian::date scheduler::third_sunday() const {
    return find_date(schedule::third,
                     boost::gregorian::greg_weekday(boost::date_time::Sunday));
}

/* Fourth */
boost::gregorian::date scheduler::fourth_monday() const {
    return find_date(schedule::fourth,
                     boost::gregorian::greg_weekday(boost::date_time::Monday));
}
boost::gregorian::date scheduler::fourth_tuesday() const {
    return find_date(schedule::fourth,
                     boost::gregorian::greg_weekday(boost::date_time::Tuesday));
}
boost::gregorian::date scheduler::fourth_wednesday() const {
    return find_date(schedule::fourth,
                     boost::gregorian::greg_weekday(boost::date_time::Wednesday));
}
boost::gregorian::date scheduler::fourth_thursday() const {
    return find_date(schedule::fourth,
                     boost::gregorian::greg_weekday(boost::date_time::Thursday));
}
boost::gregorian::date scheduler::fourth_friday() const {
    return find_date(schedule::fourth,
                     boost::gregorian::greg_weekday(boost::date_time::Friday));
}
boost::gregorian::date scheduler::fourth_saturday() const {
    return find_date(schedule::fourth,
                     boost::gregorian::greg_weekday(boost::date_time::Saturday));
}
boost::gregorian::date scheduler::fourth_sunday() const {
    return find_date(schedule::fourth,
                     boost::gregorian::greg_weekday(boost::date_time::Sunday));
}

/* Last */
boost::gregorian::date scheduler::last_monday() const {
    return find_date(schedule::last,
                     boost::gregorian::greg_weekday(boost::date_time::Monday));
}
boost::gregorian::date scheduler::last_tuesday() const {
    return find_date(schedule::last,
                     boost::gregorian::greg_weekday(boost::date_time::Tuesday));
}
boost::gregorian::date scheduler::last_wednesday() const {
    return find_date(schedule::last,
                     boost::gregorian::greg_weekday(boost::date_time::Wednesday));
}
boost::gregorian::date scheduler::last_thursday() const {
    return find_date(schedule::last,
                     boost::gregorian::greg_weekday(boost::date_time::Thursday));
}
boost::gregorian::date scheduler::last_friday() const {
    return find_date(schedule::last,
                     boost::gregorian::greg_weekday(boost::date_time::Friday));
}
boost::gregorian::date scheduler::last_saturday() const {
    return find_date(schedule::last,
                     boost::gregorian::greg_weekday(boost::date_time::Saturday));
}
boost::gregorian::date scheduler::last_sunday() const {
    return find_date(schedule::last,
                     boost::gregorian::greg_weekday(boost::date_time::Sunday));
}

}  // namespace meetup
