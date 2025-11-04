#include "meetup.h"
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(int year, unsigned month)
    : year_{year}, month_{month} {}

boost::gregorian::date scheduler::day(boost::date_time::weekdays wd, schedule s) const {
    using namespace boost::gregorian;

    if (month_ < 1 || month_ > 12) {
        throw std::invalid_argument("Invalid month");
    }

    unsigned end_day = gregorian_calendar::end_of_month_day(year_, month_);

    auto matches = [&](unsigned d) {
        date dt(year_, month_, d);
        return dt.day_of_week().as_number() == static_cast<unsigned>(wd);
    };

    switch (s) {
        case schedule::teenth: {
            for (unsigned d = 13; d <= 19; ++d) {
                if (matches(d)) {
                    return date(year_, month_, d);
                }
            }
            break;
        }
        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth:
        case schedule::fifth: {
            unsigned target = static_cast<unsigned>(s) + 1; // first == 0
            unsigned count = 0;
            for (unsigned d = 1; d <= end_day; ++d) {
                if (matches(d) && ++count == target) {
                    return date(year_, month_, d);
                }
            }
            throw std::domain_error("Requested weekday occurrence does not exist");
        }
        case schedule::last: {
            for (int d = static_cast<int>(end_day); d >= 1; --d) {
                if (matches(static_cast<unsigned>(d))) {
                    return date(year_, month_, static_cast<unsigned>(d));
                }
            }
            break;
        }
    }

    throw std::logic_error("Unable to determine meetup day");
}

// convenience wrappers for teenth days
boost::gregorian::date scheduler::monteenth() const { return day(boost::date_time::Monday, schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth() const { return day(boost::date_time::Tuesday, schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth() const { return day(boost::date_time::Wednesday, schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return day(boost::date_time::Thursday, schedule::teenth); }
boost::gregorian::date scheduler::friteenth() const { return day(boost::date_time::Friday, schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return day(boost::date_time::Saturday, schedule::teenth); }
boost::gregorian::date scheduler::sunteenth() const { return day(boost::date_time::Sunday, schedule::teenth); }

// first
boost::gregorian::date scheduler::first_monday() const { return day(boost::date_time::Monday, schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const { return day(boost::date_time::Tuesday, schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return day(boost::date_time::Wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const { return day(boost::date_time::Thursday, schedule::first); }
boost::gregorian::date scheduler::first_friday() const { return day(boost::date_time::Friday, schedule::first); }
boost::gregorian::date scheduler::first_saturday() const { return day(boost::date_time::Saturday, schedule::first); }
boost::gregorian::date scheduler::first_sunday() const { return day(boost::date_time::Sunday, schedule::first); }

// second
boost::gregorian::date scheduler::second_monday() const { return day(boost::date_time::Monday, schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const { return day(boost::date_time::Tuesday, schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return day(boost::date_time::Wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const { return day(boost::date_time::Thursday, schedule::second); }
boost::gregorian::date scheduler::second_friday() const { return day(boost::date_time::Friday, schedule::second); }
boost::gregorian::date scheduler::second_saturday() const { return day(boost::date_time::Saturday, schedule::second); }
boost::gregorian::date scheduler::second_sunday() const { return day(boost::date_time::Sunday, schedule::second); }

// third
boost::gregorian::date scheduler::third_monday() const { return day(boost::date_time::Monday, schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const { return day(boost::date_time::Tuesday, schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return day(boost::date_time::Wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const { return day(boost::date_time::Thursday, schedule::third); }
boost::gregorian::date scheduler::third_friday() const { return day(boost::date_time::Friday, schedule::third); }
boost::gregorian::date scheduler::third_saturday() const { return day(boost::date_time::Saturday, schedule::third); }
boost::gregorian::date scheduler::third_sunday() const { return day(boost::date_time::Sunday, schedule::third); }

// fourth
boost::gregorian::date scheduler::fourth_monday() const { return day(boost::date_time::Monday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return day(boost::date_time::Tuesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return day(boost::date_time::Wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return day(boost::date_time::Thursday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return day(boost::date_time::Friday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return day(boost::date_time::Saturday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return day(boost::date_time::Sunday, schedule::fourth); }

// last
boost::gregorian::date scheduler::last_monday() const { return day(boost::date_time::Monday, schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const { return day(boost::date_time::Tuesday, schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return day(boost::date_time::Wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const { return day(boost::date_time::Thursday, schedule::last); }
boost::gregorian::date scheduler::last_friday() const { return day(boost::date_time::Friday, schedule::last); }
boost::gregorian::date scheduler::last_saturday() const { return day(boost::date_time::Saturday, schedule::last); }
boost::gregorian::date scheduler::last_sunday() const { return day(boost::date_time::Sunday, schedule::last); }

}  // namespace meetup
