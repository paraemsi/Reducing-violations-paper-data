#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;
using boost::date_time::weekdays;

scheduler::scheduler(int month, int year)
    : m_month(month), m_year(year) {}

date scheduler::find_nth_weekday(int nth, weekdays wd) const {
    // nth: 1=first, 2=second, etc.
    date d(m_year, m_month, 1);
    int count = 0;
    while (d.month() == m_month) {
        if (d.day_of_week() == wd) {
            ++count;
            if (count == nth)
                return d;
        }
        d += days(1);
    }
    throw std::domain_error("No such weekday in this month");
}

date scheduler::find_last_weekday(weekdays wd) const {
    date d = date(m_year, m_month, gregorian_calendar::end_of_month_day(m_year, m_month));
    while (d.day_of_week() != wd) {
        d -= days(1);
    }
    return d;
}

date scheduler::find_teenth_weekday(weekdays wd) const {
    for (int day = 13; day <= 19; ++day) {
        date d(m_year, m_month, day);
        if (d.day_of_week() == wd)
            return d;
    }
    throw std::domain_error("No teenth weekday in this month");
}

date scheduler::monteenth() const { return find_teenth_weekday(Monday); }
date scheduler::tuesteenth() const { return find_teenth_weekday(Tuesday); }
date scheduler::wednesteenth() const { return find_teenth_weekday(Wednesday); }
date scheduler::thursteenth() const { return find_teenth_weekday(Thursday); }
date scheduler::friteenth() const { return find_teenth_weekday(Friday); }
date scheduler::saturteenth() const { return find_teenth_weekday(Saturday); }
date scheduler::sunteenth() const { return find_teenth_weekday(Sunday); }

// First
date scheduler::first_monday() const { return find_nth_weekday(1, Monday); }
date scheduler::first_tuesday() const { return find_nth_weekday(1, Tuesday); }
date scheduler::first_wednesday() const { return find_nth_weekday(1, Wednesday); }
date scheduler::first_thursday() const { return find_nth_weekday(1, Thursday); }
date scheduler::first_friday() const { return find_nth_weekday(1, Friday); }
date scheduler::first_saturday() const { return find_nth_weekday(1, Saturday); }
date scheduler::first_sunday() const { return find_nth_weekday(1, Sunday); }

// Second
date scheduler::second_monday() const { return find_nth_weekday(2, Monday); }
date scheduler::second_tuesday() const { return find_nth_weekday(2, Tuesday); }
date scheduler::second_wednesday() const { return find_nth_weekday(2, Wednesday); }
date scheduler::second_thursday() const { return find_nth_weekday(2, Thursday); }
date scheduler::second_friday() const { return find_nth_weekday(2, Friday); }
date scheduler::second_saturday() const { return find_nth_weekday(2, Saturday); }
date scheduler::second_sunday() const { return find_nth_weekday(2, Sunday); }

// Third
date scheduler::third_monday() const { return find_nth_weekday(3, Monday); }
date scheduler::third_tuesday() const { return find_nth_weekday(3, Tuesday); }
date scheduler::third_wednesday() const { return find_nth_weekday(3, Wednesday); }
date scheduler::third_thursday() const { return find_nth_weekday(3, Thursday); }
date scheduler::third_friday() const { return find_nth_weekday(3, Friday); }
date scheduler::third_saturday() const { return find_nth_weekday(3, Saturday); }
date scheduler::third_sunday() const { return find_nth_weekday(3, Sunday); }

// Fourth
date scheduler::fourth_monday() const { return find_nth_weekday(4, Monday); }
date scheduler::fourth_tuesday() const { return find_nth_weekday(4, Tuesday); }
date scheduler::fourth_wednesday() const { return find_nth_weekday(4, Wednesday); }
date scheduler::fourth_thursday() const { return find_nth_weekday(4, Thursday); }
date scheduler::fourth_friday() const { return find_nth_weekday(4, Friday); }
date scheduler::fourth_saturday() const { return find_nth_weekday(4, Saturday); }
date scheduler::fourth_sunday() const { return find_nth_weekday(4, Sunday); }

// Last
date scheduler::last_monday() const { return find_last_weekday(Monday); }
date scheduler::last_tuesday() const { return find_last_weekday(Tuesday); }
date scheduler::last_wednesday() const { return find_last_weekday(Wednesday); }
date scheduler::last_thursday() const { return find_last_weekday(Thursday); }
date scheduler::last_friday() const { return find_last_weekday(Friday); }
date scheduler::last_saturday() const { return find_last_weekday(Saturday); }
date scheduler::last_sunday() const { return find_last_weekday(Sunday); }

}  // namespace meetup
