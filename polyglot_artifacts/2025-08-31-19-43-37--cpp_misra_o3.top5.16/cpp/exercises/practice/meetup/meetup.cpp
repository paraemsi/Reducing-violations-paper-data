#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

scheduler::scheduler(std::int32_t year, std::uint32_t month)
    : m_year{year}, m_month{month}
{
    if ((month == 0U) || (month > 12U)) {
        throw std::out_of_range("month must be in 1..12");
    }
}

/* static */ bool scheduler::is_leap_year(std::int32_t year) noexcept
{
    return ((year % static_cast<std::int32_t>(400)) == 0) ||
           (((year % static_cast<std::int32_t>(4)) == 0) &&
            ((year % static_cast<std::int32_t>(100)) != 0));
}

/* static */ std::uint32_t scheduler::days_in_month(std::int32_t year,
                                                    std::uint32_t month) noexcept
{
    constexpr std::uint32_t days_per_month[12U] =
        {31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

    std::uint32_t result = days_per_month[month - 1U];
    if ((month == 2U) && (is_leap_year(year)))
    {
        result = result + 1U;
    }
    return result;
}

boost::gregorian::date scheduler::day(boost::date_time::weekdays wanted_weekday,
                                      schedule which) const
{
    constexpr std::int32_t week_length = 7;

    /* Handle the teenth schedule */
    if (which == schedule::teenth)
    {
        for (std::int32_t d = 13; d <= 19; ++d)
        {
            const boost::gregorian::date current{static_cast<int>(m_year),
                                                 static_cast<unsigned int>(m_month),
                                                 static_cast<unsigned int>(d)};
            const boost::date_time::weekdays curr_wd =
                current.day_of_week().as_enum();
            if (curr_wd == wanted_weekday)
            {
                return current;
            }
        }
    }
    else if (which == schedule::last)
    {
        const std::uint32_t dim = days_in_month(m_year, m_month);
        for (std::int32_t d = static_cast<std::int32_t>(dim);
             d >= (static_cast<std::int32_t>(dim) - week_length + 1); --d)
        {
            const boost::gregorian::date current{static_cast<int>(m_year),
                                                 static_cast<unsigned int>(m_month),
                                                 static_cast<unsigned int>(d)};
            const boost::date_time::weekdays curr_wd =
                current.day_of_week().as_enum();
            if (curr_wd == wanted_weekday)
            {
                return current;
            }
        }
    }
    else
    {
        std::int32_t occurrence = 0;
        const std::uint32_t dim = days_in_month(m_year, m_month);

        for (std::int32_t d = 1; d <= static_cast<std::int32_t>(dim); ++d)
        {
            const boost::gregorian::date current{static_cast<int>(m_year),
                                                 static_cast<unsigned int>(m_month),
                                                 static_cast<unsigned int>(d)};
            const boost::date_time::weekdays curr_wd =
                current.day_of_week().as_enum();
            if (curr_wd == wanted_weekday)
            {
                occurrence = occurrence + 1;
                bool match = false;

                switch (which)
                {
                case schedule::first:
                    match = (occurrence == 1);
                    break;
                case schedule::second:
                    match = (occurrence == 2);
                    break;
                case schedule::third:
                    match = (occurrence == 3);
                    break;
                case schedule::fourth:
                    match = (occurrence == 4);
                    break;
                default:
                    break;
                }

                if (match)
                {
                    return current;
                }
            }
        }
    }

    throw std::logic_error("Requested meetup day does not exist");
}

#define MEETUP_GEN(fn, wd, sch) \
boost::gregorian::date scheduler::fn() const \
{ \
    /* boost::date_time::weekdays is an unscoped enum,          */ \
    /* therefore its enumerators (Monday, Tuesday, …) live      */ \
    /* directly in namespace boost::date_time.                  */ \
    return day(boost::date_time::wd, schedule::sch); \
}

/* --- teenth --- */
MEETUP_GEN(monteenth, Monday, teenth)
MEETUP_GEN(tuesteenth, Tuesday, teenth)
MEETUP_GEN(wednesteenth, Wednesday, teenth)
MEETUP_GEN(thursteenth, Thursday, teenth)
MEETUP_GEN(friteenth, Friday, teenth)
MEETUP_GEN(saturteenth, Saturday, teenth)
MEETUP_GEN(sunteenth, Sunday, teenth)

/* --- first --- */
MEETUP_GEN(first_monday, Monday, first)
MEETUP_GEN(first_tuesday, Tuesday, first)
MEETUP_GEN(first_wednesday, Wednesday, first)
MEETUP_GEN(first_thursday, Thursday, first)
MEETUP_GEN(first_friday, Friday, first)
MEETUP_GEN(first_saturday, Saturday, first)
MEETUP_GEN(first_sunday, Sunday, first)

/* --- second --- */
MEETUP_GEN(second_monday, Monday, second)
MEETUP_GEN(second_tuesday, Tuesday, second)
MEETUP_GEN(second_wednesday, Wednesday, second)
MEETUP_GEN(second_thursday, Thursday, second)
MEETUP_GEN(second_friday, Friday, second)
MEETUP_GEN(second_saturday, Saturday, second)
MEETUP_GEN(second_sunday, Sunday, second)

/* --- third --- */
MEETUP_GEN(third_monday, Monday, third)
MEETUP_GEN(third_tuesday, Tuesday, third)
MEETUP_GEN(third_wednesday, Wednesday, third)
MEETUP_GEN(third_thursday, Thursday, third)
MEETUP_GEN(third_friday, Friday, third)
MEETUP_GEN(third_saturday, Saturday, third)
MEETUP_GEN(third_sunday, Sunday, third)

/* --- fourth --- */
MEETUP_GEN(fourth_monday, Monday, fourth)
MEETUP_GEN(fourth_tuesday, Tuesday, fourth)
MEETUP_GEN(fourth_wednesday, Wednesday, fourth)
MEETUP_GEN(fourth_thursday, Thursday, fourth)
MEETUP_GEN(fourth_friday, Friday, fourth)
MEETUP_GEN(fourth_saturday, Saturday, fourth)
MEETUP_GEN(fourth_sunday, Sunday, fourth)

/* --- last --- */
MEETUP_GEN(last_monday, Monday, last)
MEETUP_GEN(last_tuesday, Tuesday, last)
MEETUP_GEN(last_wednesday, Wednesday, last)
MEETUP_GEN(last_thursday, Thursday, last)
MEETUP_GEN(last_friday, Friday, last)
MEETUP_GEN(last_saturday, Saturday, last)
MEETUP_GEN(last_sunday, Sunday, last)

#undef MEETUP_GEN

} // namespace meetup
