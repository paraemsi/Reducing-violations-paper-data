#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

date scheduler::find_teenth(greg_weekday weekday) const {
    for (int day = 13; day <= 19; day++) {
        date d(year_, month_, day);
        if (d.day_of_week() == weekday) {
            return d;
        }
    }
    // According to the instructions, each weekday has exactly one teenth day, so this should never happen
    return date(year_, month_, 13);
}

date scheduler::find_nth_weekday(int nth, greg_weekday weekday) const {
    // Find the first day of the month
    date first_day(year_, month_, 1);
    // Find the first occurrence of the weekday
    // If the first day is after the target weekday, we need to add days to reach the next occurrence
    int days_to_add = (weekday - first_day.day_of_week() + 7) % 7;
    date result = first_day + days(days_to_add);
    // Add weeks to get to the nth occurrence
    result += weeks(nth - 1);
    // Check if the result is still in the same month
    if (result.month() != month_) {
        // If not, we need to find the last occurrence which will be handled by find_last
        // But for first, second, etc., this shouldn't happen
        // Adjust to find the appropriate day
        result -= weeks(1);
    }
    return result;
}

date scheduler::find_last(greg_weekday weekday) const {
    // Get the last day of the month
    date last_day = date(year_, month_, 1).end_of_month();
    // Find the last occurrence of the weekday by working backwards from the end of the month
    int days_to_subtract = (last_day.day_of_week() - weekday + 7) % 7;
    return last_day - days(days_to_subtract);
}

// Teenth methods
date scheduler::monteenth() const { return find_teenth(Monday); }
date scheduler::tuesteenth() const { return find_teenth(Tuesday); }
date scheduler::wednesteenth() const { return find_teenth(Wednesday); }
date scheduler::thursteenth() const { return find_teenth(Thursday); }
date scheduler::friteenth() const { return find_teenth(Friday); }
date scheduler::saturteenth() const { return find_teenth(Saturday); }
date scheduler::sunteenth() const { return find_teenth(Sunday); }

// First week methods
date scheduler::first_monday() const { return find_nth_weekday(1, Monday); }
date scheduler::first_tuesday() const { return find_nth_weekday(1, Tuesday); }
date scheduler::first_wednesday() const { return find_nth_weekday(1, Wednesday); }
date scheduler::first_thursday() const { return find_nth_weekday(1, Thursday); }
date scheduler::first_friday() const { return find_nth_weekday(1, Friday); }
date scheduler::first_saturday() const { return find_nth_weekday(1, Saturday); }
date scheduler::first_sunday() const { return find_nth_weekday(1, Sunday); }

// Second week methods
date scheduler::second_monday() const { return find_nth_weekday(2, Monday); }
date scheduler::second_tuesday() const { return find_nth_weekday(2, Tuesday); }
date scheduler::second_wednesday() const { return find_nth_weekday(2, Wednesday); }
date scheduler::second_thursday() const { return find_nth_weekday(2, Thursday); }
date scheduler::second_friday() const { return find_nth_weekday(2, Friday); }
date scheduler::second_saturday() const { return find_nth_weekday(2, Saturday); }
date scheduler::second_sunday() const { return find_nth_weekday(2, Sunday); }

// Third week methods
date scheduler::third_monday() const { return find_nth_weekday(3, Monday); }
date scheduler::third_tuesday() const { return find_nth_weekday(3, Tuesday); }
date scheduler::third_wednesday() const { return find_nth_weekday(3, Wednesday); }
date scheduler::third_thursday() const { return find_nth_weekday(3, Thursday); }
date scheduler::third_friday() const { return find_nth_weekday(3, Friday); }
date scheduler::third_saturday() const { return find_nth_weekday(3, Saturday); }
date scheduler::third_sunday() const { return find_nth_weekday(3, Sunday); }

// Fourth week methods
date scheduler::fourth_monday() const { return find_nth_weekday(4, Monday); }
date scheduler::fourth_tuesday() const { return find_nth_weekday(4, Tuesday); }
date scheduler::fourth_wednesday() const { return find_nth_weekday(4, Wednesday); }
date scheduler::fourth_thursday() const { return find_nth_weekday(4, Thursday); }
date scheduler::fourth_friday() const { return find_nth_weekday(4, Friday); }
date scheduler::fourth_saturday() const { return find_nth_weekday(4, Saturday); }
date scheduler::fourth_sunday() const { return find_nth_weekday(4, Sunday); }

// Last week methods
date scheduler::last_monday() const { return find_last(Monday); }
date scheduler::last_tuesday() const { return find_last(Tuesday); }
date scheduler::last_wednesday() const { return find_last(Wednesday); }
date scheduler::last_thursday() const { return find_last(Thursday); }
date scheduler::last_friday() const { return find_last(Friday); }
date scheduler::last_saturday() const { return find_last(Saturday); }
date scheduler::last_sunday() const { return find_last(Sunday); }

}  // namespace meetup
