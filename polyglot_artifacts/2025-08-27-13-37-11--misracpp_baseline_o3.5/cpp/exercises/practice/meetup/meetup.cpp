#include "meetup.h"

#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>


namespace meetup {

scheduler::scheduler(int year, unsigned int month)
    : year_{year}, month_{month} {}

// Return the requested meetup day as a std::chrono::year_month_day
boost::gregorian::date scheduler::day(boost::date_time::weekdays wd,
                                      schedule s) const
{
    std::vector<boost::gregorian::date> matches;

    int last_day = boost::gregorian::gregorian_calendar::end_of_month_day(year_, month_);

    for (int d = 1; d <= last_day; ++d) {
        boost::gregorian::date cur(year_, month_, d);
        if (cur.day_of_week().as_enum() == wd) {
            matches.push_back(cur);
        }
    }

    switch (s) {
        case schedule::first:  return matches.at(0);
        case schedule::second: return matches.at(1);
        case schedule::third:  return matches.at(2);
        case schedule::fourth: return matches.at(3);
        case schedule::fifth:  return matches.at(4);
        case schedule::last:   return matches.back();
        case schedule::teenth:
            for (const auto& d : matches) {
                int num = d.day();
                if (num >= 13 && num <= 19) {
                    return d;
                }
            }
            break;
    }
    return boost::gregorian::date{}; // not_a_date_time
}

}  // namespace meetup
