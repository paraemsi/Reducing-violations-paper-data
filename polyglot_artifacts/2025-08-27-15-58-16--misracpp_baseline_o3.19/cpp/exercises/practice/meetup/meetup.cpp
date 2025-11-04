#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::gregorian_calendar;
using boost::date_time::weekdays;

scheduler::scheduler(int year, int month)
    : m_year(year), m_month(month) {}

// helper: days in current month
static int days_in_month(int year, int month)
{
    return gregorian_calendar::end_of_month_day(year, month);
}

date scheduler::get_day(weekdays target_wd, schedule sched) const
{
    date first(m_year, m_month, 1);
    int first_wd = first.day_of_week().as_number(); // 0 = Sunday

    int day_num = 0;

    switch (sched) {
        case schedule::teenth: {
            for (int d = 13; d <= 19; ++d) {
                date dt(m_year, m_month, d);
                if (dt.day_of_week().as_number() == static_cast<int>(target_wd)) {
                    day_num = d;
                    break;
                }
            }
            break;
        }

        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth: {
            int ordinal = 0;
            if (sched == schedule::first) ordinal = 0;
            else if (sched == schedule::second) ordinal = 1;
            else if (sched == schedule::third) ordinal = 2;
            else if (sched == schedule::fourth) ordinal = 3;

            int diff = (static_cast<int>(target_wd) - first_wd + 7) % 7;
            day_num = 1 + diff + 7 * ordinal;
            break;
        }

        case schedule::last: {
            int last_day = days_in_month(m_year, m_month);
            date last(m_year, m_month, last_day);
            int last_wd = last.day_of_week().as_number();

            int diff = (last_wd - static_cast<int>(target_wd) + 7) % 7;
            day_num = last_day - diff;
            break;
        }
    }

    return date(m_year, m_month, day_num);
}

// convenience wrappers
// teenth
date scheduler::monteenth()  const { return get_day(boost::date_time::Monday,    schedule::teenth); }
date scheduler::tuesteenth() const { return get_day(boost::date_time::Tuesday,   schedule::teenth); }
date scheduler::wednesteenth() const { return get_day(boost::date_time::Wednesday, schedule::teenth); }
date scheduler::thursteenth() const { return get_day(boost::date_time::Thursday, schedule::teenth); }
date scheduler::friteenth() const { return get_day(boost::date_time::Friday,     schedule::teenth); }
date scheduler::saturteenth() const { return get_day(boost::date_time::Saturday, schedule::teenth); }
date scheduler::sunteenth() const { return get_day(boost::date_time::Sunday,     schedule::teenth); }

// first
date scheduler::first_monday() const { return get_day(boost::date_time::Monday, schedule::first); }
date scheduler::first_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::first); }
date scheduler::first_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::first); }
date scheduler::first_thursday() const { return get_day(boost::date_time::Thursday, schedule::first); }
date scheduler::first_friday() const { return get_day(boost::date_time::Friday, schedule::first); }
date scheduler::first_saturday() const { return get_day(boost::date_time::Saturday, schedule::first); }
date scheduler::first_sunday() const { return get_day(boost::date_time::Sunday, schedule::first); }

// second
date scheduler::second_monday() const { return get_day(boost::date_time::Monday, schedule::second); }
date scheduler::second_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::second); }
date scheduler::second_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::second); }
date scheduler::second_thursday() const { return get_day(boost::date_time::Thursday, schedule::second); }
date scheduler::second_friday() const { return get_day(boost::date_time::Friday, schedule::second); }
date scheduler::second_saturday() const { return get_day(boost::date_time::Saturday, schedule::second); }
date scheduler::second_sunday() const { return get_day(boost::date_time::Sunday, schedule::second); }

// third
date scheduler::third_monday() const { return get_day(boost::date_time::Monday, schedule::third); }
date scheduler::third_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::third); }
date scheduler::third_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::third); }
date scheduler::third_thursday() const { return get_day(boost::date_time::Thursday, schedule::third); }
date scheduler::third_friday() const { return get_day(boost::date_time::Friday, schedule::third); }
date scheduler::third_saturday() const { return get_day(boost::date_time::Saturday, schedule::third); }
date scheduler::third_sunday() const { return get_day(boost::date_time::Sunday, schedule::third); }

// fourth
date scheduler::fourth_monday() const { return get_day(boost::date_time::Monday, schedule::fourth); }
date scheduler::fourth_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::fourth); }
date scheduler::fourth_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::fourth); }
date scheduler::fourth_thursday() const { return get_day(boost::date_time::Thursday, schedule::fourth); }
date scheduler::fourth_friday() const { return get_day(boost::date_time::Friday, schedule::fourth); }
date scheduler::fourth_saturday() const { return get_day(boost::date_time::Saturday, schedule::fourth); }
date scheduler::fourth_sunday() const { return get_day(boost::date_time::Sunday, schedule::fourth); }

// last
date scheduler::last_monday() const { return get_day(boost::date_time::Monday, schedule::last); }
date scheduler::last_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::last); }
date scheduler::last_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::last); }
date scheduler::last_thursday() const { return get_day(boost::date_time::Thursday, schedule::last); }
date scheduler::last_friday() const { return get_day(boost::date_time::Friday, schedule::last); }
date scheduler::last_saturday() const { return get_day(boost::date_time::Saturday, schedule::last); }
date scheduler::last_sunday() const { return get_day(boost::date_time::Sunday, schedule::last); }

}  // namespace meetup
