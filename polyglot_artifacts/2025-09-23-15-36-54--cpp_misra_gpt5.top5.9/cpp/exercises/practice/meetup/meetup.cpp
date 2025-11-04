#include "meetup.h"

namespace {

// Determine if a year is a leap year in the Gregorian calendar.
static constexpr bool is_leap_year(std::int32_t const year) noexcept
{
    // Leap if divisible by 400, or divisible by 4 and not by 100.
    if (((year % static_cast<std::int32_t>(400)) == static_cast<std::int32_t>(0))) {
        return true;
    } else {
        if ((((year % static_cast<std::int32_t>(4)) == static_cast<std::int32_t>(0))) &&
            (((year % static_cast<std::int32_t>(100)) != static_cast<std::int32_t>(0)))) {
            return true;
        } else {
            return false;
        }
    }
}

// Days in month for given year/month (month: 1..12).
static constexpr std::int32_t days_in_month(std::int32_t const year, std::int32_t const month) noexcept
{
    // 31-day months
    if (((month == static_cast<std::int32_t>(1)) ||
         (month == static_cast<std::int32_t>(3)) ||
         (month == static_cast<std::int32_t>(5)) ||
         (month == static_cast<std::int32_t>(7)) ||
         (month == static_cast<std::int32_t>(8)) ||
         (month == static_cast<std::int32_t>(10)) ||
         (month == static_cast<std::int32_t>(12)))) {
        return static_cast<std::int32_t>(31);
    } else {
        // 30-day months
        if (((month == static_cast<std::int32_t>(4)) ||
             (month == static_cast<std::int32_t>(6)) ||
             (month == static_cast<std::int32_t>(9)) ||
             (month == static_cast<std::int32_t>(11)))) {
            return static_cast<std::int32_t>(30);
        } else {
            // February
            if (is_leap_year(year)) {
                return static_cast<std::int32_t>(29);
            } else {
                return static_cast<std::int32_t>(28);
            }
        }
    }
}

// Month offset used by Tomohiko Sakamoto’s algorithm (0-based for January).
static constexpr std::int32_t month_offset(std::int32_t const month) noexcept
{
    // Offsets for Jan..Dec: {0,3,2,5,0,3,5,1,4,6,2,4}
    // Implemented via switch to avoid array indexing conversions.
    switch (month) {
        case 1:  { return static_cast<std::int32_t>(0); }
        case 2:  { return static_cast<std::int32_t>(3); }
        case 3:  { return static_cast<std::int32_t>(2); }
        case 4:  { return static_cast<std::int32_t>(5); }
        case 5:  { return static_cast<std::int32_t>(0); }
        case 6:  { return static_cast<std::int32_t>(3); }
        case 7:  { return static_cast<std::int32_t>(5); }
        case 8:  { return static_cast<std::int32_t>(1); }
        case 9:  { return static_cast<std::int32_t>(4); }
        case 10: { return static_cast<std::int32_t>(6); }
        case 11: { return static_cast<std::int32_t>(2); }
        case 12: { return static_cast<std::int32_t>(4); }
        default: { return static_cast<std::int32_t>(0); } // Undefined month; return 0 to keep noexcept.
    }
}

// Compute day-of-week (0 = Sunday .. 6 = Saturday) for a given Y-M-D.
// Valid for Gregorian dates; behavior for invalid inputs is undefined.
static constexpr std::int32_t weekday_index(std::int32_t const year, std::int32_t const month, std::int32_t const day) noexcept
{
    // Sakamoto’s algorithm variant
    std::int32_t y = year;
    std::int32_t const m = month;
    std::int32_t const d = day;

    // If Jan or Feb, treat as months 13 and 14 of previous year.
    if ((m < static_cast<std::int32_t>(3))) {
        y = (y - static_cast<std::int32_t>(1));
    } else {
        // no adjustment
    }

    std::int32_t const w =
        ( (y + (y / static_cast<std::int32_t>(4)))
        - (y / static_cast<std::int32_t>(100))
        + (y / static_cast<std::int32_t>(400))
        + month_offset(m)
        + d ) % static_cast<std::int32_t>(7);

    // Ensure non-negative modulo result (it already is with this algorithm).
    return w;
}

// Convert enum weekday to index 0..6 with Sunday = 0.
static constexpr std::int32_t weekday_to_index(meetup::weekday const wd) noexcept
{
    return static_cast<std::int32_t>(wd);
}

// Build a Boost gregorian date from year, month, day.
static meetup::date build_date(std::int32_t const year, std::int32_t const month, std::int32_t const day) noexcept
{
    using boost_date = boost::gregorian::date;
    using year_t = boost_date::year_type;
    using month_t = boost_date::month_type;
    using day_t = boost_date::day_type;
    return boost_date(static_cast<year_t>(year), static_cast<month_t>(month), static_cast<day_t>(day));
}

} // anonymous namespace

