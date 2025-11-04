#include "meetup.h"
#include <string>
#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace bg = boost::gregorian;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

boost::gregorian::date scheduler::find_teenth(int target_dow) const {
    for (int day = 13; day <= 19; ++day) {
        bg::date d(year_, month_, day);
        if (d.day_of_week() == target_dow) {
            return d;
        }
    }
    return bg::date(year_, month_, 1); // Should never reach here
}

boost::gregorian::date scheduler::find_nth_weekday(int nth, int target_dow) const {
    bg::date first_day(year_, month_, 1);
    int first_dow = first_day.day_of_week();
    int days_to_add = (target_dow - first_dow + 7) % 7;
    bg::date result = first_day + bg::days(days_to_add);
    // Add (n-1) weeks
    result += bg::weeks(nth - 1);
    // Make sure we're still in the same month
    if (result.month() != month_) {
        // If not, move back by one week
        result -= bg::weeks(1);
    }
    return result;
}

boost::gregorian::date scheduler::find_last(int target_dow) const {
    int last_day = bg::gregorian_calendar::end_of_month_day(year_, month_);
    bg::date d(year_, month_, last_day);
    while (d.day_of_week() != target_dow) {
        d -= bg::days(1);
    }
    return d;
}

// Teenth implementations
boost::gregorian::date scheduler::monteenth() const { return find_teenth(1); }
boost::gregorian::date scheduler::tuesteenth() const { return find_teenth(2); }
boost::gregorian::date scheduler::wednesteenth() const { return find_teenth(3); }
boost::gregorian::date scheduler::thursteenth() const { return find_teenth(4); }
boost::gregorian::date scheduler::friteenth() const { return find_teenth(5); }
boost::gregorian::date scheduler::saturteenth() const { return find_teenth(6); }
boost::gregorian::date scheduler::sunteenth() const { return find_teenth(0); }

// First week implementations
boost::gregorian::date scheduler::first_monday() const { return find_nth_weekday(1, 1); }
boost::gregorian::date scheduler::first_tuesday() const { return find_nth_weekday(1, 2); }
boost::gregorian::date scheduler::first_wednesday() const { return find_nth_weekday(1, 3); }
boost::gregorian::date scheduler::first_thursday() const { return find_nth_weekday(1, 4); }
boost::gregorian::date scheduler::first_friday() const { return find_nth_weekday(1, 5); }
boost::gregorian::date scheduler::first_saturday() const { return find_nth_weekday(1, 6); }
boost::gregorian::date scheduler::first_sunday() const { return find_nth_weekday(1, 0); }

// Second week implementations
boost::gregorian::date scheduler::second_monday() const { return find_nth_weekday(2, 1); }
boost::gregorian::date scheduler::second_tuesday() const { return find_nth_weekday(2, 2); }
boost::gregorian::date scheduler::second_wednesday() const { return find_nth_weekday(2, 3); }
boost::gregorian::date scheduler::second_thursday() const { return find_nth_weekday(2, 4); }
boost::gregorian::date scheduler::second_friday() const { return find_nth_weekday(2, 5); }
boost::gregorian::date scheduler::second_saturday() const { return find_nth_weekday(2, 6); }
boost::gregorian::date scheduler::second_sunday() const { return find_nth_weekday(2, 0); }

// Third week implementations
boost::gregorian::date scheduler::third_monday() const { return find_nth_weekday(3, 1); }
boost::gregorian::date scheduler::third_tuesday() const { return find_nth_weekday(3, 2); }
boost::gregorian::date scheduler::third_wednesday() const { return find_nth_weekday(3, 3); }
boost::gregorian::date scheduler::third_thursday() const { return find_nth_weekday(3, 4); }
boost::gregorian::date scheduler::third_friday() const { return find_nth_weekday(3, 5); }
boost::gregorian::date scheduler::third_saturday() const { return find_nth_weekday(3, 6); }
boost::gregorian::date scheduler::third_sunday() const { return find_nth_weekday(3, 0); }

// Fourth week implementations
boost::gregorian::date scheduler::fourth_monday() const { return find_nth_weekday(4, 1); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_nth_weekday(4, 2); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_nth_weekday(4, 3); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_nth_weekday(4, 4); }
boost::gregorian::date scheduler::fourth_friday() const { return find_nth_weekday(4, 5); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_nth_weekday(4, 6); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_nth_weekday(4, 0); }

// Last week implementations
boost::gregorian::date scheduler::last_monday() const { return find_last(1); }
boost::gregorian::date scheduler::last_tuesday() const { return find_last(2); }
boost::gregorian::date scheduler::last_wednesday() const { return find_last(3); }
boost::gregorian::date scheduler::last_thursday() const { return find_last(4); }
boost::gregorian::date scheduler::last_friday() const { return find_last(5); }
boost::gregorian::date scheduler::last_saturday() const { return find_last(6); }
boost::gregorian::date scheduler::last_sunday() const { return find_last(0); }

}  // namespace meetup
