#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(greg_month month, int year)
    : m_month(month), m_year(year) {}

date scheduler::find_nth_weekday(int n, boost::date_time::weekdays wd) const {
    // n = 1 for first, 2 for second, etc.
    date first_day(m_year, m_month, 1);
    int first_wd = first_day.day_of_week();
    int add_days = (7 + wd - first_wd) % 7 + 7 * (n - 1);
    date result = first_day + date_duration(add_days);
    if (result.month() != m_month) throw std::domain_error("No such day in month");
    return result;
}

date scheduler::find_last_weekday(boost::date_time::weekdays wd) const {
    date first_day(m_year, m_month, 1);
    date last_day = first_day.end_of_month();
    int last_wd = last_day.day_of_week();
    int sub_days = (7 + last_wd - wd) % 7;
    date result = last_day - date_duration(sub_days);
    if (result.month() != m_month) throw std::domain_error("No such day in month");
    return result;
}

date scheduler::find_teenth_weekday(boost::date_time::weekdays wd) const {
    date teenth_start(m_year, m_month, 13);
    for (int i = 0; i < 7; ++i) {
        date d = teenth_start + date_duration(i);
        if (d.day_of_week() == wd)
            return d;
    }
    throw std::domain_error("No teenth weekday found");
}

// Teenth
date scheduler::monteenth() const { return find_teenth_weekday(boost::date_time::Monday); }
date scheduler::tuesteenth() const { return find_teenth_weekday(boost::date_time::Tuesday); }
date scheduler::wednesteenth() const { return find_teenth_weekday(boost::date_time::Wednesday); }
date scheduler::thursteenth() const { return find_teenth_weekday(boost::date_time::Thursday); }
date scheduler::friteenth() const { return find_teenth_weekday(boost::date_time::Friday); }
date scheduler::saturteenth() const { return find_teenth_weekday(boost::date_time::Saturday); }
date scheduler::sunteenth() const { return find_teenth_weekday(boost::date_time::Sunday); }

// First
date scheduler::first_monday() const { return find_nth_weekday(1, boost::date_time::Monday); }
date scheduler::first_tuesday() const { return find_nth_weekday(1, boost::date_time::Tuesday); }
date scheduler::first_wednesday() const { return find_nth_weekday(1, boost::date_time::Wednesday); }
date scheduler::first_thursday() const { return find_nth_weekday(1, boost::date_time::Thursday); }
date scheduler::first_friday() const { return find_nth_weekday(1, boost::date_time::Friday); }
date scheduler::first_saturday() const { return find_nth_weekday(1, boost::date_time::Saturday); }
date scheduler::first_sunday() const { return find_nth_weekday(1, boost::date_time::Sunday); }

// Second
date scheduler::second_monday() const { return find_nth_weekday(2, boost::date_time::Monday); }
date scheduler::second_tuesday() const { return find_nth_weekday(2, boost::date_time::Tuesday); }
date scheduler::second_wednesday() const { return find_nth_weekday(2, boost::date_time::Wednesday); }
date scheduler::second_thursday() const { return find_nth_weekday(2, boost::date_time::Thursday); }
date scheduler::second_friday() const { return find_nth_weekday(2, boost::date_time::Friday); }
date scheduler::second_saturday() const { return find_nth_weekday(2, boost::date_time::Saturday); }
date scheduler::second_sunday() const { return find_nth_weekday(2, boost::date_time::Sunday); }

// Third
date scheduler::third_monday() const { return find_nth_weekday(3, boost::date_time::Monday); }
date scheduler::third_tuesday() const { return find_nth_weekday(3, boost::date_time::Tuesday); }
date scheduler::third_wednesday() const { return find_nth_weekday(3, boost::date_time::Wednesday); }
date scheduler::third_thursday() const { return find_nth_weekday(3, boost::date_time::Thursday); }
date scheduler::third_friday() const { return find_nth_weekday(3, boost::date_time::Friday); }
date scheduler::third_saturday() const { return find_nth_weekday(3, boost::date_time::Saturday); }
date scheduler::third_sunday() const { return find_nth_weekday(3, boost::date_time::Sunday); }

// Fourth
date scheduler::fourth_monday() const { return find_nth_weekday(4, boost::date_time::Monday); }
date scheduler::fourth_tuesday() const { return find_nth_weekday(4, boost::date_time::Tuesday); }
date scheduler::fourth_wednesday() const { return find_nth_weekday(4, boost::date_time::Wednesday); }
date scheduler::fourth_thursday() const { return find_nth_weekday(4, boost::date_time::Thursday); }
date scheduler::fourth_friday() const { return find_nth_weekday(4, boost::date_time::Friday); }
date scheduler::fourth_saturday() const { return find_nth_weekday(4, boost::date_time::Saturday); }
date scheduler::fourth_sunday() const { return find_nth_weekday(4, boost::date_time::Sunday); }

// Last
date scheduler::last_monday() const { return find_last_weekday(boost::date_time::Monday); }
date scheduler::last_tuesday() const { return find_last_weekday(boost::date_time::Tuesday); }
date scheduler::last_wednesday() const { return find_last_weekday(boost::date_time::Wednesday); }
date scheduler::last_thursday() const { return find_last_weekday(boost::date_time::Thursday); }
date scheduler::last_friday() const { return find_last_weekday(boost::date_time::Friday); }
date scheduler::last_saturday() const { return find_last_weekday(boost::date_time::Saturday); }
date scheduler::last_sunday() const { return find_last_weekday(boost::date_time::Sunday); }

}  // namespace meetup
