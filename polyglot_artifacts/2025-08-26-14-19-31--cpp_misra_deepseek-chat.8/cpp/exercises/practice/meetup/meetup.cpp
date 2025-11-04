#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <map>
#include <stdexcept>
#include <cstdint>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(std::int32_t year, std::int32_t month) 
    : year_(year), month_(month) {}

// Helper function to find a date given week and day of week
date scheduler::find_date(const std::string& week, const std::string& day_of_week) const {
    static const std::map<std::string, std::int32_t> days{
        {"Sunday", 0}, {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3},
        {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}
    };
    std::int32_t target_dow = days.at(day_of_week);
    
    if (week == "teenth") {
        for (std::int32_t day = 13; day <= 19; day++) {
            date current(year_, month_, day);
            if (current.day_of_week().as_number() == target_dow) {
                return current;
            }
        }
    } else {
        date first_day(year_, month_, 1);
        if (week == "last") {
            date last_day = first_day.end_of_month();
            for (date d = last_day; d.month() == month_; d = d - days(1)) {
                if (d.day_of_week().as_number() == target_dow) {
                    return d;
                }
            }
        } else {
            std::int32_t occurrence;
            if (week == "first") occurrence = 1;
            else if (week == "second") occurrence = 2;
            else if (week == "third") occurrence = 3;
            else if (week == "fourth") occurrence = 4;
            else throw std::invalid_argument("Invalid week specification");
            
            std::int32_t count = 0;
            for (date d = first_day; d.month() == month_; d = d + days(1)) {
                if (d.day_of_week().as_number() == target_dow) {
                    count++;
                    if (count == occurrence) {
                        return d;
                    }
                }
            }
        }
    }
    throw std::runtime_error("No meetup date found");
}

// Implement all the member functions explicitly
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

}  // namespace meetup
