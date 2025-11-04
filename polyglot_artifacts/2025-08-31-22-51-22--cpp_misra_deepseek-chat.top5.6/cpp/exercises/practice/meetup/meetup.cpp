#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <map>
#include <stdexcept>

namespace meetup {

namespace {

boost::gregorian::date find_teenth(int year, int month, boost::gregorian::greg_weekday weekday) {
    for (int day = 13; day <= 19; day++) {
        boost::gregorian::date current_date(year, month, day);
        if (current_date.day_of_week() == weekday) {
            return current_date;
        }
    }
    throw std::runtime_error("Teenth day not found");
}

}  // namespace

// Teenth implementations
boost::gregorian::date scheduler::monteenth() const { return find_teenth(year_, month_.as_number(), boost::gregorian::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return find_teenth(year_, month_.as_number(), boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return find_teenth(year_, month_.as_number(), boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return find_teenth(year_, month_.as_number(), boost::gregorian::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return find_teenth(year_, month_.as_number(), boost::gregorian::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return find_teenth(year_, month_.as_number(), boost::gregorian::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return find_teenth(year_, month_.as_number(), boost::gregorian::Sunday); }

// First implementations
boost::gregorian::date scheduler::first_monday() const { return boost::gregorian::first_day_of_the_week_in_month(boost::gregorian::Monday, month_).get_date(year_); }
boost::gregorian::date scheduler::first_tuesday() const { return boost::gregorian::first_day_of_the_week_in_month(boost::gregorian::Tuesday, month_).get_date(year_); }
boost::gregorian::date scheduler::first_wednesday() const { return boost::gregorian::first_day_of_the_week_in_month(boost::gregorian::Wednesday, month_).get_date(year_); }
boost::gregorian::date scheduler::first_thursday() const { return boost::gregorian::first_day_of_the_week_in_month(boost::gregorian::Thursday, month_).get_date(year_); }
boost::gregorian::date scheduler::first_friday() const { return boost::gregorian::first_day_of_the_week_in_month(boost::gregorian::Friday, month_).get_date(year_); }
boost::gregorian::date scheduler::first_saturday() const { return boost::gregorian::first_day_of_the_week_in_month(boost::gregorian::Saturday, month_).get_date(year_); }
boost::gregorian::date scheduler::first_sunday() const { return boost::gregorian::first_day_of_the_week_in_month(boost::gregorian::Sunday, month_).get_date(year_); }

// Second implementations
boost::gregorian::date scheduler::second_monday() const { return boost::gregorian::nth_day_of_the_week_in_month(2, boost::gregorian::Monday, month_).get_date(year_); }
boost::gregorian::date scheduler::second_tuesday() const { return boost::gregorian::nth_day_of_the_week_in_month(2, boost::gregorian::Tuesday, month_).get_date(year_); }
boost::gregorian::date scheduler::second_wednesday() const { return boost::gregorian::nth_day_of_the_week_in_month(2, boost::gregorian::Wednesday, month_).get_date(year_); }
boost::gregorian::date scheduler::second_thursday() const { return boost::gregorian::nth_day_of_the_week_in_month(2, boost::gregorian::Thursday, month_).get_date(year_); }
boost::gregorian::date scheduler::second_friday() const { return boost::gregorian::nth_day_of_the_week_in_month(2, boost::gregorian::Friday, month_).get_date(year_); }
boost::gregorian::date scheduler::second_saturday() const { return boost::gregorian::nth_day_of_the_week_in_month(2, boost::gregorian::Saturday, month_).get_date(year_); }
boost::gregorian::date scheduler::second_sunday() const { return boost::gregorian::nth_day_of_the_week_in_month(2, boost::gregorian::Sunday, month_).get_date(year_); }

// Third implementations
boost::gregorian::date scheduler::third_monday() const { return boost::gregorian::nth_day_of_the_week_in_month(3, boost::gregorian::Monday, month_).get_date(year_); }
boost::gregorian::date scheduler::third_tuesday() const { return boost::gregorian::nth_day_of_the_week_in_month(3, boost::gregorian::Tuesday, month_).get_date(year_); }
boost::gregorian::date scheduler::third_wednesday() const { return boost::gregorian::nth_day_of_the_week_in_month(3, boost::gregorian::Wednesday, month_).get_date(year_); }
boost::gregorian::date scheduler::third_thursday() const { return boost::gregorian::nth_day_of_the_week_in_month(3, boost::gregorian::Thursday, month_).get_date(year_); }
boost::gregorian::date scheduler::third_friday() const { return boost::gregorian::nth_day_of_the_week_in_month(3, boost::gregorian::Friday, month_).get_date(year_); }
boost::gregorian::date scheduler::third_saturday() const { return boost::gregorian::nth_day_of_the_week_in_month(3, boost::gregorian::Saturday, month_).get_date(year_); }
boost::gregorian::date scheduler::third_sunday() const { return boost::gregorian::nth_day_of_the_week_in_month(3, boost::gregorian::Sunday, month_).get_date(year_); }

// Fourth implementations
boost::gregorian::date scheduler::fourth_monday() const { return boost::gregorian::nth_day_of_the_week_in_month(4, boost::gregorian::Monday, month_).get_date(year_); }
boost::gregorian::date scheduler::fourth_tuesday() const { return boost::gregorian::nth_day_of_the_week_in_month(4, boost::gregorian::Tuesday, month_).get_date(year_); }
boost::gregorian::date scheduler::fourth_wednesday() const { return boost::gregorian::nth_day_of_the_week_in_month(4, boost::gregorian::Wednesday, month_).get_date(year_); }
boost::gregorian::date scheduler::fourth_thursday() const { return boost::gregorian::nth_day_of_the_week_in_month(4, boost::gregorian::Thursday, month_).get_date(year_); }
boost::gregorian::date scheduler::fourth_friday() const { return boost::gregorian::nth_day_of_the_week_in_month(4, boost::gregorian::Friday, month_).get_date(year_); }
boost::gregorian::date scheduler::fourth_saturday() const { return boost::gregorian::nth_day_of_the_week_in_month(4, boost::gregorian::Saturday, month_).get_date(year_); }
boost::gregorian::date scheduler::fourth_sunday() const { return boost::gregorian::nth_day_of_the_week_in_month(4, boost::gregorian::Sunday, month_).get_date(year_); }

// Last implementations
boost::gregorian::date scheduler::last_monday() const { return boost::gregorian::last_day_of_the_week_in_month(boost::gregorian::Monday, month_).get_date(year_); }
boost::gregorian::date scheduler::last_tuesday() const { return boost::gregorian::last_day_of_the_week_in_month(boost::gregorian::Tuesday, month_).get_date(year_); }
boost::gregorian::date scheduler::last_wednesday() const { return boost::gregorian::last_day_of_the_week_in_month(boost::gregorian::Wednesday, month_).get_date(year_); }
boost::gregorian::date scheduler::last_thursday() const { return boost::gregorian::last_day_of_the_week_in_month(boost::gregorian::Thursday, month_).get_date(year_); }
boost::gregorian::date scheduler::last_friday() const { return boost::gregorian::last_day_of_the_week_in_month(boost::gregorian::Friday, month_).get_date(year_); }
boost::gregorian::date scheduler::last_saturday() const { return boost::gregorian::last_day_of_the_week_in_month(boost::gregorian::Saturday, month_).get_date(year_); }
boost::gregorian::date scheduler::last_sunday() const { return boost::gregorian::last_day_of_the_week_in_month(boost::gregorian::Sunday, month_).get_date(year_); }

}  // namespace meetup
