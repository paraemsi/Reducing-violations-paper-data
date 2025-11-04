#include "meetup.h"
#include <stdexcept>

namespace meetup {

using boost::gregorian::date;
using boost::date_time::weekdays;

scheduler::scheduler(boost::gregorian::months_of_year month, int year)
    : month_{month}, year_{year} {}

date scheduler::teenth(weekdays wd) const
{
    for (int day = 13; day <= 19; ++day) {
        date d(year_, month_, day);
        if (d.day_of_week() == wd)
            return d;
    }
    throw std::logic_error{"No teenth found"};
}

date scheduler::nth(weekdays wd, int n) const
{
    int count = 0;
    int last_day = boost::gregorian::gregorian_calendar::end_of_month_day(year_, month_);
    for (int day = 1; day <= last_day; ++day) {
        date d(year_, month_, day);
        if (d.day_of_week() == wd) {
            ++count;
            if (count == n)
                return d;
        }
    }
    throw std::logic_error{"Nth weekday not found"};
}

date scheduler::last(weekdays wd) const
{
    int last_day = boost::gregorian::gregorian_calendar::end_of_month_day(year_, month_);
    for (int day = last_day; day >= 1; --day) {
        date d(year_, month_, day);
        if (d.day_of_week() == wd)
            return d;
    }
    throw std::logic_error{"Last weekday not found"};
}

// teenth
date scheduler::monteenth() const { return teenth(boost::date_time::Monday); }
date scheduler::tuesteenth() const { return teenth(boost::date_time::Tuesday); }
date scheduler::wednesteenth() const { return teenth(boost::date_time::Wednesday); }
date scheduler::thursteenth() const { return teenth(boost::date_time::Thursday); }
date scheduler::friteenth() const { return teenth(boost::date_time::Friday); }
date scheduler::saturteenth() const { return teenth(boost::date_time::Saturday); }
date scheduler::sunteenth() const { return teenth(boost::date_time::Sunday); }

// first
date scheduler::first_monday()   const { return nth(boost::date_time::Monday,    1); }
date scheduler::first_tuesday()  const { return nth(boost::date_time::Tuesday,   1); }
date scheduler::first_wednesday()const { return nth(boost::date_time::Wednesday, 1); }
date scheduler::first_thursday() const { return nth(boost::date_time::Thursday,  1); }
date scheduler::first_friday()   const { return nth(boost::date_time::Friday,    1); }
date scheduler::first_saturday() const { return nth(boost::date_time::Saturday,  1); }
date scheduler::first_sunday()   const { return nth(boost::date_time::Sunday,    1); }

// second
date scheduler::second_monday()   const { return nth(boost::date_time::Monday,    2); }
date scheduler::second_tuesday()  const { return nth(boost::date_time::Tuesday,   2); }
date scheduler::second_wednesday()const { return nth(boost::date_time::Wednesday, 2); }
date scheduler::second_thursday() const { return nth(boost::date_time::Thursday,  2); }
date scheduler::second_friday()   const { return nth(boost::date_time::Friday,    2); }
date scheduler::second_saturday() const { return nth(boost::date_time::Saturday,  2); }
date scheduler::second_sunday()   const { return nth(boost::date_time::Sunday,    2); }

// third
date scheduler::third_monday()   const { return nth(boost::date_time::Monday,    3); }
date scheduler::third_tuesday()  const { return nth(boost::date_time::Tuesday,   3); }
date scheduler::third_wednesday()const { return nth(boost::date_time::Wednesday, 3); }
date scheduler::third_thursday() const { return nth(boost::date_time::Thursday,  3); }
date scheduler::third_friday()   const { return nth(boost::date_time::Friday,    3); }
date scheduler::third_saturday() const { return nth(boost::date_time::Saturday,  3); }
date scheduler::third_sunday()   const { return nth(boost::date_time::Sunday,    3); }

// fourth
date scheduler::fourth_monday()   const { return nth(boost::date_time::Monday,    4); }
date scheduler::fourth_tuesday()  const { return nth(boost::date_time::Tuesday,   4); }
date scheduler::fourth_wednesday()const { return nth(boost::date_time::Wednesday, 4); }
date scheduler::fourth_thursday() const { return nth(boost::date_time::Thursday,  4); }
date scheduler::fourth_friday()   const { return nth(boost::date_time::Friday,    4); }
date scheduler::fourth_saturday() const { return nth(boost::date_time::Saturday,  4); }
date scheduler::fourth_sunday()   const { return nth(boost::date_time::Sunday,    4); }

// last
date scheduler::last_monday()   const { return last(boost::date_time::Monday);    }
date scheduler::last_tuesday()  const { return last(boost::date_time::Tuesday);   }
date scheduler::last_wednesday()const { return last(boost::date_time::Wednesday); }
date scheduler::last_thursday() const { return last(boost::date_time::Thursday);  }
date scheduler::last_friday()   const { return last(boost::date_time::Friday);    }
date scheduler::last_saturday() const { return last(boost::date_time::Saturday);  }
date scheduler::last_sunday()   const { return last(boost::date_time::Sunday);    }

}  // namespace meetup
