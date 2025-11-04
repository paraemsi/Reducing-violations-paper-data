#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <map>
#include <string>
#include <stdexcept>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

boost::gregorian::date scheduler::find_day(const std::string& week, const std::string& weekday) const {
    // Map weekdays to boost gregorian weekdays
    static const std::map<std::string, boost::date_time::weekdays> weekday_map{
        {"Monday", boost::gregorian::Monday},
        {"Tuesday", boost::gregorian::Tuesday},
        {"Wednesday", boost::gregorian::Wednesday},
        {"Thursday", boost::gregorian::Thursday},
        {"Friday", boost::gregorian::Friday},
        {"Saturday", boost::gregorian::Saturday},
        {"Sunday", boost::gregorian::Sunday}
    };
    
    // Find the target weekday
    auto it_weekday = weekday_map.find(weekday);
    if (it_weekday == weekday_map.end()) {
        throw std::invalid_argument("Invalid weekday");
    }
    auto target_weekday = it_weekday->second;
    
    if (week == "first") {
        boost::gregorian::first_day_of_the_week_in_month first(target_weekday);
        return first.get_date(year_, month_);
    } else if (week == "second") {
        boost::gregorian::second_day_of_the_week_in_month second(target_weekday);
        return second.get_date(year_, month_);
    } else if (week == "third") {
        boost::gregorian::third_day_of_the_week_in_month third(target_weekday);
        return third.get_date(year_, month_);
    } else if (week == "fourth") {
        boost::gregorian::fourth_day_of_the_week_in_month fourth(target_weekday);
        return fourth.get_date(year_, month_);
    } else if (week == "last") {
        boost::gregorian::last_day_of_the_week_in_month last(target_weekday);
        return last.get_date(year_, month_);
    } else if (week == "teenth") {
        // For teenth, find the first occurrence and check if it's in 13-19
        // Start from the 13th
        boost::gregorian::date start(year_, month_, 13);
        // Find the next target weekday
        while (start.day_of_week() != target_weekday) {
            start += boost::gregorian::days(1);
        }
        // Since teenth days are between 13-19, and each weekday appears exactly once in this range
        return start;
    } else {
        throw std::invalid_argument("Invalid week specification");
    }
}

// Teenth implementations
boost::gregorian::date scheduler::monteenth() const { return find_day("teenth", "Monday"); }
boost::gregorian::date scheduler::tuesteenth() const { return find_day("teenth", "Tuesday"); }
boost::gregorian::date scheduler::wednesteenth() const { return find_day("teenth", "Wednesday"); }
boost::gregorian::date scheduler::thursteenth() const { return find_day("teenth", "Thursday"); }
boost::gregorian::date scheduler::friteenth() const { return find_day("teenth", "Friday"); }
boost::gregorian::date scheduler::saturteenth() const { return find_day("teenth", "Saturday"); }
boost::gregorian::date scheduler::sunteenth() const { return find_day("teenth", "Sunday"); }

// First week implementations
boost::gregorian::date scheduler::first_monday() const { return find_day("first", "Monday"); }
boost::gregorian::date scheduler::first_tuesday() const { return find_day("first", "Tuesday"); }
boost::gregorian::date scheduler::first_wednesday() const { return find_day("first", "Wednesday"); }
boost::gregorian::date scheduler::first_thursday() const { return find_day("first", "Thursday"); }
boost::gregorian::date scheduler::first_friday() const { return find_day("first", "Friday"); }
boost::gregorian::date scheduler::first_saturday() const { return find_day("first", "Saturday"); }
boost::gregorian::date scheduler::first_sunday() const { return find_day("first", "Sunday"); }

// Second week implementations
boost::gregorian::date scheduler::second_monday() const { return find_day("second", "Monday"); }
boost::gregorian::date scheduler::second_tuesday() const { return find_day("second", "Tuesday"); }
boost::gregorian::date scheduler::second_wednesday() const { return find_day("second", "Wednesday"); }
boost::gregorian::date scheduler::second_thursday() const { return find_day("second", "Thursday"); }
boost::gregorian::date scheduler::second_friday() const { return find_day("second", "Friday"); }
boost::gregorian::date scheduler::second_saturday() const { return find_day("second", "Saturday"); }
boost::gregorian::date scheduler::second_sunday() const { return find_day("second", "Sunday"); }

// Third week implementations
boost::gregorian::date scheduler::third_monday() const { return find_day("third", "Monday"); }
boost::gregorian::date scheduler::third_tuesday() const { return find_day("third", "Tuesday"); }
boost::gregorian::date scheduler::third_wednesday() const { return find_day("third", "Wednesday"); }
boost::gregorian::date scheduler::third_thursday() const { return find_day("third", "Thursday"); }
boost::gregorian::date scheduler::third_friday() const { return find_day("third", "Friday"); }
boost::gregorian::date scheduler::third_saturday() const { return find_day("third", "Saturday"); }
boost::gregorian::date scheduler::third_sunday() const { return find_day("third", "Sunday"); }

// Fourth week implementations
boost::gregorian::date scheduler::fourth_monday() const { return find_day("fourth", "Monday"); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_day("fourth", "Tuesday"); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_day("fourth", "Wednesday"); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_day("fourth", "Thursday"); }
boost::gregorian::date scheduler::fourth_friday() const { return find_day("fourth", "Friday"); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_day("fourth", "Saturday"); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_day("fourth", "Sunday"); }

// Last week implementations
boost::gregorian::date scheduler::last_monday() const { return find_day("last", "Monday"); }
boost::gregorian::date scheduler::last_tuesday() const { return find_day("last", "Tuesday"); }
boost::gregorian::date scheduler::last_wednesday() const { return find_day("last", "Wednesday"); }
boost::gregorian::date scheduler::last_thursday() const { return find_day("last", "Thursday"); }
boost::gregorian::date scheduler::last_friday() const { return find_day("last", "Friday"); }
boost::gregorian::date scheduler::last_saturday() const { return find_day("last", "Saturday"); }
boost::gregorian::date scheduler::last_sunday() const { return find_day("last", "Sunday"); }

}  // namespace meetup
