#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

scheduler::scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept
    : month_(month), year_(year)
{
}

auto scheduler::monteenth() const -> boost::gregorian::date
{
    return teenth(boost::date_time::Monday);
}

auto scheduler::tuesteenth() const -> boost::gregorian::date
{
    return teenth(boost::date_time::Tuesday);
}

auto scheduler::wednesteenth() const -> boost::gregorian::date
{
    return teenth(boost::date_time::Wednesday);
}

auto scheduler::thursteenth() const -> boost::gregorian::date
{
    return teenth(boost::date_time::Thursday);
}

auto scheduler::friteenth() const -> boost::gregorian::date
{
    return teenth(boost::date_time::Friday);
}

auto scheduler::saturteenth() const -> boost::gregorian::date
{
    return teenth(boost::date_time::Saturday);
}

auto scheduler::sunteenth() const -> boost::gregorian::date
{
    return teenth(boost::date_time::Sunday);
}

auto scheduler::first_monday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Monday, 1U);
}

auto scheduler::first_tuesday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Tuesday, 1U);
}

auto scheduler::first_wednesday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Wednesday, 1U);
}

auto scheduler::first_thursday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Thursday, 1U);
}

auto scheduler::first_friday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Friday, 1U);
}

auto scheduler::first_saturday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Saturday, 1U);
}

auto scheduler::first_sunday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Sunday, 1U);
}

auto scheduler::second_monday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Monday, 2U);
}

auto scheduler::second_tuesday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Tuesday, 2U);
}

auto scheduler::second_wednesday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Wednesday, 2U);
}

auto scheduler::second_thursday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Thursday, 2U);
}

auto scheduler::second_friday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Friday, 2U);
}

auto scheduler::second_saturday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Saturday, 2U);
}

auto scheduler::second_sunday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Sunday, 2U);
}

auto scheduler::third_monday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Monday, 3U);
}

auto scheduler::third_tuesday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Tuesday, 3U);
}

auto scheduler::third_wednesday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Wednesday, 3U);
}

auto scheduler::third_thursday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Thursday, 3U);
}

auto scheduler::third_friday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Friday, 3U);
}

auto scheduler::third_saturday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Saturday, 3U);
}

auto scheduler::third_sunday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Sunday, 3U);
}

auto scheduler::fourth_monday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Monday, 4U);
}

auto scheduler::fourth_tuesday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Tuesday, 4U);
}

auto scheduler::fourth_wednesday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Wednesday, 4U);
}

auto scheduler::fourth_thursday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Thursday, 4U);
}

auto scheduler::fourth_friday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Friday, 4U);
}

auto scheduler::fourth_saturday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Saturday, 4U);
}

auto scheduler::fourth_sunday() const -> boost::gregorian::date
{
    return nth(boost::date_time::Sunday, 4U);
}

auto scheduler::last_monday() const -> boost::gregorian::date
{
    return last(boost::date_time::Monday);
}

auto scheduler::last_tuesday() const -> boost::gregorian::date
{
    return last(boost::date_time::Tuesday);
}

auto scheduler::last_wednesday() const -> boost::gregorian::date
{
    return last(boost::date_time::Wednesday);
}

auto scheduler::last_thursday() const -> boost::gregorian::date
{
    return last(boost::date_time::Thursday);
}

auto scheduler::last_friday() const -> boost::gregorian::date
{
    return last(boost::date_time::Friday);
}

auto scheduler::last_saturday() const -> boost::gregorian::date
{
    return last(boost::date_time::Saturday);
}

auto scheduler::last_sunday() const -> boost::gregorian::date
{
    return last(boost::date_time::Sunday);
}

auto scheduler::teenth(boost::date_time::weekdays wd) const -> boost::gregorian::date
{
    for (std::int32_t d = 13; d <= 19; d = (d + 1)) {
        const boost::gregorian::date current(static_cast<boost::gregorian::date::year_type>(year_), month_, static_cast<boost::gregorian::date::day_type>(d));
        if (((current.day_of_week()).as_enum()) == wd) {
            return current;
        } else {
            // continue
        }
    }
    // According to problem statement, this path should be unreachable.
    // Return 19th as a safe fallback.
    return boost::gregorian::date(static_cast<boost::gregorian::date::year_type>(year_), month_, static_cast<boost::gregorian::date::day_type>(19));
}

auto scheduler::nth(boost::date_time::weekdays wd, std::uint32_t n) const -> boost::gregorian::date
{
    boost::gregorian::nth_day_of_the_week_in_month::week_num wn = boost::gregorian::nth_day_of_the_week_in_month::first;
    switch (n) {
        case 1U: {
            wn = boost::gregorian::nth_day_of_the_week_in_month::first;
            break;
        }
        case 2U: {
            wn = boost::gregorian::nth_day_of_the_week_in_month::second;
            break;
        }
        case 3U: {
            wn = boost::gregorian::nth_day_of_the_week_in_month::third;
            break;
        }
        default: {
            // Treat other values as fourth by specification usage (1..4).
            wn = boost::gregorian::nth_day_of_the_week_in_month::fourth;
            break;
        }
    }

    const boost::gregorian::nth_day_of_the_week_in_month rule(wn, wd, month_);
    return rule.get_date(static_cast<boost::gregorian::date::year_type>(year_));
}

auto scheduler::last(boost::date_time::weekdays wd) const -> boost::gregorian::date
{
    const boost::gregorian::last_day_of_the_week_in_month rule(wd, month_);
    return rule.get_date(static_cast<boost::gregorian::date::year_type>(year_));
}

}  // namespace meetup
