#include "meetup.h"

namespace meetup {

namespace {

// Gregorian leap year
constexpr bool is_leap_year(std::int32_t year) noexcept
{
    // Leap if divisible by 400, or divisible by 4 but not 100
    return (((year % 400) == 0) || (((year % 4) == 0) && ((year % 100) != 0)));
}

constexpr std::int32_t days_in_month(std::int32_t year, std::int32_t month) noexcept
{
    switch (month) {
        case 1:
            return 31;
        case 2:
            return (is_leap_year(year) ? 29 : 28);
        case 3:
            return 31;
        case 4:
            return 30;
        case 5:
            return 31;
        case 6:
            return 30;
        case 7:
            return 31;
        case 8:
            return 31;
        case 9:
            return 30;
        case 10:
            return 31;
        case 11:
            return 30;
        case 12:
            return 31;
        default:
            // Undefined month: return 0 days
            return 0;
    }
}

// 0 = Sunday, 1 = Monday, ..., 6 = Saturday
std::int32_t weekday_index(std::int32_t year, std::int32_t month, std::int32_t day) noexcept
{
    // Sakamoto's algorithm
    static constexpr std::int32_t t[12] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };

    std::int32_t y = year;
    if ((month < 3)) {
        y = y - 1;
    }

    std::int32_t res = (y + (y / 4) - (y / 100) + (y / 400) + t[month - 1] + day);
    std::int32_t wd = (res % 7);
    if (wd < 0) {
        wd = wd + 7;
    }
    return wd;
}

std::int32_t compute_day(std::int32_t year, std::int32_t month, weekday wd, schedule sch) noexcept
{
    const std::int32_t target = static_cast<std::int32_t>(wd);
    const std::int32_t dim = days_in_month(year, month);

    if (dim <= 0) {
        return 0;
    }

    if (sch == schedule::teenth) {
        for (std::int32_t d = 13; d <= 19; d = d + 1) {
            if (weekday_index(year, month, d) == target) {
                return d;
            }
        }
        return 0;
    }

    if (sch == schedule::last) {
        const std::int32_t dow_last = weekday_index(year, month, dim);
        const std::int32_t delta = ((dow_last - target) + 7) % 7;
        const std::int32_t d = dim - delta;
        return d;
    }

    // first..fourth
    const std::int32_t dow_first = weekday_index(year, month, 1);
    const std::int32_t first_occurrence = (1 + (((target - dow_first) + 7) % 7));

    std::int32_t week_index = 0;
    switch (sch) {
        case schedule::first:
            week_index = 0;
            break;
        case schedule::second:
            week_index = 1;
            break;
        case schedule::third:
            week_index = 2;
            break;
        case schedule::fourth:
            week_index = 3;
            break;
        default:
            // Should not reach here for 'last' and 'teenth'
            week_index = 0;
            break;
    }

    const std::int32_t d = first_occurrence + (week_index * 7);
    if (d <= dim) {
        return d;
    } else {
        // Out of range (e.g., "fourth" when only three occurrences in the month)
        return 0;
    }
}

} // namespace

scheduler::scheduler(std::int32_t year, std::int32_t month) noexcept
    : year_(year), month_(month)
{
}

std::int32_t scheduler::day(weekday wd, schedule sch) const noexcept
{
    return compute_day(year_, month_, wd, sch);
}

// teenth
std::int32_t scheduler::monteenth() const noexcept
{
    return this->day(weekday::monday, schedule::teenth);
}

std::int32_t scheduler::tuesteenth() const noexcept
{
    return this->day(weekday::tuesday, schedule::teenth);
}

std::int32_t scheduler::wednesteenth() const noexcept
{
    return this->day(weekday::wednesday, schedule::teenth);
}

std::int32_t scheduler::thursteenth() const noexcept
{
    return this->day(weekday::thursday, schedule::teenth);
}

std::int32_t scheduler::friteenth() const noexcept
{
    return this->day(weekday::friday, schedule::teenth);
}

std::int32_t scheduler::saturteenth() const noexcept
{
    return this->day(weekday::saturday, schedule::teenth);
}

std::int32_t scheduler::sunteenth() const noexcept
{
    return this->day(weekday::sunday, schedule::teenth);
}

// first
std::int32_t scheduler::first_monday() const noexcept
{
    return this->day(weekday::monday, schedule::first);
}

