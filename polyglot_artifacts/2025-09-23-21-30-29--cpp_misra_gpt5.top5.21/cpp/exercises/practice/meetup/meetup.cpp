#include "meetup.h"

namespace meetup {

namespace {

using boost::gregorian::date;
using boost::gregorian::months_of_year;
using boost::gregorian::greg_weekday;

inline greg_weekday wd_monday() { return greg_weekday(boost::date_time::Monday); }
inline greg_weekday wd_tuesday() { return greg_weekday(boost::date_time::Tuesday); }
inline greg_weekday wd_wednesday() { return greg_weekday(boost::date_time::Wednesday); }
inline greg_weekday wd_thursday() { return greg_weekday(boost::date_time::Thursday); }
inline greg_weekday wd_friday() { return greg_weekday(boost::date_time::Friday); }
inline greg_weekday wd_saturday() { return greg_weekday(boost::date_time::Saturday); }
inline greg_weekday wd_sunday() { return greg_weekday(boost::date_time::Sunday); }

date teenth(std::int32_t y, months_of_year m, greg_weekday wd)
{
    for (std::uint8_t d = static_cast<std::uint8_t>(13); (d <= static_cast<std::uint8_t>(19)); ++d) {
        const date dt(static_cast<int>(y), m, static_cast<int>(d));
        if ((dt.day_of_week() == wd)) {
            return dt;
        }
    }
    return date(static_cast<int>(y), m, static_cast<int>(13));
}

date nth_weekday_in_month(std::int32_t y, months_of_year m, greg_weekday wd, std::uint8_t n)
{
    boost::gregorian::nth_day_of_the_week_in_month::week_num wn =
        boost::gregorian::nth_day_of_the_week_in_month::first;

    switch (n) {
        case static_cast<std::uint8_t>(1):
        {
            wn = boost::gregorian::nth_day_of_the_week_in_month::first;
            break;
        }
        case static_cast<std::uint8_t>(2):
        {
            wn = boost::gregorian::nth_day_of_the_week_in_month::second;
            break;
        }
        case static_cast<std::uint8_t>(3):
        {
            wn = boost::gregorian::nth_day_of_the_week_in_month::third;
            break;
        }
        case static_cast<std::uint8_t>(4):
        {
            wn = boost::gregorian::nth_day_of_the_week_in_month::fourth;
            break;
        }
        default:
        {
            wn = boost::gregorian::nth_day_of_the_week_in_month::first;
            break;
        }
    }

    const boost::gregorian::nth_day_of_the_week_in_month rule(wn, wd, m);
    return rule.get_date(static_cast<int>(y));
}

date last_weekday_in_month(std::int32_t y, months_of_year m, greg_weekday wd)
{
    const boost::gregorian::last_day_of_the_week_in_month rule(wd, m);
    return rule.get_date(static_cast<int>(y));
}

} // unnamed namespace

// teenth implementations
boost::gregorian::date scheduler::monteenth() const
{
    return teenth(m_year, m_month, wd_monday());
}

boost::gregorian::date scheduler::tuesteenth() const
{
    return teenth(m_year, m_month, wd_tuesday());
}

boost::gregorian::date scheduler::wednesteenth() const
{
    return teenth(m_year, m_month, wd_wednesday());
}

boost::gregorian::date scheduler::thursteenth() const
{
    return teenth(m_year, m_month, wd_thursday());
}

boost::gregorian::date scheduler::friteenth() const
{
    return teenth(m_year, m_month, wd_friday());
}

boost::gregorian::date scheduler::saturteenth() const
{
    return teenth(m_year, m_month, wd_saturday());
}

boost::gregorian::date scheduler::sunteenth() const
{
    return teenth(m_year, m_month, wd_sunday());
}

// first
boost::gregorian::date scheduler::first_monday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_monday(), static_cast<std::uint8_t>(1));
}

boost::gregorian::date scheduler::first_tuesday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_tuesday(), static_cast<std::uint8_t>(1));
}

