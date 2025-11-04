#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper functions
date scheduler::find_nth_weekday(int nth, greg_weekday weekday) const {
    date first_of_month(year_, month_, 1);
    // Find the first occurrence of the weekday
    date first_weekday = first_of_month;
    while (first_weekday.day_of_week() != weekday) {
        first_weekday = first_weekday + days(1);
    }
    // Add (nth-1) weeks
    return first_weekday + weeks(nth - 1);
}

date scheduler::find_teenth(greg_weekday weekday) const {
    // Check days 13-19 to find which matches the weekday
    for (int day = 13; day <= 19; day++) {
        date candidate(year_, month_, day);
        if (candidate.day_of_week() == weekday) {
            return candidate;
        }
    }
    throw std::runtime_error("No teenth found");
}

date scheduler::find_last(greg_weekday weekday) const {
    // Get the last day of the month by finding the first of next month and subtracting one day
    int next_month = month_ + 1;
    int next_year = year_;
    if (next_month > 12) {
        next_month = 1;
        next_year = year_ + 1;
    }
    date first_of_next_month(next_year, next_month, 1);
    date last_of_month = first_of_next_month - days(1);
    
    while (last_of_month.day_of_week() != weekday) {
        last_of_month = last_of_month - days(1);
    }
    return last_of_month;
}

// Teenth implementations
#define IMPLEMENT_TEENTH(day_name, boost_weekday) \
    date scheduler::day_name##teenth() const { \
        return find_teenth(boost_weekday); \
    }

IMPLEMENT_TEENTH(mon, Monday)
IMPLEMENT_TEENTH(tues, Tuesday)
IMPLEMENT_TEENTH(wednes, Wednesday)
IMPLEMENT_TEENTH(thurs, Thursday)
IMPLEMENT_TEENTH(fri, Friday)
IMPLEMENT_TEENTH(satur, Saturday)
IMPLEMENT_TEENTH(sun, Sunday)

// First week implementations
#define IMPLEMENT_FIRST(day_name, boost_weekday) \
    date scheduler::first_##day_name() const { \
        return find_nth_weekday(1, boost_weekday); \
    }

IMPLEMENT_FIRST(monday, Monday)
IMPLEMENT_FIRST(tuesday, Tuesday)
IMPLEMENT_FIRST(wednesday, Wednesday)
IMPLEMENT_FIRST(thursday, Thursday)
IMPLEMENT_FIRST(friday, Friday)
IMPLEMENT_FIRST(saturday, Saturday)
IMPLEMENT_FIRST(sunday, Sunday)

// Second week implementations
#define IMPLEMENT_SECOND(day_name, boost_weekday) \
    date scheduler::second_##day_name() const { \
        return find_nth_weekday(2, boost_weekday); \
    }

IMPLEMENT_SECOND(monday, Monday)
IMPLEMENT_SECOND(tuesday, Tuesday)
IMPLEMENT_SECOND(wednesday, Wednesday)
IMPLEMENT_SECOND(thursday, Thursday)
IMPLEMENT_SECOND(friday, Friday)
IMPLEMENT_SECOND(saturday, Saturday)
IMPLEMENT_SECOND(sunday, Sunday)

// Third week implementations
#define IMPLEMENT_THIRD(day_name, boost_weekday) \
    date scheduler::third_##day_name() const { \
        return find_nth_weekday(3, boost_weekday); \
    }

IMPLEMENT_THIRD(monday, Monday)
IMPLEMENT_THIRD(tuesday, Tuesday)
IMPLEMENT_THIRD(wednesday, Wednesday)
IMPLEMENT_THIRD(thursday, Thursday)
IMPLEMENT_THIRD(friday, Friday)
IMPLEMENT_THIRD(saturday, Saturday)
IMPLEMENT_THIRD(sunday, Sunday)

// Fourth week implementations
#define IMPLEMENT_FOURTH(day_name, boost_weekday) \
    date scheduler::fourth_##day_name() const { \
        return find_nth_weekday(4, boost_weekday); \
    }

IMPLEMENT_FOURTH(monday, Monday)
IMPLEMENT_FOURTH(tuesday, Tuesday)
IMPLEMENT_FOURTH(wednesday, Wednesday)
IMPLEMENT_FOURTH(thursday, Thursday)
IMPLEMENT_FOURTH(friday, Friday)
IMPLEMENT_FOURTH(saturday, Saturday)
IMPLEMENT_FOURTH(sunday, Sunday)

// Last week implementations
#define IMPLEMENT_LAST(day_name, boost_weekday) \
    date scheduler::last_##day_name() const { \
        return find_last(boost_weekday); \
    }

IMPLEMENT_LAST(monday, Monday)
IMPLEMENT_LAST(tuesday, Tuesday)
IMPLEMENT_LAST(wednesday, Wednesday)
IMPLEMENT_LAST(thursday, Thursday)
IMPLEMENT_LAST(friday, Friday)
IMPLEMENT_LAST(saturday, Saturday)
IMPLEMENT_LAST(sunday, Sunday)

}  // namespace meetup
