#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;
using boost::date_time::weekdays;

scheduler::scheduler(greg_month month, int year)
    : m_month(month), m_year(year) {}

date scheduler::find_nth_weekday(int n, weekdays wd) const {
    // n: 1=first, 2=second, 3=third, 4=fourth
    date first(m_year, m_month, 1);
    int first_wd = first.day_of_week();
    int offset = (static_cast<int>(wd) - first_wd + 7) % 7;
    int day = 1 + offset + 7 * (n - 1);
    date result(m_year, m_month, day);
    if (result.month() != m_month)
        throw std::out_of_range("No such weekday in this week");
    return result;
}

date scheduler::find_teenth_weekday(weekdays wd) const {
    for (int d = 13; d <= 19; ++d) {
        date dt(m_year, m_month, d);
        if (dt.day_of_week() == wd)
            return dt;
    }
    throw std::out_of_range("No teenth weekday found");
}

date scheduler::find_last_weekday(weekdays wd) const {
    date d = date(m_year, m_month, gregorian_calendar::end_of_month_day(m_year, m_month.as_number()));
    int diff = (d.day_of_week() - wd + 7) % 7;
    return d - date_duration(diff);
}

// Teenth
date scheduler::monteenth() const { return find_teenth_weekday(weekdays::Monday); }
date scheduler::tuesteenth() const { return find_teenth_weekday(weekdays::Tuesday); }
date scheduler::wednesteenth() const { return find_teenth_weekday(weekdays::Wednesday); }
date scheduler::thursteenth() const { return find_teenth_weekday(weekdays::Thursday); }
date scheduler::friteenth() const { return find_teenth_weekday(weekdays::Friday); }
date scheduler::saturteenth() const { return find_teenth_weekday(weekdays::Saturday); }
date scheduler::sunteenth() const { return find_teenth_weekday(weekdays::Sunday); }

// First
date scheduler::first_monday() const { return find_nth_weekday(1, weekdays::Monday); }
date scheduler::first_tuesday() const { return find_nth_weekday(1, weekdays::Tuesday); }
date scheduler::first_wednesday() const { return find_nth_weekday(1, weekdays::Wednesday); }
date scheduler::first_thursday() const { return find_nth_weekday(1, weekdays::Thursday); }
date scheduler::first_friday() const { return find_nth_weekday(1, weekdays::Friday); }
date scheduler::first_saturday() const { return find_nth_weekday(1, weekdays::Saturday); }
date scheduler::first_sunday() const { return find_nth_weekday(1, weekdays::Sunday); }

// Second
date scheduler::second_monday() const { return find_nth_weekday(2, weekdays::Monday); }
date scheduler::second_tuesday() const { return find_nth_weekday(2, weekdays::Tuesday); }
date scheduler::second_wednesday() const { return find_nth_weekday(2, weekdays::Wednesday); }
date scheduler::second_thursday() const { return find_nth_weekday(2, weekdays::Thursday); }
date scheduler::second_friday() const { return find_nth_weekday(2, weekdays::Friday); }
date scheduler::second_saturday() const { return find_nth_weekday(2, weekdays::Saturday); }
date scheduler::second_sunday() const { return find_nth_weekday(2, weekdays::Sunday); }

// Third
date scheduler::third_monday() const { return find_nth_weekday(3, weekdays::Monday); }
date scheduler::third_tuesday() const { return find_nth_weekday(3, weekdays::Tuesday); }
date scheduler::third_wednesday() const { return find_nth_weekday(3, weekdays::Wednesday); }
date scheduler::third_thursday() const { return find_nth_weekday(3, weekdays::Thursday); }
date scheduler::third_friday() const { return find_nth_weekday(3, weekdays::Friday); }
date scheduler::third_saturday() const { return find_nth_weekday(3, weekdays::Saturday); }
date scheduler::third_sunday() const { return find_nth_weekday(3, weekdays::Sunday); }

// Fourth
date scheduler::fourth_monday() const { return find_nth_weekday(4, weekdays::Monday); }
date scheduler::fourth_tuesday() const { return find_nth_weekday(4, weekdays::Tuesday); }
date scheduler::fourth_wednesday() const { return find_nth_weekday(4, weekdays::Wednesday); }
date scheduler::fourth_thursday() const { return find_nth_weekday(4, weekdays::Thursday); }
date scheduler::fourth_friday() const { return find_nth_weekday(4, weekdays::Friday); }
date scheduler::fourth_saturday() const { return find_nth_weekday(4, weekdays::Saturday); }
date scheduler::fourth_sunday() const { return find_nth_weekday(4, weekdays::Sunday); }

// Last
date scheduler::last_monday() const { return find_last_weekday(weekdays::Monday); }
date scheduler::last_tuesday() const { return find_last_weekday(weekdays::Tuesday); }
date scheduler::last_wednesday() const { return find_last_weekday(weekdays::Wednesday); }
date scheduler::last_thursday() const { return find_last_weekday(weekdays::Thursday); }
date scheduler::last_friday() const { return find_last_weekday(weekdays::Friday); }
date scheduler::last_saturday() const { return find_last_weekday(weekdays::Saturday); }
date scheduler::last_sunday() const { return find_last_weekday(weekdays::Sunday); }

}  // namespace meetup
