#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
using namespace boost::gregorian;

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

date scheduler::find_teenth_day(boost::gregorian::greg_weekday weekday) const {
    for (int day = 13; day <= 19; day++) {
        date d(year_, month_, day);
        if (d.day_of_week() == weekday) {
            return d;
        }
    }
    throw std::runtime_error("Teenth day not found");
}

date scheduler::find_nth_day(int nth, boost::gregorian::greg_weekday weekday) const {
    // Start from the first day of the month
    date d(year_, month_, 1);
    // Find the first occurrence of the weekday
    while (d.day_of_week() != weekday) {
        d += days(1);
    }
    // Add (nth-1) weeks
    return d + weeks(nth - 1);
}

date scheduler::find_last_day(boost::gregorian::greg_weekday weekday) const {
    // Start from the last day of the month
    date d(year_, month_, gregorian_calendar::end_of_month_day(year_, month_));
    // Go backwards until we find the weekday
    while (d.day_of_week() != weekday) {
        d -= days(1);
    }
    return d;
}

// Implement all the interface methods by using the actual boost weekday objects
#define IMPLEMENT_TEENTH(day_name, weekday) \
    date scheduler::day_name() const { \
        return find_teenth_day(weekday()); \
    }

IMPLEMENT_TEENTH(monteenth, Monday)
IMPLEMENT_TEENTH(tuesteenth, Tuesday)
IMPLEMENT_TEENTH(wednesteenth, Wednesday)
IMPLEMENT_TEENTH(thursteenth, Thursday)
IMPLEMENT_TEENTH(friteenth, Friday)
IMPLEMENT_TEENTH(saturteenth, Saturday)
IMPLEMENT_TEENTH(sunteenth, Sunday)

#define IMPLEMENT_FIRST(day_name, weekday) \
    date scheduler::day_name() const { \
        return find_nth_day(1, weekday()); \
    }

IMPLEMENT_FIRST(first_monday, Monday)
IMPLEMENT_FIRST(first_tuesday, Tuesday)
IMPLEMENT_FIRST(first_wednesday, Wednesday)
IMPLEMENT_FIRST(first_thursday, Thursday)
IMPLEMENT_FIRST(first_friday, Friday)
IMPLEMENT_FIRST(first_saturday, Saturday)
IMPLEMENT_FIRST(first_sunday, Sunday)

#define IMPLEMENT_SECOND(day_name, weekday) \
    date scheduler::day_name() const { \
        return find_nth_day(2, weekday()); \
    }

IMPLEMENT_SECOND(second_monday, Monday)
IMPLEMENT_SECOND(second_tuesday, Tuesday)
IMPLEMENT_SECOND(second_wednesday, Wednesday)
IMPLEMENT_SECOND(second_thursday, Thursday)
IMPLEMENT_SECOND(second_friday, Friday)
IMPLEMENT_SECOND(second_saturday, Saturday)
IMPLEMENT_SECOND(second_sunday, Sunday)

#define IMPLEMENT_THIRD(day_name, weekday) \
    date scheduler::day_name() const { \
        return find_nth_day(3, weekday()); \
    }

IMPLEMENT_THIRD(third_monday, Monday)
IMPLEMENT_THIRD(third_tuesday, Tuesday)
IMPLEMENT_THIRD(third_wednesday, Wednesday)
IMPLEMENT_THIRD(third_thursday, Thursday)
IMPLEMENT_THIRD(third_friday, Friday)
IMPLEMENT_THIRD(third_saturday, Saturday)
IMPLEMENT_THIRD(third_sunday, Sunday)

#define IMPLEMENT_FOURTH(day_name, weekday) \
    date scheduler::day_name() const { \
        return find_nth_day(4, weekday()); \
    }

IMPLEMENT_FOURTH(fourth_monday, Monday)
IMPLEMENT_FOURTH(fourth_tuesday, Tuesday)
IMPLEMENT_FOURTH(fourth_wednesday, Wednesday)
IMPLEMENT_FOURTH(fourth_thursday, Thursday)
IMPLEMENT_FOURTH(fourth_friday, Friday)
IMPLEMENT_FOURTH(fourth_saturday, Saturday)
IMPLEMENT_FOURTH(fourth_sunday, Sunday)

#define IMPLEMENT_LAST(day_name, weekday) \
    date scheduler::day_name() const { \
        return find_last_day(weekday()); \
    }

IMPLEMENT_LAST(last_monday, Monday)
IMPLEMENT_LAST(last_tuesday, Tuesday)
IMPLEMENT_LAST(last_wednesday, Wednesday)
IMPLEMENT_LAST(last_thursday, Thursday)
IMPLEMENT_LAST(last_friday, Friday)
IMPLEMENT_LAST(last_saturday, Saturday)
IMPLEMENT_LAST(last_sunday, Sunday)

}  // namespace meetup
