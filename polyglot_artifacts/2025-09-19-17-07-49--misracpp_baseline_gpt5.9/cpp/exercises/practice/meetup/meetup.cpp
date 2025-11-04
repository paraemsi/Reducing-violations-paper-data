#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::months_of_year;
using boost::gregorian::gregorian_calendar;

namespace {
constexpr int SUN = 0;
constexpr int MON = 1;
constexpr int TUE = 2;
constexpr int WED = 3;
constexpr int THU = 4;
constexpr int FRI = 5;
constexpr int SAT = 6;

int end_of_month_day(int year, int month_num) {
    return gregorian_calendar::end_of_month_day(year, static_cast<unsigned short>(month_num));
}

date nth_weekday_in_month(int year, months_of_year month, int weekday, int nth) {
    int month_num = static_cast<int>(month); // 1..12
    date first{year, month_num, 1};
    int wd1 = first.day_of_week().as_number(); // 0=Sun..6=Sat
    int delta = (weekday - wd1 + 7) % 7;
    int day = 1 + delta + 7 * (nth - 1);
    return date{year, month_num, day};
}

date last_weekday_in_month(int year, months_of_year month, int weekday) {
    int month_num = static_cast<int>(month);
    int last_dom = end_of_month_day(year, month_num);
    date last{year, month_num, last_dom};
    int wd_last = last.day_of_week().as_number();
    int delta = (wd_last - weekday + 7) % 7;
    int day = last_dom - delta;
    return date{year, month_num, day};
}

date teenth_weekday_in_month(int year, months_of_year month, int weekday) {
    int month_num = static_cast<int>(month);
    for (int d = 13; d <= 19; ++d) {
        date candidate{year, month_num, d};
        if (candidate.day_of_week().as_number() == weekday) {
            return candidate;
        }
    }
    // Should never reach here for valid input
    return date{year, month_num, 13};
}
} // namespace

scheduler::scheduler(months_of_year month, int year)
    : month_{month}, year_{year} {}

// Teenth
date scheduler::monteenth() const { return teenth_weekday_in_month(year_, month_, MON); }
date scheduler::tuesteenth() const { return teenth_weekday_in_month(year_, month_, TUE); }
date scheduler::wednesteenth() const { return teenth_weekday_in_month(year_, month_, WED); }
date scheduler::thursteenth() const { return teenth_weekday_in_month(year_, month_, THU); }
date scheduler::friteenth() const { return teenth_weekday_in_month(year_, month_, FRI); }
date scheduler::saturteenth() const { return teenth_weekday_in_month(year_, month_, SAT); }
date scheduler::sunteenth() const { return teenth_weekday_in_month(year_, month_, SUN); }

// First
date scheduler::first_monday() const { return nth_weekday_in_month(year_, month_, MON, 1); }
date scheduler::first_tuesday() const { return nth_weekday_in_month(year_, month_, TUE, 1); }
date scheduler::first_wednesday() const { return nth_weekday_in_month(year_, month_, WED, 1); }
date scheduler::first_thursday() const { return nth_weekday_in_month(year_, month_, THU, 1); }
date scheduler::first_friday() const { return nth_weekday_in_month(year_, month_, FRI, 1); }
date scheduler::first_saturday() const { return nth_weekday_in_month(year_, month_, SAT, 1); }
date scheduler::first_sunday() const { return nth_weekday_in_month(year_, month_, SUN, 1); }

// Second
date scheduler::second_monday() const { return nth_weekday_in_month(year_, month_, MON, 2); }
date scheduler::second_tuesday() const { return nth_weekday_in_month(year_, month_, TUE, 2); }
date scheduler::second_wednesday() const { return nth_weekday_in_month(year_, month_, WED, 2); }
date scheduler::second_thursday() const { return nth_weekday_in_month(year_, month_, THU, 2); }
date scheduler::second_friday() const { return nth_weekday_in_month(year_, month_, FRI, 2); }
date scheduler::second_saturday() const { return nth_weekday_in_month(year_, month_, SAT, 2); }
date scheduler::second_sunday() const { return nth_weekday_in_month(year_, month_, SUN, 2); }

// Third
date scheduler::third_monday() const { return nth_weekday_in_month(year_, month_, MON, 3); }
date scheduler::third_tuesday() const { return nth_weekday_in_month(year_, month_, TUE, 3); }
date scheduler::third_wednesday() const { return nth_weekday_in_month(year_, month_, WED, 3); }
date scheduler::third_thursday() const { return nth_weekday_in_month(year_, month_, THU, 3); }
date scheduler::third_friday() const { return nth_weekday_in_month(year_, month_, FRI, 3); }
date scheduler::third_saturday() const { return nth_weekday_in_month(year_, month_, SAT, 3); }
date scheduler::third_sunday() const { return nth_weekday_in_month(year_, month_, SUN, 3); }

// Fourth
date scheduler::fourth_monday() const { return nth_weekday_in_month(year_, month_, MON, 4); }
date scheduler::fourth_tuesday() const { return nth_weekday_in_month(year_, month_, TUE, 4); }
date scheduler::fourth_wednesday() const { return nth_weekday_in_month(year_, month_, WED, 4); }
date scheduler::fourth_thursday() const { return nth_weekday_in_month(year_, month_, THU, 4); }
date scheduler::fourth_friday() const { return nth_weekday_in_month(year_, month_, FRI, 4); }
date scheduler::fourth_saturday() const { return nth_weekday_in_month(year_, month_, SAT, 4); }
date scheduler::fourth_sunday() const { return nth_weekday_in_month(year_, month_, SUN, 4); }

// Last
date scheduler::last_monday() const { return last_weekday_in_month(year_, month_, MON); }
date scheduler::last_tuesday() const { return last_weekday_in_month(year_, month_, TUE); }
date scheduler::last_wednesday() const { return last_weekday_in_month(year_, month_, WED); }
date scheduler::last_thursday() const { return last_weekday_in_month(year_, month_, THU); }
date scheduler::last_friday() const { return last_weekday_in_month(year_, month_, FRI); }
date scheduler::last_saturday() const { return last_weekday_in_month(year_, month_, SAT); }
date scheduler::last_sunday() const { return last_weekday_in_month(year_, month_, SUN); }

}  // namespace meetup
