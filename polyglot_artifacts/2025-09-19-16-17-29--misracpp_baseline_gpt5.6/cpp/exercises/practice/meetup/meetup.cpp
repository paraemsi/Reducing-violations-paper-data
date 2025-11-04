#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::gregorian_calendar;
using boost::gregorian::days;
using boost::date_time::months_of_year;
using boost::date_time::weekdays;
using boost::gregorian::greg_weekday;

scheduler::scheduler(months_of_year month, int year)
    : year_(year), month_(month) {}

date scheduler::teenth(weekdays wd) const {
    for (int day = 13; day <= 19; ++day) {
        date d(year_, static_cast<unsigned short>(month_), day);
        if (d.day_of_week() == greg_weekday(wd)) {
            return d;
        }
    }
    throw std::logic_error("No teenth day found");
}

date scheduler::nth_weekday(weekdays wd, int n) const {
    date d(year_, static_cast<unsigned short>(month_), 1);
    while (d.day_of_week() != greg_weekday(wd)) {
        d += days(1);
    }
    d += days(7 * (n - 1));
    return d;
}

date scheduler::last_weekday(weekdays wd) const {
    int last_dom = gregorian_calendar::end_of_month_day(
        year_, static_cast<unsigned short>(month_));
    date d(year_, static_cast<unsigned short>(month_), last_dom);
    while (d.day_of_week() != greg_weekday(wd)) {
        d -= days(1);
    }
    return d;
}

// teenth
date scheduler::monteenth() const { return teenth(boost::date_time::Monday); }
date scheduler::tuesteenth() const { return teenth(boost::date_time::Tuesday); }
date scheduler::wednesteenth() const { return teenth(boost::date_time::Wednesday); }
date scheduler::thursteenth() const { return teenth(boost::date_time::Thursday); }
date scheduler::friteenth() const { return teenth(boost::date_time::Friday); }
date scheduler::saturteenth() const { return teenth(boost::date_time::Saturday); }
date scheduler::sunteenth() const { return teenth(boost::date_time::Sunday); }

// first
date scheduler::first_monday() const { return nth_weekday(boost::date_time::Monday, 1); }
date scheduler::first_tuesday() const { return nth_weekday(boost::date_time::Tuesday, 1); }
date scheduler::first_wednesday() const { return nth_weekday(boost::date_time::Wednesday, 1); }
date scheduler::first_thursday() const { return nth_weekday(boost::date_time::Thursday, 1); }
date scheduler::first_friday() const { return nth_weekday(boost::date_time::Friday, 1); }
date scheduler::first_saturday() const { return nth_weekday(boost::date_time::Saturday, 1); }
date scheduler::first_sunday() const { return nth_weekday(boost::date_time::Sunday, 1); }

// second
date scheduler::second_monday() const { return nth_weekday(boost::date_time::Monday, 2); }
date scheduler::second_tuesday() const { return nth_weekday(boost::date_time::Tuesday, 2); }
date scheduler::second_wednesday() const { return nth_weekday(boost::date_time::Wednesday, 2); }
date scheduler::second_thursday() const { return nth_weekday(boost::date_time::Thursday, 2); }
date scheduler::second_friday() const { return nth_weekday(boost::date_time::Friday, 2); }
date scheduler::second_saturday() const { return nth_weekday(boost::date_time::Saturday, 2); }
date scheduler::second_sunday() const { return nth_weekday(boost::date_time::Sunday, 2); }

// third
date scheduler::third_monday() const { return nth_weekday(boost::date_time::Monday, 3); }
date scheduler::third_tuesday() const { return nth_weekday(boost::date_time::Tuesday, 3); }
date scheduler::third_wednesday() const { return nth_weekday(boost::date_time::Wednesday, 3); }
date scheduler::third_thursday() const { return nth_weekday(boost::date_time::Thursday, 3); }
date scheduler::third_friday() const { return nth_weekday(boost::date_time::Friday, 3); }
date scheduler::third_saturday() const { return nth_weekday(boost::date_time::Saturday, 3); }
date scheduler::third_sunday() const { return nth_weekday(boost::date_time::Sunday, 3); }

// fourth
date scheduler::fourth_monday() const { return nth_weekday(boost::date_time::Monday, 4); }
date scheduler::fourth_tuesday() const { return nth_weekday(boost::date_time::Tuesday, 4); }
date scheduler::fourth_wednesday() const { return nth_weekday(boost::date_time::Wednesday, 4); }
date scheduler::fourth_thursday() const { return nth_weekday(boost::date_time::Thursday, 4); }
date scheduler::fourth_friday() const { return nth_weekday(boost::date_time::Friday, 4); }
date scheduler::fourth_saturday() const { return nth_weekday(boost::date_time::Saturday, 4); }
date scheduler::fourth_sunday() const { return nth_weekday(boost::date_time::Sunday, 4); }

// last
date scheduler::last_monday() const { return last_weekday(boost::date_time::Monday); }
date scheduler::last_tuesday() const { return last_weekday(boost::date_time::Tuesday); }
date scheduler::last_wednesday() const { return last_weekday(boost::date_time::Wednesday); }
date scheduler::last_thursday() const { return last_weekday(boost::date_time::Thursday); }
date scheduler::last_friday() const { return last_weekday(boost::date_time::Friday); }
date scheduler::last_saturday() const { return last_weekday(boost::date_time::Saturday); }
date scheduler::last_sunday() const { return last_weekday(boost::date_time::Sunday); }

}  // namespace meetup
