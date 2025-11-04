#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using boost::gregorian::date;

scheduler::scheduler(int month, int year)
    : month_{month}, year_{year} {}

date scheduler::meetup(boost::date_time::weekdays wd, which w) const {
    const date first_day(year_, month_, 1);

    if (w == which::teenth) {
        for (int d = 13; d <= 19; ++d) {
            const date dt(year_, month_, d);
            if (dt.day_of_week().as_number() == static_cast<int>(wd)) {
                return dt;
            }
        }
        // Should never happen as each weekday occurs exactly once in the teenth range
        return first_day;
    }

    if (w == which::last) {
        const date last_day = first_day.end_of_month();
        const int back = (last_day.day_of_week().as_number() - static_cast<int>(wd) + 7) % 7;
        return last_day - boost::gregorian::days(back);
    }

    // first..fourth
    const int target_index = static_cast<int>(wd);
    const int first_wd = first_day.day_of_week().as_number();
    const int offset = (target_index - first_wd + 7) % 7;
    const int n = static_cast<int>(w); // 1..4
    const int day = 1 + offset + 7 * (n - 1);
    return date(year_, month_, day);
}

// "teenth" occurrences
date scheduler::monteenth() const { return meetup(boost::date_time::Monday, which::teenth); }
date scheduler::tuesteenth() const { return meetup(boost::date_time::Tuesday, which::teenth); }
date scheduler::wednesteenth() const { return meetup(boost::date_time::Wednesday, which::teenth); }
date scheduler::thursteenth() const { return meetup(boost::date_time::Thursday, which::teenth); }
date scheduler::friteenth() const { return meetup(boost::date_time::Friday, which::teenth); }
date scheduler::saturteenth() const { return meetup(boost::date_time::Saturday, which::teenth); }
date scheduler::sunteenth() const { return meetup(boost::date_time::Sunday, which::teenth); }

// first occurrences
date scheduler::first_monday() const { return meetup(boost::date_time::Monday, which::first); }
date scheduler::first_tuesday() const { return meetup(boost::date_time::Tuesday, which::first); }
date scheduler::first_wednesday() const { return meetup(boost::date_time::Wednesday, which::first); }
date scheduler::first_thursday() const { return meetup(boost::date_time::Thursday, which::first); }
date scheduler::first_friday() const { return meetup(boost::date_time::Friday, which::first); }
date scheduler::first_saturday() const { return meetup(boost::date_time::Saturday, which::first); }
date scheduler::first_sunday() const { return meetup(boost::date_time::Sunday, which::first); }

// second occurrences
date scheduler::second_monday() const { return meetup(boost::date_time::Monday, which::second); }
date scheduler::second_tuesday() const { return meetup(boost::date_time::Tuesday, which::second); }
date scheduler::second_wednesday() const { return meetup(boost::date_time::Wednesday, which::second); }
date scheduler::second_thursday() const { return meetup(boost::date_time::Thursday, which::second); }
date scheduler::second_friday() const { return meetup(boost::date_time::Friday, which::second); }
date scheduler::second_saturday() const { return meetup(boost::date_time::Saturday, which::second); }
date scheduler::second_sunday() const { return meetup(boost::date_time::Sunday, which::second); }

// third occurrences
date scheduler::third_monday() const { return meetup(boost::date_time::Monday, which::third); }
date scheduler::third_tuesday() const { return meetup(boost::date_time::Tuesday, which::third); }
date scheduler::third_wednesday() const { return meetup(boost::date_time::Wednesday, which::third); }
date scheduler::third_thursday() const { return meetup(boost::date_time::Thursday, which::third); }
date scheduler::third_friday() const { return meetup(boost::date_time::Friday, which::third); }
date scheduler::third_saturday() const { return meetup(boost::date_time::Saturday, which::third); }
date scheduler::third_sunday() const { return meetup(boost::date_time::Sunday, which::third); }

// fourth occurrences
date scheduler::fourth_monday() const { return meetup(boost::date_time::Monday, which::fourth); }
date scheduler::fourth_tuesday() const { return meetup(boost::date_time::Tuesday, which::fourth); }
date scheduler::fourth_wednesday() const { return meetup(boost::date_time::Wednesday, which::fourth); }
date scheduler::fourth_thursday() const { return meetup(boost::date_time::Thursday, which::fourth); }
date scheduler::fourth_friday() const { return meetup(boost::date_time::Friday, which::fourth); }
date scheduler::fourth_saturday() const { return meetup(boost::date_time::Saturday, which::fourth); }
date scheduler::fourth_sunday() const { return meetup(boost::date_time::Sunday, which::fourth); }

// last occurrences
date scheduler::last_monday() const { return meetup(boost::date_time::Monday, which::last); }
date scheduler::last_tuesday() const { return meetup(boost::date_time::Tuesday, which::last); }
date scheduler::last_wednesday() const { return meetup(boost::date_time::Wednesday, which::last); }
date scheduler::last_thursday() const { return meetup(boost::date_time::Thursday, which::last); }
date scheduler::last_friday() const { return meetup(boost::date_time::Friday, which::last); }
date scheduler::last_saturday() const { return meetup(boost::date_time::Saturday, which::last); }
date scheduler::last_sunday() const { return meetup(boost::date_time::Sunday, which::last); }

}  // namespace meetup
