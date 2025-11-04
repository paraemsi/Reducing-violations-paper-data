#include "meetup.h"
#include <map>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper function to find the nth weekday
date scheduler::find_nth_weekday(int nth, greg_weekday weekday) const {
    date start_date(year_, month_, 1);
    int count = 0;
    for (day_iterator itr(start_date); itr->month() == month_; ++itr) {
        if (itr->day_of_week() == weekday) {
            count++;
            if (count == nth) {
                return *itr;
            }
        }
    }
    throw std::runtime_error("Date not found");
}

// Helper function to find teenth day
date scheduler::find_teenth(greg_weekday weekday) const {
    for (int day = 13; day <= 19; day++) {
        date current_date(year_, month_, day);
        if (current_date.day_of_week() == weekday) {
            return current_date;
        }
    }
    throw std::runtime_error("Teenth day not found");
}

// Helper function to find last weekday
date scheduler::find_last(greg_weekday weekday) const {
    date end_date(year_, month_, 1);
    end_date = end_date.end_of_month();
    for (day_iterator itr(end_date); itr->month() == month_; --itr) {
        if (itr->day_of_week() == weekday) {
            return *itr;
        }
    }
    throw std::runtime_error("Last weekday not found");
}

// Implement all the interface functions
#define IMPLEMENT_TEENTH(day_name, weekday_num) \
    date scheduler::day_name##teenth() const { \
        return find_teenth(greg_weekday(weekday_num)); \
    }

IMPLEMENT_TEENTH(mon, 1)
IMPLEMENT_TEENTH(tues, 2)
IMPLEMENT_TEENTH(wednes, 3)
IMPLEMENT_TEENTH(thurs, 4)
IMPLEMENT_TEENTH(fri, 5)
IMPLEMENT_TEENTH(satur, 6)
IMPLEMENT_TEENTH(sun, 0)

#define IMPLEMENT_WEEK(prefix, nth, day_name, weekday_num) \
    date scheduler::prefix##_##day_name() const { \
        return find_nth_weekday(nth, greg_weekday(weekday_num)); \
    }

#define IMPLEMENT_FIRST(day_name, weekday_num) IMPLEMENT_WEEK(first, 1, day_name, weekday_num)
#define IMPLEMENT_SECOND(day_name, weekday_num) IMPLEMENT_WEEK(second, 2, day_name, weekday_num)
#define IMPLEMENT_THIRD(day_name, weekday_num) IMPLEMENT_WEEK(third, 3, day_name, weekday_num)
#define IMPLEMENT_FOURTH(day_name, weekday_num) IMPLEMENT_WEEK(fourth, 4, day_name, weekday_num)

IMPLEMENT_FIRST(monday, 1)
IMPLEMENT_FIRST(tuesday, 2)
IMPLEMENT_FIRST(wednesday, 3)
IMPLEMENT_FIRST(thursday, 4)
IMPLEMENT_FIRST(friday, 5)
IMPLEMENT_FIRST(saturday, 6)
IMPLEMENT_FIRST(sunday, 0)

IMPLEMENT_SECOND(monday, 1)
IMPLEMENT_SECOND(tuesday, 2)
IMPLEMENT_SECOND(wednesday, 3)
IMPLEMENT_SECOND(thursday, 4)
IMPLEMENT_SECOND(friday, 5)
IMPLEMENT_SECOND(saturday, 6)
IMPLEMENT_SECOND(sunday, 0)

IMPLEMENT_THIRD(monday, 1)
IMPLEMENT_THIRD(tuesday, 2)
IMPLEMENT_THIRD(wednesday, 3)
IMPLEMENT_THIRD(thursday, 4)
IMPLEMENT_THIRD(friday, 5)
IMPLEMENT_THIRD(saturday, 6)
IMPLEMENT_THIRD(sunday, 0)

IMPLEMENT_FOURTH(monday, 1)
IMPLEMENT_FOURTH(tuesday, 2)
IMPLEMENT_FOURTH(wednesday, 3)
IMPLEMENT_FOURTH(thursday, 4)
IMPLEMENT_FOURTH(friday, 5)
IMPLEMENT_FOURTH(saturday, 6)
IMPLEMENT_FOURTH(sunday, 0)

#define IMPLEMENT_LAST(day_name, weekday_num) \
    date scheduler::last_##day_name() const { \
        return find_last(greg_weekday(weekday_num)); \
    }

IMPLEMENT_LAST(monday, 1)
IMPLEMENT_LAST(tuesday, 2)
IMPLEMENT_LAST(wednesday, 3)
IMPLEMENT_LAST(thursday, 4)
IMPLEMENT_LAST(friday, 5)
IMPLEMENT_LAST(saturday, 6)
IMPLEMENT_LAST(sunday, 0)

}  // namespace meetup
