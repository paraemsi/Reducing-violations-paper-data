#include "meetup.h"
#include <stdexcept>
using namespace std;

namespace meetup {

scheduler::scheduler(int year, int month) : year_(year), month_(month) {}

// Helper function to find the nth weekday
boost::gregorian::date scheduler::find_nth_weekday(int nth, boost::gregorian::greg_weekday weekday) const {
    int count = 0;
    boost::gregorian::date start(year_, month_, 1);
    boost::gregorian::date end = start.end_of_month();
    
    for (boost::gregorian::day_iterator it(start); it <= end; ++it) {
        if (it->day_of_week() == weekday) {
            count++;
            if (count == nth) {
                return *it;
            }
        }
    }
    throw runtime_error("Date not found");
}

// Helper function to find teenth weekday (13-19)
boost::gregorian::date scheduler::find_teenth(boost::gregorian::greg_weekday weekday) const {
    for (int day = 13; day <= 19; day++) {
        boost::gregorian::date d(year_, month_, day);
        if (d.day_of_week() == weekday) {
            return d;
        }
    }
    throw runtime_error("Teenth not found");
}

// Helper function to find last weekday
boost::gregorian::date scheduler::find_last(boost::gregorian::greg_weekday weekday) const {
    boost::gregorian::date end(year_, month_, 1);
    end = end.end_of_month();
    
    // Start from the last day of the month and go backwards
    for (int day = end.day(); day >= 1; day--) {
        boost::gregorian::date d(year_, month_, day);
        if (d.day_of_week() == weekday) {
            return d;
        }
    }
    throw runtime_error("Last weekday not found");
}

// Implement all the interface methods
// Teenth methods
boost::gregorian::date scheduler::monteenth() const { return find_teenth(boost::gregorian::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return find_teenth(boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return find_teenth(boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return find_teenth(boost::gregorian::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return find_teenth(boost::gregorian::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return find_teenth(boost::gregorian::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return find_teenth(boost::gregorian::Sunday); }

// First week
boost::gregorian::date scheduler::first_monday() const { return find_nth_weekday(1, boost::gregorian::Monday); }
boost::gregorian::date scheduler::first_tuesday() const { return find_nth_weekday(1, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::first_wednesday() const { return find_nth_weekday(1, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::first_thursday() const { return find_nth_weekday(1, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::first_friday() const { return find_nth_weekday(1, boost::gregorian::Friday); }
boost::gregorian::date scheduler::first_saturday() const { return find_nth_weekday(1, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::first_sunday() const { return find_nth_weekday(1, boost::gregorian::Sunday); }

// Second week
boost::gregorian::date scheduler::second_monday() const { return find_nth_weekday(2, boost::gregorian::Monday); }
boost::gregorian::date scheduler::second_tuesday() const { return find_nth_weekday(2, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::second_wednesday() const { return find_nth_weekday(2, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::second_thursday() const { return find_nth_weekday(2, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::second_friday() const { return find_nth_weekday(2, boost::gregorian::Friday); }
boost::gregorian::date scheduler::second_saturday() const { return find_nth_weekday(2, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::second_sunday() const { return find_nth_weekday(2, boost::gregorian::Sunday); }

// Third week
boost::gregorian::date scheduler::third_monday() const { return find_nth_weekday(3, boost::gregorian::Monday); }
boost::gregorian::date scheduler::third_tuesday() const { return find_nth_weekday(3, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::third_wednesday() const { return find_nth_weekday(3, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::third_thursday() const { return find_nth_weekday(3, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::third_friday() const { return find_nth_weekday(3, boost::gregorian::Friday); }
boost::gregorian::date scheduler::third_saturday() const { return find_nth_weekday(3, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::third_sunday() const { return find_nth_weekday(3, boost::gregorian::Sunday); }

// Fourth week
boost::gregorian::date scheduler::fourth_monday() const { return find_nth_weekday(4, boost::gregorian::Monday); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_nth_weekday(4, boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_nth_weekday(4, boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_nth_weekday(4, boost::gregorian::Thursday); }
boost::gregorian::date scheduler::fourth_friday() const { return find_nth_weekday(4, boost::gregorian::Friday); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_nth_weekday(4, boost::gregorian::Saturday); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_nth_weekday(4, boost::gregorian::Sunday); }

// Last week
boost::gregorian::date scheduler::last_monday() const { return find_last(boost::gregorian::Monday); }
boost::gregorian::date scheduler::last_tuesday() const { return find_last(boost::gregorian::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return find_last(boost::gregorian::Wednesday); }
boost::gregorian::date scheduler::last_thursday() const { return find_last(boost::gregorian::Thursday); }
boost::gregorian::date scheduler::last_friday() const { return find_last(boost::gregorian::Friday); }
boost::gregorian::date scheduler::last_saturday() const { return find_last(boost::gregorian::Saturday); }
boost::gregorian::date scheduler::last_sunday() const { return find_last(boost::gregorian::Sunday); }

}  // namespace meetup
