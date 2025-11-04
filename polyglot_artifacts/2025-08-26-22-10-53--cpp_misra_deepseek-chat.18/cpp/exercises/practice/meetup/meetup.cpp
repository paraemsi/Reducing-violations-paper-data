#include "meetup.h"
#include <string>
#include <map>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

namespace bg = boost::gregorian;

scheduler::scheduler(std::int32_t month, std::int32_t year) : month_(month), year_(year) {}

// Helper function to find a date given week and weekday
bg::date scheduler::find_date(const std::string& week, const std::string& weekday) const {
    std::map<std::string, bg::greg_weekday> weekday_map = {
        {"Monday", bg::Monday},
        {"Tuesday", bg::Tuesday},
        {"Wednesday", bg::Wednesday},
        {"Thursday", bg::Thursday},
        {"Friday", bg::Friday},
        {"Saturday", bg::Saturday},
        {"Sunday", bg::Sunday}
    };
    
    bg::greg_weekday target_weekday = weekday_map.at(weekday);
    
    if (week == "last") {
        bg::date last_day(year_, month_, bg::gregorian_calendar::end_of_month_day(year_, month_));
        while (last_day.day_of_week() != target_weekday) {
            last_day -= bg::days(1);
        }
        return last_day;
    }
    
    std::int32_t start_day;
    std::int32_t end_day;
    if (week == "first") {
        start_day = 1;
        end_day = 7;
    } else if (week == "second") {
        start_day = 8;
        end_day = 14;
    } else if (week == "third") {
        start_day = 15;
        end_day = 21;
    } else if (week == "fourth") {
        start_day = 22;
        end_day = 28;
    } else if (week == "teenth") {
        start_day = 13;
        end_day = 19;
    } else {
        throw std::invalid_argument("Invalid week specification");
    }
    
    for (std::int32_t day = start_day; day <= end_day; day++) {
        try {
            bg::date current_date(year_, month_, day);
            if (current_date.day_of_week() == target_weekday) {
                return current_date;
            }
        } catch (...) {
            continue;
        }
    }
    throw std::runtime_error("No matching date found");
}

// Implement all the member functions
// For teenth functions, the names are slightly different from the pattern
bg::date scheduler::monteenth() const { return find_date("teenth", "Monday"); }
bg::date scheduler::tuesteenth() const { return find_date("teenth", "Tuesday"); }
bg::date scheduler::wednesteenth() const { return find_date("teenth", "Wednesday"); }
bg::date scheduler::thursteenth() const { return find_date("teenth", "Thursday"); }
bg::date scheduler::friteenth() const { return find_date("teenth", "Friday"); }
bg::date scheduler::saturteenth() const { return find_date("teenth", "Saturday"); }
bg::date scheduler::sunteenth() const { return find_date("teenth", "Sunday"); }

// First week
bg::date scheduler::first_monday() const { return find_date("first", "Monday"); }
bg::date scheduler::first_tuesday() const { return find_date("first", "Tuesday"); }
bg::date scheduler::first_wednesday() const { return find_date("first", "Wednesday"); }
bg::date scheduler::first_thursday() const { return find_date("first", "Thursday"); }
bg::date scheduler::first_friday() const { return find_date("first", "Friday"); }
bg::date scheduler::first_saturday() const { return find_date("first", "Saturday"); }
bg::date scheduler::first_sunday() const { return find_date("first", "Sunday"); }

// Second week
bg::date scheduler::second_monday() const { return find_date("second", "Monday"); }
bg::date scheduler::second_tuesday() const { return find_date("second", "Tuesday"); }
bg::date scheduler::second_wednesday() const { return find_date("second", "Wednesday"); }
bg::date scheduler::second_thursday() const { return find_date("second", "Thursday"); }
bg::date scheduler::second_friday() const { return find_date("second", "Friday"); }
bg::date scheduler::second_saturday() const { return find_date("second", "Saturday"); }
bg::date scheduler::second_sunday() const { return find_date("second", "Sunday"); }

// Third week
bg::date scheduler::third_monday() const { return find_date("third", "Monday"); }
bg::date scheduler::third_tuesday() const { return find_date("third", "Tuesday"); }
bg::date scheduler::third_wednesday() const { return find_date("third", "Wednesday"); }
bg::date scheduler::third_thursday() const { return find_date("third", "Thursday"); }
bg::date scheduler::third_friday() const { return find_date("third", "Friday"); }
bg::date scheduler::third_saturday() const { return find_date("third", "Saturday"); }
bg::date scheduler::third_sunday() const { return find_date("third", "Sunday"); }

// Fourth week
bg::date scheduler::fourth_monday() const { return find_date("fourth", "Monday"); }
bg::date scheduler::fourth_tuesday() const { return find_date("fourth", "Tuesday"); }
bg::date scheduler::fourth_wednesday() const { return find_date("fourth", "Wednesday"); }
bg::date scheduler::fourth_thursday() const { return find_date("fourth", "Thursday"); }
bg::date scheduler::fourth_friday() const { return find_date("fourth", "Friday"); }
bg::date scheduler::fourth_saturday() const { return find_date("fourth", "Saturday"); }
bg::date scheduler::fourth_sunday() const { return find_date("fourth", "Sunday"); }

// Last week
bg::date scheduler::last_monday() const { return find_date("last", "Monday"); }
bg::date scheduler::last_tuesday() const { return find_date("last", "Tuesday"); }
bg::date scheduler::last_wednesday() const { return find_date("last", "Wednesday"); }
bg::date scheduler::last_thursday() const { return find_date("last", "Thursday"); }
bg::date scheduler::last_friday() const { return find_date("last", "Friday"); }
bg::date scheduler::last_saturday() const { return find_date("last", "Saturday"); }
bg::date scheduler::last_sunday() const { return find_date("last", "Sunday"); }

}  // namespace meetup
