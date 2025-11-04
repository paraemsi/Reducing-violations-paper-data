#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

namespace {
    using boost::gregorian::date;
    using boost::gregorian::days;
    using boost::date_time::weekdays;

    // Return the last day of the given month.
    date end_of_month(int y, unsigned int m) {
        unsigned short last = boost::gregorian::gregorian_calendar::end_of_month_day(y, m);
        return date(y, m, last);
    }

    // Find the first occurrence of the weekday on or after the given date.
    date find_from(date start, weekdays wd) {
        for (int i = 0; i < 7; ++i, start += days{1}) {
            if (start.day_of_week() == wd)
                return start;
        }
        throw std::logic_error("weekday not found");
    }
}

/**
 * Compute requested meetup day.
 */
boost::gregorian::date
scheduler::meetup_day(boost::date_time::weekdays wd, schedule sc) const
{
    using boost::gregorian::date;
    using boost::gregorian::days;

    if (m_month < 1 || m_month > 12)
        throw std::invalid_argument("Invalid month");

    date start(m_year, m_month, 1);

    switch (sc) {
        case schedule::teenth:
            return find_from(date(m_year, m_month, 13), wd);
        case schedule::first:
            return find_from(start, wd);
        case schedule::second:
            return find_from(start + days{7}, wd);
        case schedule::third:
            return find_from(start + days{14}, wd);
        case schedule::fourth:
            return find_from(start + days{21}, wd);
        case schedule::last: {
            date cur = end_of_month(m_year, m_month);
            for (int i = 0; i < 7; ++i, cur -= days{1}) {
                if (cur.day_of_week() == wd)
                    return cur;
            }
            break;
        }
    }
    throw std::logic_error("Requested meetup day does not exist");
}

}  // namespace meetup
