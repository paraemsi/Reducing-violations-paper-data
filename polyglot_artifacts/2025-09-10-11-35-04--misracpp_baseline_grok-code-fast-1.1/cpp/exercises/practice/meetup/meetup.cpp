#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

scheduler::scheduler(boost::gregorian::month m, int y) : month_(m), year_(y) {}

boost::gregorian::date scheduler::day(weekday wd, week w) const {
    using namespace boost::gregorian;
    date d(year_, month_, 1);
    greg_weekday first_wd(d.day_of_week());
    int first_wd_int = first_wd.as_number();  // 0=Sun, 6=Sat
    int target_wd_int = static_cast<int>(wd);  // 0=Sun, 6=Sat

    if (w == week::teenth) {
        for (int day_num = 13; day_num <= 19; ++day_num) {
            date candidate(year_, month_, day_num);
            if (candidate.day_of_week().as_number() == target_wd_int) {
                return candidate;
            }
        }
        throw std::runtime_error("No teenth day found for the given weekday");
    } else {
        // For first, second, third, fourth, last
        int n;
        if (w == week::first) n = 1;
        else if (w == week::second) n = 2;
        else if (w == week::third) n = 3;
        else if (w == week::fourth) n = 4;
        else { // last
            // Find last day of month
            date last_d = d.end_of_month();
            int last_d_int = last_d.day();
            int weekday_last = last_d.day_of_week().as_number();
            // Offset to find the last occurrence of target_wd
            int offset = (target_wd_int - weekday_last + 7) % 7;
            int target_d = last_d_int - offset;
            return date(year_, month_, target_d);
        }
        // For first to fourth
        int offset = (target_wd_int - first_wd_int + 7) % 7;
        int target_d = 1 + offset + (n - 1) * 7;
        // Check if within month
        date last_d = d.end_of_month();
        if (target_d > last_d.day()) {
            throw std::runtime_error("Invalid date: calculated day exceeds month length");
        }
        return date(year_, month_, target_d);
    }
}

boost::gregorian::date scheduler::monteenth() const { return day(weekday::monday, week::teenth); }
boost::gregorian::date scheduler::tuesteenth() const { return day(weekday::tuesday, week::teenth); }
boost::gregorian::date scheduler::wednesteenth() const { return day(weekday::wednesday, week::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return day(weekday::thursday, week::teenth); }
boost::gregorian::date scheduler::friteenth() const { return day(weekday::friday, week::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return day(weekday::saturday, week::teenth); }
boost::gregorian::date scheduler::sunteenth() const { return day(weekday::sunday, week::teenth); }
boost::gregorian::date scheduler::first_monday() const { return day(weekday::monday, week::first); }
boost::gregorian::date scheduler::first_tuesday() const { return day(weekday::tuesday, week::first); }
boost::gregorian::date scheduler::first_wednesday() const { return day(weekday::wednesday, week::first); }
boost::gregorian::date scheduler::first_thursday() const { return day(weekday::thursday, week::first); }
boost::gregorian::date scheduler::first_friday() const { return day(weekday::friday, week::first); }
boost::gregorian::date scheduler::first_saturday() const { return day(weekday::saturday, week::first); }
boost::gregorian::date scheduler::first_sunday() const { return day(weekday::sunday, week::first); }
boost::gregorian::date scheduler::second_monday() const { return day(weekday::monday, week::second); }
boost::gregorian::date scheduler::second_tuesday() const { return day(weekday::tuesday, week::second); }
boost::gregorian::date scheduler::second_wednesday() const { return day(weekday::wednesday, week::second); }
boost::gregorian::date scheduler::second_thursday() const { return day(weekday::thursday, week::second); }
boost::gregorian::date scheduler::second_friday() const { return day(weekday::friday, week::second); }
boost::gregorian::date scheduler::second_saturday() const { return day(weekday::saturday, week::second); }
boost::gregorian::date scheduler::second_sunday() const { return day(weekday::sunday, week::second); }
boost::gregorian::date scheduler::third_monday() const { return day(weekday::monday, week::third); }
boost::gregorian::date scheduler::third_tuesday() const { return day(weekday::tuesday, week::third); }
boost::gregorian::date scheduler::third_wednesday() const { return day(weekday::wednesday, week::third); }
boost::gregorian::date scheduler::third_thursday() const { return day(weekday::thursday, week::third); }
boost::gregorian::date scheduler::third_friday() const { return day(weekday::friday, week::third); }
boost::gregorian::date scheduler::third_saturday() const { return day(weekday::saturday, week::third); }
boost::gregorian::date scheduler::third_sunday() const { return day(weekday::sunday, week::third); }
boost::gregorian::date scheduler::fourth_monday() const { return day(weekday::monday, week::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return day(weekday::tuesday, week::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return day(weekday::wednesday, week::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return day(weekday::thursday, week::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return day(weekday::friday, week::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return day(weekday::saturday, week::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return day(weekday::sunday, week::fourth); }
boost::gregorian::date scheduler::last_monday() const { return day(weekday::monday, week::last); }
boost::gregorian::date scheduler::last_tuesday() const { return day(weekday::tuesday, week::last); }
boost::gregorian::date scheduler::last_wednesday() const { return day(weekday::wednesday, week::last); }
boost::gregorian::date scheduler::last_thursday() const { return day(weekday::thursday, week::last); }
boost::gregorian::date scheduler::last_friday() const { return day(weekday::friday, week::last); }
boost::gregorian::date scheduler::last_saturday() const { return day(weekday::saturday, week::last); }
boost::gregorian::date scheduler::last_sunday() const { return day(weekday::sunday, week::last); }

}  // namespace meetup
