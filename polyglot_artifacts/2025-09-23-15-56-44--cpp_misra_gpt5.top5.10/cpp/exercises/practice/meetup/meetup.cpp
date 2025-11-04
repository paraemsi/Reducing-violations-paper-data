#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace {

// Gregorian leap year check
inline bool is_leap_year(std::int32_t year) noexcept
{
    // Leap if divisible by 400, or divisible by 4 but not by 100
    return ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0));
}

// Days in month for given year/month (month: 1..12)
inline std::int32_t days_in_month(std::int32_t year, std::int32_t month)
{
    if ((month < 1) || (month > 12)) {
        throw std::out_of_range("month out of range");
    }

    switch (month) {
        case 1:  { return 31; }
        case 2:  { return is_leap_year(year) ? 29 : 28; }
        case 3:  { return 31; }
        case 4:  { return 30; }
        case 5:  { return 31; }
        case 6:  { return 30; }
        case 7:  { return 31; }
        case 8:  { return 31; }
        case 9:  { return 30; }
        case 10: { return 31; }
        case 11: { return 30; }
        case 12: { return 31; }
        default: { throw std::out_of_range("month out of range"); }
    }
}

// Day of week for Gregorian date (0=Sunday, 1=Monday, ..., 6=Saturday)
inline std::int32_t day_of_week(std::int32_t year, std::int32_t month, std::int32_t day)
{
    // Zeller's congruence, adapted to return 0=Sunday..6=Saturday
    std::int32_t y = year;
    std::int32_t m = month;
    if (m <= 2) {
        m += 12;
        y -= 1;
    }

    const std::int32_t K = (y % 100);
    const std::int32_t J = (y / 100);

    const std::int32_t h = (day + ((13 * (m + 1)) / 5) + K + (K / 4) + (J / 4) + (5 * J)) % 7;
    const std::int32_t w = (h + 6) % 7; // convert 0=Sat..6=Fri -> 0=Sun..6=Sat
    return w;
}

} // namespace

namespace meetup {

scheduler::scheduler(std::int32_t year, std::int32_t month) noexcept
    : m_year(year), m_month(month)
{
    // Intentionally not validating here due to noexcept; validation happens in day()
}

std::int32_t scheduler::day(weekday wd, schedule s) const
{
    if ((m_month < 1) || (m_month > 12)) {
        throw std::out_of_range("month out of range");
    }

    const std::int32_t dim = days_in_month(m_year, m_month);

    const std::int32_t first_wday = day_of_week(m_year, m_month, 1);
    const std::int32_t target_wday = static_cast<std::int32_t>(wd);

    const std::int32_t delta = (((target_wday - first_wday) + 7) % 7);
    const std::int32_t first_occurrence = (1 + delta);

    std::int32_t result_day = first_occurrence;

    switch (s) {
        case schedule::first: {
            result_day = first_occurrence;
            break;
        }
        case schedule::second: {
            result_day = (first_occurrence + 7);
            break;
        }
        case schedule::third: {
            result_day = (first_occurrence + 14);
            break;
        }
        case schedule::fourth: {
            result_day = (first_occurrence + 21);
            break;
        }
        case schedule::last: {
            std::int32_t candidate = first_occurrence;
            while (((candidate + 7) <= dim)) {
                candidate += 7;
            }
            result_day = candidate;
            break;
        }
        case schedule::teenth: {
            std::int32_t candidate = first_occurrence;
            while (candidate < 13) {
                candidate += 7;
            }
            // By construction candidate will be within [13,19]
            result_day = candidate;
            break;
        }
        default: {
            throw std::out_of_range("invalid schedule");
        }
    }

    if ((result_day < 1) || (result_day > dim)) {
        throw std::out_of_range("computed day out of range");
    }

    return result_day;
}

boost::gregorian::date scheduler::date_for(weekday wd, schedule s) const
{
    const std::int32_t dom = day(wd, s);
    return boost::gregorian::date(static_cast<int>(m_year), static_cast<int>(m_month), static_cast<int>(dom));
}

// Teenth occurrences
boost::gregorian::date scheduler::monteenth() const { return date_for(weekday::monday, schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth() const { return date_for(weekday::tuesday, schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth() const { return date_for(weekday::wednesday, schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return date_for(weekday::thursday, schedule::teenth); }
boost::gregorian::date scheduler::friteenth() const { return date_for(weekday::friday, schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return date_for(weekday::saturday, schedule::teenth); }
boost::gregorian::date scheduler::sunteenth() const { return date_for(weekday::sunday, schedule::teenth); }

// First occurrences
boost::gregorian::date scheduler::first_monday() const { return date_for(weekday::monday, schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const { return date_for(weekday::tuesday, schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return date_for(weekday::wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const { return date_for(weekday::thursday, schedule::first); }
boost::gregorian::date scheduler::first_friday() const { return date_for(weekday::friday, schedule::first); }
boost::gregorian::date scheduler::first_saturday() const { return date_for(weekday::saturday, schedule::first); }
boost::gregorian::date scheduler::first_sunday() const { return date_for(weekday::sunday, schedule::first); }

// Second occurrences
boost::gregorian::date scheduler::second_monday() const { return date_for(weekday::monday, schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const { return date_for(weekday::tuesday, schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return date_for(weekday::wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const { return date_for(weekday::thursday, schedule::second); }
boost::gregorian::date scheduler::second_friday() const { return date_for(weekday::friday, schedule::second); }
boost::gregorian::date scheduler::second_saturday() const { return date_for(weekday::saturday, schedule::second); }
boost::gregorian::date scheduler::second_sunday() const { return date_for(weekday::sunday, schedule::second); }

// Third occurrences
boost::gregorian::date scheduler::third_monday() const { return date_for(weekday::monday, schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const { return date_for(weekday::tuesday, schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return date_for(weekday::wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const { return date_for(weekday::thursday, schedule::third); }
boost::gregorian::date scheduler::third_friday() const { return date_for(weekday::friday, schedule::third); }
boost::gregorian::date scheduler::third_saturday() const { return date_for(weekday::saturday, schedule::third); }
boost::gregorian::date scheduler::third_sunday() const { return date_for(weekday::sunday, schedule::third); }

// Fourth occurrences
boost::gregorian::date scheduler::fourth_monday() const { return date_for(weekday::monday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return date_for(weekday::tuesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return date_for(weekday::wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return date_for(weekday::thursday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return date_for(weekday::friday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return date_for(weekday::saturday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return date_for(weekday::sunday, schedule::fourth); }

// Last occurrences
boost::gregorian::date scheduler::last_monday() const { return date_for(weekday::monday, schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const { return date_for(weekday::tuesday, schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return date_for(weekday::wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const { return date_for(weekday::thursday, schedule::last); }
boost::gregorian::date scheduler::last_friday() const { return date_for(weekday::friday, schedule::last); }
boost::gregorian::date scheduler::last_saturday() const { return date_for(weekday::saturday, schedule::last); }
boost::gregorian::date scheduler::last_sunday() const { return date_for(weekday::sunday, schedule::last); }

}  // namespace meetup
