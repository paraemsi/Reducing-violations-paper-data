#include "meetup.h"
#include <stdexcept>
#include <algorithm>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {



/* ======================================================================
 *              Implementation of class `scheduler`
 * ====================================================================*/
scheduler::scheduler(boost::gregorian::months_of_year month, int year)
    : year_{year}, month_{month} {}

boost::gregorian::date scheduler::compute(boost::gregorian::greg_weekday weekday,
                                          schedule sched) const {
    using namespace boost::gregorian;

    /* teenth -----------------------------------------------------------*/
    if (sched == schedule::teenth) {
        for (day_type d = 13; d <= 19; ++d) {
            date dt{year_, month_, d};
            if (dt.day_of_week() == weekday) {
                return dt;
            }
        }
        throw std::logic_error{"teenth day not found"};
    }

    /* last -------------------------------------------------------------*/
    const unsigned eom = gregorian_calendar::end_of_month_day(year_, month_);
    if (sched == schedule::last) {
        for (day_type d = eom; d >= 1; --d) {
            date dt{year_, month_, d};
            if (dt.day_of_week() == weekday) {
                return dt;
            }
        }
        throw std::logic_error{"last weekday not found"};
    }

    /* first/second/third/fourth ---------------------------------------*/
    unsigned index = 0;
    switch (sched) {
        case schedule::first:  index = 0; break;
        case schedule::second: index = 1; break;
        case schedule::third:  index = 2; break;
        case schedule::fourth: index = 3; break;
        default: break;
    }

    const date first_of_month{year_, month_, 1};
    unsigned first_wd = first_of_month.day_of_week().as_number(); /* 0-6 */
    unsigned want_wd  = weekday.as_number();
    unsigned offset   = (want_wd + 7u - first_wd) % 7u;
    unsigned day      = 1u + offset + 7u * index;

    if (day > eom) {
        throw std::logic_error{"weekday occurrence not present in month"};
    }
    return date{year_, month_, static_cast<day_type>(day)};
}

/* ---------- helper macros to generate the many thin wrappers ---------*/
#define DEFINE_TEENTH(method, WD_CONST) \
    boost::gregorian::date scheduler::method() const { \
        return compute(boost::gregorian::greg_weekday{boost::date_time::WD_CONST}, \
                       schedule::teenth); \
    }

#define DEFINE_NTH(prefix, sched, method, WD_CONST) \
    boost::gregorian::date scheduler::prefix##_##method() const { \
        return compute(boost::gregorian::greg_weekday{boost::date_time::WD_CONST}, \
                       schedule::sched); \
    }

#define DEFINE_LAST(method, WD_CONST) \
    boost::gregorian::date scheduler::last_##method() const { \
        return compute(boost::gregorian::greg_weekday{boost::date_time::WD_CONST}, \
                       schedule::last); \
    }

/* teenths */
DEFINE_TEENTH(monteenth,  Monday)
DEFINE_TEENTH(tuesteenth, Tuesday)
DEFINE_TEENTH(wednesteenth, Wednesday)
DEFINE_TEENTH(thursteenth, Thursday)
DEFINE_TEENTH(friteenth,  Friday)
DEFINE_TEENTH(saturteenth, Saturday)
DEFINE_TEENTH(sunteenth,  Sunday)

/* first */
DEFINE_NTH(first,  first,  monday,    Monday)
DEFINE_NTH(first,  first,  tuesday,   Tuesday)
DEFINE_NTH(first,  first,  wednesday, Wednesday)
DEFINE_NTH(first,  first,  thursday,  Thursday)
DEFINE_NTH(first,  first,  friday,    Friday)
DEFINE_NTH(first,  first,  saturday,  Saturday)
DEFINE_NTH(first,  first,  sunday,    Sunday)

/* second */
DEFINE_NTH(second, second, monday,    Monday)
DEFINE_NTH(second, second, tuesday,   Tuesday)
DEFINE_NTH(second, second, wednesday, Wednesday)
DEFINE_NTH(second, second, thursday,  Thursday)
DEFINE_NTH(second, second, friday,    Friday)
DEFINE_NTH(second, second, saturday,  Saturday)
DEFINE_NTH(second, second, sunday,    Sunday)

/* third */
DEFINE_NTH(third,  third,  monday,    Monday)
DEFINE_NTH(third,  third,  tuesday,   Tuesday)
DEFINE_NTH(third,  third,  wednesday, Wednesday)
DEFINE_NTH(third,  third,  thursday,  Thursday)
DEFINE_NTH(third,  third,  friday,    Friday)
DEFINE_NTH(third,  third,  saturday,  Saturday)
DEFINE_NTH(third,  third,  sunday,    Sunday)

/* fourth */
DEFINE_NTH(fourth, fourth, monday,    Monday)
DEFINE_NTH(fourth, fourth, tuesday,   Tuesday)
DEFINE_NTH(fourth, fourth, wednesday, Wednesday)
DEFINE_NTH(fourth, fourth, thursday,  Thursday)
DEFINE_NTH(fourth, fourth, friday,    Friday)
DEFINE_NTH(fourth, fourth, saturday,  Saturday)
DEFINE_NTH(fourth, fourth, sunday,    Sunday)

/* last */
DEFINE_LAST(monday,    Monday)
DEFINE_LAST(tuesday,   Tuesday)
DEFINE_LAST(wednesday, Wednesday)
DEFINE_LAST(thursday,  Thursday)
DEFINE_LAST(friday,    Friday)
DEFINE_LAST(saturday,  Saturday)
DEFINE_LAST(sunday,    Sunday)

#undef DEFINE_TEENTH
#undef DEFINE_NTH
#undef DEFINE_LAST

}  // namespace meetup
