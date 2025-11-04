#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
#include <map>
#include <string>
#include <vector>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Teenth implementations
boost::gregorian::date scheduler::monteenth() const { return meetup_day("Monday", "teenth"); }
boost::gregorian::date scheduler::tuesteenth() const { return meetup_day("Tuesday", "teenth"); }
boost::gregorian::date scheduler::wednesteenth() const { return meetup_day("Wednesday", "teenth"); }
boost::gregorian::date scheduler::thursteenth() const { return meetup_day("Thursday", "teenth"); }
boost::gregorian::date scheduler::friteenth() const { return meetup_day("Friday", "teenth"); }
boost::gregorian::date scheduler::saturteenth() const { return meetup_day("Saturday", "teenth"); }
boost::gregorian::date scheduler::sunteenth() const { return meetup_day("Sunday", "teenth"); }

// First week implementations
boost::gregorian::date scheduler::first_monday() const { return meetup_day("Monday", "first"); }
boost::gregorian::date scheduler::first_tuesday() const { return meetup_day("Tuesday", "first"); }
boost::gregorian::date scheduler::first_wednesday() const { return meetup_day("Wednesday", "first"); }
boost::gregorian::date scheduler::first_thursday() const { return meetup_day("Thursday", "first"); }
boost::gregorian::date scheduler::first_friday() const { return meetup_day("Friday", "first"); }
boost::gregorian::date scheduler::first_saturday() const { return meetup_day("Saturday", "first"); }
boost::gregorian::date scheduler::first_sunday() const { return meetup_day("Sunday", "first"); }

// Second week implementations
boost::gregorian::date scheduler::second_monday() const { return meetup_day("Monday", "second"); }
boost::gregorian::date scheduler::second_tuesday() const { return meetup_day("Tuesday", "second"); }
boost::gregorian::date scheduler::second_wednesday() const { return meetup_day("Wednesday", "second"); }
boost::gregorian::date scheduler::second_thursday() const { return meetup_day("Thursday", "second"); }
boost::gregorian::date scheduler::second_friday() const { return meetup_day("Friday", "second"); }
boost::gregorian::date scheduler::second_saturday() const { return meetup_day("Saturday", "second"); }
boost::gregorian::date scheduler::second_sunday() const { return meetup_day("Sunday", "second"); }

// Third week implementations
boost::gregorian::date scheduler::third_monday() const { return meetup_day("Monday", "third"); }
boost::gregorian::date scheduler::third_tuesday() const { return meetup_day("Tuesday", "third"); }
boost::gregorian::date scheduler::third_wednesday() const { return meetup_day("Wednesday", "third"); }
boost::gregorian::date scheduler::third_thursday() const { return meetup_day("Thursday", "third"); }
boost::gregorian::date scheduler::third_friday() const { return meetup_day("Friday", "third"); }
boost::gregorian::date scheduler::third_saturday() const { return meetup_day("Saturday", "third"); }
boost::gregorian::date scheduler::third_sunday() const { return meetup_day("Sunday", "third"); }

// Fourth week implementations
boost::gregorian::date scheduler::fourth_monday() const { return meetup_day("Monday", "fourth"); }
boost::gregorian::date scheduler::fourth_tuesday() const { return meetup_day("Tuesday", "fourth"); }
boost::gregorian::date scheduler::fourth_wednesday() const { return meetup_day("Wednesday", "fourth"); }
boost::gregorian::date scheduler::fourth_thursday() const { return meetup_day("Thursday", "fourth"); }
boost::gregorian::date scheduler::fourth_friday() const { return meetup_day("Friday", "fourth"); }
boost::gregorian::date scheduler::fourth_saturday() const { return meetup_day("Saturday", "fourth"); }
boost::gregorian::date scheduler::fourth_sunday() const { return meetup_day("Sunday", "fourth"); }

// Last week implementations
boost::gregorian::date scheduler::last_monday() const { return meetup_day("Monday", "last"); }
boost::gregorian::date scheduler::last_tuesday() const { return meetup_day("Tuesday", "last"); }
boost::gregorian::date scheduler::last_wednesday() const { return meetup_day("Wednesday", "last"); }
boost::gregorian::date scheduler::last_thursday() const { return meetup_day("Thursday", "last"); }
boost::gregorian::date scheduler::last_friday() const { return meetup_day("Friday", "last"); }
boost::gregorian::date scheduler::last_saturday() const { return meetup_day("Saturday", "last"); }
boost::gregorian::date scheduler::last_sunday() const { return meetup_day("Sunday", "last"); }

boost::gregorian::date scheduler::meetup_day(const std::string& weekday, const std::string& which) const {
    // Map weekdays to their corresponding numbers (Sunday=0, Monday=1, etc.)
    static std::map<std::string, int> weekday_map = {
        {"Sunday", 0},
        {"Monday", 1},
        {"Tuesday", 2},
        {"Wednesday", 3},
        {"Thursday", 4},
        {"Friday", 5},
        {"Saturday", 6}
    };
    
    // Get the corresponding weekday number
    auto it = weekday_map.find(weekday);
    if (it == weekday_map.end()) {
        throw std::invalid_argument("Invalid weekday");
    }
    int target_weekday = it->second;
    
    // Start from the first day of the month
    boost::gregorian::date start_date(year_, month_, 1);
    boost::gregorian::date end_date = start_date.end_of_month();
    
    if (which == "teenth") {
        // Check days 13 to 19
        for (int day = 13; day <= 19; ++day) {
            boost::gregorian::date current(year_, month_, day);
            if (current.day_of_week().as_number() == target_weekday) {
                return current;
            }
        }
    } else {
        // Find all occurrences of the target weekday in the month
        std::vector<boost::gregorian::date> occurrences;
        boost::gregorian::date current = start_date;
        while (current <= end_date) {
            if (current.day_of_week().as_number() == target_weekday) {
                occurrences.push_back(current);
            }
            current += boost::gregorian::days(1);
        }
        
        if (which == "first") {
            return occurrences[0];
        } else if (which == "second") {
            return occurrences[1];
        } else if (which == "third") {
            return occurrences[2];
        } else if (which == "fourth") {
            return occurrences[3];
        } else if (which == "last") {
            return occurrences.back();
        } else {
            throw std::invalid_argument("Invalid which");
        }
    }
    
    throw std::runtime_error("No valid date found");
}

}  // namespace meetup
