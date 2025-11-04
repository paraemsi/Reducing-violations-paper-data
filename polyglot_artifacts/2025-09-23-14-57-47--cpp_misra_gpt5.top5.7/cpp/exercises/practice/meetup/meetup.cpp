#include "meetup.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace {

// Type aliases for clarity
using i32 = std::int32_t;
using u32 = std::uint32_t;
using u8 = std::uint8_t;

// Gregorian leap-year check
constexpr bool is_leap_year(i32 year) noexcept
{
    return ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0));
}

// Days in month for given year/month (month: 1..12)
u32 days_in_month(i32 year, u32 month)
{
    switch (month) {
        case 1U:  { return 31U; }
        case 2U:  { return (is_leap_year(year)) ? 29U : 28U; }
        case 3U:  { return 31U; }
        case 4U:  { return 30U; }
        case 5U:  { return 31U; }
        case 6U:  { return 30U; }
        case 7U:  { return 31U; }
        case 8U:  { return 31U; }
        case 9U:  { return 30U; }
        case 10U: { return 31U; }
        case 11U: { return 30U; }
        case 12U: { return 31U; }
        default:  { throw std::invalid_argument("month must be in 1..12"); }
    }
}

// Day of week with Monday = 0, ..., Sunday = 6
i32 day_of_week_monday0(i32 year, u32 month, u32 day)
{
    // Sakamoto's algorithm (Gregorian calendar)
    // Base yields: 0 = Sunday, 1 = Monday, ..., 6 = Saturday
    static const std::array<i32, 12U> month_table = { { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 } };

    i32 y = year;
    if (month < 3U) {
        y = (y - 1);
    }

    const std::size_t idx = static_cast<std::size_t>((month - 1U));
    i32 w = (y + (y / 4) - (y / 100) + (y / 400) + month_table[idx] + static_cast<i32>(day));
    w = (w % 7);

    // Convert to Monday=0 .. Sunday=6
    const i32 monday0 = ((w + 6) % 7);
    return monday0;
}

i32 weekday_to_index(meetup::weekday wd) noexcept
{
    return static_cast<i32>(static_cast<u8>(wd));
}

u32 compute_meetup_day(i32 year, u32 month, meetup::weekday wd, meetup::schedule sc)
{
    if ((month < 1U) || (month > 12U)) {
        throw std::invalid_argument("month must be in 1..12");
    }

    const i32 target = weekday_to_index(wd);

    if (sc == meetup::schedule::teenth) {
        for (u32 d = 13U; d <= 19U; d = (d + 1U)) {
            const i32 dow = day_of_week_monday0(year, month, d);
            if (dow == target) {
                return d;
            }
        }
        // Should be unreachable: exactly one teenth weekday exists
        throw std::runtime_error("no teenth match found");
    }

    if (sc == meetup::schedule::last) {
        const u32 last_dom = days_in_month(year, month);
        const i32 dow_last = day_of_week_monday0(year, month, last_dom);
        const i32 diff = (dow_last - target);
        i32 mod = (diff % 7);
        if (mod < 0) {
            mod = (mod + 7);
        }
        const u32 result = (last_dom - static_cast<u32>(mod));
        return result;
    }

    // first/second/third/fourth
    u32 k = 0U;
    switch (sc) {
        case meetup::schedule::first:  { k = 0U; break; }
        case meetup::schedule::second: { k = 1U; break; }
        case meetup::schedule::third:  { k = 2U; break; }
        case meetup::schedule::fourth: { k = 3U; break; }
        default:                       { throw std::invalid_argument("invalid schedule"); }
    }

    const i32 dow_first = day_of_week_monday0(year, month, 1U);
    const i32 diff0 = (target - dow_first);
    i32 mod0 = (diff0 % 7);
    if (mod0 < 0) {
        mod0 = (mod0 + 7);
    }
    const i32 first_occurrence = (1 + mod0);
    const i32 result_dom = (first_occurrence + static_cast<i32>(7U * k));
    return static_cast<u32>(result_dom);
}

// Construct a boost::gregorian::date safely from fixed-width integers
boost::gregorian::date make_date(i32 year, u32 month, u32 day)
{
    using date_type = boost::gregorian::date;
    return date_type(
        static_cast<date_type::year_type>(year),
        static_cast<date_type::month_type>(month),
        static_cast<date_type::day_type>(day)
    );
}

} // unnamed namespace

namespace meetup {

scheduler::scheduler(std::int32_t year, std::uint32_t month) noexcept
    : year_{year}, month_{month}
{
}

std::uint32_t scheduler::day(weekday wd, schedule sc) const
{
    return compute_meetup_day(year_, month_, wd, sc);
}

boost::gregorian::date scheduler::monteenth() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::monday, schedule::teenth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::tuesteenth() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::tuesday, schedule::teenth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::wednesteenth() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::wednesday, schedule::teenth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::thursteenth() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::thursday, schedule::teenth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::friteenth() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::friday, schedule::teenth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::saturteenth() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::saturday, schedule::teenth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::sunteenth() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::sunday, schedule::teenth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::first_monday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::monday, schedule::first);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::first_tuesday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::tuesday, schedule::first);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::first_wednesday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::wednesday, schedule::first);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::first_thursday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::thursday, schedule::first);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::first_friday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::friday, schedule::first);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::first_saturday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::saturday, schedule::first);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::first_sunday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::sunday, schedule::first);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::second_monday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::monday, schedule::second);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::second_tuesday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::tuesday, schedule::second);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::second_wednesday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::wednesday, schedule::second);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::second_thursday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::thursday, schedule::second);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::second_friday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::friday, schedule::second);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::second_saturday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::saturday, schedule::second);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::second_sunday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::sunday, schedule::second);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::third_monday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::monday, schedule::third);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::third_tuesday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::tuesday, schedule::third);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::third_wednesday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::wednesday, schedule::third);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::third_thursday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::thursday, schedule::third);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::third_friday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::friday, schedule::third);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::third_saturday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::saturday, schedule::third);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::third_sunday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::sunday, schedule::third);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::fourth_monday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::monday, schedule::fourth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::fourth_tuesday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::tuesday, schedule::fourth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::fourth_wednesday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::wednesday, schedule::fourth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::fourth_thursday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::thursday, schedule::fourth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::fourth_friday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::friday, schedule::fourth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::fourth_saturday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::saturday, schedule::fourth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::fourth_sunday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::sunday, schedule::fourth);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::last_monday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::monday, schedule::last);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::last_tuesday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::tuesday, schedule::last);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::last_wednesday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::wednesday, schedule::last);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::last_thursday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::thursday, schedule::last);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::last_friday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::friday, schedule::last);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::last_saturday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::saturday, schedule::last);
    return make_date(year_, month_, dom);
}

boost::gregorian::date scheduler::last_sunday() const
{
    const std::uint32_t dom = compute_meetup_day(year_, month_, weekday::sunday, schedule::last);
    return make_date(year_, month_, dom);
}

std::uint32_t day(std::int32_t year, std::uint32_t month, weekday wd, schedule sc)
{
    return compute_meetup_day(year, month, wd, sc);
}

}  // namespace meetup
