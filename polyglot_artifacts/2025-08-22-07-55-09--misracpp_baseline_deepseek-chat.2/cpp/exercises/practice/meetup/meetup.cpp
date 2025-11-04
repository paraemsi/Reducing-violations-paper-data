#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
using namespace boost::gregorian;

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

date scheduler::find_teenth(int weekday) const {
    for (int day = 13; day <= 19; day++) {
        date current(year_, month_, day);
        if (current.day_of_week() == weekday) {
            return current;
        }
    }
    throw std::runtime_error("Teenth day not found");
}

date scheduler::find_nth_weekday(int nth, int weekday) const {
    date start_date(year_, month_, 1);
    int count = 0;
    for (day_iterator it(start_date); it->month() == month_; ++it) {
        if (it->day_of_week() == weekday) {
            count++;
            if (count == nth) {
                return *it;
            }
        }
    }
    throw std::runtime_error("Nth weekday not found");
}

date scheduler::find_last(int weekday) const {
    // Start from the last day of the month and work backwards
    int last_day = gregorian_calendar::end_of_month_day(year_, month_);
    for (int day = last_day; day >= 1; day--) {
        date current(year_, month_, day);
        if (current.day_of_week() == weekday) {
            return current;
        }
    }
    throw std::runtime_error("Last weekday not found");
}

// Teenth days
date scheduler::monteenth() const { return find_teenth(1); }
date scheduler::tuesteenth() const { return find_teenth(2); }
date scheduler::wednesteenth() const { return find_teenth(3); }
date scheduler::thursteenth() const { return find_teenth(4); }
date scheduler::friteenth() const { return find_teenth(5); }
date scheduler::saturteenth() const { return find_teenth(6); }
date scheduler::sunteenth() const { return find_teenth(0); }

// First week days
date scheduler::first_monday() const { return find_nth_weekday(1, 1); }
date scheduler::first_tuesday() const { return find_nth_weekday(1, 2); }
date scheduler::first_wednesday() const { return find_nth_weekday(1, 3); }
date scheduler::first_thursday() const { return find_nth_weekday(1, 4); }
date scheduler::first_friday() const { return find_nth_weekday(1, 5); }
date scheduler::first_saturday() const { return find_nth_weekday(1, 6); }
date scheduler::first_sunday() const { return find_nth_weekday(1, 0); }

// Second week days
date scheduler::second_monday() const { return find_nth_weekday(2, 1); }
date scheduler::second_tuesday() const { return find_nth_weekday(2, 2); }
date scheduler::second_wednesday() const { return find_nth_weekday(2, 3); }
date scheduler::second_thursday() const { return find_nth_weekday(2, 4); }
date scheduler::second_friday() const { return find_nth_weekday(2, 5); }
date scheduler::second_saturday() const { return find_nth_weekday(2, 6); }
date scheduler::second_sunday() const { return find_nth_weekday(2, 0); }

// Third week days
date scheduler::third_monday() const { return find_nth_weekday(3, 1); }
date scheduler::third_tuesday() const { return find_nth_weekday(3, 2); }
date scheduler::third_wednesday() const { return find_nth_weekday(3, 3); }
date scheduler::third_thursday() const { return find_nth_weekday(3, 4); }
date scheduler::third_friday() const { return find_nth_weekday(3, 5); }
date scheduler::third_saturday() const { return find_nth_weekday(3, 6); }
date scheduler::third_sunday() const { return find_nth_weekday(3, 0); }

// Fourth week days
date scheduler::fourth_monday() const { return find_nth_weekday(4, 1); }
date scheduler::fourth_tuesday() const { return find_nth_weekday(4, 2); }
date scheduler::fourth_wednesday() const { return find_nth_weekday(4, 3); }
date scheduler::fourth_thursday() const { return find_nth_weekday(4, 4); }
date scheduler::fourth_friday() const { return find_nth_weekday(4, 5); }
date scheduler::fourth_saturday() const { return find_nth_weekday(4, 6); }
date scheduler::fourth_sunday() const { return find_nth_weekday(4, 0); }

// Last week days
date scheduler::last_monday() const { return find_last(1); }
date scheduler::last_tuesday() const { return find_last(2); }
date scheduler::last_wednesday() const { return find_last(3); }
date scheduler::last_thursday() const { return find_last(4); }
date scheduler::last_friday() const { return find_last(5); }
date scheduler::last_saturday() const { return find_last(6); }
date scheduler::last_sunday() const { return find_last(0); }

}  // namespace meetup
