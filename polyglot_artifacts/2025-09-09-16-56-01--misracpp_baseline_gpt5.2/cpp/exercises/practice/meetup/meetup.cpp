#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::months_of_year;
using boost::date_time::weekdays;

static int dow_num(weekdays wd) { return static_cast<int>(wd); }

static date first_of_month(int year, months_of_year month) {
    return date(year, static_cast<unsigned short>(month), 1);
}

static unsigned short end_of_month_day(int year, months_of_year month) {
    return boost::gregorian::gregorian_calendar::end_of_month_day(year, static_cast<unsigned short>(month));
}

static date nth_weekday_of_month(int year, months_of_year month, weekdays wd, int n) {
    date first = first_of_month(year, month);
    int first_dow = first.day_of_week().as_number(); // 0=Sun .. 6=Sat
    int desired = dow_num(wd);
    int offset = (desired - first_dow + 7) % 7;
    date d = first + boost::gregorian::days(offset + 7*(n-1));
    return d;
}

static date last_weekday_of_month(int year, months_of_year month, weekdays wd) {
    unsigned short last_dom = end_of_month_day(year, month);
    date lastd(year, static_cast<unsigned short>(month), last_dom);
    int li = lastd.day_of_week().as_number();
    int desired = dow_num(wd);
    int back = (li - desired + 7) % 7;
    return lastd - boost::gregorian::days(back);
}

static date teenth_weekday_of_month(int year, months_of_year month, weekdays wd) {
    for (int d = 13; d <= 19; ++d) {
        date curr(year, static_cast<unsigned short>(month), static_cast<unsigned short>(d));
        if (curr.day_of_week().as_number() == dow_num(wd)) {
            return curr;
        }
    }
    // Should never happen
    return date(boost::date_time::not_a_date_time);
}

scheduler::scheduler(months_of_year month, int year)
    : year_(year), month_(month) {}

date scheduler::monteenth() const { return teenth_weekday_of_month(year_, month_, weekdays::Monday); }
date scheduler::tuesteenth() const { return teenth_weekday_of_month(year_, month_, weekdays::Tuesday); }
date scheduler::wednesteenth() const { return teenth_weekday_of_month(year_, month_, weekdays::Wednesday); }
date scheduler::thursteenth() const { return teenth_weekday_of_month(year_, month_, weekdays::Thursday); }
date scheduler::friteenth() const { return teenth_weekday_of_month(year_, month_, weekdays::Friday); }
date scheduler::saturteenth() const { return teenth_weekday_of_month(year_, month_, weekdays::Saturday); }
date scheduler::sunteenth() const { return teenth_weekday_of_month(year_, month_, weekdays::Sunday); }

date scheduler::first_monday() const { return nth_weekday_of_month(year_, month_, weekdays::Monday, 1); }
date scheduler::first_tuesday() const { return nth_weekday_of_month(year_, month_, weekdays::Tuesday, 1); }
date scheduler::first_wednesday() const { return nth_weekday_of_month(year_, month_, weekdays::Wednesday, 1); }
date scheduler::first_thursday() const { return nth_weekday_of_month(year_, month_, weekdays::Thursday, 1); }
date scheduler::first_friday() const { return nth_weekday_of_month(year_, month_, weekdays::Friday, 1); }
date scheduler::first_saturday() const { return nth_weekday_of_month(year_, month_, weekdays::Saturday, 1); }
date scheduler::first_sunday() const { return nth_weekday_of_month(year_, month_, weekdays::Sunday, 1); }

date scheduler::second_monday() const { return nth_weekday_of_month(year_, month_, weekdays::Monday, 2); }
date scheduler::second_tuesday() const { return nth_weekday_of_month(year_, month_, weekdays::Tuesday, 2); }
date scheduler::second_wednesday() const { return nth_weekday_of_month(year_, month_, weekdays::Wednesday, 2); }
date scheduler::second_thursday() const { return nth_weekday_of_month(year_, month_, weekdays::Thursday, 2); }
date scheduler::second_friday() const { return nth_weekday_of_month(year_, month_, weekdays::Friday, 2); }
date scheduler::second_saturday() const { return nth_weekday_of_month(year_, month_, weekdays::Saturday, 2); }
date scheduler::second_sunday() const { return nth_weekday_of_month(year_, month_, weekdays::Sunday, 2); }

date scheduler::third_monday() const { return nth_weekday_of_month(year_, month_, weekdays::Monday, 3); }
date scheduler::third_tuesday() const { return nth_weekday_of_month(year_, month_, weekdays::Tuesday, 3); }
date scheduler::third_wednesday() const { return nth_weekday_of_month(year_, month_, weekdays::Wednesday, 3); }
date scheduler::third_thursday() const { return nth_weekday_of_month(year_, month_, weekdays::Thursday, 3); }
date scheduler::third_friday() const { return nth_weekday_of_month(year_, month_, weekdays::Friday, 3); }
date scheduler::third_saturday() const { return nth_weekday_of_month(year_, month_, weekdays::Saturday, 3); }
date scheduler::third_sunday() const { return nth_weekday_of_month(year_, month_, weekdays::Sunday, 3); }

date scheduler::fourth_monday() const { return nth_weekday_of_month(year_, month_, weekdays::Monday, 4); }
date scheduler::fourth_tuesday() const { return nth_weekday_of_month(year_, month_, weekdays::Tuesday, 4); }
date scheduler::fourth_wednesday() const { return nth_weekday_of_month(year_, month_, weekdays::Wednesday, 4); }
date scheduler::fourth_thursday() const { return nth_weekday_of_month(year_, month_, weekdays::Thursday, 4); }
date scheduler::fourth_friday() const { return nth_weekday_of_month(year_, month_, weekdays::Friday, 4); }
date scheduler::fourth_saturday() const { return nth_weekday_of_month(year_, month_, weekdays::Saturday, 4); }
date scheduler::fourth_sunday() const { return nth_weekday_of_month(year_, month_, weekdays::Sunday, 4); }

date scheduler::last_monday() const { return last_weekday_of_month(year_, month_, weekdays::Monday); }
date scheduler::last_tuesday() const { return last_weekday_of_month(year_, month_, weekdays::Tuesday); }
date scheduler::last_wednesday() const { return last_weekday_of_month(year_, month_, weekdays::Wednesday); }
date scheduler::last_thursday() const { return last_weekday_of_month(year_, month_, weekdays::Thursday); }
date scheduler::last_friday() const { return last_weekday_of_month(year_, month_, weekdays::Friday); }
date scheduler::last_saturday() const { return last_weekday_of_month(year_, month_, weekdays::Saturday); }
date scheduler::last_sunday() const { return last_weekday_of_month(year_, month_, weekdays::Sunday); }

}  // namespace meetup
