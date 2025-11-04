#include "meetup.h"
#include <string>
#include <map>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

using namespace boost::gregorian;
using month_type = boost::date_time::month_functor<boost::gregorian::date>::month_type;

scheduler::scheduler(month_type month, std::int32_t year) 
    : month_(month), year_(year) {
}

// Helper functions
date scheduler::find_teenth_day(greg_weekday weekday) const {
    for (std::int32_t day = 13; day <= 19; day++) {
        date candidate(static_cast<date::year_type>(year_), 
                       month_, 
                       static_cast<date::day_type>(day));
        if (candidate.day_of_week() == weekday) {
            return candidate;
        }
    }
    throw std::runtime_error("No teenth day found");
}

date scheduler::find_nth_day(std::int32_t n, greg_weekday weekday) const {
    first_day_of_the_week_in_month fd(weekday, month_);
    return fd.get_date(static_cast<date::year_type>(year_)) + weeks(n - 1);
}

date scheduler::find_last_day(greg_weekday weekday) const {
    last_day_of_the_week_in_month ld(weekday, month_);
    return ld.get_date(static_cast<date::year_type>(year_));
}

// Teenth days
date scheduler::monteenth() const { return find_teenth_day(Monday); }
date scheduler::tuesteenth() const { return find_teenth_day(Tuesday); }
date scheduler::wednesteenth() const { return find_teenth_day(Wednesday); }
date scheduler::thursteenth() const { return find_teenth_day(Thursday); }
date scheduler::friteenth() const { return find_teenth_day(Friday); }
date scheduler::saturteenth() const { return find_teenth_day(Saturday); }
date scheduler::sunteenth() const { return find_teenth_day(Sunday); }

// First days
date scheduler::first_monday() const { return find_nth_day(1, Monday); }
date scheduler::first_tuesday() const { return find_nth_day(1, Tuesday); }
date scheduler::first_wednesday() const { return find_nth_day(1, Wednesday); }
date scheduler::first_thursday() const { return find_nth_day(1, Thursday); }
date scheduler::first_friday() const { return find_nth_day(1, Friday); }
date scheduler::first_saturday() const { return find_nth_day(1, Saturday); }
date scheduler::first_sunday() const { return find_nth_day(1, Sunday); }

// Second days
date scheduler::second_monday() const { return find_nth_day(2, Monday); }
date scheduler::second_tuesday() const { return find_nth_day(2, Tuesday); }
date scheduler::second_wednesday() const { return find_nth_day(2, Wednesday); }
date scheduler::second_thursday() const { return find_nth_day(2, Thursday); }
date scheduler::second_friday() const { return find_nth_day(2, Friday); }
date scheduler::second_saturday() const { return find_nth_day(2, Saturday); }
date scheduler::second_sunday() const { return find_nth_day(2, Sunday); }

// Third days
date scheduler::third_monday() const { return find_nth_day(3, Monday); }
date scheduler::third_tuesday() const { return find_nth_day(3, Tuesday); }
date scheduler::third_wednesday() const { return find_nth_day(3, Wednesday); }
date scheduler::third_thursday() const { return find_nth_day(3, Thursday); }
date scheduler::third_friday() const { return find_nth_day(3, Friday); }
date scheduler::third_saturday() const { return find_nth_day(3, Saturday); }
date scheduler::third_sunday() const { return find_nth_day(3, Sunday); }

// Fourth days
date scheduler::fourth_monday() const { return find_nth_day(4, Monday); }
date scheduler::fourth_tuesday() const { return find_nth_day(4, Tuesday); }
date scheduler::fourth_wednesday() const { return find_nth_day(4, Wednesday); }
date scheduler::fourth_thursday() const { return find_nth_day(4, Thursday); }
date scheduler::fourth_friday() const { return find_nth_day(4, Friday); }
date scheduler::fourth_saturday() const { return find_nth_day(4, Saturday); }
date scheduler::fourth_sunday() const { return find_nth_day(4, Sunday); }

// Last days
date scheduler::last_monday() const { return find_last_day(Monday); }
date scheduler::last_tuesday() const { return find_last_day(Tuesday); }
date scheduler::last_wednesday() const { return find_last_day(Wednesday); }
date scheduler::last_thursday() const { return find_last_day(Thursday); }
date scheduler::last_friday() const { return find_last_day(Friday); }
date scheduler::last_saturday() const { return find_last_day(Saturday); }
date scheduler::last_sunday() const { return find_last_day(Sunday); }

}  // namespace meetup
