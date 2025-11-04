#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(int month, int year) : month_(month), year_(year) {}

boost::gregorian::date scheduler::find_nth_weekday(int nth, boost::gregorian::greg_weekday weekday) const {
    // Start from the first day of the month
    boost::gregorian::date first_of_month(year_, month_, 1);
    
    // Find the first occurrence of the target weekday
    int days_to_add = (weekday.as_number() - first_of_month.day_of_week().as_number() + 7) % 7;
    boost::gregorian::date first_occurrence = first_of_month + boost::gregorian::days(days_to_add);
    
    // Add weeks to reach the desired occurrence
    return first_occurrence + boost::gregorian::weeks(nth - 1);
}

boost::gregorian::date scheduler::find_teenth(boost::gregorian::greg_weekday weekday) const {
    // Check each day from 13 to 19
    for (int day = 13; day <= 19; day++) {
        boost::gregorian::date candidate(year_, month_, day);
        if (candidate.day_of_week() == weekday) {
            return candidate;
        }
    }
    throw std::runtime_error("No teenth found");
}

boost::gregorian::date scheduler::find_last(boost::gregorian::greg_weekday weekday) const {
    // Start from the last day of the month
    boost::gregorian::date last_of_month = boost::gregorian::date(year_, month_, 1).end_of_month();
    
    // Find the last occurrence by working backwards
    int days_to_subtract = (last_of_month.day_of_week().as_number() - weekday.as_number() + 7) % 7;
    return last_of_month - boost::gregorian::days(days_to_subtract);
}

// Implement all the member functions
// For teenth functions, we need to map to the correct Boost weekdays
boost::gregorian::date scheduler::monteenth() const { 
    return find_teenth(boost::gregorian::Monday); 
}
boost::gregorian::date scheduler::tuesteenth() const { 
    return find_teenth(boost::gregorian::Tuesday); 
}
boost::gregorian::date scheduler::wednesteenth() const { 
    return find_teenth(boost::gregorian::Wednesday); 
}
boost::gregorian::date scheduler::thursteenth() const { 
    return find_teenth(boost::gregorian::Thursday); 
}
boost::gregorian::date scheduler::friteenth() const { 
    return find_teenth(boost::gregorian::Friday); 
}
boost::gregorian::date scheduler::saturteenth() const { 
    return find_teenth(boost::gregorian::Saturday); 
}
boost::gregorian::date scheduler::sunteenth() const { 
    return find_teenth(boost::gregorian::Sunday); 
}

// First week functions
boost::gregorian::date scheduler::first_monday() const { 
    return find_nth_weekday(1, boost::gregorian::Monday); 
}
boost::gregorian::date scheduler::first_tuesday() const { 
    return find_nth_weekday(1, boost::gregorian::Tuesday); 
}
boost::gregorian::date scheduler::first_wednesday() const { 
    return find_nth_weekday(1, boost::gregorian::Wednesday); 
}
boost::gregorian::date scheduler::first_thursday() const { 
    return find_nth_weekday(1, boost::gregorian::Thursday); 
}
boost::gregorian::date scheduler::first_friday() const { 
    return find_nth_weekday(1, boost::gregorian::Friday); 
}
boost::gregorian::date scheduler::first_saturday() const { 
    return find_nth_weekday(1, boost::gregorian::Saturday); 
}
boost::gregorian::date scheduler::first_sunday() const { 
    return find_nth_weekday(1, boost::gregorian::Sunday); 
}

// Second week functions
boost::gregorian::date scheduler::second_monday() const { 
    return find_nth_weekday(2, boost::gregorian::Monday); 
}
boost::gregorian::date scheduler::second_tuesday() const { 
    return find_nth_weekday(2, boost::gregorian::Tuesday); 
}
boost::gregorian::date scheduler::second_wednesday() const { 
    return find_nth_weekday(2, boost::gregorian::Wednesday); 
}
boost::gregorian::date scheduler::second_thursday() const { 
    return find_nth_weekday(2, boost::gregorian::Thursday); 
}
boost::gregorian::date scheduler::second_friday() const { 
    return find_nth_weekday(2, boost::gregorian::Friday); 
}
boost::gregorian::date scheduler::second_saturday() const { 
    return find_nth_weekday(2, boost::gregorian::Saturday); 
}
boost::gregorian::date scheduler::second_sunday() const { 
    return find_nth_weekday(2, boost::gregorian::Sunday); 
}

// Third week functions
boost::gregorian::date scheduler::third_monday() const { 
    return find_nth_weekday(3, boost::gregorian::Monday); 
}
boost::gregorian::date scheduler::third_tuesday() const { 
    return find_nth_weekday(3, boost::gregorian::Tuesday); 
}
boost::gregorian::date scheduler::third_wednesday() const { 
    return find_nth_weekday(3, boost::gregorian::Wednesday); 
}
boost::gregorian::date scheduler::third_thursday() const { 
    return find_nth_weekday(3, boost::gregorian::Thursday); 
}
boost::gregorian::date scheduler::third_friday() const { 
    return find_nth_weekday(3, boost::gregorian::Friday); 
}
boost::gregorian::date scheduler::third_saturday() const { 
    return find_nth_weekday(3, boost::gregorian::Saturday); 
}
boost::gregorian::date scheduler::third_sunday() const { 
    return find_nth_weekday(3, boost::gregorian::Sunday); 
}

// Fourth week functions
boost::gregorian::date scheduler::fourth_monday() const { 
    return find_nth_weekday(4, boost::gregorian::Monday); 
}
boost::gregorian::date scheduler::fourth_tuesday() const { 
    return find_nth_weekday(4, boost::gregorian::Tuesday); 
}
boost::gregorian::date scheduler::fourth_wednesday() const { 
    return find_nth_weekday(4, boost::gregorian::Wednesday); 
}
boost::gregorian::date scheduler::fourth_thursday() const { 
    return find_nth_weekday(4, boost::gregorian::Thursday); 
}
boost::gregorian::date scheduler::fourth_friday() const { 
    return find_nth_weekday(4, boost::gregorian::Friday); 
}
boost::gregorian::date scheduler::fourth_saturday() const { 
    return find_nth_weekday(4, boost::gregorian::Saturday); 
}
boost::gregorian::date scheduler::fourth_sunday() const { 
    return find_nth_weekday(4, boost::gregorian::Sunday); 
}

// Last week functions
boost::gregorian::date scheduler::last_monday() const { 
    return find_last(boost::gregorian::Monday); 
}
boost::gregorian::date scheduler::last_tuesday() const { 
    return find_last(boost::gregorian::Tuesday); 
}
boost::gregorian::date scheduler::last_wednesday() const { 
    return find_last(boost::gregorian::Wednesday); 
}
boost::gregorian::date scheduler::last_thursday() const { 
    return find_last(boost::gregorian::Thursday); 
}
boost::gregorian::date scheduler::last_friday() const { 
    return find_last(boost::gregorian::Friday); 
}
boost::gregorian::date scheduler::last_saturday() const { 
    return find_last(boost::gregorian::Saturday); 
}
boost::gregorian::date scheduler::last_sunday() const { 
    return find_last(boost::gregorian::Sunday); 
}

}  // namespace meetup
