#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(int month, int year)
    : m_month{month}, m_year{year} {}


// days in a month, Gregorian calendar
static unsigned days_in_month(int year, int month) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2: {
            const bool leap = (year % 4 == 0 && year % 100 != 0) ||
                              (year % 400 == 0);
            return leap ? 29 : 28;
        }
        default:
            throw std::invalid_argument("Month out of range");
    }
}

boost::gregorian::date scheduler::get_day(boost::gregorian::greg_weekday target,
                                          schedule sched) const {
    using namespace boost::gregorian;

    if (m_month < 1 || m_month > 12)
        throw std::invalid_argument("Month out of range");

    if (sched == schedule::teenth) {
        for (unsigned d = 13; d <= 19; ++d) {
            date dt{m_year, m_month, d};
            if (dt.day_of_week() == target)
                return dt;
        }
    } else if (sched == schedule::last) {
        unsigned last = days_in_month(m_year, m_month);
        for (int d = static_cast<int>(last); d >= 1; --d) {
            date dt{m_year, m_month, static_cast<unsigned>(d)};
            if (dt.day_of_week() == target)
                return dt;
        }
    } else {
        int target_index = 0;
        switch (sched) {
            case schedule::first:  target_index = 1; break;
            case schedule::second: target_index = 2; break;
            case schedule::third:  target_index = 3; break;
            case schedule::fourth: target_index = 4; break;
            case schedule::fifth:  target_index = 5; break;
            default: break;
        }

        int index = 0;
        for (unsigned d = 1; d <= days_in_month(m_year, m_month); ++d) {
            date dt{m_year, m_month, d};
            if (dt.day_of_week() == target && ++index == target_index)
                return dt;
        }
    }

    throw std::domain_error("Requested meetup day does not exist");
}

#define MEETUP_DEFINE_NAMED(name, weekday_const, sched_enum)                              \
boost::gregorian::date scheduler::name() const {                                          \
    return get_day(boost::gregorian::greg_weekday(boost::date_time::weekday_const),       \
                   schedule::sched_enum);                                                 \
}

MEETUP_DEFINE_NAMED(monteenth,  Monday, teenth)
MEETUP_DEFINE_NAMED(tuesteenth, Tuesday, teenth)
MEETUP_DEFINE_NAMED(wednesteenth, Wednesday, teenth)
MEETUP_DEFINE_NAMED(thursteenth, Thursday, teenth)
MEETUP_DEFINE_NAMED(friteenth,  Friday, teenth)
MEETUP_DEFINE_NAMED(saturteenth, Saturday, teenth)
MEETUP_DEFINE_NAMED(sunteenth, Sunday, teenth)

MEETUP_DEFINE_NAMED(first_monday,    Monday, first)
MEETUP_DEFINE_NAMED(first_tuesday,   Tuesday, first)
MEETUP_DEFINE_NAMED(first_wednesday, Wednesday, first)
MEETUP_DEFINE_NAMED(first_thursday,  Thursday, first)
MEETUP_DEFINE_NAMED(first_friday,    Friday, first)
MEETUP_DEFINE_NAMED(first_saturday,  Saturday, first)
MEETUP_DEFINE_NAMED(first_sunday,    Sunday, first)

MEETUP_DEFINE_NAMED(second_monday,    Monday, second)
MEETUP_DEFINE_NAMED(second_tuesday,   Tuesday, second)
MEETUP_DEFINE_NAMED(second_wednesday, Wednesday, second)
MEETUP_DEFINE_NAMED(second_thursday,  Thursday, second)
MEETUP_DEFINE_NAMED(second_friday,    Friday, second)
MEETUP_DEFINE_NAMED(second_saturday,  Saturday, second)
MEETUP_DEFINE_NAMED(second_sunday,    Sunday, second)

MEETUP_DEFINE_NAMED(third_monday,    Monday, third)
MEETUP_DEFINE_NAMED(third_tuesday,   Tuesday, third)
MEETUP_DEFINE_NAMED(third_wednesday, Wednesday, third)
MEETUP_DEFINE_NAMED(third_thursday,  Thursday, third)
MEETUP_DEFINE_NAMED(third_friday,    Friday, third)
MEETUP_DEFINE_NAMED(third_saturday,  Saturday, third)
MEETUP_DEFINE_NAMED(third_sunday,    Sunday, third)

MEETUP_DEFINE_NAMED(fourth_monday,    Monday, fourth)
MEETUP_DEFINE_NAMED(fourth_tuesday,   Tuesday, fourth)
MEETUP_DEFINE_NAMED(fourth_wednesday, Wednesday, fourth)
MEETUP_DEFINE_NAMED(fourth_thursday,  Thursday, fourth)
MEETUP_DEFINE_NAMED(fourth_friday,    Friday, fourth)
MEETUP_DEFINE_NAMED(fourth_saturday,  Saturday, fourth)
MEETUP_DEFINE_NAMED(fourth_sunday,    Sunday, fourth)

MEETUP_DEFINE_NAMED(last_monday,    Monday, last)
MEETUP_DEFINE_NAMED(last_tuesday,   Tuesday, last)
MEETUP_DEFINE_NAMED(last_wednesday, Wednesday, last)
MEETUP_DEFINE_NAMED(last_thursday,  Thursday, last)
MEETUP_DEFINE_NAMED(last_friday,    Friday, last)
MEETUP_DEFINE_NAMED(last_saturday,  Saturday, last)
MEETUP_DEFINE_NAMED(last_sunday,    Sunday, last)

#undef MEETUP_DEFINE_NAMED

}  // namespace meetup
