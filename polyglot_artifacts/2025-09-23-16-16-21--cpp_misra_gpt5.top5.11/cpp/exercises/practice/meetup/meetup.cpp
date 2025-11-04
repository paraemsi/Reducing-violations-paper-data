#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {

// Return true if year is a leap year in the Gregorian calendar
inline bool is_leap_year(std::uint32_t year) noexcept
{
    // Leap if divisible by 4 and (not divisible by 100 or divisible by 400)
    if (((year % 4U) == 0U) && (((year % 100U) != 0U) || ((year % 400U) == 0U))) {
        return true;
    } else {
        return false;
    }
}

// Days in month for given year/month (month: 1..12)
inline std::uint32_t days_in_month(std::uint32_t year, std::uint32_t month) noexcept
{
    switch (month) {
        case 1U:  { return 31U; }
        case 2U:  { return (is_leap_year(year) ? 29U : 28U); }
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
        default:  { return 0U; } // Undefined month; caller should ensure 1..12
    }
}

inline std::uint32_t weekday_to_index(weekday wd) noexcept
{
    switch (wd) {
        case weekday::Sunday:    { return 0U; }
        case weekday::Monday:    { return 1U; }
        case weekday::Tuesday:   { return 2U; }
        case weekday::Wednesday: { return 3U; }
        case weekday::Thursday:  { return 4U; }
        case weekday::Friday:    { return 5U; }
        case weekday::Saturday:  { return 6U; }
        default:                 { return 0U; }
    }
}

inline weekday index_to_weekday(std::uint32_t idx) noexcept
{
    switch (idx % 7U) {
        case 0U: { return weekday::Sunday; }
        case 1U: { return weekday::Monday; }
        case 2U: { return weekday::Tuesday; }
        case 3U: { return weekday::Wednesday; }
        case 4U: { return weekday::Thursday; }
        case 5U: { return weekday::Friday; }
        default: { return weekday::Saturday; }
    }
}

// Zeller's congruence for Gregorian calendar to compute weekday
// Returns weekday with Sunday as 0
inline weekday compute_weekday(std::uint32_t year, std::uint32_t month, std::uint32_t day) noexcept
{
    std::uint32_t y = year;
    std::uint32_t m = month;
    const std::uint32_t q = day;

    if ((m == 1U) || (m == 2U)) {
        // January and February are counted as months 13 and 14 of the previous year
        m = m + 12U;
        y = y - 1U;
    } else {
        // nothing
    }

    const std::uint32_t K = (y % 100U);
    const std::uint32_t J = (y / 100U);

    const std::uint32_t h = (q + ((13U * (m + 1U)) / 5U) + K + (K / 4U) + (J / 4U) + (5U * J)) % 7U;
    const std::uint32_t dow = (h + 6U) % 7U; // Convert Zeller (0=Sat) to (0=Sun)

    return index_to_weekday(dow);
}

inline boost::gregorian::date make_date(std::uint32_t year, std::uint32_t month, std::uint32_t day) noexcept
{
    return boost::gregorian::date(static_cast<int>(year), static_cast<int>(month), static_cast<int>(day));
}

} // anonymous namespace

scheduler::scheduler(std::uint32_t year, std::uint32_t month) noexcept
    : year_{year}
    , month_{month}
{
    // Intentionally empty
}

std::uint32_t scheduler::day(weekday wd, schedule s) const noexcept
{
    const std::uint32_t dim = days_in_month(year_, month_);
    const std::uint32_t desired = weekday_to_index(wd);

    if (s == schedule::teenth) {
        for (std::uint32_t d = 13U; d <= 19U; d = d + 1U) {
            const weekday w = compute_weekday(year_, month_, d);
            if (weekday_to_index(w) == desired) {
                return d;
            }
        }
        // Fallback (should never happen)
        return 0U;
    } else if ((s == schedule::first) || (s == schedule::second) || (s == schedule::third) || (s == schedule::fourth)) {
        const weekday first_wd = compute_weekday(year_, month_, 1U);
        const std::uint32_t first_idx = weekday_to_index(first_wd);
        const std::uint32_t offset = (desired + (7U - first_idx)) % 7U;
        std::uint32_t week_add = 0U;

        if (s == schedule::first) {
            week_add = 0U;
        } else if (s == schedule::second) {
            week_add = 1U;
        } else if (s == schedule::third) {
            week_add = 2U;
        } else { // fourth
            week_add = 3U;
        }

        const std::uint32_t d = (1U + offset) + (7U * week_add);
        if (d <= dim) {
            return d;
        } else {
            // Should not happen for valid inputs
            return 0U;
        }
    } else { // last
        const weekday last_wd = compute_weekday(year_, month_, dim);
        const std::uint32_t last_idx = weekday_to_index(last_wd);
        const std::uint32_t back = (last_idx + (7U - desired)) % 7U;
        const std::uint32_t d = dim - back;
        return d;
    }
}

