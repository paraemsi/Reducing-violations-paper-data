#include "meetup.h"

#include <cstdint>
#include <cstddef>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

// Helpers

static constexpr bool is_leap_year(std::int32_t const y) noexcept
{
    // Leap year if divisible by 4 and not by 100, or divisible by 400
    return ((((y % 4) == 0) && ((y % 100) != 0)) || ((y % 400) == 0));
}

static constexpr std::int32_t days_in_month(std::int32_t const y, std::int32_t const m) noexcept
{
    // 1..12 expected for m
    switch (m) {
        case 1:
        {
            return 31;
        }
        case 2:
        {
            return (is_leap_year(y)) ? 29 : 28;
        }
        case 3:
        {
            return 31;
        }
        case 4:
        {
            return 30;
        }
        case 5:
        {
            return 31;
        }
        case 6:
        {
            return 30;
        }
        case 7:
        {
            return 31;
        }
        case 8:
        {
            return 31;
        }
        case 9:
        {
            return 30;
        }
        case 10:
        {
            return 31;
        }
        case 11:
        {
            return 30;
        }
        case 12:
        {
            return 31;
        }
        default:
        {
            return 0; // invalid month
        }
    }
}

static constexpr std::int32_t weekday_index(weekday const wd) noexcept
{
    // Map enum to 0..6 where 0 = Sunday
    switch (wd) {
        case weekday::sunday:
        {
            return 0;
        }
        case weekday::monday:
        {
            return 1;
        }
        case weekday::tuesday:
        {
            return 2;
        }
        case weekday::wednesday:
        {
            return 3;
        }
        case weekday::thursday:
        {
            return 4;
        }
        case weekday::friday:
        {
            return 5;
        }
        case weekday::saturday:
        {
            return 6;
        }
        default:
        {
            return 0;
        }
    }
}

static std::int32_t day_of_week(std::int32_t y, std::int32_t m, std::int32_t d) noexcept
{
    // Sakamoto's algorithm
    // Returns 0..6 where 0 = Sunday
    static constexpr std::int32_t t[12] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    if (m < 3) {
        y = (y - 1);
    } else {
        // no-op
        y = y;
    }
    std::int32_t const dow = (y + (y / 4) - (y / 100) + (y / 400) + t[static_cast<std::size_t>(m - 1)] + d) % 7;
    return (dow + 7) % 7;
}

date meetup_day(std::int32_t const year, std::int32_t const month, weekday const wd, schedule const sch)
{
    // Basic validation
    if (!((month >= 1) && (month <= 12))) {
        return date{year, month, 0};
    }

    std::int32_t const dim = days_in_month(year, month);
    if (!(dim > 0)) {
        return date{year, month, 0};
    }

    std::int32_t const target_wd = weekday_index(wd);

    if (sch == schedule::teenth) {
        for (std::int32_t d = 13; (d <= 19); d = (d + 1)) {
            if (day_of_week(year, month, d) == target_wd) {
                return date{year, month, d};
            } else {
                // continue
            }
        }
        return date{year, month, 0};
    } else if ((sch == schedule::first) || (sch == schedule::second) || (sch == schedule::third) || (sch == schedule::fourth)) {
        std::int32_t const first_wd = day_of_week(year, month, 1);
        std::int32_t const offset = (((target_wd + 7) - first_wd) % 7);

        std::int32_t n = 0;
        if (sch == schedule::first) {
            n = 0;
        } else if (sch == schedule::second) {
            n = 1;
        } else if (sch == schedule::third) {
            n = 2;
        } else {
            n = 3;
        }

        std::int32_t const day = 1 + offset + (n * 7);
        if ((day >= 1) && (day <= dim)) {
            return date{year, month, day};
        } else {
            return date{year, month, 0};
        }
    } else if (sch == schedule::last) {
        std::int32_t const last_day = dim;
        std::int32_t const last_wd = day_of_week(year, month, last_day);
        std::int32_t const delta = (((last_wd + 7) - target_wd) % 7);
        std::int32_t const day = last_day - delta;
        if ((day >= 1) && (day <= dim)) {
            return date{year, month, day};
        } else {
            return date{year, month, 0};
        }
    } else {
        // Unknown schedule
        return date{year, month, 0};
    }
}

scheduler::scheduler(boost::gregorian::months_of_year const month, std::int32_t const year) noexcept
    : month_(month), year_(year)
{
}

boost::gregorian::date scheduler::nth_weekday(std::uint8_t const n, boost::date_time::weekdays const wd) const
{
    using boost::gregorian::nth_day_of_the_week_in_month;
    nth_day_of_the_week_in_month::week_num wn = nth_day_of_the_week_in_month::first;
    if (n == static_cast<std::uint8_t>(1U)) {
        wn = nth_day_of_the_week_in_month::first;
    } else if (n == static_cast<std::uint8_t>(2U)) {
        wn = nth_day_of_the_week_in_month::second;
    } else if (n == static_cast<std::uint8_t>(3U)) {
        wn = nth_day_of_the_week_in_month::third;
    } else {
        wn = nth_day_of_the_week_in_month::fourth;
    }
    nth_day_of_the_week_in_month const gen(wn, wd, month_);
    return gen.get_date(static_cast<int>(year_));
}

boost::gregorian::date scheduler::last_weekday(boost::date_time::weekdays const wd) const
{
    boost::gregorian::last_day_of_the_week_in_month const gen(wd, month_);
    return gen.get_date(static_cast<int>(year_));
}

boost::gregorian::date scheduler::teenth_weekday(boost::date_time::weekdays const wd) const
{
    for (std::int32_t d = 13; (d <= 19); d = (d + 1)) {
        boost::gregorian::date const dt(static_cast<int>(year_), month_, static_cast<int>(d));
        if (dt.day_of_week() == wd) {
            return dt;
        } else {
            // continue
        }
    }
    // Should never reach here for valid inputs
    return boost::gregorian::date(); // not_a_date_time
}

