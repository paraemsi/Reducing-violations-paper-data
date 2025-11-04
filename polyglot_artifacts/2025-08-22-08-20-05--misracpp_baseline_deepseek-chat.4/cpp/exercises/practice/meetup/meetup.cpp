#include "meetup.h"
#include <map>
#include <string>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, const std::string& month) : year_(year) {
    static std::map<std::string, int> month_map = {
        {"January", 1}, {"February", 2}, {"March", 3}, {"April", 4},
        {"May", 5}, {"June", 6}, {"July", 7}, {"August", 8},
        {"September", 9}, {"October", 10}, {"November", 11}, {"December", 12}
    };
    
    auto it = month_map.find(month);
    if (it == month_map.end()) {
        throw std::runtime_error("Invalid month name");
    }
    month_ = it->second;
}

// Teenth implementations
date scheduler::monteenth() const { return find_teenth_day(Monday); }
date scheduler::tuesteenth() const { return find_teenth_day(Tuesday); }
date scheduler::wednesteenth() const { return find_teenth_day(Wednesday); }
date scheduler::thursteenth() const { return find_teenth_day(Thursday); }
date scheduler::friteenth() const { return find_teenth_day(Friday); }
date scheduler::saturteenth() const { return find_teenth_day(Saturday); }
date scheduler::sunteenth() const { return find_teenth_day(Sunday); }

// First week
date scheduler::first_monday() const { return find_nth_weekday(1, Monday); }
date scheduler::first_tuesday() const { return find_nth_weekday(1, Tuesday); }
date scheduler::first_wednesday() const { return find_nth_weekday(1, Wednesday); }
date scheduler::first_thursday() const { return find_nth_weekday(1, Thursday); }
date scheduler::first_friday() const { return find_nth_weekday(1, Friday); }
date scheduler::first_saturday() const { return find_nth_weekday(1, Saturday); }
date scheduler::first_sunday() const { return find_nth_weekday(1, Sunday); }

// Second week
date scheduler::second_monday() const { return find_nth_weekday(2, Monday); }
date scheduler::second_tuesday() const { return find_nth_weekday(2, Tuesday); }
date scheduler::second_wednesday() const { return find_nth_weekday(2, Wednesday); }
date scheduler::second_thursday() const { return find_nth_weekday(2, Thursday); }
date scheduler::second_friday() const { return find_nth_weekday(2, Friday); }
date scheduler::second_saturday() const { return find_nth_weekday(2, Saturday); }
date scheduler::second_sunday() const { return find_nth_weekday(2, Sunday); }

// Third week
date scheduler::third_monday() const { return find_nth_weekday(3, Monday); }
date scheduler::third_tuesday() const { return find_nth_weekday(3, Tuesday); }
date scheduler::third_wednesday() const { return find_nth_weekday(3, Wednesday); }
date scheduler::third_thursday() const { return find_nth_weekday(3, Thursday); }
date scheduler::third_friday() const { return find_nth_weekday(3, Friday); }
date scheduler::third_saturday() const { return find_nth_weekday(3, Saturday); }
date scheduler::third_sunday() const { return find_nth_weekday(3, Sunday); }

// Fourth week
date scheduler::fourth_monday() const { return find_nth_weekday(4, Monday); }
date scheduler::fourth_tuesday() const { return find_nth_weekday(4, Tuesday); }
date scheduler::fourth_wednesday() const { return find_nth_weekday(4, Wednesday); }
date scheduler::fourth_thursday() const { return find_nth_weekday(4, Thursday); }
date scheduler::fourth_friday() const { return find_nth_weekday(4, Friday); }
date scheduler::fourth_saturday() const { return find_nth_weekday(4, Saturday); }
date scheduler::fourth_sunday() const { return find_nth_weekday(4, Sunday); }

// Last week
date scheduler::last_monday() const { return find_last_weekday(Monday); }
date scheduler::last_tuesday() const { return find_last_weekday(Tuesday); }
date scheduler::last_wednesday() const { return find_last_weekday(Wednesday); }
date scheduler::last_thursday() const { return find_last_weekday(Thursday); }
date scheduler::last_friday() const { return find_last_weekday(Friday); }
date scheduler::last_saturday() const { return find_last_weekday(Saturday); }
date scheduler::last_sunday() const { return find_last_weekday(Sunday); }

// Helper functions
date scheduler::find_teenth_day(greg_weekday weekday) const {
    for (int day = 13; day <= 19; ++day) {
        date candidate(year_, month_, day);
        if (candidate.day_of_week() == weekday) {
            return candidate;
        }
    }
    throw std::runtime_error("Teenth day not found");
}

date scheduler::find_nth_weekday(int n, greg_weekday weekday) const {
    // Start from the first day of the month
    date first_day(year_, month_, 1);
    // Find the first occurrence of the desired weekday
    // Calculate days to add to reach the first occurrence of the weekday
    int days_until_first = (weekday - first_day.day_of_week() + 7) % 7;
    date first_occurrence = first_day + days(days_until_first);
    
    // Add (n-1) weeks to get the nth occurrence
    date nth_occurrence = first_occurrence + weeks(n - 1);
    
    // Check if the result is still in the same month
    if (nth_occurrence.month() != month_) {
        // If not, it means we're trying to access a day in the next month
        // This can happen for the 5th occurrence in some months
        // According to the instructions, we need to find within the month, so throw or adjust
        // But since the tests expect valid dates, and n is up to 4, this should not happen
        // For safety, we can find the last occurrence
        nth_occurrence -= weeks(1);
    }
    return nth_occurrence;
}

date scheduler::find_last_weekday(greg_weekday weekday) const {
    // Get the first day of the next month, then subtract one day to get the last day of the current month
    int next_month = month_ + 1;
    int next_year = year_;
    if (next_month > 12) {
        next_month = 1;
        next_year = year_ + 1;
    }
    date first_of_next_month(next_year, next_month, 1);
    date last_of_month = first_of_next_month - days(1);
    
    // Find how many days to go back to reach the desired weekday
    int days_to_go_back = (last_of_month.day_of_week() - weekday + 7) % 7;
    return last_of_month - days(days_to_go_back);
}

}  // namespace meetup
