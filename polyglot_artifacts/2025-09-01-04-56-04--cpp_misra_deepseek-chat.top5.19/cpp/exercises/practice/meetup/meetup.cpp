#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

scheduler::scheduler(int year, boost::date_time::months_of_year month) : year_(year), month_(static_cast<int>(month)) {}

// Helper function to find the nth occurrence of a specific day of the week
boost::gregorian::date find_nth_weekday(int year, int month, int nth, boost::gregorian::greg_weekday weekday) {
    boost::gregorian::date first_of_month(year, month, 1);
    boost::gregorian::first_day_of_the_week_in_month fd(weekday, nth);
    return fd.get_date(year, month);
}

// Helper function to find the last occurrence of a specific day of the week
boost::gregorian::date find_last_weekday(int year, int month, boost::gregorian::greg_weekday weekday) {
    boost::gregorian::date last_of_month = boost::gregorian::date(year, month, 1).end_of_month();
    while (last_of_month.day_of_week() != weekday) {
        last_of_month -= boost::gregorian::days(1);
    }
    return last_of_month;
}

// Helper function to find teenth day (13-19) of a specific day of the week
boost::gregorian::date find_teenth_weekday(int year, int month, boost::gregorian::greg_weekday weekday) {
    for (int day = 13; day <= 19; ++day) {
        boost::gregorian::date candidate(year, month, day);
        if (candidate.day_of_week() == weekday) {
            return candidate;
        }
    }
    throw std::runtime_error("Teenth day not found");
}

// Implement all the member functions
#define IMPLEMENT_TEENTH(prefix, weekday) \
boost::gregorian::date scheduler::prefix##teenth() const { \
    return find_teenth_weekday(year_, month_, boost::gregorian::greg_weekday(boost::date_time::weekdays::weekday)); \
}

#define IMPLEMENT_FIRST(day_name, weekday) \
boost::gregorian::date scheduler::first_##day_name() const { \
    return find_nth_weekday(year_, month_, 1, boost::gregorian::greg_weekday(boost::date_time::weekdays::weekday)); \
}

#define IMPLEMENT_SECOND(day_name, weekday) \
boost::gregorian::date scheduler::second_##day_name() const { \
    return find_nth_weekday(year_, month_, 2, boost::gregorian::greg_weekday(boost::date_time::weekdays::weekday)); \
}

#define IMPLEMENT_THIRD(day_name, weekday) \
boost::gregorian::date scheduler::third_##day_name() const { \
    return find_nth_weekday(year_, month_, 3, boost::gregorian::greg_weekday(boost::date_time::weekdays::weekday)); \
}

#define IMPLEMENT_FOURTH(day_name, weekday) \
boost::gregorian::date scheduler::fourth_##day_name() const { \
    return find_nth_weekday(year_, month_, 4, boost::gregorian::greg_weekday(boost::date_time::weekdays::weekday)); \
}

#define IMPLEMENT_LAST(day_name, weekday) \
boost::gregorian::date scheduler::last_##day_name() const { \
    return find_last_weekday(year_, month_, boost::gregorian::greg_weekday(boost::date_time::weekdays::weekday)); \
}

IMPLEMENT_TEENTH(mon, Monday)
IMPLEMENT_TEENTH(tues, Tuesday)
IMPLEMENT_TEENTH(wednes, Wednesday)
IMPLEMENT_TEENTH(thurs, Thursday)
IMPLEMENT_TEENTH(fri, Friday)
IMPLEMENT_TEENTH(satur, Saturday)
IMPLEMENT_TEENTH(sun, Sunday)

IMPLEMENT_FIRST(monday, Monday)
IMPLEMENT_FIRST(tuesday, Tuesday)
IMPLEMENT_FIRST(wednesday, Wednesday)
IMPLEMENT_FIRST(thursday, Thursday)
IMPLEMENT_FIRST(friday, Friday)
IMPLEMENT_FIRST(saturday, Saturday)
IMPLEMENT_FIRST(sunday, Sunday)

IMPLEMENT_SECOND(monday, Monday)
IMPLEMENT_SECOND(tuesday, Tuesday)
IMPLEMENT_SECOND(wednesday, Wednesday)
IMPLEMENT_SECOND(thursday, Thursday)
IMPLEMENT_SECOND(friday, Friday)
IMPLEMENT_SECOND(saturday, Saturday)
IMPLEMENT_SECOND(sunday, Sunday)

IMPLEMENT_THIRD(monday, Monday)
IMPLEMENT_THIRD(tuesday, Tuesday)
IMPLEMENT_THIRD(wednesday, Wednesday)
IMPLEMENT_THIRD(thursday, Thursday)
IMPLEMENT_THIRD(friday, Friday)
IMPLEMENT_THIRD(saturday, Saturday)
IMPLEMENT_THIRD(sunday, Sunday)

IMPLEMENT_FOURTH(monday, Monday)
IMPLEMENT_FOURTH(tuesday, Tuesday)
IMPLEMENT_FOURTH(wednesday, Wednesday)
IMPLEMENT_FOURTH(thursday, Thursday)
IMPLEMENT_FOURTH(friday, Friday)
IMPLEMENT_FOURTH(saturday, Saturday)
IMPLEMENT_FOURTH(sunday, Sunday)

IMPLEMENT_LAST(monday, Monday)
IMPLEMENT_LAST(tuesday, Tuesday)
IMPLEMENT_LAST(wednesday, Wednesday)
IMPLEMENT_LAST(thursday, Thursday)
IMPLEMENT_LAST(friday, Friday)
IMPLEMENT_LAST(saturday, Saturday)
IMPLEMENT_LAST(sunday, Sunday)

}  // namespace meetup
