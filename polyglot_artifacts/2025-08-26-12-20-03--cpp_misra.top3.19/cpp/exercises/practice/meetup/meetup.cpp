#include "meetup.h"
#include <stdexcept>

namespace meetup {

namespace {
    // Helper: get number of days in a month
    meetup::day_t days_in_month(std::int32_t year, std::uint32_t month)
    {
        static const meetup::day_t days_per_month[12] = {
            31, 28, 31, 30, 31, 30,
            31, 31, 30, 31, 30, 31
        };
        if ((month == 0U) || (month > 12U)) {
            throw std::invalid_argument("Invalid month");
        }
        meetup::day_t days = days_per_month[month - 1U];
        // Leap year check for February
        if ((month == 2U) &&
            (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0)))) {
            days = static_cast<meetup::day_t>(29);
        }
        return days;
    }

    // Helper: get weekday for a given date (0=Sunday, 6=Saturday)
    meetup::Weekday calc_weekday(std::int32_t year, std::uint32_t month, meetup::day_t day)
    {
        // Zeller's congruence, valid for Gregorian calendar
        std::int32_t y = year;
        std::uint32_t m = month;
        if (m < 3U) {
            m = static_cast<std::uint32_t>(m + 12U);
            y = static_cast<std::int32_t>(y - 1);
        }
        std::uint32_t K = static_cast<std::uint32_t>(y % 100);
        std::uint32_t J = static_cast<std::uint32_t>(y / 100);
        std::uint32_t h = static_cast<std::uint32_t>(
            (day + ((13U * (m + 1U)) / 5U) + K + (K / 4U) + (J / 4U) + (5U * J)) % 7U
        );
        // 0=Saturday, 1=Sunday, ..., 6=Friday
        // Convert to 0=Sunday, ..., 6=Saturday
        std::uint32_t d = static_cast<std::uint32_t>((h + 6U) % 7U);
        return static_cast<meetup::Weekday>(d);
    }
}

scheduler::scheduler(std::uint32_t month, std::int32_t year)
    : m_year(year), m_month(month)
{
    if ((month < 1U) || (month > 12U)) {
        throw std::invalid_argument("Invalid month");
    }
}

meetup::day_t scheduler::find_day(Weekday weekday, Schedule schedule) const
{
    meetup::day_t days = days_in_month(m_year, m_month);

    if (schedule == Schedule::Teenth) {
        for (meetup::day_t d = 13U; d <= 19U; ++d) {
            if (calc_weekday(m_year, m_month, d) == weekday) {
                return d;
            }
        }
        throw std::logic_error("No teenth weekday found");
    }

    meetup::day_t first = 1U;
    for (meetup::day_t d = 1U; d <= 7U; ++d) {
        if (calc_weekday(m_year, m_month, d) == weekday) {
            first = d;
            break;
        }
    }

    meetup::day_t day = 0U;
    if (schedule == Schedule::First) {
        day = first;
    } else if (schedule == Schedule::Second) {
        day = static_cast<meetup::day_t>(first + 7U);
    } else if (schedule == Schedule::Third) {
        day = static_cast<meetup::day_t>(first + 14U);
    } else if (schedule == Schedule::Fourth) {
        day = static_cast<meetup::day_t>(first + 21U);
        if (day > days) {
            throw std::logic_error("No fourth weekday in this month");
        }
    } else if (schedule == Schedule::Last) {
        for (meetup::day_t d = days; d >= (days - 6U); --d) {
            if (calc_weekday(m_year, m_month, d) == weekday) {
                day = d;
                break;
            }
        }
    } else {
        throw std::invalid_argument("Unknown schedule");
    }

    if ((day < 1U) || (day > days)) {
        throw std::logic_error("No such weekday in this month");
    }
    return day;
}

// Teenth
meetup::day_t scheduler::monteenth() const { return find_day(Weekday::Monday, Schedule::Teenth); }
meetup::day_t scheduler::tuesteenth() const { return find_day(Weekday::Tuesday, Schedule::Teenth); }
meetup::day_t scheduler::wednesteenth() const { return find_day(Weekday::Wednesday, Schedule::Teenth); }
meetup::day_t scheduler::thursteenth() const { return find_day(Weekday::Thursday, Schedule::Teenth); }
meetup::day_t scheduler::friteenth() const { return find_day(Weekday::Friday, Schedule::Teenth); }
meetup::day_t scheduler::saturteenth() const { return find_day(Weekday::Saturday, Schedule::Teenth); }
meetup::day_t scheduler::sunteenth() const { return find_day(Weekday::Sunday, Schedule::Teenth); }

