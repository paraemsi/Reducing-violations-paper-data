#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;

// ctor
scheduler::scheduler(boost::gregorian::months_of_year month, int year)
    : year_{year}, month_{month} {}

// internal helper ------------------------------------------------------------
boost::gregorian::date
scheduler::get_date(boost::date_time::weekdays wd, schedule s) const {
    using namespace boost::gregorian;
    switch (s) {
        case schedule::teenth: {
            for (int d = 13; d <= 19; ++d) {
                date dt(year_, static_cast<unsigned short>(month_), d);
                if (dt.day_of_week().as_enum() == wd) {
                    return dt;
                }
            }
            break;
        }
        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth: {
            int skip_weeks = 0;
            switch (s) {
                case schedule::first:  skip_weeks = 0; break;
                case schedule::second: skip_weeks = 1; break;
                case schedule::third:  skip_weeks = 2; break;
                case schedule::fourth: skip_weeks = 3; break;
                default: break;
            }
            date dt(year_, static_cast<unsigned short>(month_), 1);
            while (dt.day_of_week().as_enum() != wd) {
                dt += days(1);
            }
            dt += days(7 * skip_weeks);
            return dt;
        }
        case schedule::last: {
            unsigned short last_dom =
                gregorian_calendar::end_of_month_day(year_,
                                                     static_cast<unsigned short>(month_));
            date dt(year_, static_cast<unsigned short>(month_), last_dom);
            while (dt.day_of_week().as_enum() != wd) {
                dt -= days(1);
            }
            return dt;
        }
    }
    throw std::logic_error("invalid schedule");
}

// macro helpers to generate the boiler-plate ---------------------------------
#define DEFINE_TEENTH(fn, day_) \
    boost::gregorian::date scheduler::fn() const { \
        return get_date(boost::date_time::day_, schedule::teenth); \
    }

#define DEFINE_NTH(fn, day_, sched_) \
    boost::gregorian::date scheduler::fn() const { \
        return get_date(boost::date_time::day_, schedule::sched_); \
    }

// teenths
DEFINE_TEENTH(monteenth, Monday)
DEFINE_TEENTH(tuesteenth, Tuesday)
DEFINE_TEENTH(wednesteenth, Wednesday)
DEFINE_TEENTH(thursteenth, Thursday)
DEFINE_TEENTH(friteenth, Friday)
DEFINE_TEENTH(saturteenth, Saturday)
DEFINE_TEENTH(sunteenth, Sunday)

// first
DEFINE_NTH(first_monday,    Monday,    first)
DEFINE_NTH(first_tuesday,   Tuesday,   first)
DEFINE_NTH(first_wednesday, Wednesday, first)
DEFINE_NTH(first_thursday,  Thursday,  first)
DEFINE_NTH(first_friday,    Friday,    first)
DEFINE_NTH(first_saturday,  Saturday,  first)
DEFINE_NTH(first_sunday,    Sunday,    first)

// second
DEFINE_NTH(second_monday,    Monday,    second)
DEFINE_NTH(second_tuesday,   Tuesday,   second)
DEFINE_NTH(second_wednesday, Wednesday, second)
DEFINE_NTH(second_thursday,  Thursday,  second)
DEFINE_NTH(second_friday,    Friday,    second)
DEFINE_NTH(second_saturday,  Saturday,  second)
DEFINE_NTH(second_sunday,    Sunday,    second)

// third
DEFINE_NTH(third_monday,    Monday,    third)
DEFINE_NTH(third_tuesday,   Tuesday,   third)
DEFINE_NTH(third_wednesday, Wednesday, third)
DEFINE_NTH(third_thursday,  Thursday,  third)
DEFINE_NTH(third_friday,    Friday,    third)
DEFINE_NTH(third_saturday,  Saturday,  third)
DEFINE_NTH(third_sunday,    Sunday,    third)

// fourth
DEFINE_NTH(fourth_monday,    Monday,    fourth)
DEFINE_NTH(fourth_tuesday,   Tuesday,   fourth)
DEFINE_NTH(fourth_wednesday, Wednesday, fourth)
DEFINE_NTH(fourth_thursday,  Thursday,  fourth)
DEFINE_NTH(fourth_friday,    Friday,    fourth)
DEFINE_NTH(fourth_saturday,  Saturday,  fourth)
DEFINE_NTH(fourth_sunday,    Sunday,    fourth)

// last
DEFINE_NTH(last_monday,    Monday,    last)
DEFINE_NTH(last_tuesday,   Tuesday,   last)
DEFINE_NTH(last_wednesday, Wednesday, last)
DEFINE_NTH(last_thursday,  Thursday,  last)
DEFINE_NTH(last_friday,    Friday,    last)
DEFINE_NTH(last_saturday,  Saturday,  last)
DEFINE_NTH(last_sunday,    Sunday,    last)

// cleanup macros
#undef DEFINE_TEENTH
#undef DEFINE_NTH

}  // namespace meetup
