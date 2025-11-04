#include "meetup.h"

namespace meetup {

scheduler::scheduler(int year, int month)
    : year_(year), month_(static_cast<unsigned>(month)) {}

boost::gregorian::date scheduler::day(weekday wd, schedule s) const {
    using boost::gregorian::date;
    using boost::gregorian::gregorian_calendar;

    const int target = static_cast<int>(wd);

    auto windex = [&](int d) -> int {
        return static_cast<int>(date(year_, month_, d).day_of_week());
    };

    int dom = 1;

    switch (s) {
        case schedule::teenth: {
            const int base = 13;
            const int diff = (target - windex(base) + 7) % 7;
            dom = base + diff; // [13,19]
            break;
        }
        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth: {
            const int diff = (target - windex(1) + 7) % 7;
            const int first_match = 1 + diff;
            int add_weeks = 0;
            if (s == schedule::second) add_weeks = 1;
            else if (s == schedule::third) add_weeks = 2;
            else if (s == schedule::fourth) add_weeks = 3;
            dom = first_match + 7 * add_weeks;
            break;
        }
        case schedule::last: {
            const int last_dom = gregorian_calendar::end_of_month_day(year_, month_);
            const int wlast = windex(last_dom);
            const int diff_back = (wlast - target + 7) % 7;
            dom = last_dom - diff_back;
            break;
        }
    }

    return date(year_, month_, dom);
}

// teenth
boost::gregorian::date scheduler::monteenth() const { return day(weekday::monday, schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth() const { return day(weekday::tuesday, schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth() const { return day(weekday::wednesday, schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return day(weekday::thursday, schedule::teenth); }
boost::gregorian::date scheduler::friteenth() const { return day(weekday::friday, schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return day(weekday::saturday, schedule::teenth); }
boost::gregorian::date scheduler::sunteenth() const { return day(weekday::sunday, schedule::teenth); }

// first
boost::gregorian::date scheduler::first_monday() const { return day(weekday::monday, schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const { return day(weekday::tuesday, schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return day(weekday::wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const { return day(weekday::thursday, schedule::first); }
boost::gregorian::date scheduler::first_friday() const { return day(weekday::friday, schedule::first); }
boost::gregorian::date scheduler::first_saturday() const { return day(weekday::saturday, schedule::first); }
boost::gregorian::date scheduler::first_sunday() const { return day(weekday::sunday, schedule::first); }

// second
boost::gregorian::date scheduler::second_monday() const { return day(weekday::monday, schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const { return day(weekday::tuesday, schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return day(weekday::wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const { return day(weekday::thursday, schedule::second); }
boost::gregorian::date scheduler::second_friday() const { return day(weekday::friday, schedule::second); }
boost::gregorian::date scheduler::second_saturday() const { return day(weekday::saturday, schedule::second); }
boost::gregorian::date scheduler::second_sunday() const { return day(weekday::sunday, schedule::second); }

// third
boost::gregorian::date scheduler::third_monday() const { return day(weekday::monday, schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const { return day(weekday::tuesday, schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return day(weekday::wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const { return day(weekday::thursday, schedule::third); }
boost::gregorian::date scheduler::third_friday() const { return day(weekday::friday, schedule::third); }
boost::gregorian::date scheduler::third_saturday() const { return day(weekday::saturday, schedule::third); }
boost::gregorian::date scheduler::third_sunday() const { return day(weekday::sunday, schedule::third); }

// fourth
boost::gregorian::date scheduler::fourth_monday() const { return day(weekday::monday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return day(weekday::tuesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return day(weekday::wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return day(weekday::thursday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return day(weekday::friday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return day(weekday::saturday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return day(weekday::sunday, schedule::fourth); }

// last
boost::gregorian::date scheduler::last_monday() const { return day(weekday::monday, schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const { return day(weekday::tuesday, schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return day(weekday::wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const { return day(weekday::thursday, schedule::last); }
boost::gregorian::date scheduler::last_friday() const { return day(weekday::friday, schedule::last); }
boost::gregorian::date scheduler::last_saturday() const { return day(weekday::saturday, schedule::last); }
boost::gregorian::date scheduler::last_sunday() const { return day(weekday::sunday, schedule::last); }

}  // namespace meetup
