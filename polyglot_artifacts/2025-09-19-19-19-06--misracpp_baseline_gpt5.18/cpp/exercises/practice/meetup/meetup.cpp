#include "meetup.h"

#include <stdexcept>

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::greg_month;
using boost::gregorian::greg_weekday;
using boost::gregorian::nth_day_of_the_week_in_month;
using boost::gregorian::last_day_of_the_week_in_month;

scheduler::scheduler(greg_month month, int year) : month_{month}, year_{year} {}
scheduler::scheduler(boost::gregorian::months_of_year month, int year)
    : month_{greg_month{month}}, year_{year} {}

date scheduler::teenth(greg_weekday wd) const {
    for (int d = 13; d <= 19; ++d) {
        date dt(year_, month_.as_number(), d);
        if (dt.day_of_week() == wd) {
            return dt;
        }
    }
    throw std::logic_error("No teenth weekday found");
}

date scheduler::nth_weekday(nth_day_of_the_week_in_month::week_num nth, greg_weekday wd) const {
    nth_day_of_the_week_in_month rule(nth, wd, static_cast<int>(month_.as_number()), year_);
    return rule.get_date();
}

date scheduler::last_weekday(greg_weekday wd) const {
    last_day_of_the_week_in_month rule(wd, static_cast<int>(month_.as_number()), year_);
    return rule.get_date();
}

// Teenth occurrences
date scheduler::monteenth() const { return teenth(greg_weekday{boost::date_time::Monday}); }
date scheduler::tuesteenth() const { return teenth(greg_weekday{boost::date_time::Tuesday}); }
date scheduler::wednesteenth() const { return teenth(greg_weekday{boost::date_time::Wednesday}); }
date scheduler::thursteenth() const { return teenth(greg_weekday{boost::date_time::Thursday}); }
date scheduler::friteenth() const { return teenth(greg_weekday{boost::date_time::Friday}); }
date scheduler::saturteenth() const { return teenth(greg_weekday{boost::date_time::Saturday}); }
date scheduler::sunteenth() const { return teenth(greg_weekday{boost::date_time::Sunday}); }

// First occurrences
date scheduler::first_monday() const { return nth_weekday(nth_day_of_the_week_in_month::first, greg_weekday{boost::date_time::Monday}); }
date scheduler::first_tuesday() const { return nth_weekday(nth_day_of_the_week_in_month::first, greg_weekday{boost::date_time::Tuesday}); }
date scheduler::first_wednesday() const { return nth_weekday(nth_day_of_the_week_in_month::first, greg_weekday{boost::date_time::Wednesday}); }
date scheduler::first_thursday() const { return nth_weekday(nth_day_of_the_week_in_month::first, greg_weekday{boost::date_time::Thursday}); }
date scheduler::first_friday() const { return nth_weekday(nth_day_of_the_week_in_month::first, greg_weekday{boost::date_time::Friday}); }
date scheduler::first_saturday() const { return nth_weekday(nth_day_of_the_week_in_month::first, greg_weekday{boost::date_time::Saturday}); }
date scheduler::first_sunday() const { return nth_weekday(nth_day_of_the_week_in_month::first, greg_weekday{boost::date_time::Sunday}); }

// Second occurrences
date scheduler::second_monday() const { return nth_weekday(nth_day_of_the_week_in_month::second, greg_weekday{boost::date_time::Monday}); }
date scheduler::second_tuesday() const { return nth_weekday(nth_day_of_the_week_in_month::second, greg_weekday{boost::date_time::Tuesday}); }
date scheduler::second_wednesday() const { return nth_weekday(nth_day_of_the_week_in_month::second, greg_weekday{boost::date_time::Wednesday}); }
date scheduler::second_thursday() const { return nth_weekday(nth_day_of_the_week_in_month::second, greg_weekday{boost::date_time::Thursday}); }
date scheduler::second_friday() const { return nth_weekday(nth_day_of_the_week_in_month::second, greg_weekday{boost::date_time::Friday}); }
date scheduler::second_saturday() const { return nth_weekday(nth_day_of_the_week_in_month::second, greg_weekday{boost::date_time::Saturday}); }
date scheduler::second_sunday() const { return nth_weekday(nth_day_of_the_week_in_month::second, greg_weekday{boost::date_time::Sunday}); }

// Third occurrences
date scheduler::third_monday() const { return nth_weekday(nth_day_of_the_week_in_month::third, greg_weekday{boost::date_time::Monday}); }
date scheduler::third_tuesday() const { return nth_weekday(nth_day_of_the_week_in_month::third, greg_weekday{boost::date_time::Tuesday}); }
date scheduler::third_wednesday() const { return nth_weekday(nth_day_of_the_week_in_month::third, greg_weekday{boost::date_time::Wednesday}); }
date scheduler::third_thursday() const { return nth_weekday(nth_day_of_the_week_in_month::third, greg_weekday{boost::date_time::Thursday}); }
date scheduler::third_friday() const { return nth_weekday(nth_day_of_the_week_in_month::third, greg_weekday{boost::date_time::Friday}); }
date scheduler::third_saturday() const { return nth_weekday(nth_day_of_the_week_in_month::third, greg_weekday{boost::date_time::Saturday}); }
date scheduler::third_sunday() const { return nth_weekday(nth_day_of_the_week_in_month::third, greg_weekday{boost::date_time::Sunday}); }

// Fourth occurrences
date scheduler::fourth_monday() const { return nth_weekday(nth_day_of_the_week_in_month::fourth, greg_weekday{boost::date_time::Monday}); }
date scheduler::fourth_tuesday() const { return nth_weekday(nth_day_of_the_week_in_month::fourth, greg_weekday{boost::date_time::Tuesday}); }
date scheduler::fourth_wednesday() const { return nth_weekday(nth_day_of_the_week_in_month::fourth, greg_weekday{boost::date_time::Wednesday}); }
date scheduler::fourth_thursday() const { return nth_weekday(nth_day_of_the_week_in_month::fourth, greg_weekday{boost::date_time::Thursday}); }
date scheduler::fourth_friday() const { return nth_weekday(nth_day_of_the_week_in_month::fourth, greg_weekday{boost::date_time::Friday}); }
date scheduler::fourth_saturday() const { return nth_weekday(nth_day_of_the_week_in_month::fourth, greg_weekday{boost::date_time::Saturday}); }
date scheduler::fourth_sunday() const { return nth_weekday(nth_day_of_the_week_in_month::fourth, greg_weekday{boost::date_time::Sunday}); }

// Last occurrences
date scheduler::last_monday() const { return last_weekday(greg_weekday{boost::date_time::Monday}); }
date scheduler::last_tuesday() const { return last_weekday(greg_weekday{boost::date_time::Tuesday}); }
date scheduler::last_wednesday() const { return last_weekday(greg_weekday{boost::date_time::Wednesday}); }
date scheduler::last_thursday() const { return last_weekday(greg_weekday{boost::date_time::Thursday}); }
date scheduler::last_friday() const { return last_weekday(greg_weekday{boost::date_time::Friday}); }
date scheduler::last_saturday() const { return last_weekday(greg_weekday{boost::date_time::Saturday}); }
date scheduler::last_sunday() const { return last_weekday(greg_weekday{boost::date_time::Sunday}); }

}  // namespace meetup
