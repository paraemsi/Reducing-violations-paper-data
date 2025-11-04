#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
using namespace boost::gregorian;

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper function to find the nth weekday
date scheduler::find_nth_weekday(int nth, const greg_weekday& weekday) const {
    // Start from the first day of the month
    date d(year_, month_, 1);
    
    // Find the first occurrence of the desired weekday
    while (d.day_of_week() != weekday) {
        d += days(1);
    }
    
    // Add (nth-1) weeks
    d += weeks(nth - 1);
    // Check if we're still in the same month
    if (d.month() != month_) {
        throw std::runtime_error("Nth weekday not found in month");
    }
    return d;
}

// Helper function to find teenth day
date scheduler::find_teenth(const greg_weekday& weekday) const {
    // Check days 13-19
    for (int day = 13; day <= 19; ++day) {
        date d(year_, month_, day);
        if (d.day_of_week() == weekday) {
            return d;
        }
    }
    throw std::runtime_error("Teenth day not found");
}

// Helper function to find last weekday
date scheduler::find_last(const greg_weekday& weekday) const {
    // Get the last day of the month by finding the first day of next month and subtracting one day
    date d;
    if (month_ == 12) {
        d = date(year_ + 1, 1, 1) - days(1);
    } else {
        d = date(year_, month_ + 1, 1) - days(1);
    }
    
    // Go backwards until we find the desired weekday
    while (d.day_of_week() != weekday) {
        d -= days(1);
    }
    return d;
}

// Implement all the interface methods
#define IMPLEMENT_TEENTH(day_name, weekday) \
    date scheduler::day_name##teenth() const { \
        return find_teenth(greg_weekday(weekday)); \
    }

IMPLEMENT_TEENTH(mon, 1)  // Monday
IMPLEMENT_TEENTH(tues, 2) // Tuesday
IMPLEMENT_TEENTH(wednes, 3) // Wednesday
IMPLEMENT_TEENTH(thurs, 4) // Thursday
IMPLEMENT_TEENTH(fri, 5) // Friday
IMPLEMENT_TEENTH(satur, 6) // Saturday
IMPLEMENT_TEENTH(sun, 0) // Sunday

#define IMPLEMENT_FIRST(day_name, weekday) \
    date scheduler::first_##day_name() const { \
        return find_nth_weekday(1, greg_weekday(weekday)); \
    }

IMPLEMENT_FIRST(monday, 1)
IMPLEMENT_FIRST(tuesday, 2)
IMPLEMENT_FIRST(wednesday, 3)
IMPLEMENT_FIRST(thursday, 4)
IMPLEMENT_FIRST(friday, 5)
IMPLEMENT_FIRST(saturday, 6)
IMPLEMENT_FIRST(sunday, 0)

#define IMPLEMENT_SECOND(day_name, weekday) \
    date scheduler::second_##day_name() const { \
        return find_nth_weekday(2, greg_weekday(weekday)); \
    }

IMPLEMENT_SECOND(monday, 1)
IMPLEMENT_SECOND(tuesday, 2)
IMPLEMENT_SECOND(wednesday, 3)
IMPLEMENT_SECOND(thursday, 4)
IMPLEMENT_SECOND(friday, 5)
IMPLEMENT_SECOND(saturday, 6)
IMPLEMENT_SECOND(sunday, 0)

#define IMPLEMENT_THIRD(day_name, weekday) \
    date scheduler::third_##day_name() const { \
        return find_nth_weekday(3, greg_weekday(weekday)); \
    }

IMPLEMENT_THIRD(monday, 1)
IMPLEMENT_THIRD(tuesday, 2)
IMPLEMENT_THIRD(wednesday, 3)
IMPLEMENT_THIRD(thursday, 4)
IMPLEMENT_THIRD(friday, 5)
IMPLEMENT_THIRD(saturday, 6)
IMPLEMENT_THIRD(sunday, 0)

#define IMPLEMENT_FOURTH(day_name, weekday) \
    date scheduler::fourth_##day_name() const { \
        return find_nth_weekday(4, greg_weekday(weekday)); \
    }

IMPLEMENT_FOURTH(monday, 1)
IMPLEMENT_FOURTH(tuesday, 2)
IMPLEMENT_FOURTH(wednesday, 3)
IMPLEMENT_FOURTH(thursday, 4)
IMPLEMENT_FOURTH(friday, 5)
IMPLEMENT_FOURTH(saturday, 6)
IMPLEMENT_FOURTH(sunday, 0)

#define IMPLEMENT_LAST(day_name, weekday) \
    date scheduler::last_##day_name() const { \
        return find_last(greg_weekday(weekday)); \
    }

IMPLEMENT_LAST(monday, 1)
IMPLEMENT_LAST(tuesday, 2)
IMPLEMENT_LAST(wednesday, 3)
IMPLEMENT_LAST(thursday, 4)
IMPLEMENT_LAST(friday, 5)
IMPLEMENT_LAST(saturday, 6)
IMPLEMENT_LAST(sunday, 0)

}  // namespace meetup
