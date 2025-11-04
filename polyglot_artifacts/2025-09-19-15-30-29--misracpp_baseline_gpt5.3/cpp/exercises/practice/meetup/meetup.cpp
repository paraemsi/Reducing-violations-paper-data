#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {

using boost::gregorian::date;
using boost::gregorian::months_of_year;

// 0=Sunday ... 6=Saturday, same as Boost's greg_weekday::as_number()
inline int weekday_number(boost::date_time::weekdays wd) {
    return static_cast<int>(wd);
}

inline date nth_weekday_of_month(int year, months_of_year month, boost::date_time::weekdays wd, int n) {
    date first{year, month, 1};
    const int first_wd = first.day_of_week().as_number();
    const int target = weekday_number(wd);
    const int delta = (target - first_wd + 7) % 7;
    const int dom = 1 + delta + 7 * (n - 1);
    return date{year, month, dom};
}

inline date last_weekday_of_month(int year, months_of_year month, boost::date_time::weekdays wd) {
    const int target = weekday_number(wd);
    const int last_dom = boost::gregorian::gregorian_calendar::end_of_month_day(year, static_cast<unsigned short>(month));
    date last{year, month, last_dom};
    const int last_wd = last.day_of_week().as_number();
    const int back = (last_wd - target + 7) % 7;
    return date{year, month, last_dom - back};
}

inline date teenth_weekday_of_month(int year, months_of_year month, boost::date_time::weekdays wd) {
    date first{year, month, 1};
    const int first_wd = first.day_of_week().as_number();
    const int target = weekday_number(wd);
    int dom = 1 + (target - first_wd + 7) % 7;
    while (dom < 13) dom += 7;
    // dom will be between 13 and 19 inclusive
    return date{year, month, dom};
}

} // anonymous namespace

scheduler::scheduler(boost::gregorian::months_of_year month, int year)
    : month_(month), year_(year) {}

// teenth
boost::gregorian::date scheduler::monteenth() const { return teenth_weekday_of_month(year_, month_, boost::date_time::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return teenth_weekday_of_month(year_, month_, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return teenth_weekday_of_month(year_, month_, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return teenth_weekday_of_month(year_, month_, boost::date_time::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return teenth_weekday_of_month(year_, month_, boost::date_time::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return teenth_weekday_of_month(year_, month_, boost::date_time::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return teenth_weekday_of_month(year_, month_, boost::date_time::Sunday); }

// first
boost::gregorian::date scheduler::first_monday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Monday, 1); }
boost::gregorian::date scheduler::first_tuesday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Tuesday, 1); }
boost::gregorian::date scheduler::first_wednesday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Wednesday, 1); }
boost::gregorian::date scheduler::first_thursday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Thursday, 1); }
boost::gregorian::date scheduler::first_friday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Friday, 1); }
boost::gregorian::date scheduler::first_saturday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Saturday, 1); }
boost::gregorian::date scheduler::first_sunday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Sunday, 1); }

// second
boost::gregorian::date scheduler::second_monday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Monday, 2); }
boost::gregorian::date scheduler::second_tuesday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Tuesday, 2); }
boost::gregorian::date scheduler::second_wednesday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Wednesday, 2); }
boost::gregorian::date scheduler::second_thursday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Thursday, 2); }
boost::gregorian::date scheduler::second_friday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Friday, 2); }
boost::gregorian::date scheduler::second_saturday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Saturday, 2); }
boost::gregorian::date scheduler::second_sunday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Sunday, 2); }

// third
boost::gregorian::date scheduler::third_monday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Monday, 3); }
boost::gregorian::date scheduler::third_tuesday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Tuesday, 3); }
boost::gregorian::date scheduler::third_wednesday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Wednesday, 3); }
boost::gregorian::date scheduler::third_thursday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Thursday, 3); }
boost::gregorian::date scheduler::third_friday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Friday, 3); }
boost::gregorian::date scheduler::third_saturday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Saturday, 3); }
boost::gregorian::date scheduler::third_sunday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Sunday, 3); }

// fourth
boost::gregorian::date scheduler::fourth_monday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Monday, 4); }
boost::gregorian::date scheduler::fourth_tuesday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Tuesday, 4); }
boost::gregorian::date scheduler::fourth_wednesday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Wednesday, 4); }
boost::gregorian::date scheduler::fourth_thursday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Thursday, 4); }
boost::gregorian::date scheduler::fourth_friday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Friday, 4); }
boost::gregorian::date scheduler::fourth_saturday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Saturday, 4); }
boost::gregorian::date scheduler::fourth_sunday() const { return nth_weekday_of_month(year_, month_, boost::date_time::Sunday, 4); }

// last
boost::gregorian::date scheduler::last_monday() const { return last_weekday_of_month(year_, month_, boost::date_time::Monday); }
boost::gregorian::date scheduler::last_tuesday() const { return last_weekday_of_month(year_, month_, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return last_weekday_of_month(year_, month_, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::last_thursday() const { return last_weekday_of_month(year_, month_, boost::date_time::Thursday); }
boost::gregorian::date scheduler::last_friday() const { return last_weekday_of_month(year_, month_, boost::date_time::Friday); }
boost::gregorian::date scheduler::last_saturday() const { return last_weekday_of_month(year_, month_, boost::date_time::Saturday); }
boost::gregorian::date scheduler::last_sunday() const { return last_weekday_of_month(year_, month_, boost::date_time::Sunday); }

}  // namespace meetup
