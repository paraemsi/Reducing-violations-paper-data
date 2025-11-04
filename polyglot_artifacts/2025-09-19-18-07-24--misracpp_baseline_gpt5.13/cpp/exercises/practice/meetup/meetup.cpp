#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(int year, int month) : year_{year}, month_{month} {}

int scheduler::days_in_month(int year, int month) {
    // month: 1..12
    static const int mdays_common[13] = {0,
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    if (month != 2) {
        return mdays_common[month];
    }
    // February
    const bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    return leap ? 29 : 28;
}

int scheduler::day_of_week(int year, int month, int day) {
    // Zeller's congruence (Gregorian calendar)
    // Returns 0=Sunday..6=Saturday
    int y = year;
    int m = month;
    if (m < 3) {
        m += 12;
        --y;
    }
    const int K = y % 100;
    const int J = y / 100;
    int h = (day + (13 * (m + 1)) / 5 + K + (K / 4) + (J / 4) + (5 * J)) % 7;
    // h = 0: Saturday, 1: Sunday, 2: Monday, ..., 6: Friday
    int dow = (h + 6) % 7; // 0: Sunday, 1: Monday, ..., 6: Saturday
    return dow;
}

boost::gregorian::date scheduler::from_day(int day) const {
    return boost::gregorian::date(year_, month_, day);
}

boost::gregorian::date scheduler::nth_weekday(int target_wd, int n) const {
    // n in [1..4]
    int first_wd = day_of_week(year_, month_, 1);
    int delta = (target_wd - first_wd + 7) % 7;
    int day = 1 + delta + 7 * (n - 1);
    return from_day(day);
}

boost::gregorian::date scheduler::last_weekday(int target_wd) const {
    int last_day = days_in_month(year_, month_);
    int last_wd = day_of_week(year_, month_, last_day);
    int back = (last_wd - target_wd + 7) % 7;
    int day = last_day - back;
    return from_day(day);
}

boost::gregorian::date scheduler::teenth_weekday(int target_wd) const {
    for (int d = 13; d <= 19; ++d) {
        if (day_of_week(year_, month_, d) == target_wd) {
            return from_day(d);
        }
    }
    // Should never happen because there is always exactly one teenth weekday
    return from_day(13);
}

 // Teenths
boost::gregorian::date scheduler::monteenth() const { return teenth_weekday(1); }
boost::gregorian::date scheduler::tuesteenth() const { return teenth_weekday(2); }
boost::gregorian::date scheduler::wednesteenth() const { return teenth_weekday(3); }
boost::gregorian::date scheduler::thursteenth() const { return teenth_weekday(4); }
boost::gregorian::date scheduler::friteenth() const { return teenth_weekday(5); }
boost::gregorian::date scheduler::saturteenth() const { return teenth_weekday(6); }
boost::gregorian::date scheduler::sunteenth() const { return teenth_weekday(0); }

 // First
boost::gregorian::date scheduler::first_monday() const { return nth_weekday(1, 1); }
boost::gregorian::date scheduler::first_tuesday() const { return nth_weekday(2, 1); }
boost::gregorian::date scheduler::first_wednesday() const { return nth_weekday(3, 1); }
boost::gregorian::date scheduler::first_thursday() const { return nth_weekday(4, 1); }
boost::gregorian::date scheduler::first_friday() const { return nth_weekday(5, 1); }
boost::gregorian::date scheduler::first_saturday() const { return nth_weekday(6, 1); }
boost::gregorian::date scheduler::first_sunday() const { return nth_weekday(0, 1); }

 // Second
boost::gregorian::date scheduler::second_monday() const { return nth_weekday(1, 2); }
boost::gregorian::date scheduler::second_tuesday() const { return nth_weekday(2, 2); }
boost::gregorian::date scheduler::second_wednesday() const { return nth_weekday(3, 2); }
boost::gregorian::date scheduler::second_thursday() const { return nth_weekday(4, 2); }
boost::gregorian::date scheduler::second_friday() const { return nth_weekday(5, 2); }
boost::gregorian::date scheduler::second_saturday() const { return nth_weekday(6, 2); }
boost::gregorian::date scheduler::second_sunday() const { return nth_weekday(0, 2); }

 // Third
boost::gregorian::date scheduler::third_monday() const { return nth_weekday(1, 3); }
boost::gregorian::date scheduler::third_tuesday() const { return nth_weekday(2, 3); }
boost::gregorian::date scheduler::third_wednesday() const { return nth_weekday(3, 3); }
boost::gregorian::date scheduler::third_thursday() const { return nth_weekday(4, 3); }
boost::gregorian::date scheduler::third_friday() const { return nth_weekday(5, 3); }
boost::gregorian::date scheduler::third_saturday() const { return nth_weekday(6, 3); }
boost::gregorian::date scheduler::third_sunday() const { return nth_weekday(0, 3); }

 // Fourth
boost::gregorian::date scheduler::fourth_monday() const { return nth_weekday(1, 4); }
boost::gregorian::date scheduler::fourth_tuesday() const { return nth_weekday(2, 4); }
boost::gregorian::date scheduler::fourth_wednesday() const { return nth_weekday(3, 4); }
boost::gregorian::date scheduler::fourth_thursday() const { return nth_weekday(4, 4); }
boost::gregorian::date scheduler::fourth_friday() const { return nth_weekday(5, 4); }
boost::gregorian::date scheduler::fourth_saturday() const { return nth_weekday(6, 4); }
boost::gregorian::date scheduler::fourth_sunday() const { return nth_weekday(0, 4); }

 // Last
boost::gregorian::date scheduler::last_monday() const { return last_weekday(1); }
boost::gregorian::date scheduler::last_tuesday() const { return last_weekday(2); }
boost::gregorian::date scheduler::last_wednesday() const { return last_weekday(3); }
boost::gregorian::date scheduler::last_thursday() const { return last_weekday(4); }
boost::gregorian::date scheduler::last_friday() const { return last_weekday(5); }
boost::gregorian::date scheduler::last_saturday() const { return last_weekday(6); }
boost::gregorian::date scheduler::last_sunday() const { return last_weekday(0); }

}  // namespace meetup
