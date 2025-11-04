#include "meetup.h"

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::days;
using boost::gregorian::months;

scheduler::scheduler(int year, int month) : year_{year}, month_{month} {}

date scheduler::nth_weekday(int nth, int weekday) const {
    // weekday: 0=Sun..6=Sat
    date first_of_month(year_, month_, 1);
    int first_dow = first_of_month.day_of_week().as_number(); // 0=Sun..6=Sat
    int offset = (weekday - first_dow + 7) % 7;
    int day = 1 + offset + 7 * (nth - 1);
    return date(year_, month_, day);
}

date scheduler::last_weekday(int weekday) const {
    date first_of_month(year_, month_, 1);
    date first_of_next_month = first_of_month + months(1);
    date last_of_month = first_of_next_month - days(1);
    int last_dow = last_of_month.day_of_week().as_number(); // 0=Sun..6=Sat
    int back = (last_dow - weekday + 7) % 7;
    int day = static_cast<int>(last_of_month.day()) - back;
    return date(year_, month_, day);
}

date scheduler::teenth_weekday(int weekday) const {
    for (int d = 13; d <= 19; ++d) {
        date cur(year_, month_, d);
        if (cur.day_of_week().as_number() == weekday) {
            return cur;
        }
    }
    // Should never reach here for valid calendar months
    return date(year_, month_, 13);
}

// teenth
date scheduler::monteenth() const { return teenth_weekday(1); }
date scheduler::tuesteenth() const { return teenth_weekday(2); }
date scheduler::wednesteenth() const { return teenth_weekday(3); }
date scheduler::thursteenth() const { return teenth_weekday(4); }
date scheduler::friteenth() const { return teenth_weekday(5); }
date scheduler::saturteenth() const { return teenth_weekday(6); }
date scheduler::sunteenth() const { return teenth_weekday(0); }

// first
date scheduler::first_monday() const { return nth_weekday(1, 1); }
date scheduler::first_tuesday() const { return nth_weekday(1, 2); }
date scheduler::first_wednesday() const { return nth_weekday(1, 3); }
date scheduler::first_thursday() const { return nth_weekday(1, 4); }
date scheduler::first_friday() const { return nth_weekday(1, 5); }
date scheduler::first_saturday() const { return nth_weekday(1, 6); }
date scheduler::first_sunday() const { return nth_weekday(1, 0); }

// second
date scheduler::second_monday() const { return nth_weekday(2, 1); }
date scheduler::second_tuesday() const { return nth_weekday(2, 2); }
date scheduler::second_wednesday() const { return nth_weekday(2, 3); }
date scheduler::second_thursday() const { return nth_weekday(2, 4); }
date scheduler::second_friday() const { return nth_weekday(2, 5); }
date scheduler::second_saturday() const { return nth_weekday(2, 6); }
date scheduler::second_sunday() const { return nth_weekday(2, 0); }

// third
date scheduler::third_monday() const { return nth_weekday(3, 1); }
date scheduler::third_tuesday() const { return nth_weekday(3, 2); }
date scheduler::third_wednesday() const { return nth_weekday(3, 3); }
date scheduler::third_thursday() const { return nth_weekday(3, 4); }
date scheduler::third_friday() const { return nth_weekday(3, 5); }
date scheduler::third_saturday() const { return nth_weekday(3, 6); }
date scheduler::third_sunday() const { return nth_weekday(3, 0); }

// fourth
date scheduler::fourth_monday() const { return nth_weekday(4, 1); }
date scheduler::fourth_tuesday() const { return nth_weekday(4, 2); }
date scheduler::fourth_wednesday() const { return nth_weekday(4, 3); }
date scheduler::fourth_thursday() const { return nth_weekday(4, 4); }
date scheduler::fourth_friday() const { return nth_weekday(4, 5); }
date scheduler::fourth_saturday() const { return nth_weekday(4, 6); }
date scheduler::fourth_sunday() const { return nth_weekday(4, 0); }

// last
date scheduler::last_monday() const { return last_weekday(1); }
date scheduler::last_tuesday() const { return last_weekday(2); }
date scheduler::last_wednesday() const { return last_weekday(3); }
date scheduler::last_thursday() const { return last_weekday(4); }
date scheduler::last_friday() const { return last_weekday(5); }
date scheduler::last_saturday() const { return last_weekday(6); }
date scheduler::last_sunday() const { return last_weekday(0); }

}  // namespace meetup
