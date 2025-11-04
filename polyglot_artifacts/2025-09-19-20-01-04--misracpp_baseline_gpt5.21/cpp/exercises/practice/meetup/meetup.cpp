#include "meetup.h"

namespace meetup {

using boost::gregorian::date;
using boost::date_time::weekdays;
using boost::gregorian::gregorian_calendar;

scheduler::scheduler(int year, int month) : year_{year}, month_{month} {}

date scheduler::meetup_day(weekdays wd, schedule s) const {
    switch (s) {
        case schedule::teenth: {
            for (int day_num = 13; day_num <= 19; ++day_num) {
                date d(year_, month_, day_num);
                if (d.day_of_week().as_number() == static_cast<int>(wd)) {
                    return d;
                }
            }
            break;  // Unreachable: every weekday occurs once in teenth range
        }
        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth: {
            int nth = 0;
            switch (s) {
                case schedule::first:  nth = 1; break;
                case schedule::second: nth = 2; break;
                case schedule::third:  nth = 3; break;
                case schedule::fourth: nth = 4; break;
                default: break;
            }
            date first_of_month(year_, month_, 1);
            int first_wd = first_of_month.day_of_week().as_number();  // 0=Sun..6=Sat
            int delta = (static_cast<int>(wd) - first_wd + 7) % 7;
            int day_num = 1 + delta + 7 * (nth - 1);
            return date(year_, month_, day_num);
        }
        case schedule::last: {
            int last_dom = gregorian_calendar::end_of_month_day(year_, month_);
            date last_of_month(year_, month_, last_dom);
            int delta = (last_of_month.day_of_week().as_number() - static_cast<int>(wd) + 7) % 7;
            int day_num = last_dom - delta;
            return date(year_, month_, day_num);
        }
    }

    // Fallback (should never be reached)
    return date(year_, month_, 1);
}

date scheduler::monteenth() const { return meetup_day(boost::date_time::Monday, schedule::teenth); }
date scheduler::tuesteenth() const { return meetup_day(boost::date_time::Tuesday, schedule::teenth); }
date scheduler::wednesteenth() const { return meetup_day(boost::date_time::Wednesday, schedule::teenth); }
date scheduler::thursteenth() const { return meetup_day(boost::date_time::Thursday, schedule::teenth); }
date scheduler::friteenth() const { return meetup_day(boost::date_time::Friday, schedule::teenth); }
date scheduler::saturteenth() const { return meetup_day(boost::date_time::Saturday, schedule::teenth); }
date scheduler::sunteenth() const { return meetup_day(boost::date_time::Sunday, schedule::teenth); }

date scheduler::first_monday() const { return meetup_day(boost::date_time::Monday, schedule::first); }
date scheduler::first_tuesday() const { return meetup_day(boost::date_time::Tuesday, schedule::first); }
date scheduler::first_wednesday() const { return meetup_day(boost::date_time::Wednesday, schedule::first); }
date scheduler::first_thursday() const { return meetup_day(boost::date_time::Thursday, schedule::first); }
date scheduler::first_friday() const { return meetup_day(boost::date_time::Friday, schedule::first); }
date scheduler::first_saturday() const { return meetup_day(boost::date_time::Saturday, schedule::first); }
date scheduler::first_sunday() const { return meetup_day(boost::date_time::Sunday, schedule::first); }

date scheduler::second_monday() const { return meetup_day(boost::date_time::Monday, schedule::second); }
date scheduler::second_tuesday() const { return meetup_day(boost::date_time::Tuesday, schedule::second); }
date scheduler::second_wednesday() const { return meetup_day(boost::date_time::Wednesday, schedule::second); }
date scheduler::second_thursday() const { return meetup_day(boost::date_time::Thursday, schedule::second); }
date scheduler::second_friday() const { return meetup_day(boost::date_time::Friday, schedule::second); }
date scheduler::second_saturday() const { return meetup_day(boost::date_time::Saturday, schedule::second); }
date scheduler::second_sunday() const { return meetup_day(boost::date_time::Sunday, schedule::second); }

date scheduler::third_monday() const { return meetup_day(boost::date_time::Monday, schedule::third); }
date scheduler::third_tuesday() const { return meetup_day(boost::date_time::Tuesday, schedule::third); }
date scheduler::third_wednesday() const { return meetup_day(boost::date_time::Wednesday, schedule::third); }
date scheduler::third_thursday() const { return meetup_day(boost::date_time::Thursday, schedule::third); }
date scheduler::third_friday() const { return meetup_day(boost::date_time::Friday, schedule::third); }
date scheduler::third_saturday() const { return meetup_day(boost::date_time::Saturday, schedule::third); }
date scheduler::third_sunday() const { return meetup_day(boost::date_time::Sunday, schedule::third); }

date scheduler::fourth_monday() const { return meetup_day(boost::date_time::Monday, schedule::fourth); }
date scheduler::fourth_tuesday() const { return meetup_day(boost::date_time::Tuesday, schedule::fourth); }
date scheduler::fourth_wednesday() const { return meetup_day(boost::date_time::Wednesday, schedule::fourth); }
date scheduler::fourth_thursday() const { return meetup_day(boost::date_time::Thursday, schedule::fourth); }
date scheduler::fourth_friday() const { return meetup_day(boost::date_time::Friday, schedule::fourth); }
date scheduler::fourth_saturday() const { return meetup_day(boost::date_time::Saturday, schedule::fourth); }
date scheduler::fourth_sunday() const { return meetup_day(boost::date_time::Sunday, schedule::fourth); }

date scheduler::last_monday() const { return meetup_day(boost::date_time::Monday, schedule::last); }
date scheduler::last_tuesday() const { return meetup_day(boost::date_time::Tuesday, schedule::last); }
date scheduler::last_wednesday() const { return meetup_day(boost::date_time::Wednesday, schedule::last); }
date scheduler::last_thursday() const { return meetup_day(boost::date_time::Thursday, schedule::last); }
date scheduler::last_friday() const { return meetup_day(boost::date_time::Friday, schedule::last); }
date scheduler::last_saturday() const { return meetup_day(boost::date_time::Saturday, schedule::last); }
date scheduler::last_sunday() const { return meetup_day(boost::date_time::Sunday, schedule::last); }

}  // namespace meetup
