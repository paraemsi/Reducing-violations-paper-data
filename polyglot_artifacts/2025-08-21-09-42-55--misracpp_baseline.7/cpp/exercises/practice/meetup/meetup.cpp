#include "meetup.h"
#include <stdexcept>

using namespace boost::gregorian;

namespace meetup {

scheduler::scheduler(greg_month month, int year)
    : m_month(month), m_year(year)
{}

date scheduler::get_nth_weekday(int nth, date_time::weekdays wd) const {
    // nth: 1=first, 2=second, 3=third, 4=fourth
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
    throw std::logic_error("No such weekday in month");
}

date scheduler::get_last_weekday(date_time::weekdays wd) const {
    date d = date(m_year, m_month, gregorian_calendar::end_of_month_day(m_year, m_month.as_number()));
    while (d.day_of_week() != wd) {
        d -= days(1);
    }
    return d;
}

date scheduler::get_teenth_weekday(date_time::weekdays wd) const {
    for (int day = 13; day <= 19; ++day) {
        date d(m_year, m_month, day);
        if (d.day_of_week() == wd)
            return d;
    }
    throw std::logic_error("No teenth weekday in month");
}

// teenth
date scheduler::monteenth() const { return get_teenth_weekday(Monday); }
date scheduler::tuesteenth() const { return get_teenth_weekday(Tuesday); }
date scheduler::wednesteenth() const { return get_teenth_weekday(Wednesday); }
date scheduler::thursteenth() const { return get_teenth_weekday(Thursday); }
date scheduler::friteenth() const { return get_teenth_weekday(Friday); }
date scheduler::saturteenth() const { return get_teenth_weekday(Saturday); }
date scheduler::sunteenth() const { return get_teenth_weekday(Sunday); }

// first
date scheduler::first_monday() const { return get_nth_weekday(1, Monday); }
date scheduler::first_tuesday() const { return get_nth_weekday(1, Tuesday); }
date scheduler::first_wednesday() const { return get_nth_weekday(1, Wednesday); }
date scheduler::first_thursday() const { return get_nth_weekday(1, Thursday); }
date scheduler::first_friday() const { return get_nth_weekday(1, Friday); }
date scheduler::first_saturday() const { return get_nth_weekday(1, Saturday); }
date scheduler::first_sunday() const { return get_nth_weekday(1, Sunday); }

// second
date scheduler::second_monday() const { return get_nth_weekday(2, Monday); }
date scheduler::second_tuesday() const { return get_nth_weekday(2, Tuesday); }
date scheduler::second_wednesday() const { return get_nth_weekday(2, Wednesday); }
date scheduler::second_thursday() const { return get_nth_weekday(2, Thursday); }
date scheduler::second_friday() const { return get_nth_weekday(2, Friday); }
date scheduler::second_saturday() const { return get_nth_weekday(2, Saturday); }
date scheduler::second_sunday() const { return get_nth_weekday(2, Sunday); }

// third
date scheduler::third_monday() const { return get_nth_weekday(3, Monday); }
date scheduler::third_tuesday() const { return get_nth_weekday(3, Tuesday); }
date scheduler::third_wednesday() const { return get_nth_weekday(3, Wednesday); }
date scheduler::third_thursday() const { return get_nth_weekday(3, Thursday); }
date scheduler::third_friday() const { return get_nth_weekday(3, Friday); }
date scheduler::third_saturday() const { return get_nth_weekday(3, Saturday); }
date scheduler::third_sunday() const { return get_nth_weekday(3, Sunday); }

// fourth
date scheduler::fourth_monday() const { return get_nth_weekday(4, Monday); }
date scheduler::fourth_tuesday() const { return get_nth_weekday(4, Tuesday); }
date scheduler::fourth_wednesday() const { return get_nth_weekday(4, Wednesday); }
date scheduler::fourth_thursday() const { return get_nth_weekday(4, Thursday); }
date scheduler::fourth_friday() const { return get_nth_weekday(4, Friday); }
date scheduler::fourth_saturday() const { return get_nth_weekday(4, Saturday); }
date scheduler::fourth_sunday() const { return get_nth_weekday(4, Sunday); }

// last
date scheduler::last_monday() const { return get_last_weekday(Monday); }
date scheduler::last_tuesday() const { return get_last_weekday(Tuesday); }
date scheduler::last_wednesday() const { return get_last_weekday(Wednesday); }
date scheduler::last_thursday() const { return get_last_weekday(Thursday); }
date scheduler::last_friday() const { return get_last_weekday(Friday); }
date scheduler::last_saturday() const { return get_last_weekday(Saturday); }
date scheduler::last_sunday() const { return get_last_weekday(Sunday); }

} // namespace meetup
