#include "meetup.h"

#include <cassert>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {


scheduler::scheduler(int year, unsigned month)
    : year_{year}, month_{month} {}

/*
 * Compute the meetup day requested.
 *
 *  – For first/second/third/fourth we pick the N-th weekday of the month.
 *  – For last we walk backwards from the end of the month.
 *  – For teenth we examine the seven “-teenth” days (13 … 19).
 */
boost::gregorian::date scheduler::get_day(boost::date_time::weekdays desired_weekday,
                                          schedule which) const {
    using namespace boost::gregorian;
    date first_day(year_, month_, 1);

    if (which == schedule::teenth) {
        for (unsigned d = 13; d <= 19; ++d) {
            date current(year_, month_, d);
            if (current.day_of_week() == desired_weekday) {
                return current;
            }
        }
        assert(false && "No teenth day found – logic error");
    }

    if (which == schedule::last) {
        date last_day = first_day + months(1) - days(1);
        while (last_day.day_of_week() != desired_weekday) {
            last_day -= days(1);
        }
        return last_day;
    }

    int week_offset = 0;
    switch (which) {
        case schedule::first:  week_offset = 0; break;
        case schedule::second: week_offset = 1; break;
        case schedule::third:  week_offset = 2; break;
        case schedule::fourth: week_offset = 3; break;
        default: assert(false && "Unhandled schedule value");
    }

    int diff = (static_cast<int>(desired_weekday) -
                static_cast<int>(first_day.day_of_week()) + 7) % 7;

    date result = first_day + days(diff) + weeks(week_offset);
    return result;
}

boost::gregorian::date scheduler::meetup_day(boost::date_time::weekdays wd,
                                             schedule which) const {
    return get_day(wd, which);
}

// “teenth” helpers
boost::gregorian::date scheduler::monteenth() const { return meetup_day(boost::date_time::Monday, schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth() const { return meetup_day(boost::date_time::Tuesday, schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth() const { return meetup_day(boost::date_time::Wednesday, schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return meetup_day(boost::date_time::Thursday, schedule::teenth); }
boost::gregorian::date scheduler::friteenth() const { return meetup_day(boost::date_time::Friday, schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return meetup_day(boost::date_time::Saturday, schedule::teenth); }
boost::gregorian::date scheduler::sunteenth() const { return meetup_day(boost::date_time::Sunday, schedule::teenth); }

// first
boost::gregorian::date scheduler::first_monday() const { return meetup_day(boost::date_time::Monday, schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const { return meetup_day(boost::date_time::Tuesday, schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return meetup_day(boost::date_time::Wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const { return meetup_day(boost::date_time::Thursday, schedule::first); }
boost::gregorian::date scheduler::first_friday() const { return meetup_day(boost::date_time::Friday, schedule::first); }
boost::gregorian::date scheduler::first_saturday() const { return meetup_day(boost::date_time::Saturday, schedule::first); }
boost::gregorian::date scheduler::first_sunday() const { return meetup_day(boost::date_time::Sunday, schedule::first); }

// second
boost::gregorian::date scheduler::second_monday() const { return meetup_day(boost::date_time::Monday, schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const { return meetup_day(boost::date_time::Tuesday, schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return meetup_day(boost::date_time::Wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const { return meetup_day(boost::date_time::Thursday, schedule::second); }
boost::gregorian::date scheduler::second_friday() const { return meetup_day(boost::date_time::Friday, schedule::second); }
boost::gregorian::date scheduler::second_saturday() const { return meetup_day(boost::date_time::Saturday, schedule::second); }
boost::gregorian::date scheduler::second_sunday() const { return meetup_day(boost::date_time::Sunday, schedule::second); }

// third
boost::gregorian::date scheduler::third_monday() const { return meetup_day(boost::date_time::Monday, schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const { return meetup_day(boost::date_time::Tuesday, schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return meetup_day(boost::date_time::Wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const { return meetup_day(boost::date_time::Thursday, schedule::third); }
boost::gregorian::date scheduler::third_friday() const { return meetup_day(boost::date_time::Friday, schedule::third); }
boost::gregorian::date scheduler::third_saturday() const { return meetup_day(boost::date_time::Saturday, schedule::third); }
boost::gregorian::date scheduler::third_sunday() const { return meetup_day(boost::date_time::Sunday, schedule::third); }

// fourth
boost::gregorian::date scheduler::fourth_monday() const { return meetup_day(boost::date_time::Monday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return meetup_day(boost::date_time::Tuesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return meetup_day(boost::date_time::Wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return meetup_day(boost::date_time::Thursday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return meetup_day(boost::date_time::Friday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return meetup_day(boost::date_time::Saturday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return meetup_day(boost::date_time::Sunday, schedule::fourth); }

// last
boost::gregorian::date scheduler::last_monday() const { return meetup_day(boost::date_time::Monday, schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const { return meetup_day(boost::date_time::Tuesday, schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return meetup_day(boost::date_time::Wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const { return meetup_day(boost::date_time::Thursday, schedule::last); }
boost::gregorian::date scheduler::last_friday() const { return meetup_day(boost::date_time::Friday, schedule::last); }
boost::gregorian::date scheduler::last_saturday() const { return meetup_day(boost::date_time::Saturday, schedule::last); }
boost::gregorian::date scheduler::last_sunday() const { return meetup_day(boost::date_time::Sunday, schedule::last); }

}  // namespace meetup