namespace meetup {

scheduler::scheduler(std::int32_t const year, std::int32_t const month) noexcept
    : year_(year), month_(month)
{
}

std::int32_t meetup_day(std::int32_t const year, std::int32_t const month, weekday const wd, schedule const sch) noexcept
{
    // Determine the requested day-of-month for given inputs.
    std::int32_t const target_wd = weekday_to_index(wd);
    std::int32_t const dim = days_in_month(year, month);

    if (sch == schedule::teenth) {
        // Check the teenth range [13..19].
        for (std::int32_t d = static_cast<std::int32_t>(13); d <= static_cast<std::int32_t>(19); d = (d + static_cast<std::int32_t>(1))) {
            std::int32_t const w = weekday_index(year, month, d);
            if ((w == target_wd)) {
                return d;
            } else {
                // continue
            }
        }
        // Fallback; should never be reached because each weekday has exactly one teenth.
        return static_cast<std::int32_t>(0);
    } else {
        if ((sch == schedule::last)) {
            // Find the last occurrence by walking backward from the last day.
            std::int32_t const last_dow = weekday_index(year, month, dim);
            std::int32_t const back = ( (last_dow - target_wd) + static_cast<std::int32_t>(7) ) % static_cast<std::int32_t>(7);
            std::int32_t const d = (dim - back);
            return d;
        } else {
            // first..fourth
            std::int32_t n = static_cast<std::int32_t>(0);
            if ((sch == schedule::first)) {
                n = static_cast<std::int32_t>(1);
            } else {
                if ((sch == schedule::second)) {
                    n = static_cast<std::int32_t>(2);
                } else {
                    if ((sch == schedule::third)) {
                        n = static_cast<std::int32_t>(3);
                    } else {
                        // schedule::fourth
                        n = static_cast<std::int32_t>(4);
                    }
                }
            }

            std::int32_t const first_dow = weekday_index(year, month, static_cast<std::int32_t>(1));
            std::int32_t const offset = ( (target_wd - first_dow) + static_cast<std::int32_t>(7) ) % static_cast<std::int32_t>(7);
            std::int32_t const first_occurrence = (static_cast<std::int32_t>(1) + offset);
            std::int32_t const d = (first_occurrence + (static_cast<std::int32_t>(7) * (n - static_cast<std::int32_t>(1))));
            // It is guaranteed by the problem constraints that this will be valid within the month.
            return d;
        }
    }
}

std::int32_t scheduler::meetup_day(weekday const wd, schedule const sch) const noexcept
{
    return ::meetup::meetup_day(this->year_, this->month_, wd, sch);
}

std::int32_t scheduler::day(weekday const wd, schedule const sch) const noexcept
{
    return ::meetup::meetup_day(this->year_, this->month_, wd, sch);
}

date meetup::scheduler::monteenth() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::monday, schedule::teenth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::tuesteenth() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::tuesday, schedule::teenth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::wednesteenth() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::wednesday, schedule::teenth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::thursteenth() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::thursday, schedule::teenth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::friteenth() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::friday, schedule::teenth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::saturteenth() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::saturday, schedule::teenth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::sunteenth() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::sunday, schedule::teenth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::first_monday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::monday, schedule::first);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::first_tuesday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::tuesday, schedule::first);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::first_wednesday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::wednesday, schedule::first);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::first_thursday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::thursday, schedule::first);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::first_friday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::friday, schedule::first);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::first_saturday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::saturday, schedule::first);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::first_sunday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::sunday, schedule::first);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::second_monday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::monday, schedule::second);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::second_tuesday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::tuesday, schedule::second);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::second_wednesday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::wednesday, schedule::second);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::second_thursday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::thursday, schedule::second);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::second_friday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::friday, schedule::second);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::second_saturday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::saturday, schedule::second);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::second_sunday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::sunday, schedule::second);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::third_monday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::monday, schedule::third);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::third_tuesday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::tuesday, schedule::third);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::third_wednesday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::wednesday, schedule::third);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::third_thursday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::thursday, schedule::third);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::third_friday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::friday, schedule::third);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::third_saturday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::saturday, schedule::third);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::third_sunday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::sunday, schedule::third);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::fourth_monday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::monday, schedule::fourth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::fourth_tuesday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::tuesday, schedule::fourth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::fourth_wednesday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::wednesday, schedule::fourth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::fourth_thursday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::thursday, schedule::fourth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::fourth_friday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::friday, schedule::fourth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::fourth_saturday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::saturday, schedule::fourth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::fourth_sunday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::sunday, schedule::fourth);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::last_monday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::monday, schedule::last);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::last_tuesday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::tuesday, schedule::last);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::last_wednesday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::wednesday, schedule::last);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::last_thursday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::thursday, schedule::last);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::last_friday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::friday, schedule::last);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::last_saturday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::saturday, schedule::last);
    return build_date(this->year_, this->month_, d);
}

date meetup::scheduler::last_sunday() const noexcept
{
    std::int32_t const d = this->meetup_day(weekday::sunday, schedule::last);
    return build_date(this->year_, this->month_, d);
}

}  // namespace meetup
