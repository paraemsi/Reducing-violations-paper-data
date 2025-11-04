#include "meetup.h"
#include <ctime>
#include <string>
#include <map>
#include <stdexcept>
#include <cstdint>

namespace meetup {

namespace {

std::int32_t weekday_to_int(const std::string& weekday) {
    static const std::map<std::string, std::int32_t> weekday_map = {
        {"Sunday", 0}, {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3},
        {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}
    };
    auto it = weekday_map.find(weekday);
    if (it != weekday_map.end()) {
        return it->second;
    }
    throw std::invalid_argument("Invalid weekday");
}

}  // namespace

scheduler::scheduler(std::int32_t year, std::int32_t month) : year_(year), month_(month) {}

std::int32_t scheduler::find_day(const std::string& week, const std::string& weekday) const {
    // Implementation remains the same as the previous day() function
    std::tm time_in = {};
    time_in.tm_year = static_cast<int>(year_ - 1900);
    time_in.tm_mon = static_cast<int>(month_ - 1);
    time_in.tm_mday = 1;
    time_in.tm_isdst = -1;
    
    std::mktime(&time_in);
    
    std::int32_t first_day_weekday = static_cast<std::int32_t>(time_in.tm_wday);
    std::int32_t target_weekday = weekday_to_int(weekday);
    
    std::int32_t day_delta = (target_weekday - first_day_weekday + 7) % 7;
    std::int32_t first_occurrence = 1 + day_delta;
    
    if (week == "first") {
        return first_occurrence;
    } else if (week == "second") {
        return first_occurrence + 7;
    } else if (week == "third") {
        return first_occurrence + 14;
    } else if (week == "fourth") {
        return first_occurrence + 21;
    } else if (week == "last") {
        std::tm time_temp = time_in;
        time_temp.tm_mon += 1;
        time_temp.tm_mday = 0;
        std::mktime(&time_temp);
        std::int32_t last_day = static_cast<std::int32_t>(time_temp.tm_mday);
        
        std::tm last_time = time_in;
        last_time.tm_mday = static_cast<int>(last_day);
        std::mktime(&last_time);
        std::int32_t last_weekday = static_cast<std::int32_t>(last_time.tm_wday);
        
        std::int32_t offset = (last_weekday - target_weekday + 7) % 7;
        return last_day - offset;
    } else if (week == "teenth") {
        for (std::int32_t day = 13; day <= 19; day++) {
            std::tm time_check = time_in;
            time_check.tm_mday = static_cast<int>(day);
            std::mktime(&time_check);
            if (static_cast<std::int32_t>(time_check.tm_wday) == target_weekday) {
                return day;
            }
        }
    }
    throw std::invalid_argument("Invalid week specification");
}

// Implement all the member functions
#define IMPLEMENT_TEENTH(day_name, weekday_str) \
std::int32_t scheduler::day_name##teenth() const { \
    return find_day("teenth", weekday_str); \
}
IMPLEMENT_TEENTH(mon, "Monday")
IMPLEMENT_TEENTH(tues, "Tuesday")
IMPLEMENT_TEENTH(wednes, "Wednesday")
IMPLEMENT_TEENTH(thurs, "Thursday")
IMPLEMENT_TEENTH(fri, "Friday")
IMPLEMENT_TEENTH(satur, "Saturday")
IMPLEMENT_TEENTH(sun, "Sunday")

#define IMPLEMENT_FIRST(day_name) \
std::int32_t scheduler::first_##day_name() const { \
    return find_day("first", #day_name); \
}
IMPLEMENT_FIRST(monday)
IMPLEMENT_FIRST(tuesday)
IMPLEMENT_FIRST(wednesday)
IMPLEMENT_FIRST(thursday)
IMPLEMENT_FIRST(friday)
IMPLEMENT_FIRST(saturday)
IMPLEMENT_FIRST(sunday)

#define IMPLEMENT_SECOND(day_name) \
std::int32_t scheduler::second_##day_name() const { \
    return find_day("second", #day_name); \
}
IMPLEMENT_SECOND(monday)
IMPLEMENT_SECOND(tuesday)
IMPLEMENT_SECOND(wednesday)
IMPLEMENT_SECOND(thursday)
IMPLEMENT_SECOND(friday)
IMPLEMENT_SECOND(saturday)
IMPLEMENT_SECOND(sunday)

#define IMPLEMENT_THIRD(day_name) \
std::int32_t scheduler::third_##day_name() const { \
    return find_day("third", #day_name); \
}
IMPLEMENT_THIRD(monday)
IMPLEMENT_THIRD(tuesday)
IMPLEMENT_THIRD(wednesday)
IMPLEMENT_THIRD(thursday)
IMPLEMENT_THIRD(friday)
IMPLEMENT_THIRD(saturday)
IMPLEMENT_THIRD(sunday)

#define IMPLEMENT_FOURTH(day_name) \
std::int32_t scheduler::fourth_##day_name() const { \
    return find_day("fourth", #day_name); \
}
IMPLEMENT_FOURTH(monday)
IMPLEMENT_FOURTH(tuesday)
IMPLEMENT_FOURTH(wednesday)
IMPLEMENT_FOURTH(thursday)
IMPLEMENT_FOURTH(friday)
IMPLEMENT_FOURTH(saturday)
IMPLEMENT_FOURTH(sunday)

#define IMPLEMENT_LAST(day_name) \
std::int32_t scheduler::last_##day_name() const { \
    return find_day("last", #day_name); \
}
IMPLEMENT_LAST(monday)
IMPLEMENT_LAST(tuesday)
IMPLEMENT_LAST(wednesday)
IMPLEMENT_LAST(thursday)
IMPLEMENT_LAST(friday)
IMPLEMENT_LAST(saturday)
IMPLEMENT_LAST(sunday)

}  // namespace meetup