// First
meetup::day_t scheduler::first_monday() const { return find_day(Weekday::Monday, Schedule::First); }
meetup::day_t scheduler::first_tuesday() const { return find_day(Weekday::Tuesday, Schedule::First); }
meetup::day_t scheduler::first_wednesday() const { return find_day(Weekday::Wednesday, Schedule::First); }
meetup::day_t scheduler::first_thursday() const { return find_day(Weekday::Thursday, Schedule::First); }
meetup::day_t scheduler::first_friday() const { return find_day(Weekday::Friday, Schedule::First); }
meetup::day_t scheduler::first_saturday() const { return find_day(Weekday::Saturday, Schedule::First); }
meetup::day_t scheduler::first_sunday() const { return find_day(Weekday::Sunday, Schedule::First); }

// Second
meetup::day_t scheduler::second_monday() const { return find_day(Weekday::Monday, Schedule::Second); }
meetup::day_t scheduler::second_tuesday() const { return find_day(Weekday::Tuesday, Schedule::Second); }
meetup::day_t scheduler::second_wednesday() const { return find_day(Weekday::Wednesday, Schedule::Second); }
meetup::day_t scheduler::second_thursday() const { return find_day(Weekday::Thursday, Schedule::Second); }
meetup::day_t scheduler::second_friday() const { return find_day(Weekday::Friday, Schedule::Second); }
meetup::day_t scheduler::second_saturday() const { return find_day(Weekday::Saturday, Schedule::Second); }
meetup::day_t scheduler::second_sunday() const { return find_day(Weekday::Sunday, Schedule::Second); }

// Third
meetup::day_t scheduler::third_monday() const { return find_day(Weekday::Monday, Schedule::Third); }
meetup::day_t scheduler::third_tuesday() const { return find_day(Weekday::Tuesday, Schedule::Third); }
meetup::day_t scheduler::third_wednesday() const { return find_day(Weekday::Wednesday, Schedule::Third); }
meetup::day_t scheduler::third_thursday() const { return find_day(Weekday::Thursday, Schedule::Third); }
meetup::day_t scheduler::third_friday() const { return find_day(Weekday::Friday, Schedule::Third); }
meetup::day_t scheduler::third_saturday() const { return find_day(Weekday::Saturday, Schedule::Third); }
meetup::day_t scheduler::third_sunday() const { return find_day(Weekday::Sunday, Schedule::Third); }

// Fourth
meetup::day_t scheduler::fourth_monday() const { return find_day(Weekday::Monday, Schedule::Fourth); }
meetup::day_t scheduler::fourth_tuesday() const { return find_day(Weekday::Tuesday, Schedule::Fourth); }
meetup::day_t scheduler::fourth_wednesday() const { return find_day(Weekday::Wednesday, Schedule::Fourth); }
meetup::day_t scheduler::fourth_thursday() const { return find_day(Weekday::Thursday, Schedule::Fourth); }
meetup::day_t scheduler::fourth_friday() const { return find_day(Weekday::Friday, Schedule::Fourth); }
meetup::day_t scheduler::fourth_saturday() const { return find_day(Weekday::Saturday, Schedule::Fourth); }
meetup::day_t scheduler::fourth_sunday() const { return find_day(Weekday::Sunday, Schedule::Fourth); }

// Last
meetup::day_t scheduler::last_monday() const { return find_day(Weekday::Monday, Schedule::Last); }
meetup::day_t scheduler::last_tuesday() const { return find_day(Weekday::Tuesday, Schedule::Last); }
meetup::day_t scheduler::last_wednesday() const { return find_day(Weekday::Wednesday, Schedule::Last); }
meetup::day_t scheduler::last_thursday() const { return find_day(Weekday::Thursday, Schedule::Last); }
meetup::day_t scheduler::last_friday() const { return find_day(Weekday::Friday, Schedule::Last); }
meetup::day_t scheduler::last_saturday() const { return find_day(Weekday::Saturday, Schedule::Last); }
meetup::day_t scheduler::last_sunday() const { return find_day(Weekday::Sunday, Schedule::Last); }

}  // namespace meetup
