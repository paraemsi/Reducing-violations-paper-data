#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
#include <cstdint>

namespace meetup {

scheduler::scheduler(boost::gregorian::greg_month month,
                     std::int32_t                 year) noexcept
    : m_month{month},
      m_year{year}
{
    /* intentionally empty */
}

boost::gregorian::date
scheduler::teenth_weekday(boost::date_time::weekdays wd) const
{
    for(std::uint32_t d = 13U; d <= 19U; ++d)
    {
        const boost::gregorian::date current{m_year,
                                             m_month,
                                             static_cast<unsigned short>(d)};
        if(current.day_of_week().as_number() == static_cast<unsigned short>(wd))
        {
            return current;
        }
    }
    throw std::logic_error("requested teenth weekday does not exist");
}

boost::gregorian::date
scheduler::nth_weekday(std::uint8_t nth, boost::date_time::weekdays wd) const
{
    if((nth == 0U) || (nth > 4U))
    {
        throw std::invalid_argument("nth must be 1-4");
    }

    const boost::gregorian::date first{m_year, m_month, 1U};
    const unsigned short first_wd{first.day_of_week().as_number()};
    const unsigned short target_wd{static_cast<unsigned short>(wd)};

    const unsigned short offset{static_cast<unsigned short>(
        (static_cast<int>(target_wd) - static_cast<int>(first_wd) + 7) % 7)};

    const unsigned short day_num{
        static_cast<unsigned short>(1U + offset + (7U * (nth - 1U)))};

    try
    {
        return boost::gregorian::date{m_year, m_month, day_num};
    }
    catch(const std::exception&)
    {
        throw std::logic_error("requested nth weekday does not exist");
    }
}

boost::gregorian::date
scheduler::last_weekday(boost::date_time::weekdays wd) const
{
    const unsigned short last_dom{
        boost::gregorian::gregorian_calendar::end_of_month_day(
            static_cast<int>(m_year),
            m_month.as_number())};

    for(std::int32_t d = static_cast<std::int32_t>(last_dom); d > 0; --d)
    {
        const boost::gregorian::date current{m_year,
                                             m_month,
                                             static_cast<unsigned short>(d)};
        if(current.day_of_week().as_number() == static_cast<unsigned short>(wd))
        {
            return current;
        }
    }
    throw std::logic_error("requested last weekday does not exist");
}

#define MEETUP_DEFINE(name, expr) \
boost::gregorian::date scheduler::name() const { return (expr); }

MEETUP_DEFINE(monteenth,  teenth_weekday(boost::date_time::Monday))
MEETUP_DEFINE(tuesteenth, teenth_weekday(boost::date_time::Tuesday))
MEETUP_DEFINE(wednesteenth, teenth_weekday(boost::date_time::Wednesday))
MEETUP_DEFINE(thursteenth, teenth_weekday(boost::date_time::Thursday))
MEETUP_DEFINE(friteenth,  teenth_weekday(boost::date_time::Friday))
MEETUP_DEFINE(saturteenth, teenth_weekday(boost::date_time::Saturday))
MEETUP_DEFINE(sunteenth,  teenth_weekday(boost::date_time::Sunday))

MEETUP_DEFINE(first_monday,    nth_weekday(1U, boost::date_time::Monday))
MEETUP_DEFINE(first_tuesday,   nth_weekday(1U, boost::date_time::Tuesday))
MEETUP_DEFINE(first_wednesday, nth_weekday(1U, boost::date_time::Wednesday))
MEETUP_DEFINE(first_thursday,  nth_weekday(1U, boost::date_time::Thursday))
MEETUP_DEFINE(first_friday,    nth_weekday(1U, boost::date_time::Friday))
MEETUP_DEFINE(first_saturday,  nth_weekday(1U, boost::date_time::Saturday))
MEETUP_DEFINE(first_sunday,    nth_weekday(1U, boost::date_time::Sunday))

MEETUP_DEFINE(second_monday,    nth_weekday(2U, boost::date_time::Monday))
MEETUP_DEFINE(second_tuesday,   nth_weekday(2U, boost::date_time::Tuesday))
MEETUP_DEFINE(second_wednesday, nth_weekday(2U, boost::date_time::Wednesday))
MEETUP_DEFINE(second_thursday,  nth_weekday(2U, boost::date_time::Thursday))
MEETUP_DEFINE(second_friday,    nth_weekday(2U, boost::date_time::Friday))
MEETUP_DEFINE(second_saturday,  nth_weekday(2U, boost::date_time::Saturday))
MEETUP_DEFINE(second_sunday,    nth_weekday(2U, boost::date_time::Sunday))

MEETUP_DEFINE(third_monday,    nth_weekday(3U, boost::date_time::Monday))
MEETUP_DEFINE(third_tuesday,   nth_weekday(3U, boost::date_time::Tuesday))
MEETUP_DEFINE(third_wednesday, nth_weekday(3U, boost::date_time::Wednesday))
MEETUP_DEFINE(third_thursday,  nth_weekday(3U, boost::date_time::Thursday))
MEETUP_DEFINE(third_friday,    nth_weekday(3U, boost::date_time::Friday))
MEETUP_DEFINE(third_saturday,  nth_weekday(3U, boost::date_time::Saturday))
MEETUP_DEFINE(third_sunday,    nth_weekday(3U, boost::date_time::Sunday))

MEETUP_DEFINE(fourth_monday,    nth_weekday(4U, boost::date_time::Monday))
MEETUP_DEFINE(fourth_tuesday,   nth_weekday(4U, boost::date_time::Tuesday))
MEETUP_DEFINE(fourth_wednesday, nth_weekday(4U, boost::date_time::Wednesday))
MEETUP_DEFINE(fourth_thursday,  nth_weekday(4U, boost::date_time::Thursday))
MEETUP_DEFINE(fourth_friday,    nth_weekday(4U, boost::date_time::Friday))
MEETUP_DEFINE(fourth_saturday,  nth_weekday(4U, boost::date_time::Saturday))
MEETUP_DEFINE(fourth_sunday,    nth_weekday(4U, boost::date_time::Sunday))

MEETUP_DEFINE(last_monday,    last_weekday(boost::date_time::Monday))
MEETUP_DEFINE(last_tuesday,   last_weekday(boost::date_time::Tuesday))
MEETUP_DEFINE(last_wednesday, last_weekday(boost::date_time::Wednesday))
MEETUP_DEFINE(last_thursday,  last_weekday(boost::date_time::Thursday))
MEETUP_DEFINE(last_friday,    last_weekday(boost::date_time::Friday))
MEETUP_DEFINE(last_saturday,  last_weekday(boost::date_time::Saturday))
MEETUP_DEFINE(last_sunday,    last_weekday(boost::date_time::Sunday))

#undef MEETUP_DEFINE

}  // namespace meetup

