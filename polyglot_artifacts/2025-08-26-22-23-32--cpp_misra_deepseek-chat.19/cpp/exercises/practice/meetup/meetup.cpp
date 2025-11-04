#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <vector>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper functions
date scheduler::find_nth_weekday(int n, greg_weekday wd) const {
    date first_of_month(year_, month_, 1);
    // Find the first occurrence of the weekday
    // Convert weekdays to numbers (Sunday=0, Monday=1, etc.)
    int target_dow = wd.as_number();
    int first_dow = first_of_month.day_of_week().as_number();
    int days_to_add = (target_dow - first_dow + 7) % 7;
    date result = first_of_month + days(days_to_add);
    // Add (n-1) weeks
    result += weeks(n - 1);
    // Check if the result is still in the same month
    if (result.month() != month_) {
        throw std::runtime_error("Nth weekday not found in month");
    }
    return result;
}

date scheduler::find_teenth(greg_weekday wd) const {
    for (int day = 13; day <= 19; ++day) {
        date current(year_, month_, day);
        if (current.day_of_week() == wd) {
            return current;
        }
    }
    throw std::runtime_error("Teenth day not found");
}

date scheduler::find_last(greg_weekday wd) const {
    date last_of_month = date(year_, month_, 1).end_of_month();
    // Find the last occurrence of the weekday
    // Convert weekdays to numbers
    int last_dow = last_of_month.day_of_week().as_number();
    int target_dow = wd.as_number();
    int days_to_subtract = (last_dow - target_dow + 7) % 7;
    return last_of_month - days(days_to_subtract);
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
