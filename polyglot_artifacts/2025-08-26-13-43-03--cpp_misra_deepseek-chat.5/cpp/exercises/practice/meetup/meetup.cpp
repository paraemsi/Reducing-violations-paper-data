#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>
#include <cstdint>

namespace meetup {

scheduler::scheduler(std::int32_t year, std::int32_t month) : year_(year), month_(month) {}

boost::gregorian::date scheduler::find_day(const std::string& weekday, const std::string& week) const {
    // Map weekday names to their corresponding numbers
    std::map<std::string, std::int32_t> weekday_map = {
        {"Monday", 1},
        {"Tuesday", 2},
        {"Wednesday", 3},
        {"Thursday", 4},
        {"Friday", 5},
        {"Saturday", 6},
        {"Sunday", 0}
    };
    
    std::int32_t target_weekday = weekday_map.at(weekday);
    
    // Start from the first day of the month
    boost::gregorian::date start_date(year_, month_, 1);
    boost::gregorian::date end_date = start_date.end_of_month();
    
    // Generate all dates that match the desired weekday
    std::vector<boost::gregorian::date> matching_days;
    for (boost::gregorian::day_iterator iter(start_date); *iter <= end_date; ++iter) {
        if (iter->day_of_week().as_number() == target_weekday) {
            matching_days.push_back(*iter);
        }
    }
    
    // Determine which date to pick based on the week specification
    if (week == "first") {
        return matching_days[0];
    } else if (week == "second") {
        return matching_days[1];
    } else if (week == "third") {
        return matching_days[2];
    } else if (week == "fourth") {
        return matching_days[3];
    } else if (week == "last") {
        return matching_days.back();
    } else if (week == "teenth") {
        for (const auto& date : matching_days) {
            std::int32_t day = date.day();
            if ((day >= 13) && (day <= 19)) {
                return date;
            }
        }
    }
    throw std::runtime_error("Invalid week specification");
}

// Implement all the interface functions
// Map teenth day parts to full day names
#define IMPLEMENT_TEENTH(day_part, full_day) \
    boost::gregorian::date scheduler::day_part##teenth() const { \
        return find_day(full_day, "teenth"); \
    }
    
#define IMPLEMENT_FIRST(day) \
    boost::gregorian::date scheduler::first_##day() const { \
        return find_day(#day, "first"); \
    }
    
#define IMPLEMENT_SECOND(day) \
    boost::gregorian::date scheduler::second_##day() const { \
        return find_day(#day, "second"); \
    }
    
#define IMPLEMENT_THIRD(day) \
    boost::gregorian::date scheduler::third_##day() const { \
        return find_day(#day, "third"); \
    }
    
#define IMPLEMENT_FOURTH(day) \
    boost::gregorian::date scheduler::fourth_##day() const { \
        return find_day(#day, "fourth"); \
    }
    
#define IMPLEMENT_LAST(day) \
    boost::gregorian::date scheduler::last_##day() const { \
        return find_day(#day, "last"); \
    }

// Note: Adjust day names to match the function names
// For teenth functions, we need to map to the correct weekday names
IMPLEMENT_TEENTH(mon, "Monday")      // maps to "mon" -> should be "Monday"
IMPLEMENT_TEENTH(tues, "Tuesday")     // maps to "tues" -> should be "Tuesday"
IMPLEMENT_TEENTH(wednes, "Wednesday")   // maps to "wednes" -> should be "Wednesday"
IMPLEMENT_TEENTH(thurs, "Thursday")    // maps to "thurs" -> should be "Thursday"
IMPLEMENT_TEENTH(fri, "Friday")      // maps to "fri" -> should be "Friday"
IMPLEMENT_TEENTH(satur, "Saturday")    // maps to "satur" -> should be "Saturday"
IMPLEMENT_TEENTH(sun, "Sunday")      // maps to "sun" -> should be "Sunday"

IMPLEMENT_FIRST(monday)
IMPLEMENT_FIRST(tuesday)
IMPLEMENT_FIRST(wednesday)
IMPLEMENT_FIRST(thursday)
IMPLEMENT_FIRST(friday)
IMPLEMENT_FIRST(saturday)
IMPLEMENT_FIRST(sunday)

IMPLEMENT_SECOND(monday)
IMPLEMENT_SECOND(tuesday)
IMPLEMENT_SECOND(wednesday)
IMPLEMENT_SECOND(thursday)
IMPLEMENT_SECOND(friday)
IMPLEMENT_SECOND(saturday)
IMPLEMENT_SECOND(sunday)

IMPLEMENT_THIRD(monday)
IMPLEMENT_THIRD(tuesday)
IMPLEMENT_THIRD(wednesday)
IMPLEMENT_THIRD(thursday)
IMPLEMENT_THIRD(friday)
IMPLEMENT_THIRD(saturday)
IMPLEMENT_THIRD(sunday)

IMPLEMENT_FOURTH(monday)
IMPLEMENT_FOURTH(tuesday)
IMPLEMENT_FOURTH(wednesday)
IMPLEMENT_FOURTH(thursday)
IMPLEMENT_FOURTH(friday)
IMPLEMENT_FOURTH(saturday)
IMPLEMENT_FOURTH(sunday)

IMPLEMENT_LAST(monday)
IMPLEMENT_LAST(tuesday)
IMPLEMENT_LAST(wednesday)
IMPLEMENT_LAST(thursday)
IMPLEMENT_LAST(friday)
IMPLEMENT_LAST(saturday)
IMPLEMENT_LAST(sunday)

}  // namespace meetup
