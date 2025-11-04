#include "meetup.h"

namespace meetup {

using boost::gregorian::date;

scheduler::scheduler(boost::gregorian::months_of_year month, int year)
    : year_{year}, month_{month} {}

// Helpers

date scheduler::nth_weekday(int nth, int wd) const {
    // First day of the month
    const int month_num = static_cast<int>(month_);
    date first{year_, month_num, 1};
    int first_wd = first.day_of_week().as_number(); // 0=Sun .. 6=Sat
    int offset = (wd - first_wd + 7) % 7;
    int day = 1 + offset + 7 * (nth - 1);
    return date{year_, month_num, day};
}

date scheduler::last_weekday(int wd) const {
    const int month_num = static_cast<int>(month_);
    int last_dom = boost::gregorian::gregorian_calendar::end_of_month_day(year_, month_num);
    date last{year_, month_num, last_dom};
    int last_wd = last.day_of_week().as_number();
    int offset = (last_wd - wd + 7) % 7;
    int day = last_dom - offset;
    return date{year_, month_num, day};
}

date scheduler::teenth_weekday(int wd) const {
    const int month_num = static_cast<int>(month_);
    // Start on the 13th and move forward to the requested weekday within the teenth range.
    date start{year_, month_num, 13};
    int start_wd = start.day_of_week().as_number();
    int offset = (wd - start_wd + 7) % 7;
    int day = 13 + offset; // guaranteed to be in [13..19]
    return date{year_, month_num, day};
}

// Teenth
date scheduler::monteenth() const { return teenth_weekday(1); }
date scheduler::tuesteenth() const { return teenth_weekday(2); }
date scheduler::wednesteenth() const { return teenth_weekday(3); }
date scheduler::thursteenth() const { return teenth_weekday(4); }
date scheduler::friteenth() const { return teenth_weekday(5); }
date scheduler::saturteenth() const { return teenth_weekday(6); }
date scheduler::sunteenth() const { return teenth_weekday(0); }

// First
date scheduler::first_monday() const { return nth_weekday(1, 1); }
date scheduler::first_tuesday() const { return nth_weekday(1, 2); }
date scheduler::first_wednesday() const { return nth_weekday(1, 3); }
date scheduler::first_thursday() const { return nth_weekday(1, 4); }
date scheduler::first_friday() const { return nth_weekday(1, 5); }
date scheduler::first_saturday() const { return nth_weekday(1, 6); }
date scheduler::first_sunday() const { return nth_weekday(1, 0); }

// Second
date scheduler::second_monday() const { return nth_weekday(2, 1); }
date scheduler::second_tuesday() const { return nth_weekday(2, 2); }
date scheduler::second_wednesday() const { return nth_weekday(2, 3); }
date scheduler::second_thursday() const { return nth_weekday(2, 4); }
date scheduler::second_friday() const { return nth_weekday(2, 5); }
date scheduler::second_saturday() const { return nth_weekday(2, 6); }
date scheduler::second_sunday() const { return nth_weekday(2, 0); }

// Third
date scheduler::third_monday() const { return nth_weekday(3, 1); }
date scheduler::third_tuesday() const { return nth_weekday(3, 2); }
date scheduler::third_wednesday() const { return nth_weekday(3, 3); }
date scheduler::third_thursday() const { return nth_weekday(3, 4); }
date scheduler::third_friday() const { return nth_weekday(3, 5); }
date scheduler::third_saturday() const { return nth_weekday(3, 6); }
date scheduler::third_sunday() const { return nth_weekday(3, 0); }

// Fourth
date scheduler::fourth_monday() const { return nth_weekday(4, 1); }
date scheduler::fourth_tuesday() const { return nth_weekday(4, 2); }
date scheduler::fourth_wednesday() const { return nth_weekday(4, 3); }
date scheduler::fourth_thursday() const { return nth_weekday(4, 4); }
date scheduler::fourth_friday() const { return nth_weekday(4, 5); }
date scheduler::fourth_saturday() const { return nth_weekday(4, 6); }
date scheduler::fourth_sunday() const { return nth_weekday(4, 0); }

// Last
date scheduler::last_monday() const { return last_weekday(1); }
date scheduler::last_tuesday() const { return last_weekday(2); }
date scheduler::last_wednesday() const { return last_weekday(3); }
date scheduler::last_thursday() const { return last_weekday(4); }
date scheduler::last_friday() const { return last_weekday(5); }
date scheduler::last_saturday() const { return last_weekday(6); }
date scheduler::last_sunday() const { return last_weekday(0); }

}  // namespace meetup
