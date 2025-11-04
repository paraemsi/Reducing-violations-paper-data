#include "meetup.h"
#include <string>
#include <stdexcept>
#include <map>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper functions
boost::gregorian::date scheduler::find_teenth(boost::date_time::weekdays weekday) const {
    for (int day = 13; day <= 19; ++day) {
        boost::gregorian::date current_date(year_, month_, day);
        if (current_date.day_of_week() == weekday) {
            return current_date;
        }
    }
    throw std::runtime_error("No teenth day found");
}

boost::gregorian::date scheduler::find_nth_weekday(int n, boost::date_time::weekdays weekday) const {
    boost::gregorian::date start_date(year_, month_, 1);
    // Find the first occurrence of the weekday
    int start_day_of_week = start_date.day_of_week().as_number(); // 0=Sunday, 1=Monday, etc.
    int target_day_of_week = weekday; // This assumes weekday is an integer where 0=Sunday, etc.
    
    // Calculate days to add to reach the first target weekday
    int days_to_add = (target_day_of_week - start_day_of_week + 7) % 7;
    boost::gregorian::date first_occurrence = start_date + boost::gregorian::days(days_to_add);
    
    // Add weeks to reach the nth occurrence
    boost::gregorian::date result = first_occurrence + boost::gregorian::weeks(n - 1);
    
    // Check if the result is still in the same month
    if (result.month() != month_) {
        throw std::runtime_error("Date is not in the same month");
    }
    return result;
}

boost::gregorian::date scheduler::find_last(boost::date_time::weekdays weekday) const {
    // Start from the end of the month
    boost::gregorian::date start_date(year_, month_, 1);
    boost::gregorian::date end_date = start_date.end_of_month();
    // Go backwards until we find the matching weekday
    while (end_date.day_of_week() != weekday) {
        end_date -= boost::gregorian::days(1);
    }
    return end_date;
}

// Teenth implementations
boost::gregorian::date scheduler::monteenth() const { return find_teenth(boost::gregorian::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return find_teenth(boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return find_teenth(boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return find_teenth(boost::gregorian::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return find_teenth(boost::gregorian::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return find_teenth(boost::gregorian::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return find_teenth(boost::gregorian::Sunday); }

// First week implementations
boost::gregorian::date scheduler::first_monday() const { return find_nth_weekday(1, boost::gregorian::Monday); }
boost::gregorian::date scheduler::first_tuesday() const { return find_nth_weekday(1, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::first_wednesday() const { return find_nth_weekday(1, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::first_thursday() const { return find_nth_weekday(1, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::first_friday() const { return find_nth_weekday(1, boost::gregorian::Friday); }
boost::gregorian::date scheduler::first_saturday() const { return find_nth_weekday(1, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::first_sunday() const { return find_nth_weekday(1, boost::gregorian::Sunday); }

// Second week implementations
boost::gregorian::date scheduler::second_monday() const { return find_nth_weekday(2, boost::gregorian::Monday); }
boost::gregorian::date scheduler::second_tuesday() const { return find_nth_weekday(2, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::second_wednesday() const { return find_nth_weekday(2, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::second_thursday() const { return find_nth_weekday(2, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::second_friday() const { return find_nth_weekday(2, boost::gregorian::Friday); }
boost::gregorian::date scheduler::second_saturday() const { return find_nth_weekday(2, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::second_sunday() const { return find_nth_weekday(2, boost::gregorian::Sunday); }

// Third week implementations
boost::gregorian::date scheduler::third_monday() const { return find_nth_weekday(3, boost::gregorian::Monday); }
boost::gregorian::date scheduler::third_tuesday() const { return find_nth_weekday(3, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::third_wednesday() const { return find_nth_weekday(3, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::third_thursday() const { return find_nth_weekday(3, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::third_friday() const { return find_nth_weekday(3, boost::gregorian::Friday); }
boost::gregorian::date scheduler::third_saturday() const { return find_nth_weekday(3, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::third_sunday() const { return find_nth_weekday(3, boost::gregorian::Sunday); }

// Fourth week implementations
boost::gregorian::date scheduler::fourth_monday() const { return find_nth_weekday(4, boost::gregorian::Monday); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_nth_weekday(4, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_nth_weekday(4, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_nth_weekday(4, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::fourth_friday() const { return find_nth_weekday(4, boost::gregorian::Friday); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_nth_weekday(4, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_nth_weekday(4, boost::gregorian::Sunday); }

// Last week implementations
boost::gregorian::date scheduler::last_monday() const { return find_last(boost::gregorian::Monday); }
boost::gregorian::date scheduler::last_tuesday() const { return find_last(boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return find_last(boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::last_thursday() const { return find_last(boost::gregorian::Thursday); }
boost::gregorian::date scheduler::last_friday() const { return find_last(boost::gregorian::Friday); }
boost::gregorian::date scheduler::last_saturday() const { return find_last(boost::gregorian::Saturday); }
boost::gregorian::date scheduler::last_sunday() const { return find_last(boost::gregorian::Sunday); }

}  // namespace meetup
