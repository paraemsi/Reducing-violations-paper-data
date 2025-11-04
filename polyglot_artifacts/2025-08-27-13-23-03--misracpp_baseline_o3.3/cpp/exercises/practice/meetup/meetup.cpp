#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

using namespace boost::gregorian;
using boost::date_time::weekdays;

/* -------------------------------------------------------------- */
/* Construction                                                    */
/* -------------------------------------------------------------- */
scheduler::scheduler(date::year_type year, date::month_type month)
    : _year{year}, _month{month} {}

/* -------------------------------------------------------------- */
/* Internal helper                                                 */
/* -------------------------------------------------------------- */
date scheduler::day_for(weekdays wd, schedule s) const {
    /* teenth --------------------------------------------------- */
    if (s == schedule::teenth) {
        for (unsigned short d = 13; d <= 19; ++d) {
            date candidate{_year, _month, d};
            if (candidate.day_of_week() == wd)
                return candidate;
        }
        throw std::logic_error("teenth day not found");
    }

    /* last ----------------------------------------------------- */
    if (s == schedule::last) {
        unsigned short last_dom =
            gregorian_calendar::end_of_month_day(_year, _month);
        date candidate{_year, _month, last_dom};
        while (candidate.day_of_week() != wd)
            candidate -= days{1};
        return candidate;
    }

    /* first .. fourth ----------------------------------------- */
    int nth = 0;
    switch (s) {
        case schedule::first:  nth = 1; break;
        case schedule::second: nth = 2; break;
        case schedule::third:  nth = 3; break;
        case schedule::fourth: nth = 4; break;
        default: break;
    }

    if (nth == 0)
        throw std::logic_error("invalid schedule");

    date candidate{_year, _month, 1};
    while (candidate.day_of_week() != wd)
        candidate += days{1};
    candidate += days{7 * (nth - 1)};
    return candidate;
}

/* -------------------------------------------------------------- */
/* “teenth” public methods                                         */
/* -------------------------------------------------------------- */
#define DEFINE_TEENTH(name, wd) \
    date scheduler::name() const { return day_for(wd, schedule::teenth); }

DEFINE_TEENTH(monteenth,    weekdays::Monday)
DEFINE_TEENTH(tuesteenth,   weekdays::Tuesday)
DEFINE_TEENTH(wednesteenth, weekdays::Wednesday)
DEFINE_TEENTH(thursteenth,  weekdays::Thursday)
DEFINE_TEENTH(friteenth,    weekdays::Friday)
DEFINE_TEENTH(saturteenth,  weekdays::Saturday)
DEFINE_TEENTH(sunteenth,    weekdays::Sunday)

#undef DEFINE_TEENTH

/* -------------------------------------------------------------- */
/* helper macro for first/second/third/fourth/last                 */
/* -------------------------------------------------------------- */
#define DEFINE_WEEK_METHODS(prefix, sched_enum)                                         \
    date scheduler::prefix##_monday()    const { return day_for(weekdays::Monday,    schedule::sched_enum); } \
    date scheduler::prefix##_tuesday()   const { return day_for(weekdays::Tuesday,   schedule::sched_enum); } \
    date scheduler::prefix##_wednesday() const { return day_for(weekdays::Wednesday, schedule::sched_enum); } \
    date scheduler::prefix##_thursday()  const { return day_for(weekdays::Thursday,  schedule::sched_enum); } \
    date scheduler::prefix##_friday()    const { return day_for(weekdays::Friday,    schedule::sched_enum); } \
    date scheduler::prefix##_saturday()  const { return day_for(weekdays::Saturday,  schedule::sched_enum); } \
    date scheduler::prefix##_sunday()    const { return day_for(weekdays::Sunday,    schedule::sched_enum); }

DEFINE_WEEK_METHODS(first,  first)
DEFINE_WEEK_METHODS(second, second)
DEFINE_WEEK_METHODS(third,  third)
DEFINE_WEEK_METHODS(fourth, fourth)
DEFINE_WEEK_METHODS(last,   last)

#undef DEFINE_WEEK_METHODS

}  // namespace meetup
