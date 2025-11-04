#include "meetup.h"
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(int year, unsigned int month)
    : year_{year}, month_{month} {
    if (month_ < 1 || month_ > 12) {
        throw std::invalid_argument("month must be in range 1..12");
    }
}

boost::gregorian::date scheduler::get_day(const boost::gregorian::greg_weekday& wd,
                                          schedule sc) const {
    using namespace boost::gregorian;

    auto matches = [&wd](const date& d) { return d.day_of_week() == wd; };

    if (sc == schedule::teenth) {
        for (unsigned d = 13; d <= 19; ++d) {
            date dt(year_, month_, d);
            if (matches(dt)) return dt;
        }
    } else if (sc == schedule::last) {
        const unsigned last_dom = gregorian_calendar::end_of_month_day(year_, month_);
        for (int d = static_cast<int>(last_dom); d >= static_cast<int>(last_dom) - 6; --d) {
            date dt(year_, month_, static_cast<unsigned>(d));
            if (matches(dt)) return dt;
        }
    } else {
        int week_index = 0;
        switch (sc) {
            case schedule::first:  week_index = 0; break;
            case schedule::second: week_index = 1; break;
            case schedule::third:  week_index = 2; break;
            case schedule::fourth: week_index = 3; break;
            default: break;
        }
        unsigned start_day = 1 + static_cast<unsigned>(week_index) * 7;
        unsigned end_day   = start_day + 6;
        for (unsigned d = start_day; d <= end_day; ++d) {
            date dt(year_, month_, d);
            if (matches(dt)) return dt;
        }
    }
    throw std::logic_error("Requested meetup day does not exist");
}

#define MAKE_METHOD(name, weekday_token, sched_const)                         \
    boost::gregorian::date scheduler::name() const {                          \
        return get_day(                                                       \
            boost::gregorian::greg_weekday(boost::date_time::weekday_token),  \
            schedule::sched_const);                                           \
    }

MAKE_METHOD(monteenth, Monday, teenth)
MAKE_METHOD(tuesteenth, Tuesday, teenth)
MAKE_METHOD(wednesteenth, Wednesday, teenth)
MAKE_METHOD(thursteenth, Thursday, teenth)
MAKE_METHOD(friteenth, Friday, teenth)
MAKE_METHOD(saturteenth, Saturday, teenth)
MAKE_METHOD(sunteenth, Sunday, teenth)

MAKE_METHOD(first_monday, Monday, first)
MAKE_METHOD(first_tuesday, Tuesday, first)
MAKE_METHOD(first_wednesday, Wednesday, first)
MAKE_METHOD(first_thursday, Thursday, first)
MAKE_METHOD(first_friday, Friday, first)
MAKE_METHOD(first_saturday, Saturday, first)
MAKE_METHOD(first_sunday, Sunday, first)

MAKE_METHOD(second_monday, Monday, second)
MAKE_METHOD(second_tuesday, Tuesday, second)
MAKE_METHOD(second_wednesday, Wednesday, second)
MAKE_METHOD(second_thursday, Thursday, second)
MAKE_METHOD(second_friday, Friday, second)
MAKE_METHOD(second_saturday, Saturday, second)
MAKE_METHOD(second_sunday, Sunday, second)

MAKE_METHOD(third_monday, Monday, third)
MAKE_METHOD(third_tuesday, Tuesday, third)
MAKE_METHOD(third_wednesday, Wednesday, third)
MAKE_METHOD(third_thursday, Thursday, third)
MAKE_METHOD(third_friday, Friday, third)
MAKE_METHOD(third_saturday, Saturday, third)
MAKE_METHOD(third_sunday, Sunday, third)

MAKE_METHOD(fourth_monday, Monday, fourth)
MAKE_METHOD(fourth_tuesday, Tuesday, fourth)
MAKE_METHOD(fourth_wednesday, Wednesday, fourth)
MAKE_METHOD(fourth_thursday, Thursday, fourth)
MAKE_METHOD(fourth_friday, Friday, fourth)
MAKE_METHOD(fourth_saturday, Saturday, fourth)
MAKE_METHOD(fourth_sunday, Sunday, fourth)

MAKE_METHOD(last_monday, Monday, last)
MAKE_METHOD(last_tuesday, Tuesday, last)
MAKE_METHOD(last_wednesday, Wednesday, last)
MAKE_METHOD(last_thursday, Thursday, last)
MAKE_METHOD(last_friday, Friday, last)
MAKE_METHOD(last_saturday, Saturday, last)
MAKE_METHOD(last_sunday, Sunday, last)

#undef MAKE_METHOD

}  // namespace meetup
