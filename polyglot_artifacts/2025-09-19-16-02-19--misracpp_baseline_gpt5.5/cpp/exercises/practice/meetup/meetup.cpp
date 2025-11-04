#include "meetup.h"
#include <boost/date_time/gregorian_calendar.hpp>

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::days;
using boost::gregorian::gregorian_calendar;

scheduler::scheduler(boost::gregorian::greg_month month, int year)
    : month_(month), year_(year) {}

date scheduler::nth_weekday(int n, boost::date_time::weekdays wd) const {
    const date first_of_month{year_, month_, 1};
    const int first_dow = first_of_month.day_of_week().as_number(); // 0=Sun..6=Sat
    const int target = static_cast<int>(wd);                        // 0=Sun..6=Sat
    const int delta = (target - first_dow + 7) % 7;
    return first_of_month + days(delta + 7 * (n - 1));
}

date scheduler::last_weekday(boost::date_time::weekdays wd) const {
    const unsigned short eom = gregorian_calendar::end_of_month_day(year_, month_.as_number());
    const date last_of_month{year_, month_, eom};
    const int last_dow = last_of_month.day_of_week().as_number();
    const int target = static_cast<int>(wd);
    const int back = (last_dow - target + 7) % 7;
    return last_of_month - days(back);
}

date scheduler::teenth_weekday(boost::date_time::weekdays wd) const {
    date d{year_, month_, 13};
    const int target = static_cast<int>(wd);
    for (int i = 0; i < 7; ++i) {
        const date cur = d + days(i);
        if (cur.day_of_week().as_number() == target) {
            return cur;
        }
    }
    return d; // should not happen
}

// teenth
date scheduler::monteenth() const { return teenth_weekday(boost::date_time::Monday); }
date scheduler::tuesteenth() const { return teenth_weekday(boost::date_time::Tuesday); }
date scheduler::wednesteenth() const { return teenth_weekday(boost::date_time::Wednesday); }
date scheduler::thursteenth() const { return teenth_weekday(boost::date_time::Thursday); }
date scheduler::friteenth() const { return teenth_weekday(boost::date_time::Friday); }
date scheduler::saturteenth() const { return teenth_weekday(boost::date_time::Saturday); }
date scheduler::sunteenth() const { return teenth_weekday(boost::date_time::Sunday); }

// first
date scheduler::first_monday() const { return nth_weekday(1, boost::date_time::Monday); }
date scheduler::first_tuesday() const { return nth_weekday(1, boost::date_time::Tuesday); }
date scheduler::first_wednesday() const { return nth_weekday(1, boost::date_time::Wednesday); }
date scheduler::first_thursday() const { return nth_weekday(1, boost::date_time::Thursday); }
date scheduler::first_friday() const { return nth_weekday(1, boost::date_time::Friday); }
date scheduler::first_saturday() const { return nth_weekday(1, boost::date_time::Saturday); }
date scheduler::first_sunday() const { return nth_weekday(1, boost::date_time::Sunday); }

// second
date scheduler::second_monday() const { return nth_weekday(2, boost::date_time::Monday); }
date scheduler::second_tuesday() const { return nth_weekday(2, boost::date_time::Tuesday); }
date scheduler::second_wednesday() const { return nth_weekday(2, boost::date_time::Wednesday); }
date scheduler::second_thursday() const { return nth_weekday(2, boost::date_time::Thursday); }
date scheduler::second_friday() const { return nth_weekday(2, boost::date_time::Friday); }
date scheduler::second_saturday() const { return nth_weekday(2, boost::date_time::Saturday); }
date scheduler::second_sunday() const { return nth_weekday(2, boost::date_time::Sunday); }

// third
date scheduler::third_monday() const { return nth_weekday(3, boost::date_time::Monday); }
date scheduler::third_tuesday() const { return nth_weekday(3, boost::date_time::Tuesday); }
date scheduler::third_wednesday() const { return nth_weekday(3, boost::date_time::Wednesday); }
date scheduler::third_thursday() const { return nth_weekday(3, boost::date_time::Thursday); }
date scheduler::third_friday() const { return nth_weekday(3, boost::date_time::Friday); }
date scheduler::third_saturday() const { return nth_weekday(3, boost::date_time::Saturday); }
date scheduler::third_sunday() const { return nth_weekday(3, boost::date_time::Sunday); }

// fourth
date scheduler::fourth_monday() const { return nth_weekday(4, boost::date_time::Monday); }
date scheduler::fourth_tuesday() const { return nth_weekday(4, boost::date_time::Tuesday); }
date scheduler::fourth_wednesday() const { return nth_weekday(4, boost::date_time::Wednesday); }
date scheduler::fourth_thursday() const { return nth_weekday(4, boost::date_time::Thursday); }
date scheduler::fourth_friday() const { return nth_weekday(4, boost::date_time::Friday); }
date scheduler::fourth_saturday() const { return nth_weekday(4, boost::date_time::Saturday); }
date scheduler::fourth_sunday() const { return nth_weekday(4, boost::date_time::Sunday); }

// last
date scheduler::last_monday() const { return last_weekday(boost::date_time::Monday); }
date scheduler::last_tuesday() const { return last_weekday(boost::date_time::Tuesday); }
date scheduler::last_wednesday() const { return last_weekday(boost::date_time::Wednesday); }
date scheduler::last_thursday() const { return last_weekday(boost::date_time::Thursday); }
date scheduler::last_friday() const { return last_weekday(boost::date_time::Friday); }
date scheduler::last_saturday() const { return last_weekday(boost::date_time::Saturday); }
date scheduler::last_sunday() const { return last_weekday(boost::date_time::Sunday); }

}  // namespace meetup
