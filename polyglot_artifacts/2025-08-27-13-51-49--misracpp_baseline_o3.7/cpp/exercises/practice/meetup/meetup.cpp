#include "meetup.h"
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {

inline unsigned days_in_month(int year, unsigned month) {
    return boost::gregorian::gregorian_calendar::end_of_month_day(year, month);
}

} // namespace

boost::gregorian::date meetup_day(int year, unsigned month,
                                  boost::gregorian::greg_weekday weekday,
                                  schedule sched) {
    using namespace boost::gregorian;

    if (month < 1 || month > 12) {
        throw std::invalid_argument("month must be 1..12");
    }

    auto compute_from_first = [&](unsigned index) -> date {
        date first(year, month, 1);
        unsigned first_wd = first.day_of_week();      // 0 = Sunday
        unsigned target_wd = weekday.as_number();      // 0 = Sunday
        unsigned offset = (target_wd + 7 - first_wd) % 7;
        unsigned d = 1 + offset + index * 7;
        if (d > days_in_month(year, month)) {
            throw std::domain_error("Requested occurrence does not exist in this month");
        }
        return date(year, month, d);
    };

    switch (sched) {
        case schedule::teenth: {
            for (unsigned d = 13; d <= 19; ++d) {
                if (date(year, month, d).day_of_week() == weekday) {
                    return date(year, month, d);
                }
            }
            break; // should not reach
        }
        case schedule::first:
            return compute_from_first(0);
        case schedule::second:
            return compute_from_first(1);
        case schedule::third:
            return compute_from_first(2);
        case schedule::fourth:
            return compute_from_first(3);
        case schedule::fifth:
            return compute_from_first(4);
        case schedule::last: {
            unsigned last_day = days_in_month(year, month);
            date last_date(year, month, last_day);
            unsigned last_wd = last_date.day_of_week();
            unsigned target_wd = weekday.as_number();
            unsigned offset = (last_wd + 7 - target_wd) % 7;
            unsigned d = last_day - offset;
            return date(year, month, d);
        }
    }
    throw std::logic_error("Unable to compute meetup day");
}

scheduler::scheduler(int year, unsigned month)
    : m_year(year), m_month(month) {}

boost::gregorian::date scheduler::get_day(boost::gregorian::greg_weekday weekday,
                                          schedule sched) const {
    return meetup_day(m_year, m_month, weekday, sched);
}

}  // namespace meetup
