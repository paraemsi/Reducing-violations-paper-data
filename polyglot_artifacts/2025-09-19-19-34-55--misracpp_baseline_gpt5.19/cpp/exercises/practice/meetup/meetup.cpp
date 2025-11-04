#include "meetup.h"
#include <stdexcept>

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::days;
using boost::gregorian::gregorian_calendar;
using boost::gregorian::months_of_year;
using boost::date_time::weekdays;

scheduler::scheduler(months_of_year month, int year)
    : year_(year), month_(static_cast<int>(month)) {}

date scheduler::nth_weekday(int n, weekdays wd) const {
    date first(year_, month_, 1);
    int first_wd = first.day_of_week().as_number(); // 0=Sunday..6=Saturday
    int target = static_cast<int>(wd);
    int diff = (target - first_wd + 7) % 7;
    int day = 1 + diff + 7 * (n - 1);
    return date(year_, month_, day);
}

date scheduler::last_weekday(weekdays wd) const {
    int eom = gregorian_calendar::end_of_month_day(year_, month_);
    date last(year_, month_, eom);
    int last_wd = last.day_of_week().as_number();
    int target = static_cast<int>(wd);
    int back = (last_wd - target + 7) % 7;
    return last - days(back);
}

date scheduler::teenth_weekday(weekdays wd) const {
    for (int d = 13; d <= 19; ++d) {
        date dt(year_, month_, d);
        if (dt.day_of_week().as_number() == static_cast<int>(wd)) {
            return dt;
        }
    }
    throw std::logic_error("No teenth day found for given weekday");
}

// teenth
date scheduler::monteenth() const { return teenth_weekday(weekdays::Monday); }
date scheduler::tuesteenth() const { return teenth_weekday(weekdays::Tuesday); }
date scheduler::wednesteenth() const { return teenth_weekday(weekdays::Wednesday); }
date scheduler::thursteenth() const { return teenth_weekday(weekdays::Thursday); }
date scheduler::friteenth() const { return teenth_weekday(weekdays::Friday); }
date scheduler::saturteenth() const { return teenth_weekday(weekdays::Saturday); }
date scheduler::sunteenth() const { return teenth_weekday(weekdays::Sunday); }

// first
date scheduler::first_monday() const { return nth_weekday(1, weekdays::Monday); }
date scheduler::first_tuesday() const { return nth_weekday(1, weekdays::Tuesday); }
date scheduler::first_wednesday() const { return nth_weekday(1, weekdays::Wednesday); }
date scheduler::first_thursday() const { return nth_weekday(1, weekdays::Thursday); }
date scheduler::first_friday() const { return nth_weekday(1, weekdays::Friday); }
date scheduler::first_saturday() const { return nth_weekday(1, weekdays::Saturday); }
date scheduler::first_sunday() const { return nth_weekday(1, weekdays::Sunday); }

// second
date scheduler::second_monday() const { return nth_weekday(2, weekdays::Monday); }
date scheduler::second_tuesday() const { return nth_weekday(2, weekdays::Tuesday); }
date scheduler::second_wednesday() const { return nth_weekday(2, weekdays::Wednesday); }
date scheduler::second_thursday() const { return nth_weekday(2, weekdays::Thursday); }
date scheduler::second_friday() const { return nth_weekday(2, weekdays::Friday); }
date scheduler::second_saturday() const { return nth_weekday(2, weekdays::Saturday); }
date scheduler::second_sunday() const { return nth_weekday(2, weekdays::Sunday); }

// third
date scheduler::third_monday() const { return nth_weekday(3, weekdays::Monday); }
date scheduler::third_tuesday() const { return nth_weekday(3, weekdays::Tuesday); }
date scheduler::third_wednesday() const { return nth_weekday(3, weekdays::Wednesday); }
date scheduler::third_thursday() const { return nth_weekday(3, weekdays::Thursday); }
date scheduler::third_friday() const { return nth_weekday(3, weekdays::Friday); }
date scheduler::third_saturday() const { return nth_weekday(3, weekdays::Saturday); }
date scheduler::third_sunday() const { return nth_weekday(3, weekdays::Sunday); }

// fourth
date scheduler::fourth_monday() const { return nth_weekday(4, weekdays::Monday); }
date scheduler::fourth_tuesday() const { return nth_weekday(4, weekdays::Tuesday); }
date scheduler::fourth_wednesday() const { return nth_weekday(4, weekdays::Wednesday); }
date scheduler::fourth_thursday() const { return nth_weekday(4, weekdays::Thursday); }
date scheduler::fourth_friday() const { return nth_weekday(4, weekdays::Friday); }
date scheduler::fourth_saturday() const { return nth_weekday(4, weekdays::Saturday); }
date scheduler::fourth_sunday() const { return nth_weekday(4, weekdays::Sunday); }

// last
date scheduler::last_monday() const { return last_weekday(weekdays::Monday); }
date scheduler::last_tuesday() const { return last_weekday(weekdays::Tuesday); }
date scheduler::last_wednesday() const { return last_weekday(weekdays::Wednesday); }
date scheduler::last_thursday() const { return last_weekday(weekdays::Thursday); }
date scheduler::last_friday() const { return last_weekday(weekdays::Friday); }
date scheduler::last_saturday() const { return last_weekday(weekdays::Saturday); }
date scheduler::last_sunday() const { return last_weekday(weekdays::Sunday); }

}  // namespace meetup
