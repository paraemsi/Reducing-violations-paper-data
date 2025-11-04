#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

namespace meetup {

namespace {
    boost::gregorian::greg_weekday parse_weekday(const std::string& weekday) {
        if (weekday == "Monday") return boost::gregorian::Monday;
        if (weekday == "Tuesday") return boost::gregorian::Tuesday;
        if (weekday == "Wednesday") return boost::gregorian::Wednesday;
        if (weekday == "Thursday") return boost::gregorian::Thursday;
        if (weekday == "Friday") return boost::gregorian::Friday;
        if (weekday == "Saturday") return boost::gregorian::Saturday;
        if (weekday == "Sunday") return boost::gregorian::Sunday;
        throw std::runtime_error("Invalid weekday");
    }
}

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

boost::gregorian::date scheduler::find_date(const std::string& week, const std::string& weekday) const {
    // Start from the first day of the month
    boost::gregorian::date start_date(year_, month_, 1);
    // End of the month
    boost::gregorian::date end_date = start_date.end_of_month();
    
    // Target weekday
    boost::gregorian::greg_weekday target_dow = parse_weekday(weekday);
    
    // Collect all matching weekdays in the month
    std::vector<boost::gregorian::date> matching_days;
    for (boost::gregorian::day_iterator iter(start_date); *iter <= end_date; ++iter) {
        if (iter->day_of_week() == target_dow) {
            matching_days.push_back(*iter);
        }
    }
    
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
        // Find the date where day is between 13 and 19
        for (const auto& date : matching_days) {
            int day = date.day();
            if (day >= 13 && day <= 19) {
                return date;
            }
        }
    }
    throw std::runtime_error("Invalid week specification");
}

// Implement all the interface methods
// For teenth methods, we need to map to the correct weekday names
boost::gregorian::date scheduler::monteenth() const { return find_date("teenth", "Monday"); }
boost::gregorian::date scheduler::tuesteenth() const { return find_date("teenth", "Tuesday"); }
boost::gregorian::date scheduler::wednesteenth() const { return find_date("teenth", "Wednesday"); }
boost::gregorian::date scheduler::thursteenth() const { return find_date("teenth", "Thursday"); }
boost::gregorian::date scheduler::friteenth() const { return find_date("teenth", "Friday"); }
boost::gregorian::date scheduler::saturteenth() const { return find_date("teenth", "Saturday"); }
boost::gregorian::date scheduler::sunteenth() const { return find_date("teenth", "Sunday"); }

// First methods
boost::gregorian::date scheduler::first_monday() const { return find_date("first", "Monday"); }
boost::gregorian::date scheduler::first_tuesday() const { return find_date("first", "Tuesday"); }
boost::gregorian::date scheduler::first_wednesday() const { return find_date("first", "Wednesday"); }
boost::gregorian::date scheduler::first_thursday() const { return find_date("first", "Thursday"); }
boost::gregorian::date scheduler::first_friday() const { return find_date("first", "Friday"); }
boost::gregorian::date scheduler::first_saturday() const { return find_date("first", "Saturday"); }
boost::gregorian::date scheduler::first_sunday() const { return find_date("first", "Sunday"); }

// Second methods
boost::gregorian::date scheduler::second_monday() const { return find_date("second", "Monday"); }
boost::gregorian::date scheduler::second_tuesday() const { return find_date("second", "Tuesday"); }
boost::gregorian::date scheduler::second_wednesday() const { return find_date("second", "Wednesday"); }
boost::gregorian::date scheduler::second_thursday() const { return find_date("second", "Thursday"); }
boost::gregorian::date scheduler::second_friday() const { return find_date("second", "Friday"); }
boost::gregorian::date scheduler::second_saturday() const { return find_date("second", "Saturday"); }
boost::gregorian::date scheduler::second_sunday() const { return find_date("second", "Sunday"); }

// Third methods
boost::gregorian::date scheduler::third_monday() const { return find_date("third", "Monday"); }
boost::gregorian::date scheduler::third_tuesday() const { return find_date("third", "Tuesday"); }
boost::gregorian::date scheduler::third_wednesday() const { return find_date("third", "Wednesday"); }
boost::gregorian::date scheduler::third_thursday() const { return find_date("third", "Thursday"); }
boost::gregorian::date scheduler::third_friday() const { return find_date("third", "Friday"); }
boost::gregorian::date scheduler::third_saturday() const { return find_date("third", "Saturday"); }
boost::gregorian::date scheduler::third_sunday() const { return find_date("third", "Sunday"); }

// Fourth methods
boost::gregorian::date scheduler::fourth_monday() const { return find_date("fourth", "Monday"); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_date("fourth", "Tuesday"); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_date("fourth", "Wednesday"); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_date("fourth", "Thursday"); }
boost::gregorian::date scheduler::fourth_friday() const { return find_date("fourth", "Friday"); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_date("fourth", "Saturday"); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_date("fourth", "Sunday"); }

// Last methods
boost::gregorian::date scheduler::last_monday() const { return find_date("last", "Monday"); }
boost::gregorian::date scheduler::last_tuesday() const { return find_date("last", "Tuesday"); }
boost::gregorian::date scheduler::last_wednesday() const { return find_date("last", "Wednesday"); }
boost::gregorian::date scheduler::last_thursday() const { return find_date("last", "Thursday"); }
boost::gregorian::date scheduler::last_friday() const { return find_date("last", "Friday"); }
boost::gregorian::date scheduler::last_saturday() const { return find_date("last", "Saturday"); }
boost::gregorian::date scheduler::last_sunday() const { return find_date("last", "Sunday"); }

}  // namespace meetup
