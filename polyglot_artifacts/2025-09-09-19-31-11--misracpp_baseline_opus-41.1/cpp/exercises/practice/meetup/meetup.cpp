#include "meetup.h"

namespace meetup {

scheduler::scheduler(const boost::gregorian::greg_month& month, unsigned short year) 
    : month_(month.as_number()), year_(year) {
}

boost::gregorian::date scheduler::find_meetup(unsigned short weekday, int week_descriptor) const {
    using namespace boost::gregorian;
    
    // weekday: 0=Sunday, 1=Monday, 2=Tuesday, 3=Wednesday, 4=Thursday, 5=Friday, 6=Saturday
    // week_descriptor: 0=teenth, 1=first, 2=second, 3=third, 4=fourth, -1=last
    
    if (week_descriptor == 0) {
        // Teenth case: find the day between 13-19
        for (unsigned short day = 13; day <= 19; ++day) {
            date d(year_, month_, day);
            if (d.day_of_week().as_number() == weekday) {
                return d;
            }
        }
    } else if (week_descriptor == -1) {
        // Last case: find the last occurrence
        date first_of_month(year_, month_, 1);
        date last_day = first_of_month.end_of_month();
        unsigned short last_day_num = last_day.day();
        
        for (unsigned short day = last_day_num; day >= last_day_num - 6 && day >= 1; --day) {
            date d(year_, month_, day);
            if (d.day_of_week().as_number() == weekday) {
                return d;
            }
        }
    } else {
        // First, second, third, fourth case
        int count = 0;
        date first_of_month(year_, month_, 1);
        date last_day = first_of_month.end_of_month();
        unsigned short last_day_num = last_day.day();
        
        for (unsigned short day = 1; day <= last_day_num; ++day) {
            date d(year_, month_, day);
            if (d.day_of_week().as_number() == weekday) {
                count++;
                if (count == week_descriptor) {
                    return d;
                }
            }
        }
    }
    
    // Should never reach here with valid input
    return date(year_, month_, 1);
}

// Teenth methods
boost::gregorian::date scheduler::monteenth() const {
    return find_meetup(1, 0);  // Monday = 1
}

boost::gregorian::date scheduler::tuesteenth() const {
    return find_meetup(2, 0);  // Tuesday = 2
}

boost::gregorian::date scheduler::wednesteenth() const {
    return find_meetup(3, 0);  // Wednesday = 3
}

boost::gregorian::date scheduler::thursteenth() const {
    return find_meetup(4, 0);  // Thursday = 4
}

boost::gregorian::date scheduler::friteenth() const {
    return find_meetup(5, 0);  // Friday = 5
}

boost::gregorian::date scheduler::saturteenth() const {
    return find_meetup(6, 0);  // Saturday = 6
}

boost::gregorian::date scheduler::sunteenth() const {
    return find_meetup(0, 0);  // Sunday = 0
}

// First week methods
boost::gregorian::date scheduler::first_monday() const {
    return find_meetup(1, 1);
}

boost::gregorian::date scheduler::first_tuesday() const {
    return find_meetup(2, 1);
}

boost::gregorian::date scheduler::first_wednesday() const {
    return find_meetup(3, 1);
}

boost::gregorian::date scheduler::first_thursday() const {
    return find_meetup(4, 1);
}

boost::gregorian::date scheduler::first_friday() const {
    return find_meetup(5, 1);
}

boost::gregorian::date scheduler::first_saturday() const {
    return find_meetup(6, 1);
}

boost::gregorian::date scheduler::first_sunday() const {
    return find_meetup(0, 1);
}

// Second week methods
boost::gregorian::date scheduler::second_monday() const {
    return find_meetup(1, 2);
}

boost::gregorian::date scheduler::second_tuesday() const {
    return find_meetup(2, 2);
}

boost::gregorian::date scheduler::second_wednesday() const {
    return find_meetup(3, 2);
}

boost::gregorian::date scheduler::second_thursday() const {
    return find_meetup(4, 2);
}

boost::gregorian::date scheduler::second_friday() const {
    return find_meetup(5, 2);
}

boost::gregorian::date scheduler::second_saturday() const {
    return find_meetup(6, 2);
}

boost::gregorian::date scheduler::second_sunday() const {
    return find_meetup(0, 2);
}

// Third week methods
boost::gregorian::date scheduler::third_monday() const {
    return find_meetup(1, 3);
}

boost::gregorian::date scheduler::third_tuesday() const {
    return find_meetup(2, 3);
}

boost::gregorian::date scheduler::third_wednesday() const {
    return find_meetup(3, 3);
}

boost::gregorian::date scheduler::third_thursday() const {
    return find_meetup(4, 3);
}

boost::gregorian::date scheduler::third_friday() const {
    return find_meetup(5, 3);
}

boost::gregorian::date scheduler::third_saturday() const {
    return find_meetup(6, 3);
}

boost::gregorian::date scheduler::third_sunday() const {
    return find_meetup(0, 3);
}

// Fourth week methods
boost::gregorian::date scheduler::fourth_monday() const {
    return find_meetup(1, 4);
}

boost::gregorian::date scheduler::fourth_tuesday() const {
    return find_meetup(2, 4);
}

boost::gregorian::date scheduler::fourth_wednesday() const {
    return find_meetup(3, 4);
}

boost::gregorian::date scheduler::fourth_thursday() const {
    return find_meetup(4, 4);
}

boost::gregorian::date scheduler::fourth_friday() const {
    return find_meetup(5, 4);
}

boost::gregorian::date scheduler::fourth_saturday() const {
    return find_meetup(6, 4);
}

boost::gregorian::date scheduler::fourth_sunday() const {
    return find_meetup(0, 4);
}

// Last week methods
boost::gregorian::date scheduler::last_monday() const {
    return find_meetup(1, -1);
}

boost::gregorian::date scheduler::last_tuesday() const {
    return find_meetup(2, -1);
}

boost::gregorian::date scheduler::last_wednesday() const {
    return find_meetup(3, -1);
}

boost::gregorian::date scheduler::last_thursday() const {
    return find_meetup(4, -1);
}

boost::gregorian::date scheduler::last_friday() const {
    return find_meetup(5, -1);
}

boost::gregorian::date scheduler::last_saturday() const {
    return find_meetup(6, -1);
}

boost::gregorian::date scheduler::last_sunday() const {
    return find_meetup(0, -1);
}

}  // namespace meetup
