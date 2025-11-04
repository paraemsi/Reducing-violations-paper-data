#include "meetup.h"

namespace meetup {

namespace {
inline unsigned weekday_to_c_encoding(weekday w)
{
    switch (w) {
        case weekday::monday: return 1u;
        case weekday::tuesday: return 2u;
        case weekday::wednesday: return 3u;
        case weekday::thursday: return 4u;
        case weekday::friday: return 5u;
        case weekday::saturday: return 6u;
        case weekday::sunday: return 0u;
    }
    return 0u;
}

inline bool is_leap(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

inline unsigned days_in_month(int y, int m)
{
    static const unsigned dim[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (m == 2) return is_leap(y) ? 29u : 28u;
    return dim[m - 1];
}

// Sakamoto's algorithm: 0=Sunday, 1=Monday, ..., 6=Saturday
inline unsigned day_of_week(int y, int m, int d)
{
    static const int t[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if (m < 3) y -= 1;
    int w = (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
    if (w < 0) w += 7;
    return static_cast<unsigned>(w);
}
} // namespace

scheduler::scheduler(int year, int month)
    : year_{year}, month_{month} {}

boost::gregorian::date scheduler::day(weekday wd, schedule sch) const
{
    const unsigned target = weekday_to_c_encoding(wd);

    const unsigned first_w = day_of_week(year_, month_, 1);
    const unsigned offset = (target + 7u - first_w) % 7u;

    unsigned d = 0u;

    switch (sch) {
        case schedule::first:
            d = 1u + offset;
            break;
        case schedule::second:
            d = 1u + offset + 7u;
            break;
        case schedule::third:
            d = 1u + offset + 14u;
            break;
        case schedule::fourth:
            d = 1u + offset + 21u;
            break;
        case schedule::last: {
            const unsigned last_day = days_in_month(year_, month_);
            const unsigned last_w = day_of_week(year_, month_, static_cast<int>(last_day));
            const unsigned back = (last_w + 7u - target) % 7u;
            d = last_day - back;
            break;
        }
        case schedule::teenth: {
            const unsigned w13 = day_of_week(year_, month_, 13);
            const unsigned teen_offset = (target + 7u - w13) % 7u;
            d = 13u + teen_offset;
            break;
        }
    }

    return boost::gregorian::date(
        year_,
        static_cast<boost::gregorian::months_of_year>(month_),
        static_cast<int>(d)
    );
}

boost::gregorian::date scheduler::monteenth() const { return day(weekday::monday, schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth() const { return day(weekday::tuesday, schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth() const { return day(weekday::wednesday, schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return day(weekday::thursday, schedule::teenth); }
boost::gregorian::date scheduler::friteenth() const { return day(weekday::friday, schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return day(weekday::saturday, schedule::teenth); }
boost::gregorian::date scheduler::sunteenth() const { return day(weekday::sunday, schedule::teenth); }

boost::gregorian::date scheduler::first_monday() const { return day(weekday::monday, schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const { return day(weekday::tuesday, schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return day(weekday::wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const { return day(weekday::thursday, schedule::first); }
boost::gregorian::date scheduler::first_friday() const { return day(weekday::friday, schedule::first); }
boost::gregorian::date scheduler::first_saturday() const { return day(weekday::saturday, schedule::first); }
boost::gregorian::date scheduler::first_sunday() const { return day(weekday::sunday, schedule::first); }

boost::gregorian::date scheduler::second_monday() const { return day(weekday::monday, schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const { return day(weekday::tuesday, schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return day(weekday::wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const { return day(weekday::thursday, schedule::second); }
boost::gregorian::date scheduler::second_friday() const { return day(weekday::friday, schedule::second); }
boost::gregorian::date scheduler::second_saturday() const { return day(weekday::saturday, schedule::second); }
boost::gregorian::date scheduler::second_sunday() const { return day(weekday::sunday, schedule::second); }

boost::gregorian::date scheduler::third_monday() const { return day(weekday::monday, schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const { return day(weekday::tuesday, schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return day(weekday::wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const { return day(weekday::thursday, schedule::third); }
boost::gregorian::date scheduler::third_friday() const { return day(weekday::friday, schedule::third); }
boost::gregorian::date scheduler::third_saturday() const { return day(weekday::saturday, schedule::third); }
boost::gregorian::date scheduler::third_sunday() const { return day(weekday::sunday, schedule::third); }

boost::gregorian::date scheduler::fourth_monday() const { return day(weekday::monday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return day(weekday::tuesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return day(weekday::wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return day(weekday::thursday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return day(weekday::friday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return day(weekday::saturday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return day(weekday::sunday, schedule::fourth); }

boost::gregorian::date scheduler::last_monday() const { return day(weekday::monday, schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const { return day(weekday::tuesday, schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return day(weekday::wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const { return day(weekday::thursday, schedule::last); }
boost::gregorian::date scheduler::last_friday() const { return day(weekday::friday, schedule::last); }
boost::gregorian::date scheduler::last_saturday() const { return day(weekday::saturday, schedule::last); }
boost::gregorian::date scheduler::last_sunday() const { return day(weekday::sunday, schedule::last); }

}  // namespace meetup
