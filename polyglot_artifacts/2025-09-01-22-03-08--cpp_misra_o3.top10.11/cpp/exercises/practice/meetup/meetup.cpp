#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {

using boost::gregorian::date;
using boost::date_time::weekdays;

[[nodiscard]] date
find_day_in_range(year_t year,
                  month_t month,
                  weekdays target_weekday,
                  std::uint32_t first_day,
                  std::uint32_t last_day)
{
    for (std::uint32_t d { first_day }; d <= last_day; ++d) {
        const date current { static_cast<int>(year),
                             static_cast<unsigned short>(month),
                             static_cast<unsigned short>(d) };
        if (static_cast<int>(current.day_of_week().as_number())
            == static_cast<int>(target_weekday)) {
            return current;
        }
    }
    /* Logic dictates a match must be found; return range start otherwise. */
    return date { static_cast<int>(year),
                  static_cast<unsigned short>(month),
                  static_cast<unsigned short>(first_day) };
}

}  // unnamed namespace

scheduler::scheduler(year_t year, month_t month) noexcept
    : m_year { year }, m_month { month }
{
}

date scheduler::get_day(weekdays week_day, Schedule schedule) const
{
    date result { static_cast<int>(m_year),
                  static_cast<unsigned short>(m_month),
                  static_cast<unsigned short>(1U) };

    switch (schedule) {
    case Schedule::first: {
        result = find_day_in_range(m_year, m_month, week_day, 1U, 7U);
        break;
    }
    case Schedule::second: {
        result = find_day_in_range(m_year, m_month, week_day, 8U, 14U);
        break;
    }
    case Schedule::third: {
        result = find_day_in_range(m_year, m_month, week_day, 15U, 21U);
        break;
    }
    case Schedule::fourth: {
        result = find_day_in_range(m_year, m_month, week_day, 22U, 28U);
        break;
    }
    case Schedule::teenth: {
        result = find_day_in_range(m_year, m_month, week_day, 13U, 19U);
        break;
    }
    case Schedule::last: {
        const std::uint32_t last_dom {
            static_cast<std::uint32_t>(
                boost::gregorian::gregorian_calendar::end_of_month_day(
                    static_cast<int>(m_year),
                    static_cast<int>(m_month)))
        };
        const std::uint32_t start_dom { (last_dom > 6U) ? (last_dom - 6U) : 1U };
        result = find_day_in_range(m_year, m_month, week_day, start_dom, last_dom);
        break;
    }
    }

    return result;
}

/* Convenience wrappers generated through a macro to avoid repetition. */
#define MEETUP_DEFINE_WRAPPER(method, weekday_const, sched)               \
    boost::gregorian::date scheduler::method() const {                    \
        return get_day(weekday_const, sched);                             \
    }

/* 'teenth' */
MEETUP_DEFINE_WRAPPER(monteenth,       boost::date_time::Monday,    Schedule::teenth)
MEETUP_DEFINE_WRAPPER(tuesteenth,      boost::date_time::Tuesday,   Schedule::teenth)
MEETUP_DEFINE_WRAPPER(wednesteenth,    boost::date_time::Wednesday, Schedule::teenth)
MEETUP_DEFINE_WRAPPER(thursteenth,     boost::date_time::Thursday,  Schedule::teenth)
MEETUP_DEFINE_WRAPPER(friteenth,       boost::date_time::Friday,    Schedule::teenth)
MEETUP_DEFINE_WRAPPER(saturteenth,     boost::date_time::Saturday,  Schedule::teenth)
MEETUP_DEFINE_WRAPPER(sunteenth,       boost::date_time::Sunday,    Schedule::teenth)

