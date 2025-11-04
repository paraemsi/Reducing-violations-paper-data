#include "meetup.h"

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::gregorian_calendar;

scheduler::scheduler(boost::gregorian::months_of_year month, int year)
    : year_{year}, month_{month} {}

// Helpers

date scheduler::nth_weekday(unsigned n, boost::date_time::weekdays wd) const {
    // n is 1..4
    const int y = year_;
    const int m = static_cast<int>(month_);

    const date first_of_month(y, m, 1);
    const int first_wd = first_of_month.day_of_week().as_number(); // 0=Sun..6=Sat
    const int desired = static_cast<int>(wd);

    const int offset = (desired - first_wd + 7) % 7;
    const int day = 1 + offset + static_cast<int>(7 * (n - 1));

    return date(y, m, day);
}

date scheduler::last_weekday(boost::date_time::weekdays wd) const {
    const int y = year_;
    const int m = static_cast<int>(month_);

    const int last_dom = gregorian_calendar::end_of_month_day(y, m);
    const date last_of_month(y, m, last_dom);
    const int last_wd = last_of_month.day_of_week().as_number();
    const int desired = static_cast<int>(wd);

    const int back_offset = (last_wd - desired + 7) % 7;
    const int day = last_dom - back_offset;

    return date(y, m, day);
}

date scheduler::teenth_weekday(boost::date_time::weekdays wd) const {
    const int y = year_;
    const int m = static_cast<int>(month_);

    const date start(y, m, 13); // teenth range starts at 13
    const int start_wd = start.day_of_week().as_number();
    const int desired = static_cast<int>(wd);

    const int forward = (desired - start_wd + 7) % 7;
    const int day = 13 + forward; // guaranteed to be <= 19

    return date(y, m, day);
}

// Teenth

date scheduler::monteenth() const { return teenth_weekday(boost::date_time::Monday); }
date scheduler::tuesteenth() const { return teenth_weekday(boost::date_time::Tuesday); }
date scheduler::wednesteenth() const { return teenth_weekday(boost::date_time::Wednesday); }
date scheduler::thursteenth() const { return teenth_weekday(boost::date_time::Thursday); }
date scheduler::friteenth() const { return teenth_weekday(boost::date_time::Friday); }
date scheduler::saturteenth() const { return teenth_weekday(boost::date_time::Saturday); }
date scheduler::sunteenth() const { return teenth_weekday(boost::date_time::Sunday); }

// First

date scheduler::first_monday() const { return nth_weekday(1u, boost::date_time::Monday); }
date scheduler::first_tuesday() const { return nth_weekday(1u, boost::date_time::Tuesday); }
date scheduler::first_wednesday() const { return nth_weekday(1u, boost::date_time::Wednesday); }
date scheduler::first_thursday() const { return nth_weekday(1u, boost::date_time::Thursday); }
date scheduler::first_friday() const { return nth_weekday(1u, boost::date_time::Friday); }
date scheduler::first_saturday() const { return nth_weekday(1u, boost::date_time::Saturday); }
date scheduler::first_sunday() const { return nth_weekday(1u, boost::date_time::Sunday); }

// Second

date scheduler::second_monday() const { return nth_weekday(2u, boost::date_time::Monday); }
date scheduler::second_tuesday() const { return nth_weekday(2u, boost::date_time::Tuesday); }
date scheduler::second_wednesday() const { return nth_weekday(2u, boost::date_time::Wednesday); }
date scheduler::second_thursday() const { return nth_weekday(2u, boost::date_time::Thursday); }
date scheduler::second_friday() const { return nth_weekday(2u, boost::date_time::Friday); }
date scheduler::second_saturday() const { return nth_weekday(2u, boost::date_time::Saturday); }
date scheduler::second_sunday() const { return nth_weekday(2u, boost::date_time::Sunday); }

// Third

date scheduler::third_monday() const { return nth_weekday(3u, boost::date_time::Monday); }
date scheduler::third_tuesday() const { return nth_weekday(3u, boost::date_time::Tuesday); }
date scheduler::third_wednesday() const { return nth_weekday(3u, boost::date_time::Wednesday); }
date scheduler::third_thursday() const { return nth_weekday(3u, boost::date_time::Thursday); }
date scheduler::third_friday() const { return nth_weekday(3u, boost::date_time::Friday); }
date scheduler::third_saturday() const { return nth_weekday(3u, boost::date_time::Saturday); }
date scheduler::third_sunday() const { return nth_weekday(3u, boost::date_time::Sunday); }

// Fourth

date scheduler::fourth_monday() const { return nth_weekday(4u, boost::date_time::Monday); }
date scheduler::fourth_tuesday() const { return nth_weekday(4u, boost::date_time::Tuesday); }
date scheduler::fourth_wednesday() const { return nth_weekday(4u, boost::date_time::Wednesday); }
date scheduler::fourth_thursday() const { return nth_weekday(4u, boost::date_time::Thursday); }
date scheduler::fourth_friday() const { return nth_weekday(4u, boost::date_time::Friday); }
date scheduler::fourth_saturday() const { return nth_weekday(4u, boost::date_time::Saturday); }
date scheduler::fourth_sunday() const { return nth_weekday(4u, boost::date_time::Sunday); }

// Last

date scheduler::last_monday() const { return last_weekday(boost::date_time::Monday); }
date scheduler::last_tuesday() const { return last_weekday(boost::date_time::Tuesday); }
date scheduler::last_wednesday() const { return last_weekday(boost::date_time::Wednesday); }
date scheduler::last_thursday() const { return last_weekday(boost::date_time::Thursday); }
date scheduler::last_friday() const { return last_weekday(boost::date_time::Friday); }
date scheduler::last_saturday() const { return last_weekday(boost::date_time::Saturday); }
date scheduler::last_sunday() const { return last_weekday(boost::date_time::Sunday); }

}  // namespace meetup
