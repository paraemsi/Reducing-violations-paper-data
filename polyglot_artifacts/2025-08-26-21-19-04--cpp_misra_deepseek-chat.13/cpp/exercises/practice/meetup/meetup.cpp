#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace meetup {

scheduler::scheduler(std::int32_t year, std::int32_t month) : year_(year), month_(month) {
}

boost::gregorian::date scheduler::meetup_day(const std::string& week, const std::string& day_of_week) const {
    // Map day names to boost day of week
    std::map<std::string, boost::gregorian::greg_weekday> day_map = {
        {"Monday", boost::gregorian::Monday},
        {"Tuesday", boost::gregorian::Tuesday},
        {"Wednesday", boost::gregorian::Wednesday},
        {"Thursday", boost::gregorian::Thursday},
        {"Friday", boost::gregorian::Friday},
        {"Saturday", boost::gregorian::Saturday},
        {"Sunday", boost::gregorian::Sunday}
    };
    
    // Get the target day of week
    boost::gregorian::greg_weekday target_day = day_map[day_of_week];
    
    // Start from the first day of the month
    boost::gregorian::date start_date(static_cast<boost::gregorian::date::year_type>(year_), 
                                      static_cast<boost::gregorian::date::month_type>(month_), 
                                      1);
    // End at the last day of the month
    boost::gregorian::date end_date = start_date.end_of_month();
    
    // Collect all dates that match the target day of week
    std::vector<boost::gregorian::date> matching_days;
    for (boost::gregorian::day_iterator it(start_date); it <= end_date; ++it) {
        if (it->day_of_week() == target_day) {
            matching_days.push_back(*it);
        }
    }
    
    // Determine which date to pick based on the week parameter
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
            // Use the same type as returned by date.day() for comparison
            // The day() method returns an unsigned type, so we'll use it directly
            auto day = date.day();
            if ((day >= 13U) && (day <= 19U)) {
                return date;
            }
        }
    }
    // Should never reach here according to the problem statement
    return boost::gregorian::date(static_cast<boost::gregorian::date::year_type>(year_), 
                                  static_cast<boost::gregorian::date::month_type>(month_), 
                                  1U);
}

// Teenth implementations
boost::gregorian::date scheduler::monteenth() const {
    return meetup_day("teenth", "Monday");
}

boost::gregorian::date scheduler::tuesteenth() const {
    return meetup_day("teenth", "Tuesday");
}

boost::gregorian::date scheduler::wednesteenth() const {
    return meetup_day("teenth", "Wednesday");
}

boost::gregorian::date scheduler::thursteenth() const {
    return meetup_day("teenth", "Thursday");
}

boost::gregorian::date scheduler::friteenth() const {
    return meetup_day("teenth", "Friday");
}

boost::gregorian::date scheduler::saturteenth() const {
    return meetup_day("teenth", "Saturday");
}

boost::gregorian::date scheduler::sunteenth() const {
    return meetup_day("teenth", "Sunday");
}

// First week implementations
boost::gregorian::date scheduler::first_monday() const {
    return meetup_day("first", "Monday");
}

boost::gregorian::date scheduler::first_tuesday() const {
    return meetup_day("first", "Tuesday");
}

boost::gregorian::date scheduler::first_wednesday() const {
    return meetup_day("first", "Wednesday");
}

boost::gregorian::date scheduler::first_thursday() const {
    return meetup_day("first", "Thursday");
}

boost::gregorian::date scheduler::first_friday() const {
    return meetup_day("first", "Friday");
}

boost::gregorian::date scheduler::first_saturday() const {
    return meetup_day("first", "Saturday");
}

boost::gregorian::date scheduler::first_sunday() const {
    return meetup_day("first", "Sunday");
}

// Second week implementations
boost::gregorian::date scheduler::second_monday() const {
    return meetup_day("second", "Monday");
}

boost::gregorian::date scheduler::second_tuesday() const {
    return meetup_day("second", "Tuesday");
}

boost::gregorian::date scheduler::second_wednesday() const {
    return meetup_day("second", "Wednesday");
}

boost::gregorian::date scheduler::second_thursday() const {
    return meetup_day("second", "Thursday");
}

boost::gregorian::date scheduler::second_friday() const {
    return meetup_day("second", "Friday");
}

boost::gregorian::date scheduler::second_saturday() const {
    return meetup_day("second", "Saturday");
}

boost::gregorian::date scheduler::second_sunday() const {
    return meetup_day("second", "Sunday");
}

// Third week implementations
boost::gregorian::date scheduler::third_monday() const {
    return meetup_day("third", "Monday");
}

boost::gregorian::date scheduler::third_tuesday() const {
    return meetup_day("third", "Tuesday");
}

boost::gregorian::date scheduler::third_wednesday() const {
    return meetup_day("third", "Wednesday");
}

boost::gregorian::date scheduler::third_thursday() const {
    return meetup_day("third", "Thursday");
}

boost::gregorian::date scheduler::third_friday() const {
    return meetup_day("third", "Friday");
}

boost::gregorian::date scheduler::third_saturday() const {
    return meetup_day("third", "Saturday");
}

boost::gregorian::date scheduler::third_sunday() const {
    return meetup_day("third", "Sunday");
}

// Fourth week implementations
boost::gregorian::date scheduler::fourth_monday() const {
    return meetup_day("fourth", "Monday");
}

boost::gregorian::date scheduler::fourth_tuesday() const {
    return meetup_day("fourth", "Tuesday");
}

boost::gregorian::date scheduler::fourth_wednesday() const {
    return meetup_day("fourth", "Wednesday");
}

boost::gregorian::date scheduler::fourth_thursday() const {
    return meetup_day("fourth", "Thursday");
}

boost::gregorian::date scheduler::fourth_friday() const {
    return meetup_day("fourth", "Friday");
}

boost::gregorian::date scheduler::fourth_saturday() const {
    return meetup_day("fourth", "Saturday");
}

boost::gregorian::date scheduler::fourth_sunday() const {
    return meetup_day("fourth", "Sunday");
}

// Last week implementations
boost::gregorian::date scheduler::last_monday() const {
    return meetup_day("last", "Monday");
}

boost::gregorian::date scheduler::last_tuesday() const {
    return meetup_day("last", "Tuesday");
}

boost::gregorian::date scheduler::last_wednesday() const {
    return meetup_day("last", "Wednesday");
}

boost::gregorian::date scheduler::last_thursday() const {
    return meetup_day("last", "Thursday");
}

boost::gregorian::date scheduler::last_friday() const {
    return meetup_day("last", "Friday");
}

boost::gregorian::date scheduler::last_saturday() const {
    return meetup_day("last", "Saturday");
}

boost::gregorian::date scheduler::last_sunday() const {
    return meetup_day("last", "Sunday");
}

}  // namespace meetup
