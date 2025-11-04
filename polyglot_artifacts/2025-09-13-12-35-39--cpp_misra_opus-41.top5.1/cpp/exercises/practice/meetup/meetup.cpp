#include "meetup.h"
#include <cstdint>

namespace meetup {

scheduler::scheduler(boost::gregorian::greg_month month, boost::gregorian::greg_year year)
    : month_(month), year_(year) {
}

boost::gregorian::date scheduler::find_teenth_day(boost::gregorian::greg_weekday weekday) const {
    // Find the teenth day (13-19) that matches the weekday
    for (std::uint32_t day = 13U; day <= 19U; day = day + 1U) {
        boost::gregorian::date d(year_, month_, day);
        if (d.day_of_week() == weekday) {
            return d;
        }
    }
    return boost::gregorian::date();
}

boost::gregorian::date scheduler::find_nth_weekday(std::uint32_t n, boost::gregorian::greg_weekday weekday) const {
    std::uint32_t count = 0U;
    boost::gregorian::date first_of_month(year_, month_, 1U);
    boost::gregorian::date end_of_month = first_of_month.end_of_month();
    
    for (boost::gregorian::date d = first_of_month; d <= end_of_month; d = d + boost::gregorian::days(1)) {
        if (d.day_of_week() == weekday) {
            count = count + 1U;
            if (count == n) {
                return d;
            }
        }
    }
    return boost::gregorian::date();
}

boost::gregorian::date scheduler::find_last_weekday(boost::gregorian::greg_weekday weekday) const {
    boost::gregorian::date first_of_month(year_, month_, 1U);
    boost::gregorian::date end_of_month = first_of_month.end_of_month();
    
    for (boost::gregorian::date d = end_of_month; d >= first_of_month; d = d - boost::gregorian::days(1)) {
        if (d.day_of_week() == weekday) {
            return d;
        }
    }
    return boost::gregorian::date();
}

// Teenth methods
boost::gregorian::date scheduler::monteenth() const {
    return find_teenth_day(boost::gregorian::Monday);
}

boost::gregorian::date scheduler::tuesteenth() const {
    return find_teenth_day(boost::gregorian::Tuesday);
}

boost::gregorian::date scheduler::wednesteenth() const {
    return find_teenth_day(boost::gregorian::Wednesday);
}

boost::gregorian::date scheduler::thursteenth() const {
    return find_teenth_day(boost::gregorian::Thursday);
}

boost::gregorian::date scheduler::friteenth() const {
    return find_teenth_day(boost::gregorian::Friday);
}

boost::gregorian::date scheduler::saturteenth() const {
    return find_teenth_day(boost::gregorian::Saturday);
}

boost::gregorian::date scheduler::sunteenth() const {
    return find_teenth_day(boost::gregorian::Sunday);
}

// First week methods
boost::gregorian::date scheduler::first_monday() const {
    return find_nth_weekday(1U, boost::gregorian::Monday);
}

boost::gregorian::date scheduler::first_tuesday() const {
    return find_nth_weekday(1U, boost::gregorian::Tuesday);
}

boost::gregorian::date scheduler::first_wednesday() const {
    return find_nth_weekday(1U, boost::gregorian::Wednesday);
}

boost::gregorian::date scheduler::first_thursday() const {
    return find_nth_weekday(1U, boost::gregorian::Thursday);
}

boost::gregorian::date scheduler::first_friday() const {
    return find_nth_weekday(1U, boost::gregorian::Friday);
}

boost::gregorian::date scheduler::first_saturday() const {
    return find_nth_weekday(1U, boost::gregorian::Saturday);
}

boost::gregorian::date scheduler::first_sunday() const {
    return find_nth_weekday(1U, boost::gregorian::Sunday);
}

// Second week methods
boost::gregorian::date scheduler::second_monday() const {
    return find_nth_weekday(2U, boost::gregorian::Monday);
}

boost::gregorian::date scheduler::second_tuesday() const {
    return find_nth_weekday(2U, boost::gregorian::Tuesday);
}

boost::gregorian::date scheduler::second_wednesday() const {
    return find_nth_weekday(2U, boost::gregorian::Wednesday);
}

boost::gregorian::date scheduler::second_thursday() const {
    return find_nth_weekday(2U, boost::gregorian::Thursday);
}

boost::gregorian::date scheduler::second_friday() const {
    return find_nth_weekday(2U, boost::gregorian::Friday);
}

boost::gregorian::date scheduler::second_saturday() const {
    return find_nth_weekday(2U, boost::gregorian::Saturday);
}

boost::gregorian::date scheduler::second_sunday() const {
    return find_nth_weekday(2U, boost::gregorian::Sunday);
}

// Third week methods
boost::gregorian::date scheduler::third_monday() const {
    return find_nth_weekday(3U, boost::gregorian::Monday);
}

boost::gregorian::date scheduler::third_tuesday() const {
    return find_nth_weekday(3U, boost::gregorian::Tuesday);
}

boost::gregorian::date scheduler::third_wednesday() const {
    return find_nth_weekday(3U, boost::gregorian::Wednesday);
}

boost::gregorian::date scheduler::third_thursday() const {
    return find_nth_weekday(3U, boost::gregorian::Thursday);
}

boost::gregorian::date scheduler::third_friday() const {
    return find_nth_weekday(3U, boost::gregorian::Friday);
}

boost::gregorian::date scheduler::third_saturday() const {
    return find_nth_weekday(3U, boost::gregorian::Saturday);
}

boost::gregorian::date scheduler::third_sunday() const {
    return find_nth_weekday(3U, boost::gregorian::Sunday);
}

// Fourth week methods
boost::gregorian::date scheduler::fourth_monday() const {
    return find_nth_weekday(4U, boost::gregorian::Monday);
}

boost::gregorian::date scheduler::fourth_tuesday() const {
    return find_nth_weekday(4U, boost::gregorian::Tuesday);
}

boost::gregorian::date scheduler::fourth_wednesday() const {
    return find_nth_weekday(4U, boost::gregorian::Wednesday);
}

boost::gregorian::date scheduler::fourth_thursday() const {
    return find_nth_weekday(4U, boost::gregorian::Thursday);
}

boost::gregorian::date scheduler::fourth_friday() const {
    return find_nth_weekday(4U, boost::gregorian::Friday);
}

boost::gregorian::date scheduler::fourth_saturday() const {
    return find_nth_weekday(4U, boost::gregorian::Saturday);
}

boost::gregorian::date scheduler::fourth_sunday() const {
    return find_nth_weekday(4U, boost::gregorian::Sunday);
}

// Last week methods
boost::gregorian::date scheduler::last_monday() const {
    return find_last_weekday(boost::gregorian::Monday);
}

boost::gregorian::date scheduler::last_tuesday() const {
    return find_last_weekday(boost::gregorian::Tuesday);
}

boost::gregorian::date scheduler::last_wednesday() const {
    return find_last_weekday(boost::gregorian::Wednesday);
}

boost::gregorian::date scheduler::last_thursday() const {
    return find_last_weekday(boost::gregorian::Thursday);
}

boost::gregorian::date scheduler::last_friday() const {
    return find_last_weekday(boost::gregorian::Friday);
}

boost::gregorian::date scheduler::last_saturday() const {
    return find_last_weekday(boost::gregorian::Saturday);
}

boost::gregorian::date scheduler::last_sunday() const {
    return find_last_weekday(boost::gregorian::Sunday);
}

}  // namespace meetup
