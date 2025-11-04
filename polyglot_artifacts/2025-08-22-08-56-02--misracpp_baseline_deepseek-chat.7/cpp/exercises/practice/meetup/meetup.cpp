#include "meetup.h"
#include <string>
#include <map>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

date scheduler::find_date(int target_dow, const std::string& desc) const {
    date first_day(year_, month_, 1);
    date last_day = first_day.end_of_month();
    
    if (desc == "teenth") {
        for (int day = 13; day <= 19; day++) {
            date current(year_, month_, day);
            if (current.day_of_week() == target_dow) {
                return current;
            }
        }
    } else {
        int week_index;
        if (desc == "first") week_index = 1;
        else if (desc == "second") week_index = 2;
        else if (desc == "third") week_index = 3;
        else if (desc == "fourth") week_index = 4;
        else if (desc == "last") week_index = -1;
        else throw std::invalid_argument("Invalid week description");
        
        if (week_index != -1) {
            int count = 0;
            for (day_iterator it(first_day); it <= last_day; ++it) {
                if (it->day_of_week() == target_dow) {
                    count++;
                    if (count == week_index) {
                        return *it;
                    }
                }
            }
        } else {
            date result;
            for (day_iterator it(first_day); it <= last_day; ++it) {
                if (it->day_of_week() == target_dow) {
                    result = *it;
                }
            }
            return result;
        }
    }
    throw std::runtime_error("No valid date found");
}

// Implement all the methods using find_date
// Teenth days
date scheduler::monteenth() const { return find_date(1, "teenth"); }
date scheduler::tuesteenth() const { return find_date(2, "teenth"); }
date scheduler::wednesteenth() const { return find_date(3, "teenth"); }
date scheduler::thursteenth() const { return find_date(4, "teenth"); }
date scheduler::friteenth() const { return find_date(5, "teenth"); }
date scheduler::saturteenth() const { return find_date(6, "teenth"); }
date scheduler::sunteenth() const { return find_date(0, "teenth"); }

// First week
date scheduler::first_monday() const { return find_date(1, "first"); }
date scheduler::first_tuesday() const { return find_date(2, "first"); }
date scheduler::first_wednesday() const { return find_date(3, "first"); }
date scheduler::first_thursday() const { return find_date(4, "first"); }
date scheduler::first_friday() const { return find_date(5, "first"); }
date scheduler::first_saturday() const { return find_date(6, "first"); }
date scheduler::first_sunday() const { return find_date(0, "first"); }

// Second week
date scheduler::second_monday() const { return find_date(1, "second"); }
date scheduler::second_tuesday() const { return find_date(2, "second"); }
date scheduler::second_wednesday() const { return find_date(3, "second"); }
date scheduler::second_thursday() const { return find_date(4, "second"); }
date scheduler::second_friday() const { return find_date(5, "second"); }
date scheduler::second_saturday() const { return find_date(6, "second"); }
date scheduler::second_sunday() const { return find_date(0, "second"); }

// Third week
date scheduler::third_monday() const { return find_date(1, "third"); }
date scheduler::third_tuesday() const { return find_date(2, "third"); }
date scheduler::third_wednesday() const { return find_date(3, "third"); }
date scheduler::third_thursday() const { return find_date(4, "third"); }
date scheduler::third_friday() const { return find_date(5, "third"); }
date scheduler::third_saturday() const { return find_date(6, "third"); }
date scheduler::third_sunday() const { return find_date(0, "third"); }

// Fourth week
date scheduler::fourth_monday() const { return find_date(1, "fourth"); }
date scheduler::fourth_tuesday() const { return find_date(2, "fourth"); }
date scheduler::fourth_wednesday() const { return find_date(3, "fourth"); }
date scheduler::fourth_thursday() const { return find_date(4, "fourth"); }
date scheduler::fourth_friday() const { return find_date(5, "fourth"); }
date scheduler::fourth_saturday() const { return find_date(6, "fourth"); }
date scheduler::fourth_sunday() const { return find_date(0, "fourth"); }

// Last week
date scheduler::last_monday() const { return find_date(1, "last"); }
date scheduler::last_tuesday() const { return find_date(2, "last"); }
date scheduler::last_wednesday() const { return find_date(3, "last"); }
date scheduler::last_thursday() const { return find_date(4, "last"); }
date scheduler::last_friday() const { return find_date(5, "last"); }
date scheduler::last_saturday() const { return find_date(6, "last"); }
date scheduler::last_sunday() const { return find_date(0, "last"); }

}  // namespace meetup
