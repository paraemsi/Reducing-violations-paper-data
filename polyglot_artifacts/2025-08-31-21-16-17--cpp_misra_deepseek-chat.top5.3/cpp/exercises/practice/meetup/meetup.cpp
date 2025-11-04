#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper functions
date scheduler::find_nth_weekday(int nth, greg_weekday weekday) const {
    // Start from the first day of the month
    date first_day(year_, month_, 1);
    // Find the first occurrence of the weekday
    // If the first day is after the target weekday, we need to add days to reach the next week
    int days_to_add = (weekday.as_number() - first_day.day_of_week().as_number() + 7) % 7;
    date result = first_day + days(days_to_add);
    // Add (nth-1) weeks
    if (nth > 1) {
        result = result + weeks(nth - 1);
    }
    // Check if we're still in the same month
    if (result.month() != month_) {
        throw std::runtime_error("Nth weekday not found in month");
    }
    return result;
}

date scheduler::find_teenth(greg_weekday weekday) const {
    // Check days 13-19
    for (int day = 13; day <= 19; day++) {
        date candidate(year_, month_, day);
        if (candidate.day_of_week() == weekday) {
            return candidate;
        }
    }
    throw std::runtime_error("Teenth day not found");
}

date scheduler::find_last(greg_weekday weekday) const {
    // Start from the last day of the month
    date last_day = date(year_, month_, 1).end_of_month();
    // Move backwards to find the last occurrence of the weekday
    while (last_day.day_of_week() != weekday) {
        last_day -= days(1);
    }
    return last_day;
}

// Teenth implementations
date scheduler::monteenth() const { return find_teenth(Monday); }
date scheduler::tuesteenth() const { return find_teenth(Tuesday); }
date scheduler::wednesteenth() const { return find_teenth(Wednesday); }
date scheduler::thursteenth() const { return find_teenth(Thursday); }
date scheduler::friteenth() const { return find_teenth(Friday); }
date scheduler::saturteenth() const { return find_teenth(Saturday); }
date scheduler::sunteenth() const { return find_teenth(Sunday); }

// First week implementations
date scheduler::first_monday() const { return find_nth_weekday(1, Monday); }
date scheduler::first_tuesday() const { return find_nth_weekday(1, Tuesday); }
date scheduler::first_wednesday() const { return find_nth_weekday(1, Wednesday); }
date scheduler::first_thursday() const { return find_nth_weekday(1, Thursday); }
date scheduler::first_friday() const { return find_nth_weekday(1, Friday); }
date scheduler::first_saturday() const { return find_nth_weekday(1, Saturday); }
date scheduler::first_sunday() const { return find_nth_weekday(1, Sunday); }

// Second week implementations
date scheduler::second_monday() const { return find_nth_weekday(2, Monday); }
date scheduler::second_tuesday() const { return find_nth_weekday(2, Tuesday); }
date scheduler::second_wednesday() const { return find_nth_weekday(2, Wednesday); }
date scheduler::second_thursday() const { return find_nth_weekday(2, Thursday); }
date scheduler::second_friday() const { return find_nth_weekday(2, Friday); }
date scheduler::second_saturday() const { return find_nth_weekday(2, Saturday); }
date scheduler::second_sunday() const { return find_nth_weekday(2, Sunday); }

// Third week implementations
date scheduler::third_monday() const { return find_nth_weekday(3, Monday); }
date scheduler::third_tuesday() const { return find_nth_weekday(3, Tuesday); }
date scheduler::third_wednesday() const { return find_nth_weekday(3, Wednesday); }
date scheduler::third_thursday() const { return find_nth_weekday(3, Thursday); }
date scheduler::third_friday() const { return find_nth_weekday(3, Friday); }
date scheduler::third_saturday() const { return find_nth_weekday(3, Saturday); }
date scheduler::third_sunday() const { return find_nth_weekday(3, Sunday); }

// Fourth week implementations
date scheduler::fourth_monday() const { return find_nth_weekday(4, Monday); }
date scheduler::fourth_tuesday() const { return find_nth_weekday(4, Tuesday); }
date scheduler::fourth_wednesday() const { return find_nth_weekday(4, Wednesday); }
date scheduler::fourth_thursday() const { return find_nth_weekday(4, Thursday); }
date scheduler::fourth_friday() const { return find_nth_weekday(4, Friday); }
date scheduler::fourth_saturday() const { return find_nth_weekday(4, Saturday); }
date scheduler::fourth_sunday() const { return find_nth_weekday(4, Sunday); }

// Last week implementations
date scheduler::last_monday() const { return find_last(Monday); }
date scheduler::last_tuesday() const { return find_last(Tuesday); }
date scheduler::last_wednesday() const { return find_last(Wednesday); }
date scheduler::last_thursday() const { return find_last(Thursday); }
date scheduler::last_friday() const { return find_last(Friday); }
date scheduler::last_saturday() const { return find_last(Saturday); }
date scheduler::last_sunday() const { return find_last(Sunday); }

}  // namespace meetup
