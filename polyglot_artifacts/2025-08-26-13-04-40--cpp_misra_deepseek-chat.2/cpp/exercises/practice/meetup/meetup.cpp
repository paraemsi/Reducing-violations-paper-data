#include "meetup.h"
#include <string>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Implement all the member functions
boost::gregorian::date scheduler::monteenth() const { return find_date("teenth", "Monday"); }
boost::gregorian::date scheduler::tuesteenth() const { return find_date("teenth", "Tuesday"); }
boost::gregorian::date scheduler::wednesteenth() const { return find_date("teenth", "Wednesday"); }
boost::gregorian::date scheduler::thursteenth() const { return find_date("teenth", "Thursday"); }
boost::gregorian::date scheduler::friteenth() const { return find_date("teenth", "Friday"); }
boost::gregorian::date scheduler::saturteenth() const { return find_date("teenth", "Saturday"); }
boost::gregorian::date scheduler::sunteenth() const { return find_date("teenth", "Sunday"); }

boost::gregorian::date scheduler::first_monday() const { return find_date("first", "Monday"); }
boost::gregorian::date scheduler::first_tuesday() const { return find_date("first", "Tuesday"); }
boost::gregorian::date scheduler::first_wednesday() const { return find_date("first", "Wednesday"); }
boost::gregorian::date scheduler::first_thursday() const { return find_date("first", "Thursday"); }
boost::gregorian::date scheduler::first_friday() const { return find_date("first", "Friday"); }
boost::gregorian::date scheduler::first_saturday() const { return find_date("first", "Saturday"); }
boost::gregorian::date scheduler::first_sunday() const { return find_date("first", "Sunday"); }

boost::gregorian::date scheduler::second_monday() const { return find_date("second", "Monday"); }
boost::gregorian::date scheduler::second_tuesday() const { return find_date("second", "Tuesday"); }
boost::gregorian::date scheduler::second_wednesday() const { return find_date("second", "Wednesday"); }
boost::gregorian::date scheduler::second_thursday() const { return find_date("second", "Thursday"); }
boost::gregorian::date scheduler::second_friday() const { return find_date("second", "Friday"); }
boost::gregorian::date scheduler::second_saturday() const { return find_date("second", "Saturday"); }
boost::gregorian::date scheduler::second_sunday() const { return find_date("second", "Sunday"); }

boost::gregorian::date scheduler::third_monday() const { return find_date("third", "Monday"); }
boost::gregorian::date scheduler::third_tuesday() const { return find_date("third", "Tuesday"); }
boost::gregorian::date scheduler::third_wednesday() const { return find_date("third", "Wednesday"); }
boost::gregorian::date scheduler::third_thursday() const { return find_date("third", "Thursday"); }
boost::gregorian::date scheduler::third_friday() const { return find_date("third", "Friday"); }
boost::gregorian::date scheduler::third_saturday() const { return find_date("third", "Saturday"); }
boost::gregorian::date scheduler::third_sunday() const { return find_date("third", "Sunday"); }

boost::gregorian::date scheduler::fourth_monday() const { return find_date("fourth", "Monday"); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_date("fourth", "Tuesday"); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_date("fourth", "Wednesday"); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_date("fourth", "Thursday"); }
boost::gregorian::date scheduler::fourth_friday() const { return find_date("fourth", "Friday"); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_date("fourth", "Saturday"); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_date("fourth", "Sunday"); }

boost::gregorian::date scheduler::last_monday() const { return find_date("last", "Monday"); }
boost::gregorian::date scheduler::last_tuesday() const { return find_date("last", "Tuesday"); }
boost::gregorian::date scheduler::last_wednesday() const { return find_date("last", "Wednesday"); }
boost::gregorian::date scheduler::last_thursday() const { return find_date("last", "Thursday"); }
boost::gregorian::date scheduler::last_friday() const { return find_date("last", "Friday"); }
boost::gregorian::date scheduler::last_saturday() const { return find_date("last", "Saturday"); }
boost::gregorian::date scheduler::last_sunday() const { return find_date("last", "Sunday"); }

boost::gregorian::date scheduler::find_date(const std::string& week, const std::string& weekday) const {
    // Map weekdays to boost::gregorian::greg_weekday
    boost::gregorian::greg_weekday target_wday;
    if (weekday == "Sunday") target_wday = boost::gregorian::Sunday;
    else if (weekday == "Monday") target_wday = boost::gregorian::Monday;
    else if (weekday == "Tuesday") target_wday = boost::gregorian::Tuesday;
    else if (weekday == "Wednesday") target_wday = boost::gregorian::Wednesday;
    else if (weekday == "Thursday") target_wday = boost::gregorian::Thursday;
    else if (weekday == "Friday") target_wday = boost::gregorian::Friday;
    else if (weekday == "Saturday") target_wday = boost::gregorian::Saturday;
    else throw std::invalid_argument("Invalid weekday");
    
    // Create the first day of the month
    boost::gregorian::date first_day(year_, month_, 1);
    
    if (week == "teenth") {
        // Check days 13-19
        for (int day = 13; day <= 19; ++day) {
            boost::gregorian::date current_day(year_, month_, day);
            if (current_day.day_of_week() == target_wday) {
                return current_day;
            }
        }
    } else {
        // Find the nth occurrence
        boost::gregorian::first_day_of_the_week_in_month nth(target_wday);
        if (week == "first") {
            return nth.get_date(year_, month_);
        } else if (week == "second") {
            boost::gregorian::nth_day_of_the_week_in_month second_nth(2, target_wday, month_);
            return second_nth.get_date(year_);
        } else if (week == "third") {
            boost::gregorian::nth_day_of_the_week_in_month third_nth(3, target_wday, month_);
            return third_nth.get_date(year_);
        } else if (week == "fourth") {
            boost::gregorian::nth_day_of_the_week_in_month fourth_nth(4, target_wday, month_);
            return fourth_nth.get_date(year_);
        } else if (week == "last") {
            boost::gregorian::last_day_of_the_week_in_month last(target_wday, month_);
            return last.get_date(year_);
        } else {
            throw std::invalid_argument("Invalid week specification");
        }
    }
    throw std::runtime_error("No date found");
}

}  // namespace meetup