boost::gregorian::date scheduler::monteenth() const noexcept
{
    const std::uint32_t d = day(weekday::Monday, schedule::teenth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::tuesteenth() const noexcept
{
    const std::uint32_t d = day(weekday::Tuesday, schedule::teenth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::wednesteenth() const noexcept
{
    const std::uint32_t d = day(weekday::Wednesday, schedule::teenth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::thursteenth() const noexcept
{
    const std::uint32_t d = day(weekday::Thursday, schedule::teenth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::friteenth() const noexcept
{
    const std::uint32_t d = day(weekday::Friday, schedule::teenth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::saturteenth() const noexcept
{
    const std::uint32_t d = day(weekday::Saturday, schedule::teenth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::sunteenth() const noexcept
{
    const std::uint32_t d = day(weekday::Sunday, schedule::teenth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::first_monday() const noexcept
{
    const std::uint32_t d = day(weekday::Monday, schedule::first);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::first_tuesday() const noexcept
{
    const std::uint32_t d = day(weekday::Tuesday, schedule::first);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::first_wednesday() const noexcept
{
    const std::uint32_t d = day(weekday::Wednesday, schedule::first);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::first_thursday() const noexcept
{
    const std::uint32_t d = day(weekday::Thursday, schedule::first);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::first_friday() const noexcept
{
    const std::uint32_t d = day(weekday::Friday, schedule::first);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::first_saturday() const noexcept
{
    const std::uint32_t d = day(weekday::Saturday, schedule::first);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::first_sunday() const noexcept
{
    const std::uint32_t d = day(weekday::Sunday, schedule::first);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::second_monday() const noexcept
{
    const std::uint32_t d = day(weekday::Monday, schedule::second);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::second_tuesday() const noexcept
{
    const std::uint32_t d = day(weekday::Tuesday, schedule::second);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::second_wednesday() const noexcept
{
    const std::uint32_t d = day(weekday::Wednesday, schedule::second);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::second_thursday() const noexcept
{
    const std::uint32_t d = day(weekday::Thursday, schedule::second);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::second_friday() const noexcept
{
    const std::uint32_t d = day(weekday::Friday, schedule::second);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::second_saturday() const noexcept
{
    const std::uint32_t d = day(weekday::Saturday, schedule::second);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::second_sunday() const noexcept
{
    const std::uint32_t d = day(weekday::Sunday, schedule::second);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::third_monday() const noexcept
{
    const std::uint32_t d = day(weekday::Monday, schedule::third);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::third_tuesday() const noexcept
{
    const std::uint32_t d = day(weekday::Tuesday, schedule::third);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::third_wednesday() const noexcept
{
    const std::uint32_t d = day(weekday::Wednesday, schedule::third);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::third_thursday() const noexcept
{
    const std::uint32_t d = day(weekday::Thursday, schedule::third);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::third_friday() const noexcept
{
    const std::uint32_t d = day(weekday::Friday, schedule::third);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::third_saturday() const noexcept
{
    const std::uint32_t d = day(weekday::Saturday, schedule::third);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::third_sunday() const noexcept
{
    const std::uint32_t d = day(weekday::Sunday, schedule::third);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::fourth_monday() const noexcept
{
    const std::uint32_t d = day(weekday::Monday, schedule::fourth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::fourth_tuesday() const noexcept
{
    const std::uint32_t d = day(weekday::Tuesday, schedule::fourth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::fourth_wednesday() const noexcept
{
    const std::uint32_t d = day(weekday::Wednesday, schedule::fourth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::fourth_thursday() const noexcept
{
    const std::uint32_t d = day(weekday::Thursday, schedule::fourth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::fourth_friday() const noexcept
{
    const std::uint32_t d = day(weekday::Friday, schedule::fourth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::fourth_saturday() const noexcept
{
    const std::uint32_t d = day(weekday::Saturday, schedule::fourth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::fourth_sunday() const noexcept
{
    const std::uint32_t d = day(weekday::Sunday, schedule::fourth);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::last_monday() const noexcept
{
    const std::uint32_t d = day(weekday::Monday, schedule::last);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::last_tuesday() const noexcept
{
    const std::uint32_t d = day(weekday::Tuesday, schedule::last);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::last_wednesday() const noexcept
{
    const std::uint32_t d = day(weekday::Wednesday, schedule::last);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::last_thursday() const noexcept
{
    const std::uint32_t d = day(weekday::Thursday, schedule::last);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::last_friday() const noexcept
{
    const std::uint32_t d = day(weekday::Friday, schedule::last);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::last_saturday() const noexcept
{
    const std::uint32_t d = day(weekday::Saturday, schedule::last);
    return make_date(year_, month_, d);
}

boost::gregorian::date scheduler::last_sunday() const noexcept
{
    const std::uint32_t d = day(weekday::Sunday, schedule::last);
    return make_date(year_, month_, d);
}

}  // namespace meetup
