#include "meetup.h"
#include <map>
#include <string>
#include <stdexcept>
#include <boost/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper function to find the day
boost::gregorian::date scheduler::find_day(const std::string& week, const std::string& weekday) const {
    // Map weekdays to numbers
    std::map<std::string, boost::date_time::weekdays> weekday_map = {
        {"Monday", boost::gregorian::Monday},
        {"Tuesday", boost::gregorian::Tuesday},
        {"Wednesday", boost::gregorian::Wednesday},
        {"Thursday", boost::gregorian::Thursday},
        {"Friday", boost::gregorian::Friday},
        {"Saturday", boost::gregorian::Saturday},
        {"Sunday", boost::gregorian::Sunday}
    };
    
    // Get the first day of the month
    boost::gregorian::date first_day(year_, month_, 1);
    
    // Find the first occurrence of the target weekday
    int day_offset = (weekday_map[weekday] - first_day.day_of_week() + 7) % 7;
    boost::gregorian::date target_day = first_day + boost::gregorian::days(day_offset);
    
    if (week == "first") {
        return target_day;
    } else if (week == "second") {
        return target_day + boost::gregorian::weeks(1);
    } else if (week == "third") {
        return target_day + boost::gregorian::weeks(2);
    } else if (week == "fourth") {
        return target_day + boost::gregorian::weeks(3);
    } else if (week == "last") {
        // Move to the next month and subtract one week to find the last occurrence
        boost::gregorian::date next_month(year_, month_ + 1, 1);
        boost::gregorian::date last_day = next_month - boost::gregorian::days(1);
        // Find the last occurrence by going backwards up to 6 days
        while (last_day.day_of_week() != weekday_map[weekday]) {
            last_day -= boost::gregorian::days(1);
        }
        return last_day;
    } else if (week == "teenth") {
        // Adjust to be in the 13-19 range
        while (target_day.day() < 13) {
            target_day += boost::gregorian::weeks(1);
        }
        return target_day;
    }
    throw std::runtime_error("Invalid week specification");
}

// Implement all the interface functions
#define IMPLEMENT_TEENTH(short_name, full_name) boost::gregorian::date scheduler::short_name##teenth() const { \
    return find_day("teenth", full_name); \
}
IMPLEMENT_TEENTH(mon, "Monday")
IMPLEMENT_TEENTH(tues, "Tuesday")
IMPLEMENT_TEENTH(wednes, "Wednesday")
IMPLEMENT_TEENTH(thur, "Thursday")
IMPLEMENT_TEENTH(fri, "Friday")
IMPLEMENT_TEENTH(satur, "Saturday")
IMPLEMENT_TEENTH(sun, "Sunday")

#define IMPLEMENT_FIRST(day) boost::gregorian::date scheduler::first_##day() const { \
    return find_day("first", #day); \
}
IMPLEMENT_FIRST(Monday)
IMPLEMENT_FIRST(Tuesday)
IMPLEMENT_FIRST(Wednesday)
IMPLEMENT_FIRST(Thursday)
IMPLEMENT_FIRST(Friday)
IMPLEMENT_FIRST(Saturday)
IMPLEMENT_FIRST(Sunday)

#define IMPLEMENT_SECOND(day) boost::gregorian::date scheduler::second_##day() const { \
    return find_day("second", #day); \
}
IMPLEMENT_SECOND(Monday)
IMPLEMENT_SECOND(Tuesday)
IMPLEMENT_SECOND(Wednesday)
IMPLEMENT_SECOND(Thursday)
IMPLEMENT_SECOND(Friday)
IMPLEMENT_SECOND(Saturday)
IMPLEMENT_SECOND(Sunday)

#define IMPLEMENT_THIRD(day) boost::gregorian::date scheduler::third_##day() const { \
    return find_day("third", #day); \
}
IMPLEMENT_THIRD(Monday)
IMPLEMENT_THIRD(Tuesday)
IMPLEMENT_THIRD(Wednesday)
IMPLEMENT_THIRD(Thursday)
IMPLEMENT_THIRD(Friday)
IMPLEMENT_THIRD(Saturday)
IMPLEMENT_THIRD(Sunday)

#define IMPLEMENT_FOURTH(day) boost::gregorian::date scheduler::fourth_##day() const { \
    return find_day("fourth", #day); \
}
IMPLEMENT_FOURTH(Monday)
IMPLEMENT_FOURTH(Tuesday)
IMPLEMENT_FOURTH(Wednesday)
IMPLEMENT_FOURTH(Thursday)
IMPLEMENT_FOURTH(Friday)
IMPLEMENT_FOURTH(Saturday)
IMPLEMENT_FOURTH(Sunday)

#define IMPLEMENT_LAST(day) boost::gregorian::date scheduler::last_##day() const { \
    return find_day("last", #day); \
}
IMPLEMENT_LAST(Monday)
IMPLEMENT_LAST(Tuesday)
IMPLEMENT_LAST(Wednesday)
IMPLEMENT_LAST(Thursday)
IMPLEMENT_LAST(Friday)
IMPLEMENT_LAST(Saturday)
IMPLEMENT_LAST(Sunday)

}  // namespace meetup
