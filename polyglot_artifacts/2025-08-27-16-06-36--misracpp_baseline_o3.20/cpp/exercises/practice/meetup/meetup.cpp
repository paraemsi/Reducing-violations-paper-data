#include "meetup.h"
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(int year, unsigned int month)
    : _year(year), _month(static_cast<int>(month)) {
    if (month < 1 || month > 12) {
        throw std::invalid_argument("Invalid month value");
    }
}

boost::gregorian::date scheduler::day(boost::date_time::weekdays wd, schedule s) const {
    using namespace boost::gregorian;
    using boost::date_time::weekdays;

    date first_day(_year, _month, 1);
    weekdays first_wd = first_day.day_of_week().as_enum();

    int diff = (static_cast<int>(wd) - static_cast<int>(first_wd) + 7) % 7;
    date first_occurrence = first_day + days(diff);

    switch (s) {
        case schedule::first:
            return first_occurrence;
        case schedule::second:
            return first_occurrence + days(7);
        case schedule::third:
            return first_occurrence + days(14);
        case schedule::fourth:
            return first_occurrence + days(21);
        case schedule::teenth: {
            date d(_year, _month, 13);
            for (int i = 0; i < 7; ++i, d += days(1)) {
                if (d.day_of_week().as_enum() == wd) {
                    return d;
                }
            }
            throw std::logic_error("Teenth day not found");
        }
        case schedule::last: {
            date first_next_month = (_month == 12) ? date(_year + 1, 1, 1)
                                                   : date(_year, _month + 1, 1);
            date last_day = first_next_month - days(1);
            while (last_day.day_of_week().as_enum() != wd) {
                last_day -= days(1);
            }
            return last_day;
        }
    }
    throw std::logic_error("Invalid schedule");
}

#define MEETUP_DEFINE_METHOD(name, weekday_enum, sched_enum) \
boost::gregorian::date scheduler::name() const { \
    return day(boost::date_time::weekday_enum, schedule::sched_enum); \
}

MEETUP_DEFINE_METHOD(monteenth, Monday, teenth)
MEETUP_DEFINE_METHOD(tuesteenth, Tuesday, teenth)
MEETUP_DEFINE_METHOD(wednesteenth, Wednesday, teenth)
MEETUP_DEFINE_METHOD(thursteenth, Thursday, teenth)
MEETUP_DEFINE_METHOD(friteenth, Friday, teenth)
MEETUP_DEFINE_METHOD(saturteenth, Saturday, teenth)
MEETUP_DEFINE_METHOD(sunteenth, Sunday, teenth)

MEETUP_DEFINE_METHOD(first_monday, Monday, first)
MEETUP_DEFINE_METHOD(first_tuesday, Tuesday, first)
MEETUP_DEFINE_METHOD(first_wednesday, Wednesday, first)
MEETUP_DEFINE_METHOD(first_thursday, Thursday, first)
MEETUP_DEFINE_METHOD(first_friday, Friday, first)
MEETUP_DEFINE_METHOD(first_saturday, Saturday, first)
MEETUP_DEFINE_METHOD(first_sunday, Sunday, first)

MEETUP_DEFINE_METHOD(second_monday, Monday, second)
MEETUP_DEFINE_METHOD(second_tuesday, Tuesday, second)
MEETUP_DEFINE_METHOD(second_wednesday, Wednesday, second)
MEETUP_DEFINE_METHOD(second_thursday, Thursday, second)
MEETUP_DEFINE_METHOD(second_friday, Friday, second)
MEETUP_DEFINE_METHOD(second_saturday, Saturday, second)
MEETUP_DEFINE_METHOD(second_sunday, Sunday, second)

MEETUP_DEFINE_METHOD(third_monday, Monday, third)
MEETUP_DEFINE_METHOD(third_tuesday, Tuesday, third)
MEETUP_DEFINE_METHOD(third_wednesday, Wednesday, third)
MEETUP_DEFINE_METHOD(third_thursday, Thursday, third)
MEETUP_DEFINE_METHOD(third_friday, Friday, third)
MEETUP_DEFINE_METHOD(third_saturday, Saturday, third)
MEETUP_DEFINE_METHOD(third_sunday, Sunday, third)

MEETUP_DEFINE_METHOD(fourth_monday, Monday, fourth)
MEETUP_DEFINE_METHOD(fourth_tuesday, Tuesday, fourth)
MEETUP_DEFINE_METHOD(fourth_wednesday, Wednesday, fourth)
MEETUP_DEFINE_METHOD(fourth_thursday, Thursday, fourth)
MEETUP_DEFINE_METHOD(fourth_friday, Friday, fourth)
MEETUP_DEFINE_METHOD(fourth_saturday, Saturday, fourth)
MEETUP_DEFINE_METHOD(fourth_sunday, Sunday, fourth)

MEETUP_DEFINE_METHOD(last_monday, Monday, last)
MEETUP_DEFINE_METHOD(last_tuesday, Tuesday, last)
MEETUP_DEFINE_METHOD(last_wednesday, Wednesday, last)
MEETUP_DEFINE_METHOD(last_thursday, Thursday, last)
MEETUP_DEFINE_METHOD(last_friday, Friday, last)
MEETUP_DEFINE_METHOD(last_saturday, Saturday, last)
MEETUP_DEFINE_METHOD(last_sunday, Sunday, last)

#undef MEETUP_DEFINE_METHOD

}  // namespace meetup
