#include "meetup.h"
#include <string>
#include <stdexcept>
#include <array>
#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(std::int32_t year, std::int32_t month) : year_(year), month_(month) {}

boost::gregorian::date scheduler::find_date(const std::string& week, const std::string& weekday) const {
    // Map week to a range of days
    if (week == "teenth") {
        for (std::int32_t day = 13; day <= 19; day++) {
            boost::gregorian::date d(year_, month_, day);
            if (d.day_of_week().as_long_string() == weekday) {
                return d;
            }
        }
    } else {
        // Determine the start and end days based on the week
        boost::gregorian::date start_date(year_, month_, 1);
        boost::gregorian::date end_date;
        if (week == "first") {
            end_date = boost::gregorian::date(year_, month_, 7);
        } else if (week == "second") {
            start_date = boost::gregorian::date(year_, month_, 8);
            end_date = boost::gregorian::date(year_, month_, 14);
        } else if (week == "third") {
            start_date = boost::gregorian::date(year_, month_, 15);
            end_date = boost::gregorian::date(year_, month_, 21);
        } else if (week == "fourth") {
            start_date = boost::gregorian::date(year_, month_, 22);
            end_date = boost::gregorian::date(year_, month_, 28);
        } else if (week == "last") {
            // Handle last by starting from the end of the month and going backwards
            // Get the last day of the month
            boost::gregorian::date last_day(year_, month_, boost::gregorian::gregorian_calendar::end_of_month_day(year_, month_));
            // Iterate backwards from the last day to find the matching weekday
            for (boost::gregorian::day_iterator it(last_day); it->month() == month_; --it) {
                if (it->day_of_week().as_long_string() == weekday) {
                    return *it;
                }
            }
        } else {
            throw std::runtime_error("Invalid week specification");
        }
    }
    throw std::runtime_error("No valid day found");
}

// Implement all the member functions using find_date
boost::gregorian::date scheduler::monteenth() const { 
    return find_date("teenth", "Monday"); 
}
boost::gregorian::date scheduler::tuesteenth() const { 
    return find_date("teenth", "Tuesday"); 
}
boost::gregorian::date scheduler::wednesteenth() const { 
    return find_date("teenth", "Wednesday"); 
}
boost::gregorian::date scheduler::thursteenth() const { 
    return find_date("teenth", "Thursday"); 
}
boost::gregorian::date scheduler::friteenth() const { 
    return find_date("teenth", "Friday"); 
}
boost::gregorian::date scheduler::saturteenth() const { 
    return find_date("teenth", "Saturday"); 
}
boost::gregorian::date scheduler::sunteenth() const { 
    return find_date("teenth", "Sunday"); 
}

#define IMPLEMENT_WEEK(prefix, week_name) \
boost::gregorian::date scheduler::prefix##_monday() const { \
    return find_date(week_name, "Monday"); \
} \
boost::gregorian::date scheduler::prefix##_tuesday() const { \
    return find_date(week_name, "Tuesday"); \
} \
boost::gregorian::date scheduler::prefix##_wednesday() const { \
    return find_date(week_name, "Wednesday"); \
} \
boost::gregorian::date scheduler::prefix##_thursday() const { \
    return find_date(week_name, "Thursday"); \
} \
boost::gregorian::date scheduler::prefix##_friday() const { \
    return find_date(week_name, "Friday"); \
} \
boost::gregorian::date scheduler::prefix##_saturday() const { \
    return find_date(week_name, "Saturday"); \
} \
boost::gregorian::date scheduler::prefix##_sunday() const { \
    return find_date(week_name, "Sunday"); \
}

IMPLEMENT_WEEK(first, "first")
IMPLEMENT_WEEK(second, "second")
IMPLEMENT_WEEK(third, "third")
IMPLEMENT_WEEK(fourth, "fourth")
IMPLEMENT_WEEK(last, "last")

}  // namespace meetup
