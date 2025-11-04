#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/gregorian/greg_calendar.hpp>

namespace meetup {

using namespace boost::gregorian;

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

date scheduler::monteenth() const {
    for (int day = 13; day <= 19; day++) {
        date d(year_, month_, day);
        if (d.day_of_week() == Monday) {
            return d;
        }
    }
    return date(); // Should not reach here according to the problem statement
}

// Implement similar functions for other weekdays
date scheduler::tuesteenth() const {
    for (int day = 13; day <= 19; day++) {
        date d(year_, month_, day);
        if (d.day_of_week() == Tuesday) {
            return d;
        }
    }
    return date();
}

date scheduler::wednesteenth() const {
    for (int day = 13; day <= 19; day++) {
        date d(year_, month_, day);
        if (d.day_of_week() == Wednesday) {
            return d;
        }
    }
    return date();
}

date scheduler::thursteenth() const {
    for (int day = 13; day <= 19; day++) {
        date d(year_, month_, day);
        if (d.day_of_week() == Thursday) {
            return d;
        }
    }
    return date();
}

date scheduler::friteenth() const {
    for (int day = 13; day <= 19; day++) {
        date d(year_, month_, day);
        if (d.day_of_week() == Friday) {
            return d;
        }
    }
    return date();
}

date scheduler::saturteenth() const {
    for (int day = 13; day <= 19; day++) {
        date d(year_, month_, day);
        if (d.day_of_week() == Saturday) {
            return d;
        }
    }
    return date();
}

date scheduler::sunteenth() const {
    for (int day = 13; day <= 19; day++) {
        date d(year_, month_, day);
        if (d.day_of_week() == Sunday) {
            return d;
        }
    }
    return date();
}

// Helper function to find the nth occurrence of a weekday
date find_nth_weekday(int year, int month, boost::gregorian::greg_weekday weekday, int n) {
    // Start from the first day of the month
    date first_day(year, month, 1);
    // Find the first occurrence of the desired weekday
    int days_to_add = (weekday - first_day.day_of_week() + 7) % 7;
    date result = first_day + days(days_to_add);
    // Add (n-1) weeks
    result += weeks(n - 1);
    return result;
}

// Helper function to find the last occurrence of a weekday
date find_last_weekday(int year, int month, boost::gregorian::greg_weekday weekday) {
    // Start from the last day of the month
    date last_day(year, month, gregorian_calendar::end_of_month_day(year, month));
    // Find the last occurrence of the desired weekday
    int days_to_subtract = (last_day.day_of_week() - weekday + 7) % 7;
    return last_day - days(days_to_subtract);
}

date scheduler::first_monday() const { return find_nth_weekday(year_, month_, Monday, 1); }
date scheduler::first_tuesday() const { return find_nth_weekday(year_, month_, Tuesday, 1); }
date scheduler::first_wednesday() const { return find_nth_weekday(year_, month_, Wednesday, 1); }
date scheduler::first_thursday() const { return find_nth_weekday(year_, month_, Thursday, 1); }
date scheduler::first_friday() const { return find_nth_weekday(year_, month_, Friday, 1); }
date scheduler::first_saturday() const { return find_nth_weekday(year_, month_, Saturday, 1); }
date scheduler::first_sunday() const { return find_nth_weekday(year_, month_, Sunday, 1); }

date scheduler::second_monday() const { return find_nth_weekday(year_, month_, Monday, 2); }
date scheduler::second_tuesday() const { return find_nth_weekday(year_, month_, Tuesday, 2); }
date scheduler::second_wednesday() const { return find_nth_weekday(year_, month_, Wednesday, 2); }
date scheduler::second_thursday() const { return find_nth_weekday(year_, month_, Thursday, 2); }
date scheduler::second_friday() const { return find_nth_weekday(year_, month_, Friday, 2); }
date scheduler::second_saturday() const { return find_nth_weekday(year_, month_, Saturday, 2); }
date scheduler::second_sunday() const { return find_nth_weekday(year_, month_, Sunday, 2); }

date scheduler::third_monday() const { return find_nth_weekday(year_, month_, Monday, 3); }
date scheduler::third_tuesday() const { return find_nth_weekday(year_, month_, Tuesday, 3); }
date scheduler::third_wednesday() const { return find_nth_weekday(year_, month_, Wednesday, 3); }
date scheduler::third_thursday() const { return find_nth_weekday(year_, month_, Thursday, 3); }
date scheduler::third_friday() const { return find_nth_weekday(year_, month_, Friday, 3); }
date scheduler::third_saturday() const { return find_nth_weekday(year_, month_, Saturday, 3); }
date scheduler::third_sunday() const { return find_nth_weekday(year_, month_, Sunday, 3); }

date scheduler::fourth_monday() const { return find_nth_weekday(year_, month_, Monday, 4); }
date scheduler::fourth_tuesday() const { return find_nth_weekday(year_, month_, Tuesday, 4); }
date scheduler::fourth_wednesday() const { return find_nth_weekday(year_, month_, Wednesday, 4); }
date scheduler::fourth_thursday() const { return find_nth_weekday(year_, month_, Thursday, 4); }
date scheduler::fourth_friday() const { return find_nth_weekday(year_, month_, Friday, 4); }
date scheduler::fourth_saturday() const { return find_nth_weekday(year_, month_, Saturday, 4); }
date scheduler::fourth_sunday() const { return find_nth_weekday(year_, month_, Sunday, 4); }

date scheduler::last_monday() const { return find_last_weekday(year_, month_, Monday); }
date scheduler::last_tuesday() const { return find_last_weekday(year_, month_, Tuesday); }
date scheduler::last_wednesday() const { return find_last_weekday(year_, month_, Wednesday); }
date scheduler::last_thursday() const { return find_last_weekday(year_, month_, Thursday); }
date scheduler::last_friday() const { return find_last_weekday(year_, month_, Friday); }
date scheduler::last_saturday() const { return find_last_weekday(year_, month_, Saturday); }
date scheduler::last_sunday() const { return find_last_weekday(year_, month_, Sunday); }

}  // namespace meetup
