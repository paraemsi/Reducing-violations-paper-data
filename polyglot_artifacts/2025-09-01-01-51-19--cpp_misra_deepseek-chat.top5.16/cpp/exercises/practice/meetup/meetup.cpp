#include "meetup.h"
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

scheduler::scheduler(std::int32_t year, std::int32_t month) : year_(year), month_(month) {
}

// Helper functions
boost::gregorian::date scheduler::find_nth_weekday(std::int32_t n, boost::gregorian::greg_weekday weekday) const {
    // Start from the first day of the month
    boost::gregorian::date first_day(year_, month_, 1);
    
    // Find the first occurrence of the target weekday
    // The difference can be negative, so we need to handle that
    int diff = (weekday - first_day.day_of_week()).as_number();
    if (diff < 0) {
        diff += 7;
    }
    
    // Add the appropriate number of weeks
    boost::gregorian::date result = first_day + boost::gregorian::days(diff + (n - 1) * 7);
    
    // Check if the result is still in the same month
    if (result.month() != month_) {
        throw std::runtime_error("Date not found in the specified month");
    }
    return result;
}

boost::gregorian::date scheduler::find_teenth(boost::gregorian::greg_weekday weekday) const {
    for (std::int32_t day = 13; day <= 19; ++day) {
        boost::gregorian::date current(year_, month_, day);
        if (current.day_of_week() == weekday) {
            return current;
        }
    }
    throw std::runtime_error("Teenth day not found");
}

boost::gregorian::date scheduler::find_last(boost::gregorian::greg_weekday weekday) const {
    // Get the last day of the month
    boost::gregorian::date last_day = boost::gregorian::date(year_, month_, 1).end_of_month();
    
    // Find the difference to reach the desired weekday
    int diff = (last_day.day_of_week() - weekday).as_number();
    if (diff < 0) {
        diff += 7;
    }
    
    // Subtract to find the last occurrence
    boost::gregorian::date result = last_day - boost::gregorian::days(diff);
    
    // Ensure the result is in the same month
    if (result.month() != month_) {
        throw std::runtime_error("Last weekday not found in the specified month");
    }
    return result;
}

// Teenth days
boost::gregorian::date scheduler::monteenth() const { return find_teenth(boost::gregorian::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return find_teenth(boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return find_teenth(boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return find_teenth(boost::gregorian::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return find_teenth(boost::gregorian::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return find_teenth(boost::gregorian::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return find_teenth(boost::gregorian::Sunday); }

// First week days
boost::gregorian::date scheduler::first_monday() const { return find_nth_weekday(1, boost::gregorian::Monday); }
boost::gregorian::date scheduler::first_tuesday() const { return find_nth_weekday(1, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::first_wednesday() const { return find_nth_weekday(1, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::first_thursday() const { return find_nth_weekday(1, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::first_friday() const { return find_nth_weekday(1, boost::gregorian::Friday); }
boost::gregorian::date scheduler::first_saturday() const { return find_nth_weekday(1, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::first_sunday() const { return find_nth_weekday(1, boost::gregorian::Sunday); }

// Second week days
boost::gregorian::date scheduler::second_monday() const { return find_nth_weekday(2, boost::gregorian::Monday); }
boost::gregorian::date scheduler::second_tuesday() const { return find_nth_weekday(2, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::second_wednesday() const { return find_nth_weekday(2, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::second_thursday() const { return find_nth_weekday(2, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::second_friday() const { return find_nth_weekday(2, boost::gregorian::Friday); }
boost::gregorian::date scheduler::second_saturday() const { return find_nth_weekday(2, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::second_sunday() const { return find_nth_weekday(2, boost::gregorian::Sunday); }

// Third week days
boost::gregorian::date scheduler::third_monday() const { return find_nth_weekday(3, boost::gregorian::Monday); }
boost::gregorian::date scheduler::third_tuesday() const { return find_nth_weekday(3, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::third_wednesday() const { return find_nth_weekday(3, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::third_thursday() const { return find_nth_weekday(3, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::third_friday() const { return find_nth_weekday(3, boost::gregorian::Friday); }
boost::gregorian::date scheduler::third_saturday() const { return find_nth_weekday(3, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::third_sunday() const { return find_nth_weekday(3, boost::gregorian::Sunday); }

// Fourth week days
boost::gregorian::date scheduler::fourth_monday() const { return find_nth_weekday(4, boost::gregorian::Monday); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_nth_weekday(4, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_nth_weekday(4, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_nth_weekday(4, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::fourth_friday() const { return find_nth_weekday(4, boost::gregorian::Friday); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_nth_weekday(4, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_nth_weekday(4, boost::gregorian::Sunday); }

// Last week days
boost::gregorian::date scheduler::last_monday() const { return find_last(boost::gregorian::Monday); }
boost::gregorian::date scheduler::last_tuesday() const { return find_last(boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return find_last(boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::last_thursday() const { return find_last(boost::gregorian::Thursday); }
boost::gregorian::date scheduler::last_friday() const { return find_last(boost::gregorian::Friday); }
boost::gregorian::date scheduler::last_saturday() const { return find_last(boost::gregorian::Saturday); }
boost::gregorian::date scheduler::last_sunday() const { return find_last(boost::gregorian::Sunday); }

}  // namespace meetup
