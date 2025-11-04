#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <map>
#include <stdexcept>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

namespace {

boost::gregorian::greg_weekday weekday_to_boost(const std::string& weekday) {
    static const std::map<std::string, boost::gregorian::greg_weekday> weekday_map = {
        {"Monday", boost::gregorian::Monday},
        {"Tuesday", boost::gregorian::Tuesday},
        {"Wednesday", boost::gregorian::Wednesday},
        {"Thursday", boost::gregorian::Thursday},
        {"Friday", boost::gregorian::Friday},
        {"Saturday", boost::gregorian::Saturday},
        {"Sunday", boost::gregorian::Sunday}
    };
    return weekday_map.at(weekday);
}

}  // namespace

boost::gregorian::date scheduler::find_date(const std::string& week, int target_weekday_int) const {
    // Convert target_weekday_int to boost's weekday
    // Since we're passing an int, and the implementation uses the old approach, let's be consistent
    // But to use boost's comparison, we need to use the same type
    // Let's use the integer approach but make sure it matches boost's day_of_week() which returns a number where:
    // Sunday=0, Monday=1, ..., Saturday=6
    if (week == "teenth") {
        for (int day = 13; day <= 19; ++day) {
            boost::gregorian::date d(year_, month_, day);
            if (d.day_of_week() == target_weekday_int) {
                return d;
            }
        }
    } else {
        int count = 0;
        boost::gregorian::date last_found;
        
        // Iterate through all days of the month
        boost::gregorian::date start(year_, month_, 1);
        boost::gregorian::date end = start.end_of_month();
        for (boost::gregorian::day_iterator it(start); it <= end; ++it) {
            if (it->day_of_week() == target_weekday_int) {
                ++count;
                last_found = *it;
                if (week == "first" && count == 1) {
                    return *it;
                } else if (week == "second" && count == 2) {
                    return *it;
                } else if (week == "third" && count == 3) {
                    return *it;
                } else if (week == "fourth" && count == 4) {
                    return *it;
                }
            }
        }
        if (week == "last") {
            return last_found;
        }
    }
    throw std::runtime_error("Date not found");
}

// Implement all the member functions
#define IMPLEMENT_TEENTH(day_name, weekday_str) \
boost::gregorian::date scheduler::day_name##teenth() const { \
    static const std::map<std::string, int> weekday_int_map = { \
        {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}, {"Thursday", 4}, \
        {"Friday", 5}, {"Saturday", 6}, {"Sunday", 0} \
    }; \
    return find_date("teenth", weekday_int_map.at(weekday_str)); \
}

IMPLEMENT_TEENTH(mon, "Monday")
IMPLEMENT_TEENTH(tues, "Tuesday")
IMPLEMENT_TEENTH(wednes, "Wednesday")
IMPLEMENT_TEENTH(thurs, "Thursday")
IMPLEMENT_TEENTH(fri, "Friday")
IMPLEMENT_TEENTH(satur, "Saturday")
IMPLEMENT_TEENTH(sun, "Sunday")

#define IMPLEMENT_WEEK(prefix, day_name, weekday_str, week_str) \
boost::gregorian::date scheduler::prefix##_##day_name() const { \
    static const std::map<std::string, int> weekday_int_map = { \
        {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3}, {"Thursday", 4}, \
        {"Friday", 5}, {"Saturday", 6}, {"Sunday", 0} \
    }; \
    return find_date(week_str, weekday_int_map.at(weekday_str)); \
}

#define IMPLEMENT_ALL_WEEKS(day_name, weekday_str) \
IMPLEMENT_WEEK(first, day_name, weekday_str, "first") \
IMPLEMENT_WEEK(second, day_name, weekday_str, "second") \
IMPLEMENT_WEEK(third, day_name, weekday_str, "third") \
IMPLEMENT_WEEK(fourth, day_name, weekday_str, "fourth") \
IMPLEMENT_WEEK(last, day_name, weekday_str, "last")

IMPLEMENT_ALL_WEEKS(monday, "Monday")
IMPLEMENT_ALL_WEEKS(tuesday, "Tuesday")
IMPLEMENT_ALL_WEEKS(wednesday, "Wednesday")
IMPLEMENT_ALL_WEEKS(thursday, "Thursday")
IMPLEMENT_ALL_WEEKS(friday, "Friday")
IMPLEMENT_ALL_WEEKS(saturday, "Saturday")
IMPLEMENT_ALL_WEEKS(sunday, "Sunday")

}  // namespace meetup
