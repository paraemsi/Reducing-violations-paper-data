#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

std::chrono::year_month_day day(const std::chrono::year& year,
                                const std::chrono::month& month,
                                const std::chrono::weekday& weekday,
                                schedule when)
{
    /* first day of the month */
    const std::chrono::year_month_day first_ymd{year, month, std::chrono::day{static_cast<std::uint32_t>(1u)}};
    const std::chrono::sys_days first_sys{first_ymd};
    const std::chrono::weekday first_wd{first_sys};

    /* offset from the first day to the requested weekday (0-6) */
    std::chrono::days offset{weekday - first_wd};
    if (offset < std::chrono::days{0})
    {
        offset += std::chrono::days{7};
    }

    const auto select_week = [&](std::uint32_t week_index) -> std::chrono::year_month_day
    {
        return std::chrono::year_month_day{
            first_sys + offset
            + std::chrono::days{static_cast<std::int64_t>(7) * static_cast<std::int64_t>(week_index)}};
    };

    switch (when)
    {
        case schedule::first:
        {
            return select_week(0u);
        }

        case schedule::second:
        {
            return select_week(1u);
        }

        case schedule::third:
        {
            return select_week(2u);
        }

        case schedule::fourth:
        {
            return select_week(3u);
        }

        case schedule::teenth:
        {
            /* Start at the 13th and move forward until weekday matches */
            const std::chrono::year_month_day thirteenth_ymd{
                year,
                month,
                std::chrono::day{static_cast<std::uint32_t>(13u)}};
            const std::chrono::sys_days thirteenth_sys{thirteenth_ymd};
            std::chrono::days teen_offset{weekday - std::chrono::weekday{thirteenth_sys}};
            if (teen_offset < std::chrono::days{0})
            {
                teen_offset += std::chrono::days{7};
            }
            return std::chrono::year_month_day{thirteenth_sys + teen_offset};
        }

        case schedule::last:
        {
            /* First day of next month */
            const std::chrono::year_month_day first_next_month_ymd{first_ymd + std::chrono::months{1}};
            const std::chrono::sys_days first_next_month_sys{first_next_month_ymd};
            /* Last day of current month */
            const std::chrono::sys_days last_day_sys{first_next_month_sys - std::chrono::days{1}};
            const std::chrono::weekday last_wd{last_day_sys};

            std::chrono::days back_offset{last_wd - weekday};
            if (back_offset < std::chrono::days{0})
            {
                back_offset += std::chrono::days{7};
            }
            return std::chrono::year_month_day{last_day_sys - back_offset};
        }

        default:
        {
            /* Fallback – return first occurrence (should not be reached) */
            return select_week(0u);
        }
    }
}

/* -------------------------------------------------------------------------- */
/* Scheduler implementation                                                   */
/* -------------------------------------------------------------------------- */
scheduler::scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept
    : month_{month},
      year_{year}
{
}

boost::gregorian::date
scheduler::get_day(boost::date_time::weekdays weekday, schedule when) const
{
    using boost::gregorian::date;
    using boost::gregorian::days;
    using boost::gregorian::gregorian_calendar;

    if (when == schedule::teenth)
    {
        date d{static_cast<std::int32_t>(year_), month_, 13};
        while (d.day_of_week().as_number() != static_cast<unsigned short>(weekday))
        {
            d += days{1};
        }
        return d;
    }

    if (when == schedule::last)
    {
        const std::uint16_t last_dom{
            static_cast<std::uint16_t>(gregorian_calendar::end_of_month_day(
                static_cast<std::int32_t>(year_), static_cast<std::uint16_t>(month_)))};
        date d{static_cast<std::int32_t>(year_), month_, last_dom};
        while (d.day_of_week().as_number() != static_cast<unsigned short>(weekday))
        {
            d -= days{1};
        }
        return d;
    }

    std::uint32_t week_index{0u};
    switch (when)
    {
        case schedule::first:
        {
            week_index = 0u;
            break;
        }
        case schedule::second:
        {
            week_index = 1u;
            break;
        }
        case schedule::third:
        {
            week_index = 2u;
            break;
        }
        case schedule::fourth:
        {
            week_index = 3u;
            break;
        }
        default:
        {
            week_index = 0u;
            break;
        }
    }

    const date first_of_month{static_cast<std::int32_t>(year_), month_, 1};
    const std::int32_t first_wd{static_cast<std::int32_t>(first_of_month.day_of_week().as_number())};
    const std::int32_t target_wd{static_cast<std::int32_t>(weekday)};
    const std::int32_t offset{
        (static_cast<std::int32_t>(7) + target_wd - first_wd) % static_cast<std::int32_t>(7)};

    return first_of_month
           + days{offset + static_cast<std::int32_t>(7) * static_cast<std::int32_t>(week_index)};
}

