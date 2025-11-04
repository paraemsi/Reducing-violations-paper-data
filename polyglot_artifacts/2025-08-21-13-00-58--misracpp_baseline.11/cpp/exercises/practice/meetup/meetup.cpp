#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(greg_month month, int year)
    : m_month(month), m_year(year) {}

date scheduler::get_nth_weekday(int weekday, int n) const {
    // weekday: 0=Sunday, ..., 6=Saturday
    date first_day(m_year, m_month, 1);
    int first_wday = first_day.day_of_week();
    int offset = (weekday - first_wday + 7) % 7;
    int day = 1 + offset + 7 * (n - 1);
    if (day > gregorian_calendar::end_of_month_day(m_year, m_month.as_number()))
        throw std::out_of_range("No such weekday in this month");
    return date(m_year, m_month, day);
}

date scheduler::get_last_weekday(int weekday) const {
    int last_day = gregorian_calendar::end_of_month_day(m_year, m_month.as_number());
    date d(m_year, m_month, last_day);
    int d_wday = d.day_of_week();
    int offset = (d_wday - weekday + 7) % 7;
    return d - date_duration(offset);
}

date scheduler::get_teenth_weekday(int weekday) const {
    for (int d = 13; d <= 19; ++d) {
        date dt(m_year, m_month, d);
        if (dt.day_of_week() == weekday)
            return dt;
    }
    throw std::out_of_range("No teenth weekday in this month");
}

// Teenth
date scheduler::monteenth() const { return get_teenth_weekday(1); }
date scheduler::tuesteenth() const { return get_teenth_weekday(2); }
date scheduler::wednesteenth() const { return get_teenth_weekday(3); }
date scheduler::thursteenth() const { return get_teenth_weekday(4); }
date scheduler::friteenth() const { return get_teenth_weekday(5); }
date scheduler::saturteenth() const { return get_teenth_weekday(6); }
date scheduler::sunteenth() const { return get_teenth_weekday(0); }

// First
date scheduler::first_monday() const { return get_nth_weekday(1, 1); }
date scheduler::first_tuesday() const { return get_nth_weekday(2, 1); }
date scheduler::first_wednesday() const { return get_nth_weekday(3, 1); }
date scheduler::first_thursday() const { return get_nth_weekday(4, 1); }
date scheduler::first_friday() const { return get_nth_weekday(5, 1); }
date scheduler::first_saturday() const { return get_nth_weekday(6, 1); }
date scheduler::first_sunday() const { return get_nth_weekday(0, 1); }

// Second
date scheduler::second_monday() const { return get_nth_weekday(1, 2); }
date scheduler::second_tuesday() const { return get_nth_weekday(2, 2); }
date scheduler::second_wednesday() const { return get_nth_weekday(3, 2); }
date scheduler::second_thursday() const { return get_nth_weekday(4, 2); }
date scheduler::second_friday() const { return get_nth_weekday(5, 2); }
date scheduler::second_saturday() const { return get_nth_weekday(6, 2); }
date scheduler::second_sunday() const { return get_nth_weekday(0, 2); }

// Third
date scheduler::third_monday() const { return get_nth_weekday(1, 3); }
date scheduler::third_tuesday() const { return get_nth_weekday(2, 3); }
date scheduler::third_wednesday() const { return get_nth_weekday(3, 3); }
date scheduler::third_thursday() const { return get_nth_weekday(4, 3); }
date scheduler::third_friday() const { return get_nth_weekday(5, 3); }
date scheduler::third_saturday() const { return get_nth_weekday(6, 3); }
date scheduler::third_sunday() const { return get_nth_weekday(0, 3); }

// Fourth
date scheduler::fourth_monday() const { return get_nth_weekday(1, 4); }
date scheduler::fourth_tuesday() const { return get_nth_weekday(2, 4); }
date scheduler::fourth_wednesday() const { return get_nth_weekday(3, 4); }
date scheduler::fourth_thursday() const { return get_nth_weekday(4, 4); }
date scheduler::fourth_friday() const { return get_nth_weekday(5, 4); }
date scheduler::fourth_saturday() const { return get_nth_weekday(6, 4); }
date scheduler::fourth_sunday() const { return get_nth_weekday(0, 4); }

// Last
date scheduler::last_monday() const { return get_last_weekday(1); }
date scheduler::last_tuesday() const { return get_last_weekday(2); }
date scheduler::last_wednesday() const { return get_last_weekday(3); }
date scheduler::last_thursday() const { return get_last_weekday(4); }
date scheduler::last_friday() const { return get_last_weekday(5); }
date scheduler::last_saturday() const { return get_last_weekday(6); }
date scheduler::last_sunday() const { return get_last_weekday(0); }

}  // namespace meetup
