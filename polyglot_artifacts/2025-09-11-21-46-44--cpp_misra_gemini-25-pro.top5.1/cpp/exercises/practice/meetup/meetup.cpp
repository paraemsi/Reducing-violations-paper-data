#include "meetup.h"
#include <stdexcept>

namespace meetup {

scheduler::scheduler(boost::gregorian::greg_month month,
                     boost::gregorian::greg_year year)
    : month_{month}, year_{year} {}

boost::gregorian::date scheduler::day(
    boost::gregorian::greg_weekday weekday, week schedule) const {
    using boost::gregorian::date;
    using boost::gregorian::days;
    using boost::gregorian::first_day_of_the_week_in_month;
    using boost::gregorian::last_day_of_the_week_in_month;
    using boost::gregorian::weeks;

    switch (schedule) {
        case week::first: {
            return first_day_of_the_week_in_month(weekday, month_)
                .get_date(year_);
        }
        case week::second: {
            return (first_day_of_the_week_in_month(weekday, month_)
                       .get_date(year_)) +
                   weeks(1);
        }
        case week::third: {
            return (first_day_of_the_week_in_month(weekday, month_)
                       .get_date(year_)) +
                   weeks(2);
        }
        case week::fourth: {
            return (first_day_of_the_week_in_month(weekday, month_)
                       .get_date(year_)) +
                   weeks(3);
        }
        case week::last: {
            return last_day_of_the_week_in_month(weekday, month_)
                .get_date(year_);
        }
        case week::teenth: {
            date d{year_, month_, 13};
            while ((d.day_of_week()) != weekday) {
                d += days(1);
            }
            return d;
        }
    }

    throw std::logic_error("Invalid week schedule.");
}

}  // namespace meetup