// teenth
boost::gregorian::date scheduler::monteenth() const { return teenth_weekday(boost::date_time::Monday); }
boost::gregorian::date scheduler::tuesteenth() const { return teenth_weekday(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return teenth_weekday(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return teenth_weekday(boost::date_time::Thursday); }
boost::gregorian::date scheduler::friteenth() const { return teenth_weekday(boost::date_time::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return teenth_weekday(boost::date_time::Saturday); }
boost::gregorian::date scheduler::sunteenth() const { return teenth_weekday(boost::date_time::Sunday); }

// first
boost::gregorian::date scheduler::first_monday() const { return nth_weekday(static_cast<std::uint8_t>(1U), boost::date_time::Monday); }
boost::gregorian::date scheduler::first_tuesday() const { return nth_weekday(static_cast<std::uint8_t>(1U), boost::date_time::Tuesday); }
boost::gregorian::date scheduler::first_wednesday() const { return nth_weekday(static_cast<std::uint8_t>(1U), boost::date_time::Wednesday); }
boost::gregorian::date scheduler::first_thursday() const { return nth_weekday(static_cast<std::uint8_t>(1U), boost::date_time::Thursday); }
boost::gregorian::date scheduler::first_friday() const { return nth_weekday(static_cast<std::uint8_t>(1U), boost::date_time::Friday); }
boost::gregorian::date scheduler::first_saturday() const { return nth_weekday(static_cast<std::uint8_t>(1U), boost::date_time::Saturday); }
boost::gregorian::date scheduler::first_sunday() const { return nth_weekday(static_cast<std::uint8_t>(1U), boost::date_time::Sunday); }

// second
boost::gregorian::date scheduler::second_monday() const { return nth_weekday(static_cast<std::uint8_t>(2U), boost::date_time::Monday); }
boost::gregorian::date scheduler::second_tuesday() const { return nth_weekday(static_cast<std::uint8_t>(2U), boost::date_time::Tuesday); }
boost::gregorian::date scheduler::second_wednesday() const { return nth_weekday(static_cast<std::uint8_t>(2U), boost::date_time::Wednesday); }
boost::gregorian::date scheduler::second_thursday() const { return nth_weekday(static_cast<std::uint8_t>(2U), boost::date_time::Thursday); }
boost::gregorian::date scheduler::second_friday() const { return nth_weekday(static_cast<std::uint8_t>(2U), boost::date_time::Friday); }
boost::gregorian::date scheduler::second_saturday() const { return nth_weekday(static_cast<std::uint8_t>(2U), boost::date_time::Saturday); }
boost::gregorian::date scheduler::second_sunday() const { return nth_weekday(static_cast<std::uint8_t>(2U), boost::date_time::Sunday); }

// third
boost::gregorian::date scheduler::third_monday() const { return nth_weekday(static_cast<std::uint8_t>(3U), boost::date_time::Monday); }
boost::gregorian::date scheduler::third_tuesday() const { return nth_weekday(static_cast<std::uint8_t>(3U), boost::date_time::Tuesday); }
boost::gregorian::date scheduler::third_wednesday() const { return nth_weekday(static_cast<std::uint8_t>(3U), boost::date_time::Wednesday); }
boost::gregorian::date scheduler::third_thursday() const { return nth_weekday(static_cast<std::uint8_t>(3U), boost::date_time::Thursday); }
boost::gregorian::date scheduler::third_friday() const { return nth_weekday(static_cast<std::uint8_t>(3U), boost::date_time::Friday); }
boost::gregorian::date scheduler::third_saturday() const { return nth_weekday(static_cast<std::uint8_t>(3U), boost::date_time::Saturday); }
boost::gregorian::date scheduler::third_sunday() const { return nth_weekday(static_cast<std::uint8_t>(3U), boost::date_time::Sunday); }

// fourth
boost::gregorian::date scheduler::fourth_monday() const { return nth_weekday(static_cast<std::uint8_t>(4U), boost::date_time::Monday); }
boost::gregorian::date scheduler::fourth_tuesday() const { return nth_weekday(static_cast<std::uint8_t>(4U), boost::date_time::Tuesday); }
boost::gregorian::date scheduler::fourth_wednesday() const { return nth_weekday(static_cast<std::uint8_t>(4U), boost::date_time::Wednesday); }
boost::gregorian::date scheduler::fourth_thursday() const { return nth_weekday(static_cast<std::uint8_t>(4U), boost::date_time::Thursday); }
boost::gregorian::date scheduler::fourth_friday() const { return nth_weekday(static_cast<std::uint8_t>(4U), boost::date_time::Friday); }
boost::gregorian::date scheduler::fourth_saturday() const { return nth_weekday(static_cast<std::uint8_t>(4U), boost::date_time::Saturday); }
boost::gregorian::date scheduler::fourth_sunday() const { return nth_weekday(static_cast<std::uint8_t>(4U), boost::date_time::Sunday); }

// last
boost::gregorian::date scheduler::last_monday() const { return last_weekday(boost::date_time::Monday); }
boost::gregorian::date scheduler::last_tuesday() const { return last_weekday(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return last_weekday(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::last_thursday() const { return last_weekday(boost::date_time::Thursday); }
boost::gregorian::date scheduler::last_friday() const { return last_weekday(boost::date_time::Friday); }
boost::gregorian::date scheduler::last_saturday() const { return last_weekday(boost::date_time::Saturday); }
boost::gregorian::date scheduler::last_sunday() const { return last_weekday(boost::date_time::Sunday); }

}  // namespace meetup
