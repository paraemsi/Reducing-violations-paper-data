#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(greg_month month, int year)
    : m_month(month), m_year(year) {}

date scheduler::find_nth_weekday(int nth, boost::date_time::weekdays wd) const {
    // nth: 1=first, 2=second, etc.
    date first_day(m_year, m_month, 1);
    int first_wd = first_day.day_of_week();
    int offset = (7 + wd - first_wd) % 7;
    int day = 1 + offset + 7 * (nth - 1);
    if (day > gregorian_calendar::end_of_month_day(m_year, m_month.as_number()))
        throw std::out_of_range("No such day in month");
    return date(m_year, m_month, day);
}

date scheduler::find_teenth_weekday(boost::date_time::weekdays wd) const {
    for (int d = 13; d <= 19; ++d) {
        date dt(m_year, m_month, d);
        if (dt.day_of_week() == wd)
            return dt;
    }
    throw std::out_of_range("No teenth weekday found");
}

date scheduler::find_last_weekday(boost::date_time::weekdays wd) const {
    int last_day = gregorian_calendar::end_of_month_day(m_year, m_month.as_number());
    date dt(m_year, m_month, last_day);
    int offset = (7 + dt.day_of_week() - wd) % 7;
    return date(m_year, m_month, last_day - offset);
}

// teenth
date scheduler::monteenth() const { return find_teenth_weekday(Monday); }
date scheduler::tuesteenth() const { return find_teenth_weekday(Tuesday); }
date scheduler::wednesteenth() const { return find_teenth_weekday(Wednesday); }
date scheduler::thursteenth() const { return find_teenth_weekday(Thursday); }
date scheduler::friteenth() const { return find_teenth_weekday(Friday); }
date scheduler::saturteenth() const { return find_teenth_weekday(Saturday); }
date scheduler::sunteenth() const { return find_teenth_weekday(Sunday); }

// first
date scheduler::first_monday() const { return find_nth_weekday(1, Monday); }
date scheduler::first_tuesday() const { return find_nth_weekday(1, Tuesday); }
date scheduler::first_wednesday() const { return find_nth_weekday(1, Wednesday); }
date scheduler::first_thursday() const { return find_nth_weekday(1, Thursday); }
date scheduler::first_friday() const { return find_nth_weekday(1, Friday); }
date scheduler::first_saturday() const { return find_nth_weekday(1, Saturday); }
date scheduler::first_sunday() const { return find_nth_weekday(1, Sunday); }

// second
date scheduler::second_monday() const { return find_nth_weekday(2, Monday); }
date scheduler::second_tuesday() const { return find_nth_weekday(2, Tuesday); }
date scheduler::second_wednesday() const { return find_nth_weekday(2, Wednesday); }
date scheduler::second_thursday() const { return find_nth_weekday(2, Thursday); }
date scheduler::second_friday() const { return find_nth_weekday(2, Friday); }
date scheduler::second_saturday() const { return find_nth_weekday(2, Saturday); }
date scheduler::second_sunday() const { return find_nth_weekday(2, Sunday); }

// third
date scheduler::third_monday() const { return find_nth_weekday(3, Monday); }
date scheduler::third_tuesday() const { return find_nth_weekday(3, Tuesday); }
date scheduler::third_wednesday() const { return find_nth_weekday(3, Wednesday); }
date scheduler::third_thursday() const { return find_nth_weekday(3, Thursday); }
date scheduler::third_friday() const { return find_nth_weekday(3, Friday); }
date scheduler::third_saturday() const { return find_nth_weekday(3, Saturday); }
date scheduler::third_sunday() const { return find_nth_weekday(3, Sunday); }

// fourth
date scheduler::fourth_monday() const { return find_nth_weekday(4, Monday); }
date scheduler::fourth_tuesday() const { return find_nth_weekday(4, Tuesday); }
date scheduler::fourth_wednesday() const { return find_nth_weekday(4, Wednesday); }
date scheduler::fourth_thursday() const { return find_nth_weekday(4, Thursday); }
date scheduler::fourth_friday() const { return find_nth_weekday(4, Friday); }
date scheduler::fourth_saturday() const { return find_nth_weekday(4, Saturday); }
date scheduler::fourth_sunday() const { return find_nth_weekday(4, Sunday); }

// last
date scheduler::last_monday() const { return find_last_weekday(Monday); }
date scheduler::last_tuesday() const { return find_last_weekday(Tuesday); }
date scheduler::last_wednesday() const { return find_last_weekday(Wednesday); }
date scheduler::last_thursday() const { return find_last_weekday(Thursday); }
date scheduler::last_friday() const { return find_last_weekday(Friday); }
date scheduler::last_saturday() const { return find_last_weekday(Saturday); }
date scheduler::last_sunday() const { return find_last_weekday(Sunday); }

} // namespace meetup
