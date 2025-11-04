#include "meetup.h"
#include <stdexcept>

namespace meetup {

namespace {

constexpr day_t days_in_month(year_t year, month_t month)
{
    switch (month) {
        case 1U:  return 31U;
        case 2U:
            if (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0))) {
                return 29U;
            } else {
                return 28U;
            }
        case 3U:  return 31U;
        case 4U:  return 30U;
        case 5U:  return 31U;
        case 6U:  return 30U;
        case 7U:  return 31U;
        case 8U:  return 31U;
        case 9U:  return 30U;
        case 10U: return 31U;
        case 11U: return 30U;
        case 12U: return 31U;
        default:  throw std::invalid_argument("Invalid month");
    }
}

// Returns 0=Sunday, 1=Monday, ..., 6=Saturday
std::uint8_t weekday_of(year_t year, month_t month, day_t day)
{
    year_t y = year;
    month_t m = month;
    if (m < 3U) {
        m = static_cast<month_t>(m + 12U);
        y = static_cast<year_t>(y - 1);
    }
    std::uint8_t h = static_cast<std::uint8_t>(
        (day + (13 * (m + 1U)) / 5U + y + (y / 4) - (y / 100) + (y / 400)) % 7U
    );
    if (h == 0U) {
        return 6U;
    } else {
        return static_cast<std::uint8_t>(h - 1U);
    }
}

} // anonymous namespace

scheduler::scheduler(month_t month, year_t year)
    : m_month(month), m_year(year)
{
}

day_t scheduler::get_day(Weekday weekday, Schedule schedule) const
{
    day_t result = 0U;
    std::uint8_t target_wd = static_cast<std::uint8_t>(weekday);

    if (schedule == Schedule::Teenth) {
        for (day_t d = 13U; d <= 19U; ++d) {
            if (weekday_of(m_year, m_month, d) == target_wd) {
                result = d;
                break;
            }
        }
    } else if (schedule == Schedule::Last) {
        day_t dim = days_in_month(m_year, m_month);
        for (day_t d = dim; d >= 1U; --d) {
            if (weekday_of(m_year, m_month, d) == target_wd) {
                result = d;
                break;
            }
        }
    } else {
        day_t start = 1U;
        day_t end = 7U;
        switch (schedule) {
            case Schedule::First:  start = 1U;  end = 7U;  break;
            case Schedule::Second: start = 8U;  end = 14U; break;
            case Schedule::Third:  start = 15U; end = 21U; break;
            case Schedule::Fourth: start = 22U; end = 28U; break;
            default: break;
        }
        for (day_t d = start; d <= end; ++d) {
            if (weekday_of(m_year, m_month, d) == target_wd) {
                result = d;
                break;
            }
        }
    }
    if (result == 0U) {
        throw std::domain_error("No such meetup day in this month");
    }
    return result;
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
