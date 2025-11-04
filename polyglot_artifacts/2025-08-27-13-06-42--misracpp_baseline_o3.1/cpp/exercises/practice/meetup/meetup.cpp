#include "meetup.h"
#include <chrono>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using namespace boost::gregorian;
using std::chrono::year_month_day;
using std::chrono::weekday;

namespace {
const weekday Sunday { boost::date_time::Sunday };
const weekday Monday { boost::date_time::Monday };
const weekday Tuesday{ boost::date_time::Tuesday };
const weekday Wednesday{ boost::date_time::Wednesday };
const weekday Thursday{ boost::date_time::Thursday };
const weekday Friday{ boost::date_time::Friday };
const weekday Saturday{ boost::date_time::Saturday };
} // unnamed namespace

// Constructor
scheduler::scheduler(int year, unsigned int month)
    : year_{year}, month_{month} {}

// Helper to compute nth weekday (1-based)
year_month_day scheduler::nth_weekday(weekday wd, unsigned nth) const {
    date first(year_, month_, 1);                          // first day of the month
    int diff = (wd.as_number() - first.day_of_week().as_number() + 7) % 7;
    date result = first + date_duration(diff + 7 * (nth - 1));
    return result;
}

// Helper to compute last weekday of month
year_month_day scheduler::last_weekday(weekday wd) const {
    date last_day(year_, month_, 1);
    last_day = last_day.end_of_month();                       // last calendar day of month
    int diff = (last_day.day_of_week().as_number() - wd.as_number() + 7) % 7;
    return last_day - date_duration(diff);
}

// Helper to compute "teenth" weekday of month
year_month_day scheduler::teenth(weekday wd) const {
    for (unsigned d = 13; d <= 19; ++d) {
        date dt(year_, month_, d);
        if (dt.day_of_week() == wd) {
            return dt;
        }
    }
    return date(year_, month_, 1); // fallback (should never occur)
}

// teenth functions
year_month_day scheduler::monteenth() const { return teenth(Monday); }
year_month_day scheduler::tuesteenth() const { return teenth(Tuesday); }
year_month_day scheduler::wednesteenth() const { return teenth(Wednesday); }
year_month_day scheduler::thursteenth() const { return teenth(Thursday); }
year_month_day scheduler::friteenth() const { return teenth(Friday); }
year_month_day scheduler::saturteenth() const { return teenth(Saturday); }
year_month_day scheduler::sunteenth() const { return teenth(Sunday); }

// first
year_month_day scheduler::first_monday() const { return nth_weekday(Monday, 1); }
year_month_day scheduler::first_tuesday() const { return nth_weekday(Tuesday, 1); }
year_month_day scheduler::first_wednesday() const { return nth_weekday(Wednesday, 1); }
year_month_day scheduler::first_thursday() const { return nth_weekday(Thursday, 1); }
year_month_day scheduler::first_friday() const { return nth_weekday(Friday, 1); }
year_month_day scheduler::first_saturday() const { return nth_weekday(Saturday, 1); }
year_month_day scheduler::first_sunday() const { return nth_weekday(Sunday, 1); }

// second
year_month_day scheduler::second_monday() const { return nth_weekday(Monday, 2); }
year_month_day scheduler::second_tuesday() const { return nth_weekday(Tuesday, 2); }
year_month_day scheduler::second_wednesday() const { return nth_weekday(Wednesday, 2); }
year_month_day scheduler::second_thursday() const { return nth_weekday(Thursday, 2); }
year_month_day scheduler::second_friday() const { return nth_weekday(Friday, 2); }
year_month_day scheduler::second_saturday() const { return nth_weekday(Saturday, 2); }
year_month_day scheduler::second_sunday() const { return nth_weekday(Sunday, 2); }

// third
year_month_day scheduler::third_monday() const { return nth_weekday(Monday, 3); }
year_month_day scheduler::third_tuesday() const { return nth_weekday(Tuesday, 3); }
year_month_day scheduler::third_wednesday() const { return nth_weekday(Wednesday, 3); }
year_month_day scheduler::third_thursday() const { return nth_weekday(Thursday, 3); }
year_month_day scheduler::third_friday() const { return nth_weekday(Friday, 3); }
year_month_day scheduler::third_saturday() const { return nth_weekday(Saturday, 3); }
year_month_day scheduler::third_sunday() const { return nth_weekday(Sunday, 3); }

// fourth
year_month_day scheduler::fourth_monday() const { return nth_weekday(Monday, 4); }
year_month_day scheduler::fourth_tuesday() const { return nth_weekday(Tuesday, 4); }
year_month_day scheduler::fourth_wednesday() const { return nth_weekday(Wednesday, 4); }
year_month_day scheduler::fourth_thursday() const { return nth_weekday(Thursday, 4); }
year_month_day scheduler::fourth_friday() const { return nth_weekday(Friday, 4); }
year_month_day scheduler::fourth_saturday() const { return nth_weekday(Saturday, 4); }
year_month_day scheduler::fourth_sunday() const { return nth_weekday(Sunday, 4); }

// last
year_month_day scheduler::last_monday() const { return last_weekday(Monday); }
year_month_day scheduler::last_tuesday() const { return last_weekday(Tuesday); }
year_month_day scheduler::last_wednesday() const { return last_weekday(Wednesday); }
year_month_day scheduler::last_thursday() const { return last_weekday(Thursday); }
year_month_day scheduler::last_friday() const { return last_weekday(Friday); }
year_month_day scheduler::last_saturday() const { return last_weekday(Saturday); }
year_month_day scheduler::last_sunday() const { return last_weekday(Sunday); }

}  // namespace meetup
