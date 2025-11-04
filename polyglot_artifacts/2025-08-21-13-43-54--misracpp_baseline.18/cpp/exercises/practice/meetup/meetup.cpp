#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(greg_month month, int year)
    : m_month(month), m_year(year) {}

date scheduler::get_nth_weekday(int n, date_time::weekdays wd) const {
    // n = 1 for first, 2 for second, etc.
    date first_day(m_year, m_month, 1);
    int first_wd = first_day.day_of_week();
    int offset = (7 + wd - first_wd) % 7;
    int day = 1 + offset + 7 * (n - 1);
    if (day > gregorian_calendar::end_of_month_day(m_year, m_month.as_number()))
        throw std::out_of_range("No such weekday in this month");
    return date(m_year, m_month, day);
}

date scheduler::get_last_weekday(date_time::weekdays wd) const {
    int last_day_num = gregorian_calendar::end_of_month_day(m_year, m_month.as_number());
    date last_day(m_year, m_month, last_day_num);
    int last_wd = last_day.day_of_week();
    int offset = (7 + last_wd - wd) % 7;
    int day = last_day_num - offset;
    return date(m_year, m_month, day);
}

date scheduler::get_teenth_weekday(date_time::weekdays wd) const {
    for (int d = 13; d <= 19; ++d) {
        date dt(m_year, m_month, d);
        if (dt.day_of_week() == wd)
            return dt;
    }
    throw std::out_of_range("No teenth weekday in this month");
}

// teenth
date scheduler::monteenth() const { return get_teenth_weekday(date_time::Monday); }
date scheduler::tuesteenth() const { return get_teenth_weekday(date_time::Tuesday); }
date scheduler::wednesteenth() const { return get_teenth_weekday(date_time::Wednesday); }
date scheduler::thursteenth() const { return get_teenth_weekday(date_time::Thursday); }
date scheduler::friteenth() const { return get_teenth_weekday(date_time::Friday); }
date scheduler::saturteenth() const { return get_teenth_weekday(date_time::Saturday); }
date scheduler::sunteenth() const { return get_teenth_weekday(date_time::Sunday); }

// first
date scheduler::first_monday() const { return get_nth_weekday(1, date_time::Monday); }
date scheduler::first_tuesday() const { return get_nth_weekday(1, date_time::Tuesday); }
date scheduler::first_wednesday() const { return get_nth_weekday(1, date_time::Wednesday); }
date scheduler::first_thursday() const { return get_nth_weekday(1, date_time::Thursday); }
date scheduler::first_friday() const { return get_nth_weekday(1, date_time::Friday); }
date scheduler::first_saturday() const { return get_nth_weekday(1, date_time::Saturday); }
date scheduler::first_sunday() const { return get_nth_weekday(1, date_time::Sunday); }

// second
date scheduler::second_monday() const { return get_nth_weekday(2, date_time::Monday); }
date scheduler::second_tuesday() const { return get_nth_weekday(2, date_time::Tuesday); }
date scheduler::second_wednesday() const { return get_nth_weekday(2, date_time::Wednesday); }
date scheduler::second_thursday() const { return get_nth_weekday(2, date_time::Thursday); }
date scheduler::second_friday() const { return get_nth_weekday(2, date_time::Friday); }
date scheduler::second_saturday() const { return get_nth_weekday(2, date_time::Saturday); }
date scheduler::second_sunday() const { return get_nth_weekday(2, date_time::Sunday); }

// third
date scheduler::third_monday() const { return get_nth_weekday(3, date_time::Monday); }
date scheduler::third_tuesday() const { return get_nth_weekday(3, date_time::Tuesday); }
date scheduler::third_wednesday() const { return get_nth_weekday(3, date_time::Wednesday); }
date scheduler::third_thursday() const { return get_nth_weekday(3, date_time::Thursday); }
date scheduler::third_friday() const { return get_nth_weekday(3, date_time::Friday); }
date scheduler::third_saturday() const { return get_nth_weekday(3, date_time::Saturday); }
date scheduler::third_sunday() const { return get_nth_weekday(3, date_time::Sunday); }

// fourth
date scheduler::fourth_monday() const { return get_nth_weekday(4, date_time::Monday); }
date scheduler::fourth_tuesday() const { return get_nth_weekday(4, date_time::Tuesday); }
date scheduler::fourth_wednesday() const { return get_nth_weekday(4, date_time::Wednesday); }
date scheduler::fourth_thursday() const { return get_nth_weekday(4, date_time::Thursday); }
date scheduler::fourth_friday() const { return get_nth_weekday(4, date_time::Friday); }
date scheduler::fourth_saturday() const { return get_nth_weekday(4, date_time::Saturday); }
date scheduler::fourth_sunday() const { return get_nth_weekday(4, date_time::Sunday); }

// last
date scheduler::last_monday() const { return get_last_weekday(date_time::Monday); }
date scheduler::last_tuesday() const { return get_last_weekday(date_time::Tuesday); }
date scheduler::last_wednesday() const { return get_last_weekday(date_time::Wednesday); }
date scheduler::last_thursday() const { return get_last_weekday(date_time::Thursday); }
date scheduler::last_friday() const { return get_last_weekday(date_time::Friday); }
date scheduler::last_saturday() const { return get_last_weekday(date_time::Saturday); }
date scheduler::last_sunday() const { return get_last_weekday(date_time::Sunday); }

} // namespace meetup
