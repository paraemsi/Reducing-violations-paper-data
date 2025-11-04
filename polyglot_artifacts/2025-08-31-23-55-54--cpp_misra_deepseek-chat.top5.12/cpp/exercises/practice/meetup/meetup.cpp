#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

date scheduler::find_date(int week, greg_weekday weekday) const {
    // Start from the first day of the month
    date first_day(year_, month_, 1);
    // Find the first occurrence of the target weekday
    // Calculate days to add to reach the first target weekday
    int days_to_add = (weekday.as_number() - first_day.day_of_week().as_number() + 7) % 7;
    date first_occurrence = first_day + days(days_to_add);
    // Add appropriate number of weeks
    date result = first_occurrence + weeks(week);
    // Check if the result is still in the same month
    if (result.month() != month_) {
        result -= weeks(1);
    }
    return result;
}

date scheduler::find_teenth(greg_weekday weekday) const {
    // Check each teenth day (13-19) to find the one that matches the weekday
    for (int day = 13; day <= 19; ++day) {
        date candidate(year_, month_, day);
        if (candidate.day_of_week() == weekday) {
            return candidate;
        }
    }
    throw std::runtime_error("Teenth not found");
}

// Implement teenth methods
date scheduler::monteenth() const { return find_teenth(Monday); }
date scheduler::tuesteenth() const { return find_teenth(Tuesday); }
date scheduler::wednesteenth() const { return find_teenth(Wednesday); }
date scheduler::thursteenth() const { return find_teenth(Thursday); }
date scheduler::friteenth() const { return find_teenth(Friday); }
date scheduler::saturteenth() const { return find_teenth(Saturday); }
date scheduler::sunteenth() const { return find_teenth(Sunday); }

// Helper function to find last weekday
date find_last_weekday(int year, int month, greg_weekday weekday) {
    // Start from the last day of the month
    date last_day = date(year, month, 1).end_of_month();
    // Find the last occurrence of the target weekday
    int days_to_subtract = (last_day.day_of_week() - weekday + 7) % 7;
    return last_day - days(days_to_subtract);
}

// Implement each method directly
date scheduler::first_monday() const { return find_date(0, Monday); }
date scheduler::first_tuesday() const { return find_date(0, Tuesday); }
date scheduler::first_wednesday() const { return find_date(0, Wednesday); }
date scheduler::first_thursday() const { return find_date(0, Thursday); }
date scheduler::first_friday() const { return find_date(0, Friday); }
date scheduler::first_saturday() const { return find_date(0, Saturday); }
date scheduler::first_sunday() const { return find_date(0, Sunday); }

date scheduler::second_monday() const { return find_date(1, Monday); }
date scheduler::second_tuesday() const { return find_date(1, Tuesday); }
date scheduler::second_wednesday() const { return find_date(1, Wednesday); }
date scheduler::second_thursday() const { return find_date(1, Thursday); }
date scheduler::second_friday() const { return find_date(1, Friday); }
date scheduler::second_saturday() const { return find_date(1, Saturday); }
date scheduler::second_sunday() const { return find_date(1, Sunday); }

date scheduler::third_monday() const { return find_date(2, Monday); }
date scheduler::third_tuesday() const { return find_date(2, Tuesday); }
date scheduler::third_wednesday() const { return find_date(2, Wednesday); }
date scheduler::third_thursday() const { return find_date(2, Thursday); }
date scheduler::third_friday() const { return find_date(2, Friday); }
date scheduler::third_saturday() const { return find_date(2, Saturday); }
date scheduler::third_sunday() const { return find_date(2, Sunday); }

date scheduler::fourth_monday() const { return find_date(3, Monday); }
date scheduler::fourth_tuesday() const { return find_date(3, Tuesday); }
date scheduler::fourth_wednesday() const { return find_date(3, Wednesday); }
date scheduler::fourth_thursday() const { return find_date(3, Thursday); }
date scheduler::fourth_friday() const { return find_date(3, Friday); }
date scheduler::fourth_saturday() const { return find_date(3, Saturday); }
date scheduler::fourth_sunday() const { return find_date(3, Sunday); }

date scheduler::last_monday() const { return find_last_weekday(year_, month_, Monday); }
date scheduler::last_tuesday() const { return find_last_weekday(year_, month_, Tuesday); }
date scheduler::last_wednesday() const { return find_last_weekday(year_, month_, Wednesday); }
date scheduler::last_thursday() const { return find_last_weekday(year_, month_, Thursday); }
date scheduler::last_friday() const { return find_last_weekday(year_, month_, Friday); }
date scheduler::last_saturday() const { return find_last_weekday(year_, month_, Saturday); }
date scheduler::last_sunday() const { return find_last_weekday(year_, month_, Sunday); }

}  // namespace meetup
