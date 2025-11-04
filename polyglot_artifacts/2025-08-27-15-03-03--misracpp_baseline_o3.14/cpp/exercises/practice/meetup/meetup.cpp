#include "meetup.h"
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(boost::gregorian::greg_month month, int year)
    : year_{year}, month_{month} {}

boost::gregorian::date
scheduler::get(boost::gregorian::greg_weekday weekday, schedule spec) const {
    using namespace boost::gregorian;

    if (spec == schedule::teenth) {
        for (unsigned d = 13; d <= 19; ++d) {
            date candidate{year_, month_, d};
            if (candidate.day_of_week() == weekday) {
                return candidate;
            }
        }
    } else if (spec == schedule::last) {
        unsigned last_day = gregorian_calendar::end_of_month_day(
            year_, month_.as_number());
        date candidate{year_, month_, last_day};
        while (candidate.day_of_week() != weekday) {
            candidate -= days{1};
        }
        return candidate;
    } else {
        int n = 0;
        switch (spec) {
            case schedule::first:  n = 1; break;
            case schedule::second: n = 2; break;
            case schedule::third:  n = 3; break;
            case schedule::fourth: n = 4; break;
            default: throw std::logic_error("Invalid schedule spec");
        }
        date first_day{year_, month_, 1};
        int diff = (weekday.as_number() -
                    first_day.day_of_week().as_number() + 7) % 7;
        unsigned day = 1u + diff + 7u * (n - 1);
        return date{year_, month_, day};
    }
    throw std::logic_error("Invalid schedule");
}

// teenth
boost::gregorian::date scheduler::monteenth()   const { return get(boost::gregorian::Monday   , schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth()  const { return get(boost::gregorian::Tuesday  , schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth()const { return get(boost::gregorian::Wednesday, schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return get(boost::gregorian::Thursday , schedule::teenth); }
boost::gregorian::date scheduler::friteenth()   const { return get(boost::gregorian::Friday   , schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return get(boost::gregorian::Saturday , schedule::teenth); }
boost::gregorian::date scheduler::sunteenth()   const { return get(boost::gregorian::Sunday   , schedule::teenth); }

// first
boost::gregorian::date scheduler::first_monday()    const { return get(boost::gregorian::Monday   , schedule::first); }
boost::gregorian::date scheduler::first_tuesday()   const { return get(boost::gregorian::Tuesday  , schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return get(boost::gregorian::Wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday()  const { return get(boost::gregorian::Thursday , schedule::first); }
boost::gregorian::date scheduler::first_friday()    const { return get(boost::gregorian::Friday   , schedule::first); }
boost::gregorian::date scheduler::first_saturday()  const { return get(boost::gregorian::Saturday , schedule::first); }
boost::gregorian::date scheduler::first_sunday()    const { return get(boost::gregorian::Sunday   , schedule::first); }

// second
boost::gregorian::date scheduler::second_monday()    const { return get(boost::gregorian::Monday   , schedule::second); }
boost::gregorian::date scheduler::second_tuesday()   const { return get(boost::gregorian::Tuesday  , schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return get(boost::gregorian::Wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday()  const { return get(boost::gregorian::Thursday , schedule::second); }
boost::gregorian::date scheduler::second_friday()    const { return get(boost::gregorian::Friday   , schedule::second); }
boost::gregorian::date scheduler::second_saturday()  const { return get(boost::gregorian::Saturday , schedule::second); }
boost::gregorian::date scheduler::second_sunday()    const { return get(boost::gregorian::Sunday   , schedule::second); }

// third
boost::gregorian::date scheduler::third_monday()    const { return get(boost::gregorian::Monday   , schedule::third); }
boost::gregorian::date scheduler::third_tuesday()   const { return get(boost::gregorian::Tuesday  , schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return get(boost::gregorian::Wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday()  const { return get(boost::gregorian::Thursday , schedule::third); }
boost::gregorian::date scheduler::third_friday()    const { return get(boost::gregorian::Friday   , schedule::third); }
boost::gregorian::date scheduler::third_saturday()  const { return get(boost::gregorian::Saturday , schedule::third); }
boost::gregorian::date scheduler::third_sunday()    const { return get(boost::gregorian::Sunday   , schedule::third); }

// fourth
boost::gregorian::date scheduler::fourth_monday()    const { return get(boost::gregorian::Monday   , schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday()   const { return get(boost::gregorian::Tuesday  , schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return get(boost::gregorian::Wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday()  const { return get(boost::gregorian::Thursday , schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday()    const { return get(boost::gregorian::Friday   , schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday()  const { return get(boost::gregorian::Saturday , schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday()    const { return get(boost::gregorian::Sunday   , schedule::fourth); }

// last
boost::gregorian::date scheduler::last_monday()    const { return get(boost::gregorian::Monday   , schedule::last); }
boost::gregorian::date scheduler::last_tuesday()   const { return get(boost::gregorian::Tuesday  , schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return get(boost::gregorian::Wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday()  const { return get(boost::gregorian::Thursday , schedule::last); }
boost::gregorian::date scheduler::last_friday()    const { return get(boost::gregorian::Friday   , schedule::last); }
boost::gregorian::date scheduler::last_saturday()  const { return get(boost::gregorian::Saturday , schedule::last); }
boost::gregorian::date scheduler::last_sunday()    const { return get(boost::gregorian::Sunday   , schedule::last); }

}  // namespace meetup