/* first */
MEETUP_DEFINE_WRAPPER(first_monday,    boost::date_time::Monday,    Schedule::first)
MEETUP_DEFINE_WRAPPER(first_tuesday,   boost::date_time::Tuesday,   Schedule::first)
MEETUP_DEFINE_WRAPPER(first_wednesday, boost::date_time::Wednesday, Schedule::first)
MEETUP_DEFINE_WRAPPER(first_thursday,  boost::date_time::Thursday,  Schedule::first)
MEETUP_DEFINE_WRAPPER(first_friday,    boost::date_time::Friday,    Schedule::first)
MEETUP_DEFINE_WRAPPER(first_saturday,  boost::date_time::Saturday,  Schedule::first)
MEETUP_DEFINE_WRAPPER(first_sunday,    boost::date_time::Sunday,    Schedule::first)

/* second */
MEETUP_DEFINE_WRAPPER(second_monday,    boost::date_time::Monday,    Schedule::second)
MEETUP_DEFINE_WRAPPER(second_tuesday,   boost::date_time::Tuesday,   Schedule::second)
MEETUP_DEFINE_WRAPPER(second_wednesday, boost::date_time::Wednesday, Schedule::second)
MEETUP_DEFINE_WRAPPER(second_thursday,  boost::date_time::Thursday,  Schedule::second)
MEETUP_DEFINE_WRAPPER(second_friday,    boost::date_time::Friday,    Schedule::second)
MEETUP_DEFINE_WRAPPER(second_saturday,  boost::date_time::Saturday,  Schedule::second)
MEETUP_DEFINE_WRAPPER(second_sunday,    boost::date_time::Sunday,    Schedule::second)

/* third */
MEETUP_DEFINE_WRAPPER(third_monday,    boost::date_time::Monday,    Schedule::third)
MEETUP_DEFINE_WRAPPER(third_tuesday,   boost::date_time::Tuesday,   Schedule::third)
MEETUP_DEFINE_WRAPPER(third_wednesday, boost::date_time::Wednesday, Schedule::third)
MEETUP_DEFINE_WRAPPER(third_thursday,  boost::date_time::Thursday,  Schedule::third)
MEETUP_DEFINE_WRAPPER(third_friday,    boost::date_time::Friday,    Schedule::third)
MEETUP_DEFINE_WRAPPER(third_saturday,  boost::date_time::Saturday,  Schedule::third)
MEETUP_DEFINE_WRAPPER(third_sunday,    boost::date_time::Sunday,    Schedule::third)

/* fourth */
MEETUP_DEFINE_WRAPPER(fourth_monday,    boost::date_time::Monday,    Schedule::fourth)
MEETUP_DEFINE_WRAPPER(fourth_tuesday,   boost::date_time::Tuesday,   Schedule::fourth)
MEETUP_DEFINE_WRAPPER(fourth_wednesday, boost::date_time::Wednesday, Schedule::fourth)
MEETUP_DEFINE_WRAPPER(fourth_thursday,  boost::date_time::Thursday,  Schedule::fourth)
MEETUP_DEFINE_WRAPPER(fourth_friday,    boost::date_time::Friday,    Schedule::fourth)
MEETUP_DEFINE_WRAPPER(fourth_saturday,  boost::date_time::Saturday,  Schedule::fourth)
MEETUP_DEFINE_WRAPPER(fourth_sunday,    boost::date_time::Sunday,    Schedule::fourth)

/* last */
MEETUP_DEFINE_WRAPPER(last_monday,    boost::date_time::Monday,    Schedule::last)
MEETUP_DEFINE_WRAPPER(last_tuesday,   boost::date_time::Tuesday,   Schedule::last)
MEETUP_DEFINE_WRAPPER(last_wednesday, boost::date_time::Wednesday, Schedule::last)
MEETUP_DEFINE_WRAPPER(last_thursday,  boost::date_time::Thursday,  Schedule::last)
MEETUP_DEFINE_WRAPPER(last_friday,    boost::date_time::Friday,    Schedule::last)
MEETUP_DEFINE_WRAPPER(last_saturday,  boost::date_time::Saturday,  Schedule::last)
MEETUP_DEFINE_WRAPPER(last_sunday,    boost::date_time::Sunday,    Schedule::last)

#undef MEETUP_DEFINE_WRAPPER

}  // namespace meetup