/* teenth */
boost::gregorian::date scheduler::monteenth() const { return get_day(boost::date_time::Monday, schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth() const { return get_day(boost::date_time::Tuesday, schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth() const { return get_day(boost::date_time::Wednesday, schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return get_day(boost::date_time::Thursday, schedule::teenth); }
boost::gregorian::date scheduler::friteenth() const { return get_day(boost::date_time::Friday, schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return get_day(boost::date_time::Saturday, schedule::teenth); }
boost::gregorian::date scheduler::sunteenth() const { return get_day(boost::date_time::Sunday, schedule::teenth); }

/* first */
boost::gregorian::date scheduler::first_monday() const { return get_day(boost::date_time::Monday, schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const { return get_day(boost::date_time::Thursday, schedule::first); }
boost::gregorian::date scheduler::first_friday() const { return get_day(boost::date_time::Friday, schedule::first); }
boost::gregorian::date scheduler::first_saturday() const { return get_day(boost::date_time::Saturday, schedule::first); }
boost::gregorian::date scheduler::first_sunday() const { return get_day(boost::date_time::Sunday, schedule::first); }

/* second */
boost::gregorian::date scheduler::second_monday() const { return get_day(boost::date_time::Monday, schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const { return get_day(boost::date_time::Thursday, schedule::second); }
boost::gregorian::date scheduler::second_friday() const { return get_day(boost::date_time::Friday, schedule::second); }
boost::gregorian::date scheduler::second_saturday() const { return get_day(boost::date_time::Saturday, schedule::second); }
boost::gregorian::date scheduler::second_sunday() const { return get_day(boost::date_time::Sunday, schedule::second); }

/* third */
boost::gregorian::date scheduler::third_monday() const { return get_day(boost::date_time::Monday, schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const { return get_day(boost::date_time::Thursday, schedule::third); }
boost::gregorian::date scheduler::third_friday() const { return get_day(boost::date_time::Friday, schedule::third); }
boost::gregorian::date scheduler::third_saturday() const { return get_day(boost::date_time::Saturday, schedule::third); }
boost::gregorian::date scheduler::third_sunday() const { return get_day(boost::date_time::Sunday, schedule::third); }

/* fourth */
boost::gregorian::date scheduler::fourth_monday() const { return get_day(boost::date_time::Monday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return get_day(boost::date_time::Thursday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return get_day(boost::date_time::Friday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return get_day(boost::date_time::Saturday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return get_day(boost::date_time::Sunday, schedule::fourth); }

/* last */
boost::gregorian::date scheduler::last_monday() const { return get_day(boost::date_time::Monday, schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const { return get_day(boost::date_time::Thursday, schedule::last); }
boost::gregorian::date scheduler::last_friday() const { return get_day(boost::date_time::Friday, schedule::last); }
boost::gregorian::date scheduler::last_saturday() const { return get_day(boost::date_time::Saturday, schedule::last); }
boost::gregorian::date scheduler::last_sunday() const { return get_day(boost::date_time::Sunday, schedule::last); }

}  // namespace meetup