std::int32_t scheduler::first_tuesday() const noexcept
{
    return this->day(weekday::tuesday, schedule::first);
}

std::int32_t scheduler::first_wednesday() const noexcept
{
    return this->day(weekday::wednesday, schedule::first);
}

std::int32_t scheduler::first_thursday() const noexcept
{
    return this->day(weekday::thursday, schedule::first);
}

std::int32_t scheduler::first_friday() const noexcept
{
    return this->day(weekday::friday, schedule::first);
}

std::int32_t scheduler::first_saturday() const noexcept
{
    return this->day(weekday::saturday, schedule::first);
}

std::int32_t scheduler::first_sunday() const noexcept
{
    return this->day(weekday::sunday, schedule::first);
}

// second
std::int32_t scheduler::second_monday() const noexcept
{
    return this->day(weekday::monday, schedule::second);
}

std::int32_t scheduler::second_tuesday() const noexcept
{
    return this->day(weekday::tuesday, schedule::second);
}

std::int32_t scheduler::second_wednesday() const noexcept
{
    return this->day(weekday::wednesday, schedule::second);
}

std::int32_t scheduler::second_thursday() const noexcept
{
    return this->day(weekday::thursday, schedule::second);
}

std::int32_t scheduler::second_friday() const noexcept
{
    return this->day(weekday::friday, schedule::second);
}

std::int32_t scheduler::second_saturday() const noexcept
{
    return this->day(weekday::saturday, schedule::second);
}

std::int32_t scheduler::second_sunday() const noexcept
{
    return this->day(weekday::sunday, schedule::second);
}

// third
std::int32_t scheduler::third_monday() const noexcept
{
    return this->day(weekday::monday, schedule::third);
}

std::int32_t scheduler::third_tuesday() const noexcept
{
    return this->day(weekday::tuesday, schedule::third);
}

std::int32_t scheduler::third_wednesday() const noexcept
{
    return this->day(weekday::wednesday, schedule::third);
}

std::int32_t scheduler::third_thursday() const noexcept
{
    return this->day(weekday::thursday, schedule::third);
}

std::int32_t scheduler::third_friday() const noexcept
{
    return this->day(weekday::friday, schedule::third);
}

std::int32_t scheduler::third_saturday() const noexcept
{
    return this->day(weekday::saturday, schedule::third);
}

std::int32_t scheduler::third_sunday() const noexcept
{
    return this->day(weekday::sunday, schedule::third);
}

// fourth
std::int32_t scheduler::fourth_monday() const noexcept
{
    return this->day(weekday::monday, schedule::fourth);
}

std::int32_t scheduler::fourth_tuesday() const noexcept
{
    return this->day(weekday::tuesday, schedule::fourth);
}

std::int32_t scheduler::fourth_wednesday() const noexcept
{
    return this->day(weekday::wednesday, schedule::fourth);
}

std::int32_t scheduler::fourth_thursday() const noexcept
{
    return this->day(weekday::thursday, schedule::fourth);
}

std::int32_t scheduler::fourth_friday() const noexcept
{
    return this->day(weekday::friday, schedule::fourth);
}

std::int32_t scheduler::fourth_saturday() const noexcept
{
    return this->day(weekday::saturday, schedule::fourth);
}

std::int32_t scheduler::fourth_sunday() const noexcept
{
    return this->day(weekday::sunday, schedule::fourth);
}

// last
std::int32_t scheduler::last_monday() const noexcept
{
    return this->day(weekday::monday, schedule::last);
}

std::int32_t scheduler::last_tuesday() const noexcept
{
    return this->day(weekday::tuesday, schedule::last);
}

std::int32_t scheduler::last_wednesday() const noexcept
{
    return this->day(weekday::wednesday, schedule::last);
}

std::int32_t scheduler::last_thursday() const noexcept
{
    return this->day(weekday::thursday, schedule::last);
}

std::int32_t scheduler::last_friday() const noexcept
{
    return this->day(weekday::friday, schedule::last);
}

std::int32_t scheduler::last_saturday() const noexcept
{
    return this->day(weekday::saturday, schedule::last);
}

std::int32_t scheduler::last_sunday() const noexcept
{
    return this->day(weekday::sunday, schedule::last);
}

std::int32_t day(std::int32_t year, std::int32_t month, weekday wd, schedule sch) noexcept
{
    return compute_day(year, month, wd, sch);
}

}  // namespace meetup
