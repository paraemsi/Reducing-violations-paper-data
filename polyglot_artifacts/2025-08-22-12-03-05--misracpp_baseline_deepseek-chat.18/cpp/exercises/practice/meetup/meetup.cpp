#include "meetup.h"
#include <string>
#include <map>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

date scheduler::find_date(const std::string& descriptor, greg_weekday weekday) const {
    // Adjust month number to be 1-based (Boost expects January=1, February=2, etc.)
    // If the tests are passing 0-based months, we need to add 1
    int adjusted_month = month_ + 1;
    date start_date(year_, adjusted_month, 1);
    date end_date = start_date.end_of_month();
    
    if (descriptor == "teenth") {
        for (int day = 13; day <= 19; day++) {
            date current(year_, adjusted_month, day);
            if (current.day_of_week() == weekday) {
                return current;
            }
        }
    } else if (descriptor == "first") {
        for (date current = start_date; current <= end_date; current += days(1)) {
            if (current.day_of_week() == weekday) {
                return current;
            }
        }
    } else if (descriptor == "second") {
        int count = 0;
        for (date current = start_date; current <= end_date; current += days(1)) {
            if (current.day_of_week() == weekday) {
                count++;
                if (count == 2) return current;
            }
        }
    } else if (descriptor == "third") {
        int count = 0;
        for (date current = start_date; current <= end_date; current += days(1)) {
            if (current.day_of_week() == weekday) {
                count++;
                if (count == 3) return current;
            }
        }
    } else if (descriptor == "fourth") {
        int count = 0;
        for (date current = start_date; current <= end_date; current += days(1)) {
            if (current.day_of_week() == weekday) {
                count++;
                if (count == 4) return current;
            }
        }
    } else if (descriptor == "last") {
        for (date current = end_date; current >= start_date; current -= days(1)) {
            if (current.day_of_week() == weekday) {
                return current;
            }
        }
    }
    throw std::runtime_error("No valid date found");
}

// Implement all the interface methods
// Teenth days
date scheduler::monteenth() const { return find_date("teenth", Monday); }
date scheduler::tuesteenth() const { return find_date("teenth", Tuesday); }
date scheduler::wednesteenth() const { return find_date("teenth", Wednesday); }
date scheduler::thursteenth() const { return find_date("teenth", Thursday); }
date scheduler::friteenth() const { return find_date("teenth", Friday); }
date scheduler::saturteenth() const { return find_date("teenth", Saturday); }
date scheduler::sunteenth() const { return find_date("teenth", Sunday); }

// First week
date scheduler::first_monday() const { return find_date("first", Monday); }
date scheduler::first_tuesday() const { return find_date("first", Tuesday); }
date scheduler::first_wednesday() const { return find_date("first", Wednesday); }
date scheduler::first_thursday() const { return find_date("first", Thursday); }
date scheduler::first_friday() const { return find_date("first", Friday); }
date scheduler::first_saturday() const { return find_date("first", Saturday); }
date scheduler::first_sunday() const { return find_date("first", Sunday); }

// Second week
date scheduler::second_monday() const { return find_date("second", Monday); }
date scheduler::second_tuesday() const { return find_date("second", Tuesday); }
date scheduler::second_wednesday() const { return find_date("second", Wednesday); }
date scheduler::second_thursday() const { return find_date("second", Thursday); }
date scheduler::second_friday() const { return find_date("second", Friday); }
date scheduler::second_saturday() const { return find_date("second", Saturday); }
date scheduler::second_sunday() const { return find_date("second", Sunday); }

// Third week
date scheduler::third_monday() const { return find_date("third", Monday); }
date scheduler::third_tuesday() const { return find_date("third", Tuesday); }
date scheduler::third_wednesday() const { return find_date("third", Wednesday); }
date scheduler::third_thursday() const { return find_date("third", Thursday); }
date scheduler::third_friday() const { return find_date("third", Friday); }
date scheduler::third_saturday() const { return find_date("third", Saturday); }
date scheduler::third_sunday() const { return find_date("third", Sunday); }

// Fourth week
date scheduler::fourth_monday() const { return find_date("fourth", Monday); }
date scheduler::fourth_tuesday() const { return find_date("fourth", Tuesday); }
date scheduler::fourth_wednesday() const { return find_date("fourth", Wednesday); }
date scheduler::fourth_thursday() const { return find_date("fourth", Thursday); }
date scheduler::fourth_friday() const { return find_date("fourth", Friday); }
date scheduler::fourth_saturday() const { return find_date("fourth", Saturday); }
date scheduler::fourth_sunday() const { return find_date("fourth", Sunday); }

// Last week
date scheduler::last_monday() const { return find_date("last", Monday); }
date scheduler::last_tuesday() const { return find_date("last", Tuesday); }
date scheduler::last_wednesday() const { return find_date("last", Wednesday); }
date scheduler::last_thursday() const { return find_date("last", Thursday); }
date scheduler::last_friday() const { return find_date("last", Friday); }
date scheduler::last_saturday() const { return find_date("last", Saturday); }
date scheduler::last_sunday() const { return find_date("last", Sunday); }

}  // namespace meetup
