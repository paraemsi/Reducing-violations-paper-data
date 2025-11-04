#include "meetup.h"
#include <ctime>
#include <stdexcept>

namespace meetup {

namespace {

constexpr day_t days_in_month(std::int32_t year, std::uint32_t month)
{
    switch(month)
    {
        case 1U: case 3U: case 5U: case 7U: case 8U: case 10U: case 12U:
            return static_cast<day_t>(31);
        case 4U: case 6U: case 9U: case 11U:
            return static_cast<day_t>(30);
        case 2U:
            if(((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0)))
            {
                return static_cast<day_t>(29);
            }
            else
            {
                return static_cast<day_t>(28);
            }
        default:
            throw std::invalid_argument("Invalid month");
    }
}

std::uint8_t weekday_of(std::int32_t year, std::uint32_t month, day_t day)
{
    std::tm timeinfo = {};
    timeinfo.tm_year = static_cast<int>(year) - 1900;
    timeinfo.tm_mon = static_cast<int>(month) - 1;
    timeinfo.tm_mday = static_cast<int>(day);
    timeinfo.tm_hour = 12;
    std::mktime(&timeinfo);
    return static_cast<std::uint8_t>(timeinfo.tm_wday);
}

day_t find_teenth(std::int32_t year, std::uint32_t month, Weekday weekday)
{
    for(day_t d = 13U; d <= 19U; ++d)
    {
        if(weekday_of(year, month, d) == static_cast<std::uint8_t>(weekday))
        {
            return d;
        }
    }
    throw std::logic_error("No teenth day found");
}

day_t find_nth(std::int32_t year, std::uint32_t month, Weekday weekday, std::uint8_t n)
{
    day_t first_day = 1U;
    day_t last_day = days_in_month(year, month);
    std::uint8_t target_wd = static_cast<std::uint8_t>(weekday);

    day_t first_wd = first_day;
    std::uint8_t first_wd_wday = weekday_of(year, month, first_wd);
    day_t offset = (target_wd + 7U - first_wd_wday) % 7U;
    day_t day = static_cast<day_t>(first_wd + offset + (7U * n));
    if(day > last_day)
    {
        throw std::logic_error("No such weekday in this month");
    }
    return day;
}

day_t find_last(std::int32_t year, std::uint32_t month, Weekday weekday)
{
    day_t last_day = days_in_month(year, month);
    std::uint8_t target_wd = static_cast<std::uint8_t>(weekday);
    std::uint8_t last_wd_wday = weekday_of(year, month, last_day);
    day_t offset = (last_wd_wday + 7U - target_wd) % 7U;
    return static_cast<day_t>(last_day - offset);
}

} // anonymous namespace

scheduler::scheduler(std::uint32_t month, std::int32_t year)
    : m_year(year), m_month(month)
{
}

day_t scheduler::get_day(Weekday weekday, Schedule schedule) const
{
    switch(schedule)
    {
        case Schedule::First:
            return find_nth(m_year, m_month, weekday, 0U);
        case Schedule::Second:
            return find_nth(m_year, m_month, weekday, 1U);
        case Schedule::Third:
            return find_nth(m_year, m_month, weekday, 2U);
        case Schedule::Fourth:
            return find_nth(m_year, m_month, weekday, 3U);
        case Schedule::Last:
            return find_last(m_year, m_month, weekday);
        case Schedule::Teenth:
            return find_teenth(m_year, m_month, weekday);
        default:
            throw std::invalid_argument("Invalid schedule");
    }
}

// Teenth
day_t scheduler::monteenth() const { return get_day(Weekday::Monday, Schedule::Teenth); }
day_t scheduler::tuesteenth() const { return get_day(Weekday::Tuesday, Schedule::Teenth); }
day_t scheduler::wednesteenth() const { return get_day(Weekday::Wednesday, Schedule::Teenth); }
day_t scheduler::thursteenth() const { return get_day(Weekday::Thursday, Schedule::Teenth); }
day_t scheduler::friteenth() const { return get_day(Weekday::Friday, Schedule::Teenth); }
day_t scheduler::saturteenth() const { return get_day(Weekday::Saturday, Schedule::Teenth); }
day_t scheduler::sunteenth() const { return get_day(Weekday::Sunday, Schedule::Teenth); }

// First
day_t scheduler::first_monday() const { return get_day(Weekday::Monday, Schedule::First); }
day_t scheduler::first_tuesday() const { return get_day(Weekday::Tuesday, Schedule::First); }
day_t scheduler::first_wednesday() const { return get_day(Weekday::Wednesday, Schedule::First); }
day_t scheduler::first_thursday() const { return get_day(Weekday::Thursday, Schedule::First); }
day_t scheduler::first_friday() const { return get_day(Weekday::Friday, Schedule::First); }
day_t scheduler::first_saturday() const { return get_day(Weekday::Saturday, Schedule::First); }
day_t scheduler::first_sunday() const { return get_day(Weekday::Sunday, Schedule::First); }

// Second
day_t scheduler::second_monday() const { return get_day(Weekday::Monday, Schedule::Second); }
day_t scheduler::second_tuesday() const { return get_day(Weekday::Tuesday, Schedule::Second); }
day_t scheduler::second_wednesday() const { return get_day(Weekday::Wednesday, Schedule::Second); }
day_t scheduler::second_thursday() const { return get_day(Weekday::Thursday, Schedule::Second); }
day_t scheduler::second_friday() const { return get_day(Weekday::Friday, Schedule::Second); }
day_t scheduler::second_saturday() const { return get_day(Weekday::Saturday, Schedule::Second); }
day_t scheduler::second_sunday() const { return get_day(Weekday::Sunday, Schedule::Second); }

// Third
day_t scheduler::third_monday() const { return get_day(Weekday::Monday, Schedule::Third); }
day_t scheduler::third_tuesday() const { return get_day(Weekday::Tuesday, Schedule::Third); }
day_t scheduler::third_wednesday() const { return get_day(Weekday::Wednesday, Schedule::Third); }
day_t scheduler::third_thursday() const { return get_day(Weekday::Thursday, Schedule::Third); }
day_t scheduler::third_friday() const { return get_day(Weekday::Friday, Schedule::Third); }
day_t scheduler::third_saturday() const { return get_day(Weekday::Saturday, Schedule::Third); }
day_t scheduler::third_sunday() const { return get_day(Weekday::Sunday, Schedule::Third); }

// Fourth
day_t scheduler::fourth_monday() const { return get_day(Weekday::Monday, Schedule::Fourth); }
day_t scheduler::fourth_tuesday() const { return get_day(Weekday::Tuesday, Schedule::Fourth); }
day_t scheduler::fourth_wednesday() const { return get_day(Weekday::Wednesday, Schedule::Fourth); }
day_t scheduler::fourth_thursday() const { return get_day(Weekday::Thursday, Schedule::Fourth); }
day_t scheduler::fourth_friday() const { return get_day(Weekday::Friday, Schedule::Fourth); }
day_t scheduler::fourth_saturday() const { return get_day(Weekday::Saturday, Schedule::Fourth); }
day_t scheduler::fourth_sunday() const { return get_day(Weekday::Sunday, Schedule::Fourth); }

// Last
day_t scheduler::last_monday() const { return get_day(Weekday::Monday, Schedule::Last); }
day_t scheduler::last_tuesday() const { return get_day(Weekday::Tuesday, Schedule::Last); }
day_t scheduler::last_wednesday() const { return get_day(Weekday::Wednesday, Schedule::Last); }
day_t scheduler::last_thursday() const { return get_day(Weekday::Thursday, Schedule::Last); }
day_t scheduler::last_friday() const { return get_day(Weekday::Friday, Schedule::Last); }
day_t scheduler::last_saturday() const { return get_day(Weekday::Saturday, Schedule::Last); }
day_t scheduler::last_sunday() const { return get_day(Weekday::Sunday, Schedule::Last); }

}  // namespace meetup