#if 0   // old implementation disabled

namespace
{
[[nodiscard]] constexpr std::uint8_t to_uint(weekday wd) noexcept
{
    return static_cast<std::uint8_t>(wd);
}
} // unnamed namespace

std::chrono::year_month_day
day(std::int32_t      year,
    std::uint32_t     month,
    weekday           wd,
    schedule          sch)
{
    using std::chrono::day;
    using std::chrono::month;
    using std::chrono::year;
    using std::chrono::year_month_day;
    using std::chrono::year_month_day_last;
    using std::chrono::sys_days;

    if((month < 1U) || (month > 12U))
    {
        throw std::invalid_argument("month must be in 1..12");
    }

    const year  y{year};
    const month m{static_cast<unsigned>(month)};

    if((!y.ok()) || (!m.ok()))
    {
        throw std::invalid_argument("invalid year/month");
    }

    const std::chrono::weekday target_wd{to_uint(wd)};

    const year_month_day_last ymdl{y / m / std::chrono::last};
    const std::uint32_t last_dom{
        static_cast<std::uint32_t>(static_cast<unsigned>(ymdl.day()))};

    auto match_on_day =
        [&](std::uint32_t d) -> bool
        {
            const year_month_day      curr{y / m / day{d}};
            const std::chrono::weekday curr_wd{sys_days{curr}};
            return (curr_wd == target_wd);
        };

    if(sch == schedule::teenth)
    {
        for(std::uint32_t d = 13U; d <= 19U; ++d)
        {
            if(match_on_day(d))
            {
                return y / m / day{d};
            }
        }
    }
    else if(sch == schedule::last)
    {
        for(std::uint32_t d = last_dom; d > 0U; --d)
        {
            if(match_on_day(d))
            {
                return y / m / day{d};
            }
        }
    }
    else
    {
        const std::uint8_t target_occurrence{static_cast<std::uint8_t>(sch)};
        std::uint8_t       occurrence_count{0U};

        for(std::uint32_t d = 1U; d <= last_dom; ++d)
        {
            if(match_on_day(d))
            {
                ++occurrence_count;
                if(occurrence_count == target_occurrence)
                {
                    return y / m / day{d};
                }
            }
        }
    }

    throw std::logic_error("requested meetup day does not exist");
}

}  // namespace meetup
