#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

scheduler::scheduler(boost::gregorian::greg_month month, int year) : month_(month), year_(year) {}

boost::gregorian::date scheduler::day(weekday wd, week wk) {
    boost::gregorian::greg_weekday target_wd = static_cast<boost::gregorian::greg_weekday>(static_cast<int>(wd));
    boost::gregorian::date first_day(year_, month_, 1);
    boost::gregorian::date last_day = first_day.end_of_month();
    int days_in_month = last_day.day();

    if (wk == week::teenth) {
        for (int d = 13; d <= 19; ++d) {
            boost::gregorian::date candidate(year_, month_, d);
            if (candidate.day_of_week() == target_wd) {
                return candidate;
            }
        }
    } else if (wk == week::last) {
        for (int d = days_in_month; d >= 1; --d) {
            boost::gregorian::date candidate(year_, month_, d);
            if (candidate.day_of_week() == target_wd) {
                return candidate;
            }
        }
    } else {
        int target_count = (static_cast<int>(wk) + 1);
        int count = 0;
        for (int d = 1; d <= days_in_month; ++d) {
            boost::gregorian::date candidate(year_, month_, d);
            if (candidate.day_of_week() == target_wd) {
                ++count;
                if (count == target_count) {
                    return candidate;
                }
            }
        }
    }

    // If not found, though guaranteed, but to satisfy compiler
    return boost::gregorian::date();
}

boost::gregorian::date scheduler::monteenth() {
    return day(weekday::monday, week::teenth);
}

boost::gregorian::date scheduler::tuesteenth() {
    return day(weekday::tuesday, week::teenth);
}

boost::gregorian::date scheduler::wednesteenth() {
    return day(weekday::wednesday, week::teenth);
}

boost::gregorian::date scheduler::thursteenth() {
    return day(weekday::thursday, week::teenth);
}

boost::gregorian::date scheduler::friteenth() {
    return day(weekday::friday, week::teenth);
}

boost::gregorian::date scheduler::saturteenth() {
    return day(weekday::saturday, week::teenth);
}

boost::gregorian::date scheduler::sunteenth() {
    return day(weekday::sunday, week::teenth);
}

boost::gregorian::date scheduler::first_monday() {
    return day(weekday::monday, week::first);
}

boost::gregorian::date scheduler::first_tuesday() {
    return day(weekday::tuesday, week::first);
}

boost::gregorian::date scheduler::first_wednesday() {
    return day(weekday::wednesday, week::first);
}

boost::gregorian::date scheduler::first_thursday() {
    return day(weekday::thursday, week::first);
}

boost::gregorian::date scheduler::first_friday() {
    return day(weekday::friday, week::first);
}

boost::gregorian::date scheduler::first_saturday() {
    return day(weekday::saturday, week::first);
}

boost::gregorian::date scheduler::first_sunday() {
    return day(weekday::sunday, week::first);
}

boost::gregorian::date scheduler::second_monday() {
    return day(weekday::monday, week::second);
}

boost::gregorian::date scheduler::second_tuesday() {
    return day(weekday::tuesday, week::second);
}

boost::gregorian::date scheduler::second_wednesday() {
    return day(weekday::wednesday, week::second);
}

boost::gregorian::date scheduler::second_thursday() {
    return day(weekday::thursday, week::second);
}

boost::gregorian::date scheduler::second_friday() {
    return day(weekday::friday, week::second);
}

boost::gregorian::date scheduler::second_saturday() {
    return day(weekday::saturday, week::second);
}

boost::gregorian::date scheduler::second_sunday() {
    return day(weekday::sunday, week::second);
}

boost::gregorian::date scheduler::third_monday() {
    return day(weekday::monday, week::third);
}

boost::gregorian::date scheduler::third_tuesday() {
    return day(weekday::tuesday, week::third);
}

boost::gregorian::date scheduler::third_wednesday() {
    return day(weekday::wednesday, week::third);
}

boost::gregorian::date scheduler::third_thursday() {
    return day(weekday::thursday, week::third);
}

boost::gregorian::date scheduler::third_friday() {
    return day(weekday::friday, week::third);
}

boost::gregorian::date scheduler::third_saturday() {
    return day(weekday::saturday, week::third);
}

boost::gregorian::date scheduler::third_sunday() {
    return day(weekday::sunday, week::third);
}

boost::gregorian::date scheduler::fourth_monday() {
    return day(weekday::monday, week::fourth);
}

boost::gregorian::date scheduler::fourth_tuesday() {
    return day(weekday::tuesday, week::fourth);
}

boost::gregorian::date scheduler::fourth_wednesday() {
    return day(weekday::wednesday, week::fourth);
}

boost::gregorian::date scheduler::fourth_thursday() {
    return day(weekday::thursday, week::fourth);
}

boost::gregorian::date scheduler::fourth_friday() {
    return day(weekday::friday, week::fourth);
}

boost::gregorian::date scheduler::fourth_saturday() {
    return day(weekday::saturday, week::fourth);
}

boost::gregorian::date scheduler::fourth_sunday() {
    return day(weekday::sunday, week::fourth);
}

boost::gregorian::date scheduler::last_monday() {
    return day(weekday::monday, week::last);
}

boost::gregorian::date scheduler::last_tuesday() {
    return day(weekday::tuesday, week::last);
}

boost::gregorian::date scheduler::last_wednesday() {
    return day(weekday::wednesday, week::last);
}

boost::gregorian::date scheduler::last_thursday() {
    return day(weekday::thursday, week::last);
}

boost::gregorian::date scheduler::last_friday() {
    return day(weekday::friday, week::last);
}

boost::gregorian::date scheduler::last_saturday() {
    return day(weekday::saturday, week::last);
}

boost::gregorian::date scheduler::last_sunday() {
    return day(weekday::sunday, week::last);
}

}  // namespace meetup
