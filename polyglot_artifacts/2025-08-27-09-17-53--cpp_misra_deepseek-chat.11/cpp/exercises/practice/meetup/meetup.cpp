#include "meetup.h"
#include <map>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace meetup {

namespace greg = boost::gregorian;

scheduler::scheduler(std::int32_t year, std::int32_t month) : year_(year), month_(month) {}

// Helper functions
greg::date scheduler::find_nth_weekday(int nth, greg::greg_weekday weekday) const {
    // Start from the first day of the month
    greg::date current(year_, month_, 1);
    
    // Find the first occurrence of the desired weekday
    while (current.day_of_week() != weekday) {
        current = current + greg::date_duration(1);
    }
    
    // Add weeks to get to the nth occurrence
    return current + greg::date_duration((nth - 1) * 7);
}

greg::date scheduler::find_teenth(greg::greg_weekday weekday) const {
    for (std::int32_t day = 13; day <= 19; ++day) {
        greg::date current(year_, month_, day);
        if (current.day_of_week() == weekday) {
            return current;
        }
    }
    throw std::runtime_error("Teenth day not found");
}

greg::date scheduler::find_last(greg::greg_weekday weekday) const {
    greg::date last_day = greg::date(year_, month_, 1).end_of_month();
    while (last_day.day_of_week() != weekday) {
        last_day = last_day - greg::date_duration(1);
    }
    return last_day;
}

// Teenth days
greg::date scheduler::monteenth() const { return find_teenth(greg::Monday); }
greg::date scheduler::tuesteenth() const { return find_teenth(greg::Tuesday); }
greg::date scheduler::wednesteenth() const { return find_teenth(greg::Wednesday); }
greg::date scheduler::thursteenth() const { return find_teenth(greg::Thursday); }
greg::date scheduler::friteenth() const { return find_teenth(greg::Friday); }
greg::date scheduler::saturteenth() const { return find_teenth(greg::Saturday); }
greg::date scheduler::sunteenth() const { return find_teenth(greg::Sunday); }

// First days
greg::date scheduler::first_monday() const { return find_nth_weekday(1, greg::Monday); }
greg::date scheduler::first_tuesday() const { return find_nth_weekday(1, greg::Tuesday); }
greg::date scheduler::first_wednesday() const { return find_nth_weekday(1, greg::Wednesday); }
greg::date scheduler::first_thursday() const { return find_nth_weekday(1, greg::Thursday); }
greg::date scheduler::first_friday() const { return find_nth_weekday(1, greg::Friday); }
greg::date scheduler::first_saturday() const { return find_nth_weekday(1, greg::Saturday); }
greg::date scheduler::first_sunday() const { return find_nth_weekday(1, greg::Sunday); }

// Second days
greg::date scheduler::second_monday() const { return find_nth_weekday(2, greg::Monday); }
greg::date scheduler::second_tuesday() const { return find_nth_weekday(2, greg::Tuesday); }
greg::date scheduler::second_wednesday() const { return find_nth_weekday(2, greg::Wednesday); }
greg::date scheduler::second_thursday() const { return find_nth_weekday(2, greg::Thursday); }
greg::date scheduler::second_friday() const { return find_nth_weekday(2, greg::Friday); }
greg::date scheduler::second_saturday() const { return find_nth_weekday(2, greg::Saturday); }
greg::date scheduler::second_sunday() const { return find_nth_weekday(2, greg::Sunday); }

// Third days
greg::date scheduler::third_monday() const { return find_nth_weekday(3, greg::Monday); }
greg::date scheduler::third_tuesday() const { return find_nth_weekday(3, greg::Tuesday); }
greg::date scheduler::third_wednesday() const { return find_nth_weekday(3, greg::Wednesday); }
greg::date scheduler::third_thursday() const { return find_nth_weekday(3, greg::Thursday); }
greg::date scheduler::third_friday() const { return find_nth_weekday(3, greg::Friday); }
greg::date scheduler::third_saturday() const { return find_nth_weekday(3, greg::Saturday); }
greg::date scheduler::third_sunday() const { return find_nth_weekday(3, greg::Sunday); }

// Fourth days
greg::date scheduler::fourth_monday() const { return find_nth_weekday(4, greg::Monday); }
greg::date scheduler::fourth_tuesday() const { return find_nth_weekday(4, greg::Tuesday); }
greg::date scheduler::fourth_wednesday() const { return find_nth_weekday(4, greg::Wednesday); }
greg::date scheduler::fourth_thursday() const { return find_nth_weekday(4, greg::Thursday); }
greg::date scheduler::fourth_friday() const { return find_nth_weekday(4, greg::Friday); }
greg::date scheduler::fourth_saturday() const { return find_nth_weekday(4, greg::Saturday); }
greg::date scheduler::fourth_sunday() const { return find_nth_weekday(4, greg::Sunday); }

// Last days
greg::date scheduler::last_monday() const { return find_last(greg::Monday); }
greg::date scheduler::last_tuesday() const { return find_last(greg::Tuesday); }
greg::date scheduler::last_wednesday() const { return find_last(greg::Wednesday); }
greg::date scheduler::last_thursday() const { return find_last(greg::Thursday); }
greg::date scheduler::last_friday() const { return find_last(greg::Friday); }
greg::date scheduler::last_saturday() const { return find_last(greg::Saturday); }
greg::date scheduler::last_sunday() const { return find_last(greg::Sunday); }

}  // namespace meetup
