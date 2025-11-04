#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
#include <cstdint>

namespace meetup {

namespace {

boost::date_time::weekdays weekday_from_index(std::uint8_t idx)
{
    switch(idx)
    {
        case 0U: return boost::date_time::Sunday;
        case 1U: return boost::date_time::Monday;
        case 2U: return boost::date_time::Tuesday;
        case 3U: return boost::date_time::Wednesday;
        case 4U: return boost::date_time::Thursday;
        case 5U: return boost::date_time::Friday;
        case 6U: return boost::date_time::Saturday;
        default: throw std::invalid_argument("Invalid weekday index");
    }
}

boost::date_time::weekdays weekday_from_name(const std::string& name)
{
    if(name == "Monday") return boost::date_time::Monday;
    if(name == "Tuesday") return boost::date_time::Tuesday;
    if(name == "Wednesday") return boost::date_time::Wednesday;
    if(name == "Thursday") return boost::date_time::Thursday;
    if(name == "Friday") return boost::date_time::Friday;
    if(name == "Saturday") return boost::date_time::Saturday;
    if(name == "Sunday") return boost::date_time::Sunday;
    throw std::invalid_argument("Invalid weekday name: " + name);
}

} // anonymous namespace

scheduler::scheduler(boost::gregorian::month_enum month, std::int32_t year)
    : m_month(month), m_year(year)
{
}

boost::gregorian::date scheduler::find_nth_weekday(boost::date_time::weekdays wd, std::uint8_t n) const
{
    boost::gregorian::date first(m_year, m_month, 1U);
    std::uint8_t first_wd = static_cast<std::uint8_t>(first.day_of_week());
    std::uint8_t target_wd = static_cast<std::uint8_t>(wd);

    std::uint8_t day = 1U + ((7U + target_wd - first_wd) % 7U) + (7U * (n - 1U));
    if(day > static_cast<std::uint8_t>(boost::gregorian::gregorian_calendar::end_of_month_day(m_year, m_month)))
    {
        throw std::logic_error("No such weekday in this month");
    }
    return boost::gregorian::date(m_year, m_month, day);
}

boost::gregorian::date scheduler::find_teenth_weekday(boost::date_time::weekdays wd) const
{
    for(std::uint8_t d = 13U; d <= 19U; ++d)
    {
        boost::gregorian::date dt(m_year, m_month, d);
        if(dt.day_of_week() == wd)
        {
            return dt;
        }
    }
    throw std::logic_error("No teenth weekday found");
}

boost::gregorian::date scheduler::find_last_weekday(boost::date_time::weekdays wd) const
{
    std::uint8_t last_day = static_cast<std::uint8_t>(boost::gregorian::gregorian_calendar::end_of_month_day(m_year, m_month));
    for(std::int8_t d = static_cast<std::int8_t>(last_day); d >= 1; --d)
    {
        boost::gregorian::date dt(m_year, m_month, static_cast<std::uint8_t>(d));
        if(dt.day_of_week() == wd)
        {
            return dt;
        }
    }
    throw std::logic_error("No last weekday found");
}

// teenth
boost::gregorian::date scheduler::monteenth() const { return find_teenth_weekday(boost::date_time::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return find_teenth_weekday(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return find_teenth_weekday(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return find_teenth_weekday(boost::date_time::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return find_teenth_weekday(boost::date_time::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return find_teenth_weekday(boost::date_time::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return find_teenth_weekday(boost::date_time::Sunday); }

// first
boost::gregorian::date scheduler::first_monday() const { return find_nth_weekday(boost::date_time::Monday, 1U); }
boost::gregorian::date scheduler::first_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 1U); }
boost::gregorian::date scheduler::first_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 1U); }
boost::gregorian::date scheduler::first_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 1U); }
boost::gregorian::date scheduler::first_friday() const { return find_nth_weekday(boost::date_time::Friday, 1U); }
boost::gregorian::date scheduler::first_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 1U); }
boost::gregorian::date scheduler::first_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 1U); }

// second
boost::gregorian::date scheduler::second_monday() const { return find_nth_weekday(boost::date_time::Monday, 2U); }
boost::gregorian::date scheduler::second_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 2U); }
boost::gregorian::date scheduler::second_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 2U); }
boost::gregorian::date scheduler::second_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 2U); }
boost::gregorian::date scheduler::second_friday() const { return find_nth_weekday(boost::date_time::Friday, 2U); }
boost::gregorian::date scheduler::second_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 2U); }
boost::gregorian::date scheduler::second_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 2U); }

// third
boost::gregorian::date scheduler::third_monday() const { return find_nth_weekday(boost::date_time::Monday, 3U); }
boost::gregorian::date scheduler::third_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 3U); }
boost::gregorian::date scheduler::third_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 3U); }
boost::gregorian::date scheduler::third_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 3U); }
boost::gregorian::date scheduler::third_friday() const { return find_nth_weekday(boost::date_time::Friday, 3U); }
boost::gregorian::date scheduler::third_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 3U); }
boost::gregorian::date scheduler::third_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 3U); }

// fourth
boost::gregorian::date scheduler::fourth_monday() const { return find_nth_weekday(boost::date_time::Monday, 4U); }
boost::gregorian::date scheduler::fourth_tuesday() const { return find_nth_weekday(boost::date_time::Tuesday, 4U); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_nth_weekday(boost::date_time::Wednesday, 4U); }
boost::gregorian::date scheduler::fourth_thursday() const { return find_nth_weekday(boost::date_time::Thursday, 4U); }
boost::gregorian::date scheduler::fourth_friday() const { return find_nth_weekday(boost::date_time::Friday, 4U); }
boost::gregorian::date scheduler::fourth_saturday() const { return find_nth_weekday(boost::date_time::Saturday, 4U); }
boost::gregorian::date scheduler::fourth_sunday() const { return find_nth_weekday(boost::date_time::Sunday, 4U); }

// last
boost::gregorian::date scheduler::last_monday() const { return find_last_weekday(boost::date_time::Monday); }
boost::gregorian::date scheduler::last_tuesday() const { return find_last_weekday(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return find_last_weekday(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::last_thursday() const { return find_last_weekday(boost::date_time::Thursday); }
boost::gregorian::date scheduler::last_friday() const { return find_last_weekday(boost::date_time::Friday); }
boost::gregorian::date scheduler::last_saturday() const { return find_last_weekday(boost::date_time::Saturday); }
boost::gregorian::date scheduler::last_sunday() const { return find_last_weekday(boost::date_time::Sunday); }

} // namespace meetup
