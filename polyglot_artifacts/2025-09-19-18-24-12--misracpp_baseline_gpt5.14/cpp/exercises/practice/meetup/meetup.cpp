#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {
    inline bool is_leap(int y) {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    inline int days_in_month(int y, int m) {
        static const int days_per_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        int d = days_per_month[m - 1];
        return (m == 2 && is_leap(y)) ? 29 : d;
    }

    // Sakamoto's algorithm: returns 0=Sunday, 1=Monday, ..., 6=Saturday
    inline int dow_sakamoto(int y, int m, int d) {
        static const int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
        if (m < 3) y -= 1;
        return (y + y/4 - y/100 + y/400 + t[m - 1] + d) % 7;
    }

    // Convert to 0=Monday, ..., 6=Sunday to match our weekday enum
    inline int weekday_index_monday0(int y, int m, int d) {
        int w = dow_sakamoto(y, m, d); // 0=Sunday..6=Saturday
        return (w + 6) % 7;            // 0=Monday..6=Sunday
    }
} // namespace

scheduler::scheduler(int year, int month)
    : year_(year), month_(month) {}

date scheduler::meetup_day(weekday wday, schedule which) const {
    const int target = static_cast<int>(wday); // 0=Mon..6=Sun
    const int dim = days_in_month(year_, month_);
    int day = 0;

    switch (which) {
        case teenth: {
            for (int d = 13; d <= 19; ++d) {
                if (weekday_index_monday0(year_, month_, d) == target) {
                    day = d;
                    break;
                }
            }
            break;
        }
        case last: {
            const int last_w = weekday_index_monday0(year_, month_, dim);
            const int offset = (last_w - target + 7) % 7;
            day = dim - offset;
            break;
        }
        case first:
        case second:
        case third:
        case fourth: {
            int n = 1;
            if (which == second) n = 2;
            else if (which == third) n = 3;
            else if (which == fourth) n = 4;

            const int first_w = weekday_index_monday0(year_, month_, 1);
            const int delta = (target - first_w + 7) % 7;
            day = 1 + delta + 7 * (n - 1);
            break;
        }
    }

    return date(year_, month_, day);
}

date scheduler::monteenth() const { return meetup_day(Monday, teenth); }
date scheduler::tuesteenth() const { return meetup_day(Tuesday, teenth); }
date scheduler::wednesteenth() const { return meetup_day(Wednesday, teenth); }
date scheduler::thursteenth() const { return meetup_day(Thursday, teenth); }
date scheduler::friteenth() const { return meetup_day(Friday, teenth); }
date scheduler::saturteenth() const { return meetup_day(Saturday, teenth); }
date scheduler::sunteenth() const { return meetup_day(Sunday, teenth); }

date scheduler::first_monday() const { return meetup_day(Monday, first); }
date scheduler::first_tuesday() const { return meetup_day(Tuesday, first); }
date scheduler::first_wednesday() const { return meetup_day(Wednesday, first); }
date scheduler::first_thursday() const { return meetup_day(Thursday, first); }
date scheduler::first_friday() const { return meetup_day(Friday, first); }
date scheduler::first_saturday() const { return meetup_day(Saturday, first); }
date scheduler::first_sunday() const { return meetup_day(Sunday, first); }

date scheduler::second_monday() const { return meetup_day(Monday, second); }
date scheduler::second_tuesday() const { return meetup_day(Tuesday, second); }
date scheduler::second_wednesday() const { return meetup_day(Wednesday, second); }
date scheduler::second_thursday() const { return meetup_day(Thursday, second); }
date scheduler::second_friday() const { return meetup_day(Friday, second); }
date scheduler::second_saturday() const { return meetup_day(Saturday, second); }
date scheduler::second_sunday() const { return meetup_day(Sunday, second); }

date scheduler::third_monday() const { return meetup_day(Monday, third); }
date scheduler::third_tuesday() const { return meetup_day(Tuesday, third); }
date scheduler::third_wednesday() const { return meetup_day(Wednesday, third); }
date scheduler::third_thursday() const { return meetup_day(Thursday, third); }
date scheduler::third_friday() const { return meetup_day(Friday, third); }
date scheduler::third_saturday() const { return meetup_day(Saturday, third); }
date scheduler::third_sunday() const { return meetup_day(Sunday, third); }

date scheduler::fourth_monday() const { return meetup_day(Monday, fourth); }
date scheduler::fourth_tuesday() const { return meetup_day(Tuesday, fourth); }
date scheduler::fourth_wednesday() const { return meetup_day(Wednesday, fourth); }
date scheduler::fourth_thursday() const { return meetup_day(Thursday, fourth); }
date scheduler::fourth_friday() const { return meetup_day(Friday, fourth); }
date scheduler::fourth_saturday() const { return meetup_day(Saturday, fourth); }
date scheduler::fourth_sunday() const { return meetup_day(Sunday, fourth); }

date scheduler::last_monday() const { return meetup_day(Monday, last); }
date scheduler::last_tuesday() const { return meetup_day(Tuesday, last); }
date scheduler::last_wednesday() const { return meetup_day(Wednesday, last); }
date scheduler::last_thursday() const { return meetup_day(Thursday, last); }
date scheduler::last_friday() const { return meetup_day(Friday, last); }
date scheduler::last_saturday() const { return meetup_day(Saturday, last); }
date scheduler::last_sunday() const { return meetup_day(Sunday, last); }

}  // namespace meetup
