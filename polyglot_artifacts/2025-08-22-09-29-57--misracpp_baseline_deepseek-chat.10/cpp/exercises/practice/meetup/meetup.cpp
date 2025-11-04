#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <stdexcept>
#include <map>

using namespace boost::gregorian;

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Teenth implementations
date scheduler::monteenth() const { return find_date("teenth", 1); }
date scheduler::tuesteenth() const { return find_date("teenth", 2); }
date scheduler::wednesteenth() const { return find_date("teenth", 3); }
date scheduler::thursteenth() const { return find_date("teenth", 4); }
date scheduler::friteenth() const { return find_date("teenth", 5); }
date scheduler::saturteenth() const { return find_date("teenth", 6); }
date scheduler::sunteenth() const { return find_date("teenth", 0); }

// First week
date scheduler::first_monday() const { return find_date("first", 1); }
date scheduler::first_tuesday() const { return find_date("first", 2); }
date scheduler::first_wednesday() const { return find_date("first", 3); }
date scheduler::first_thursday() const { return find_date("first", 4); }
date scheduler::first_friday() const { return find_date("first", 5); }
date scheduler::first_saturday() const { return find_date("first", 6); }
date scheduler::first_sunday() const { return find_date("first", 0); }

// Second week
date scheduler::second_monday() const { return find_date("second", 1); }
date scheduler::second_tuesday() const { return find_date("second", 2); }
date scheduler::second_wednesday() const { return find_date("second", 3); }
date scheduler::second_thursday() const { return find_date("second", 4); }
date scheduler::second_friday() const { return find_date("second", 5); }
date scheduler::second_saturday() const { return find_date("second", 6); }
date scheduler::second_sunday() const { return find_date("second", 0); }

// Third week
date scheduler::third_monday() const { return find_date("third", 1); }
date scheduler::third_tuesday() const { return find_date("third", 2); }
date scheduler::third_wednesday() const { return find_date("third", 3); }
date scheduler::third_thursday() const { return find_date("third", 4); }
date scheduler::third_friday() const { return find_date("third", 5); }
date scheduler::third_saturday() const { return find_date("third", 6); }
date scheduler::third_sunday() const { return find_date("third", 0); }

// Fourth week
date scheduler::fourth_monday() const { return find_date("fourth", 1); }
date scheduler::fourth_tuesday() const { return find_date("fourth", 2); }
date scheduler::fourth_wednesday() const { return find_date("fourth", 3); }
date scheduler::fourth_thursday() const { return find_date("fourth", 4); }
date scheduler::fourth_friday() const { return find_date("fourth", 5); }
date scheduler::fourth_saturday() const { return find_date("fourth", 6); }
date scheduler::fourth_sunday() const { return find_date("fourth", 0); }

// Last week
date scheduler::last_monday() const { return find_date("last", 1); }
date scheduler::last_tuesday() const { return find_date("last", 2); }
date scheduler::last_wednesday() const { return find_date("last", 3); }
date scheduler::last_thursday() const { return find_date("last", 4); }
date scheduler::last_friday() const { return find_date("last", 5); }
date scheduler::last_saturday() const { return find_date("last", 6); }
date scheduler::last_sunday() const { return find_date("last", 0); }

date scheduler::find_date(const std::string& week, int weekday) const {
    if (week == "teenth") {
        for (int day = 13; day <= 19; ++day) {
            date candidate(year_, month_, day);
            if (candidate.day_of_week().as_number() == weekday) {
                return candidate;
            }
        }
    } else if (week == "first" || week == "second" || week == "third" || week == "fourth") {
        // Start from the first day of the month
        date start(year_, month_, 1);
        // Find the first occurrence of the desired weekday
        int start_dow = start.day_of_week().as_number();
        int offset = (weekday - start_dow + 7) % 7;
        date first_occurrence = start + days(offset);
        
        // Add weeks based on which occurrence we want
        int week_index;
        if (week == "first") week_index = 0;
        else if (week == "second") week_index = 1;
        else if (week == "third") week_index = 2;
        else if (week == "fourth") week_index = 3;
        
        date result = first_occurrence + weeks(week_index);
        // Make sure we're still in the same month
        if (result.month() != month_) {
            throw std::runtime_error("Date not found in month");
        }
        return result;
    } else if (week == "last") {
        // Start from the last day of the month and work backwards
        date end(year_, month_, 1);
        end = end.end_of_month();
        for (int i = 0; i < 7; ++i) {
            date candidate = end - days(i);
            if (candidate.day_of_week().as_number() == weekday) {
                return candidate;
            }
        }
    }
    throw std::runtime_error("Date not found");
}

}  // namespace meetup
