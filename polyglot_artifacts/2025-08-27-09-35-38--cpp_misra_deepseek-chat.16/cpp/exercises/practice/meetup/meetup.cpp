#include "meetup.h"
#include <map>
#include <string>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

boost::gregorian::date scheduler::find_teenth(const std::string& weekday) const {
    std::map<std::string, boost::gregorian::greg_weekday> weekday_map = {
        {"Monday", boost::gregorian::Monday},
        {"Tuesday", boost::gregorian::Tuesday},
        {"Wednesday", boost::gregorian::Wednesday},
        {"Thursday", boost::gregorian::Thursday},
        {"Friday", boost::gregorian::Friday},
        {"Saturday", boost::gregorian::Saturday},
        {"Sunday", boost::gregorian::Sunday}
    };
    
    boost::gregorian::date start(year_, month_, 13);
    for (int i = 0; i < 7; ++i) {
        boost::gregorian::date current = start + boost::gregorian::days(i);
        if (current.day_of_week() == weekday_map.at(weekday)) {
            return current;
        }
    }
    throw std::runtime_error("Teenth not found");
}

boost::gregorian::date scheduler::find_nth(int n, const std::string& weekday) const {
    std::map<std::string, boost::gregorian::greg_weekday> weekday_map = {
        {"Monday", boost::gregorian::Monday},
        {"Tuesday", boost::gregorian::Tuesday},
        {"Wednesday", boost::gregorian::Wednesday},
        {"Thursday", boost::gregorian::Thursday},
        {"Friday", boost::gregorian::Friday},
        {"Saturday", boost::gregorian::Saturday},
        {"Sunday", boost::gregorian::Sunday}
    };
    
    boost::gregorian::date first_of_month(year_, month_, 1);
    // Calculate days to add to reach the first occurrence of the target weekday
    int target_dow = weekday_map.at(weekday).as_number();
    int first_dow = first_of_month.day_of_week().as_number();
    int days_to_add = (target_dow - first_dow + 7) % 7;
    boost::gregorian::date result = first_of_month + boost::gregorian::days(days_to_add + (n - 1) * 7);
    
    // Make sure the result is in the same month
    if (result.month() != month_) {
        throw std::runtime_error("Nth weekday not found in month");
    }
    return result;
}

boost::gregorian::date scheduler::find_last(const std::string& weekday) const {
    std::map<std::string, boost::gregorian::greg_weekday> weekday_map = {
        {"Monday", boost::gregorian::Monday},
        {"Tuesday", boost::gregorian::Tuesday},
        {"Wednesday", boost::gregorian::Wednesday},
        {"Thursday", boost::gregorian::Thursday},
        {"Friday", boost::gregorian::Friday},
        {"Saturday", boost::gregorian::Saturday},
        {"Sunday", boost::gregorian::Sunday}
    };
    
    // Start from the last day of the month and work backwards
    boost::gregorian::date last_of_month = boost::gregorian::date(year_, month_, 1).end_of_month();
    for (int i = 0; i < 7; ++i) {
        boost::gregorian::date current = last_of_month - boost::gregorian::days(i);
        if (current.day_of_week() == weekday_map.at(weekday)) {
            return current;
        }
    }
    throw std::runtime_error("Last weekday not found");
}

// Implement all the member functions
#define IMPLEMENT_TEENTH(day, weekday) boost::gregorian::date scheduler::day##teenth() const { return find_teenth(weekday); }
IMPLEMENT_TEENTH(mon, "Monday")
IMPLEMENT_TEENTH(tues, "Tuesday")
IMPLEMENT_TEENTH(wednes, "Wednesday")
IMPLEMENT_TEENTH(thurs, "Thursday")
IMPLEMENT_TEENTH(fri, "Friday")
IMPLEMENT_TEENTH(satur, "Saturday")
IMPLEMENT_TEENTH(sun, "Sunday")

#define IMPLEMENT_FIRST(day) boost::gregorian::date scheduler::first_##day() const { return find_nth(1, #day); }
IMPLEMENT_FIRST(Monday)
IMPLEMENT_FIRST(Tuesday)
IMPLEMENT_FIRST(Wednesday)
IMPLEMENT_FIRST(Thursday)
IMPLEMENT_FIRST(Friday)
IMPLEMENT_FIRST(Saturday)
IMPLEMENT_FIRST(Sunday)

#define IMPLEMENT_SECOND(day) boost::gregorian::date scheduler::second_##day() const { return find_nth(2, #day); }
IMPLEMENT_SECOND(Monday)
IMPLEMENT_SECOND(Tuesday)
IMPLEMENT_SECOND(Wednesday)
IMPLEMENT_SECOND(Thursday)
IMPLEMENT_SECOND(Friday)
IMPLEMENT_SECOND(Saturday)
IMPLEMENT_SECOND(Sunday)

#define IMPLEMENT_THIRD(day) boost::gregorian::date scheduler::third_##day() const { return find_nth(3, #day); }
IMPLEMENT_THIRD(Monday)
IMPLEMENT_THIRD(Tuesday)
IMPLEMENT_THIRD(Wednesday)
IMPLEMENT_THIRD(Thursday)
IMPLEMENT_THIRD(Friday)
IMPLEMENT_THIRD(Saturday)
IMPLEMENT_THIRD(Sunday)

#define IMPLEMENT_FOURTH(day) boost::gregorian::date scheduler::fourth_##day() const { return find_nth(4, #day); }
IMPLEMENT_FOURTH(Monday)
IMPLEMENT_FOURTH(Tuesday)
IMPLEMENT_FOURTH(Wednesday)
IMPLEMENT_FOURTH(Thursday)
IMPLEMENT_FOURTH(Friday)
IMPLEMENT_FOURTH(Saturday)
IMPLEMENT_FOURTH(Sunday)

#define IMPLEMENT_LAST(day) boost::gregorian::date scheduler::last_##day() const { return find_last(#day); }
IMPLEMENT_LAST(Monday)
IMPLEMENT_LAST(Tuesday)
IMPLEMENT_LAST(Wednesday)
IMPLEMENT_LAST(Thursday)
IMPLEMENT_LAST(Friday)
IMPLEMENT_LAST(Saturday)
IMPLEMENT_LAST(Sunday)

}  // namespace meetup
