#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;
using boost::date_time::weekdays;

scheduler::scheduler(int year, int month) : m_year{year}, m_month{month} {}

date scheduler::get_day(weekdays wd, schedule s) const {
    const date first_day{m_year, m_month, 1};

    /* ---------- teenth ---------- */
    if (s == schedule::teenth) {
        for (int d = 13; d <= 19; ++d) {
            date candidate{m_year, m_month, d};
            if (candidate.day_of_week() == wd) {
                return candidate;
            }
        }
    }

    /* ---------- last ---------- */
    if (s == schedule::last) {
        date first_next = (m_month == 12) ? date{m_year + 1, 1, 1}
                                          : date{m_year, m_month + 1, 1};
        date last_day   = first_next - days{1};
        for (date d = last_day;; d -= days{1}) {
            if (d.day_of_week() == wd) {
                return d;
            }
        }
    }

    /* ---------- first-fourth/fifth ---------- */
    int index = 0;
    switch (s) {
        case schedule::first:  index = 0; break;
        case schedule::second: index = 1; break;
        case schedule::third:  index = 2; break;
        case schedule::fourth: index = 3; break;
        case schedule::fifth:  index = 4; break;
        default: return date{};  // unreachable for valid enum
    }

    const int diff =
        (7 + static_cast<int>(wd) - first_day.day_of_week().as_number()) % 7;
    return first_day + days{diff + 7 * index};
}

// ---------- convenience wrappers ----------
#define WEEKDAY_FN(prefix, name_token, wd_enum, sched) \
    date scheduler::prefix##_##name_token() const { \
        return get_day(boost::date_time::weekdays::wd_enum, schedule::sched); \
    }

#define TEENTH_FN(name, wd_enum) \
    date scheduler::name() const { \
        return get_day(boost::date_time::weekdays::wd_enum, schedule::teenth); \
    }

TEENTH_FN(monteenth,   Monday)
TEENTH_FN(tuesteenth,  Tuesday)
TEENTH_FN(wednesteenth,Wednesday)
TEENTH_FN(thursteenth, Thursday)
TEENTH_FN(friteenth,   Friday)
TEENTH_FN(saturteenth, Saturday)
TEENTH_FN(sunteenth,   Sunday)

WEEKDAY_FN(first,  monday,  Monday,  first)
WEEKDAY_FN(first,  tuesday, Tuesday, first)
WEEKDAY_FN(first,  wednesday, Wednesday, first)
WEEKDAY_FN(first,  thursday,  Thursday, first)
WEEKDAY_FN(first,  friday,    Friday,   first)
WEEKDAY_FN(first,  saturday,  Saturday, first)
WEEKDAY_FN(first,  sunday,    Sunday,   first)

WEEKDAY_FN(second, monday,  Monday,  second)
WEEKDAY_FN(second, tuesday, Tuesday, second)
WEEKDAY_FN(second, wednesday, Wednesday, second)
WEEKDAY_FN(second, thursday,  Thursday, second)
WEEKDAY_FN(second, friday,    Friday,   second)
WEEKDAY_FN(second, saturday,  Saturday, second)
WEEKDAY_FN(second, sunday,    Sunday,   second)

WEEKDAY_FN(third,  monday,  Monday,  third)
WEEKDAY_FN(third,  tuesday, Tuesday, third)
WEEKDAY_FN(third,  wednesday, Wednesday, third)
WEEKDAY_FN(third,  thursday,  Thursday, third)
WEEKDAY_FN(third,  friday,    Friday,   third)
WEEKDAY_FN(third,  saturday,  Saturday, third)
WEEKDAY_FN(third,  sunday,    Sunday,   third)

WEEKDAY_FN(fourth, monday,  Monday,  fourth)
WEEKDAY_FN(fourth, tuesday, Tuesday, fourth)
WEEKDAY_FN(fourth, wednesday, Wednesday, fourth)
WEEKDAY_FN(fourth, thursday,  Thursday, fourth)
WEEKDAY_FN(fourth, friday,    Friday,   fourth)
WEEKDAY_FN(fourth, saturday,  Saturday, fourth)
WEEKDAY_FN(fourth, sunday,    Sunday,   fourth)

WEEKDAY_FN(last,   monday,  Monday,  last)
WEEKDAY_FN(last,   tuesday, Tuesday, last)
WEEKDAY_FN(last,   wednesday, Wednesday, last)
WEEKDAY_FN(last,   thursday,  Thursday, last)
WEEKDAY_FN(last,   friday,    Friday,   last)
WEEKDAY_FN(last,   saturday,  Saturday, last)
WEEKDAY_FN(last,   sunday,    Sunday,   last)

#undef WEEKDAY_FN
#undef TEENTH_FN

}  // namespace meetup
