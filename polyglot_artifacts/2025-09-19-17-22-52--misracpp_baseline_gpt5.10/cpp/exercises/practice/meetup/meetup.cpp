#include "meetup.h"
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;
using boost::date_time::weekdays;

static date first_weekday_in_month(int year, unsigned month, weekdays wd) {
    date first{year, month, 1};
    greg_weekday gwd{wd};
    int diff = (gwd.as_number() - first.day_of_week().as_number() + 7) % 7;
    return first + days(diff);
}

static date nth_weekday_in_month(int year, unsigned month, weekdays wd, int n) {
    if (n < 1) throw std::invalid_argument("n must be >= 1");
    date first = first_weekday_in_month(year, month, wd);
    date d = first + days(7 * (n - 1));
    if (d.month().as_number() != month) {
        throw std::out_of_range("requested nth weekday is outside the month");
    }
    return d;
}

static date last_weekday_in_month(int year, unsigned month, weekdays wd) {
    unsigned last_dom = gregorian_calendar::end_of_month_day(year, month);
    date last{year, month, last_dom};
    greg_weekday gwd{wd};
    int back = (last.day_of_week().as_number() - gwd.as_number() + 7) % 7;
    return last - days(back);
}

static date teenth_weekday_in_month(int year, unsigned month, weekdays wd) {
    date d{year, month, 13};
    greg_weekday gwd{wd};
    while (d.day_of_week() != gwd) {
        d += days(1);
    }
    return d;
}

// teenth
date scheduler::monteenth() const { return teenth_weekday_in_month(year_, month_, weekdays::Monday); }
date scheduler::tuesteenth() const { return teenth_weekday_in_month(year_, month_, weekdays::Tuesday); }
date scheduler::wednesteenth() const { return teenth_weekday_in_month(year_, month_, weekdays::Wednesday); }
date scheduler::thursteenth() const { return teenth_weekday_in_month(year_, month_, weekdays::Thursday); }
date scheduler::friteenth() const { return teenth_weekday_in_month(year_, month_, weekdays::Friday); }
date scheduler::saturteenth() const { return teenth_weekday_in_month(year_, month_, weekdays::Saturday); }
date scheduler::sunteenth() const { return teenth_weekday_in_month(year_, month_, weekdays::Sunday); }

// first
date scheduler::first_monday() const { return nth_weekday_in_month(year_, month_, weekdays::Monday, 1); }
date scheduler::first_tuesday() const { return nth_weekday_in_month(year_, month_, weekdays::Tuesday, 1); }
date scheduler::first_wednesday() const { return nth_weekday_in_month(year_, month_, weekdays::Wednesday, 1); }
date scheduler::first_thursday() const { return nth_weekday_in_month(year_, month_, weekdays::Thursday, 1); }
date scheduler::first_friday() const { return nth_weekday_in_month(year_, month_, weekdays::Friday, 1); }
date scheduler::first_saturday() const { return nth_weekday_in_month(year_, month_, weekdays::Saturday, 1); }
date scheduler::first_sunday() const { return nth_weekday_in_month(year_, month_, weekdays::Sunday, 1); }

// second
date scheduler::second_monday() const { return nth_weekday_in_month(year_, month_, weekdays::Monday, 2); }
date scheduler::second_tuesday() const { return nth_weekday_in_month(year_, month_, weekdays::Tuesday, 2); }
date scheduler::second_wednesday() const { return nth_weekday_in_month(year_, month_, weekdays::Wednesday, 2); }
date scheduler::second_thursday() const { return nth_weekday_in_month(year_, month_, weekdays::Thursday, 2); }
date scheduler::second_friday() const { return nth_weekday_in_month(year_, month_, weekdays::Friday, 2); }
date scheduler::second_saturday() const { return nth_weekday_in_month(year_, month_, weekdays::Saturday, 2); }
date scheduler::second_sunday() const { return nth_weekday_in_month(year_, month_, weekdays::Sunday, 2); }

// third
date scheduler::third_monday() const { return nth_weekday_in_month(year_, month_, weekdays::Monday, 3); }
date scheduler::third_tuesday() const { return nth_weekday_in_month(year_, month_, weekdays::Tuesday, 3); }
date scheduler::third_wednesday() const { return nth_weekday_in_month(year_, month_, weekdays::Wednesday, 3); }
date scheduler::third_thursday() const { return nth_weekday_in_month(year_, month_, weekdays::Thursday, 3); }
date scheduler::third_friday() const { return nth_weekday_in_month(year_, month_, weekdays::Friday, 3); }
date scheduler::third_saturday() const { return nth_weekday_in_month(year_, month_, weekdays::Saturday, 3); }
date scheduler::third_sunday() const { return nth_weekday_in_month(year_, month_, weekdays::Sunday, 3); }

// fourth
date scheduler::fourth_monday() const { return nth_weekday_in_month(year_, month_, weekdays::Monday, 4); }
date scheduler::fourth_tuesday() const { return nth_weekday_in_month(year_, month_, weekdays::Tuesday, 4); }
date scheduler::fourth_wednesday() const { return nth_weekday_in_month(year_, month_, weekdays::Wednesday, 4); }
date scheduler::fourth_thursday() const { return nth_weekday_in_month(year_, month_, weekdays::Thursday, 4); }
date scheduler::fourth_friday() const { return nth_weekday_in_month(year_, month_, weekdays::Friday, 4); }
date scheduler::fourth_saturday() const { return nth_weekday_in_month(year_, month_, weekdays::Saturday, 4); }
date scheduler::fourth_sunday() const { return nth_weekday_in_month(year_, month_, weekdays::Sunday, 4); }

// last
date scheduler::last_monday() const { return last_weekday_in_month(year_, month_, weekdays::Monday); }
date scheduler::last_tuesday() const { return last_weekday_in_month(year_, month_, weekdays::Tuesday); }
date scheduler::last_wednesday() const { return last_weekday_in_month(year_, month_, weekdays::Wednesday); }
date scheduler::last_thursday() const { return last_weekday_in_month(year_, month_, weekdays::Thursday); }
date scheduler::last_friday() const { return last_weekday_in_month(year_, month_, weekdays::Friday); }
date scheduler::last_saturday() const { return last_weekday_in_month(year_, month_, weekdays::Saturday); }
date scheduler::last_sunday() const { return last_weekday_in_month(year_, month_, weekdays::Sunday); }

}  // namespace meetup