boost::gregorian::date scheduler::first_wednesday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_wednesday(), static_cast<std::uint8_t>(1));
}

boost::gregorian::date scheduler::first_thursday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_thursday(), static_cast<std::uint8_t>(1));
}

boost::gregorian::date scheduler::first_friday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_friday(), static_cast<std::uint8_t>(1));
}

boost::gregorian::date scheduler::first_saturday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_saturday(), static_cast<std::uint8_t>(1));
}

boost::gregorian::date scheduler::first_sunday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_sunday(), static_cast<std::uint8_t>(1));
}

// second
boost::gregorian::date scheduler::second_monday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_monday(), static_cast<std::uint8_t>(2));
}

boost::gregorian::date scheduler::second_tuesday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_tuesday(), static_cast<std::uint8_t>(2));
}

boost::gregorian::date scheduler::second_wednesday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_wednesday(), static_cast<std::uint8_t>(2));
}

boost::gregorian::date scheduler::second_thursday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_thursday(), static_cast<std::uint8_t>(2));
}

boost::gregorian::date scheduler::second_friday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_friday(), static_cast<std::uint8_t>(2));
}

boost::gregorian::date scheduler::second_saturday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_saturday(), static_cast<std::uint8_t>(2));
}

boost::gregorian::date scheduler::second_sunday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_sunday(), static_cast<std::uint8_t>(2));
}

// third
boost::gregorian::date scheduler::third_monday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_monday(), static_cast<std::uint8_t>(3));
}

boost::gregorian::date scheduler::third_tuesday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_tuesday(), static_cast<std::uint8_t>(3));
}

boost::gregorian::date scheduler::third_wednesday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_wednesday(), static_cast<std::uint8_t>(3));
}

boost::gregorian::date scheduler::third_thursday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_thursday(), static_cast<std::uint8_t>(3));
}

boost::gregorian::date scheduler::third_friday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_friday(), static_cast<std::uint8_t>(3));
}

boost::gregorian::date scheduler::third_saturday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_saturday(), static_cast<std::uint8_t>(3));
}

boost::gregorian::date scheduler::third_sunday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_sunday(), static_cast<std::uint8_t>(3));
}

// fourth
boost::gregorian::date scheduler::fourth_monday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_monday(), static_cast<std::uint8_t>(4));
}

boost::gregorian::date scheduler::fourth_tuesday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_tuesday(), static_cast<std::uint8_t>(4));
}

boost::gregorian::date scheduler::fourth_wednesday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_wednesday(), static_cast<std::uint8_t>(4));
}

boost::gregorian::date scheduler::fourth_thursday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_thursday(), static_cast<std::uint8_t>(4));
}

boost::gregorian::date scheduler::fourth_friday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_friday(), static_cast<std::uint8_t>(4));
}

boost::gregorian::date scheduler::fourth_saturday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_saturday(), static_cast<std::uint8_t>(4));
}

boost::gregorian::date scheduler::fourth_sunday() const
{
    return nth_weekday_in_month(m_year, m_month, wd_sunday(), static_cast<std::uint8_t>(4));
}

// last
boost::gregorian::date scheduler::last_monday() const
{
    return last_weekday_in_month(m_year, m_month, wd_monday());
}

boost::gregorian::date scheduler::last_tuesday() const
{
    return last_weekday_in_month(m_year, m_month, wd_tuesday());
}

boost::gregorian::date scheduler::last_wednesday() const
{
    return last_weekday_in_month(m_year, m_month, wd_wednesday());
}

boost::gregorian::date scheduler::last_thursday() const
{
    return last_weekday_in_month(m_year, m_month, wd_thursday());
}

boost::gregorian::date scheduler::last_friday() const
{
    return last_weekday_in_month(m_year, m_month, wd_friday());
}

boost::gregorian::date scheduler::last_saturday() const
{
    return last_weekday_in_month(m_year, m_month, wd_saturday());
}

boost::gregorian::date scheduler::last_sunday() const
{
    return last_weekday_in_month(m_year, m_month, wd_sunday());
}

}  // namespace meetup
