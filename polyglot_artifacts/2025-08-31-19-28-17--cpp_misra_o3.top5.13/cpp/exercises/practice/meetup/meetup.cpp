#include "meetup.h"

#include <array>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {

/* Determine if a year is a leap year in the Gregorian calendar. */
[[nodiscard]] constexpr bool is_leap(std::int32_t const year) noexcept
{
    return ( ( (year % 4) == 0 ) && ( (year % 100) != 0 ) )
        ||  ( (year % 400) == 0 );
}

/* Return number of days in the specified month (1–12). */
[[nodiscard]] constexpr std::uint32_t days_in_month(std::int32_t const year,
                                                    std::int32_t const month) noexcept
{
    constexpr std::array<std::uint32_t, 12U> common_year_days{
        31U, 28U, 31U, 30U, 31U, 30U,
        31U, 31U, 30U, 31U, 30U, 31U
    };

    if((month < 1) || (month > 12)) {
        return 0U;
    }

    if((month == 2) && is_leap(year)) {
        return 29U;
    }

    return common_year_days[static_cast<std::size_t>(month - 1)];
}

/* Zeller’s congruence: 0 = Saturday … 6 = Friday. */
[[nodiscard]] constexpr std::uint8_t zellers_congruence(std::int32_t year,
                                                        std::int32_t month,
                                                        std::uint32_t day) noexcept
{
    if(month < 3) {
        month = static_cast<std::int32_t>(month + 12);
        year  = static_cast<std::int32_t>(year - 1);
    }

    std::int32_t const k { year % 100 };
    std::int32_t const j { year / 100 };

    std::int32_t const h {
        static_cast<std::int32_t>(
            ( static_cast<std::int32_t>(day)
            + ( (13 * (month + 1)) / 5 )
            + k
            + ( k / 4 )
            + ( j / 4 )
            + ( 5 * j ) ) % 7 )
    };

    /* Convert: 0=Sat … 6=Fri  →  0=Sun … 6=Sat */
    return static_cast<std::uint8_t>((h + 6) % 7);
}

/* Convert Zeller result to our weekday enum. */
[[nodiscard]] constexpr weekday to_weekday(std::uint8_t zeller) noexcept
{
    return static_cast<weekday>(zeller);
}

} // namespace

::boost::gregorian::date meetup_day(std::int32_t const year,
                                       std::int32_t const month,
                                       weekday const       day_of_week,
                                       schedule const      sched)
{
    std::uint32_t const dim { days_in_month(year, month) };

    if(dim == 0U) {
        throw std::invalid_argument("month must be in the range 1–12");
    }

    std::uint32_t selected_day { 0U };

    auto const matches_weekday =
        [year, month, day_of_week](std::uint32_t d) noexcept -> bool
    {
        return to_weekday(zellers_congruence(year, month, d)) == day_of_week;
    };

    switch(sched) {
        case schedule::teenth:
        {
            for(std::uint32_t d { 13U }; d <= 19U; ++d) {
                if(matches_weekday(d)) {
                    selected_day = d;
                    break;
                }
            }
            break;
        }

        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth:
        {
            std::uint8_t const target_occurrence {
                static_cast<std::uint8_t>(sched)
            };

            std::uint8_t occurrence { 0U };
            for(std::uint32_t d { 1U }; d <= dim; ++d) {
                if(matches_weekday(d)) {
                    ++occurrence;
                    if(occurrence == target_occurrence) {
                        selected_day = d;
                        break;
                    }
                }
            }
            break;
        }

        case schedule::last:
        {
            for(std::int32_t d { static_cast<std::int32_t>(dim) }; d >= 1; --d) {
                if(matches_weekday(static_cast<std::uint32_t>(d))) {
                    selected_day = static_cast<std::uint32_t>(d);
                    break;
                }
            }
            break;
        }

        default:
            /* Unreachable with current enum values. */
            break;
    }

    if(selected_day == 0U) {
        throw std::runtime_error("requested meetup day not found");
    }

    return ::boost::gregorian::date(
        ::boost::gregorian::greg_year{static_cast<int>(year)},
        ::boost::gregorian::greg_month{static_cast<unsigned short>(month)},
        ::boost::gregorian::greg_day{static_cast<unsigned short>(selected_day)}
    );
}

/* ------------------------------------------------------------------------- */
/*                                scheduler                                  */
/* ------------------------------------------------------------------------- */

scheduler::scheduler(::boost::gregorian::greg_month month, std::int32_t year) noexcept
    : month_{month},
      year_{year}
{
}

::boost::gregorian::date scheduler::nth_weekday(schedule sched, weekday wday) const
{
    return meetup_day(year_, static_cast<std::int32_t>(month_.as_number()), wday, sched);
}

/* "teenth" occurrences */
::boost::gregorian::date scheduler::monteenth() const   { return nth_weekday(schedule::teenth, weekday::Monday); }
::boost::gregorian::date scheduler::tuesteenth() const  { return nth_weekday(schedule::teenth, weekday::Tuesday); }
::boost::gregorian::date scheduler::wednesteenth() const{ return nth_weekday(schedule::teenth, weekday::Wednesday); }
::boost::gregorian::date scheduler::thursteenth() const { return nth_weekday(schedule::teenth, weekday::Thursday); }
::boost::gregorian::date scheduler::friteenth() const   { return nth_weekday(schedule::teenth, weekday::Friday); }
::boost::gregorian::date scheduler::saturteenth() const { return nth_weekday(schedule::teenth, weekday::Saturday); }
::boost::gregorian::date scheduler::sunteenth() const   { return nth_weekday(schedule::teenth, weekday::Sunday); }

/* first occurrences */
::boost::gregorian::date scheduler::first_monday() const    { return nth_weekday(schedule::first, weekday::Monday); }
::boost::gregorian::date scheduler::first_tuesday() const   { return nth_weekday(schedule::first, weekday::Tuesday); }
::boost::gregorian::date scheduler::first_wednesday() const { return nth_weekday(schedule::first, weekday::Wednesday); }
::boost::gregorian::date scheduler::first_thursday() const  { return nth_weekday(schedule::first, weekday::Thursday); }
::boost::gregorian::date scheduler::first_friday() const    { return nth_weekday(schedule::first, weekday::Friday); }
::boost::gregorian::date scheduler::first_saturday() const  { return nth_weekday(schedule::first, weekday::Saturday); }
::boost::gregorian::date scheduler::first_sunday() const    { return nth_weekday(schedule::first, weekday::Sunday); }

/* second occurrences */
::boost::gregorian::date scheduler::second_monday() const    { return nth_weekday(schedule::second, weekday::Monday); }
::boost::gregorian::date scheduler::second_tuesday() const   { return nth_weekday(schedule::second, weekday::Tuesday); }
::boost::gregorian::date scheduler::second_wednesday() const { return nth_weekday(schedule::second, weekday::Wednesday); }
::boost::gregorian::date scheduler::second_thursday() const  { return nth_weekday(schedule::second, weekday::Thursday); }
::boost::gregorian::date scheduler::second_friday() const    { return nth_weekday(schedule::second, weekday::Friday); }
::boost::gregorian::date scheduler::second_saturday() const  { return nth_weekday(schedule::second, weekday::Saturday); }
::boost::gregorian::date scheduler::second_sunday() const    { return nth_weekday(schedule::second, weekday::Sunday); }

/* third occurrences */
::boost::gregorian::date scheduler::third_monday() const    { return nth_weekday(schedule::third, weekday::Monday); }
::boost::gregorian::date scheduler::third_tuesday() const   { return nth_weekday(schedule::third, weekday::Tuesday); }
::boost::gregorian::date scheduler::third_wednesday() const { return nth_weekday(schedule::third, weekday::Wednesday); }
::boost::gregorian::date scheduler::third_thursday() const  { return nth_weekday(schedule::third, weekday::Thursday); }
::boost::gregorian::date scheduler::third_friday() const    { return nth_weekday(schedule::third, weekday::Friday); }
::boost::gregorian::date scheduler::third_saturday() const  { return nth_weekday(schedule::third, weekday::Saturday); }
::boost::gregorian::date scheduler::third_sunday() const    { return nth_weekday(schedule::third, weekday::Sunday); }

/* fourth occurrences */
::boost::gregorian::date scheduler::fourth_monday() const    { return nth_weekday(schedule::fourth, weekday::Monday); }
::boost::gregorian::date scheduler::fourth_tuesday() const   { return nth_weekday(schedule::fourth, weekday::Tuesday); }
::boost::gregorian::date scheduler::fourth_wednesday() const { return nth_weekday(schedule::fourth, weekday::Wednesday); }
::boost::gregorian::date scheduler::fourth_thursday() const  { return nth_weekday(schedule::fourth, weekday::Thursday); }
::boost::gregorian::date scheduler::fourth_friday() const    { return nth_weekday(schedule::fourth, weekday::Friday); }
::boost::gregorian::date scheduler::fourth_saturday() const  { return nth_weekday(schedule::fourth, weekday::Saturday); }
::boost::gregorian::date scheduler::fourth_sunday() const    { return nth_weekday(schedule::fourth, weekday::Sunday); }

/* last occurrences */
::boost::gregorian::date scheduler::last_monday() const    { return nth_weekday(schedule::last, weekday::Monday); }
::boost::gregorian::date scheduler::last_tuesday() const   { return nth_weekday(schedule::last, weekday::Tuesday); }
::boost::gregorian::date scheduler::last_wednesday() const { return nth_weekday(schedule::last, weekday::Wednesday); }
::boost::gregorian::date scheduler::last_thursday() const  { return nth_weekday(schedule::last, weekday::Thursday); }
::boost::gregorian::date scheduler::last_friday() const    { return nth_weekday(schedule::last, weekday::Friday); }
::boost::gregorian::date scheduler::last_saturday() const  { return nth_weekday(schedule::last, weekday::Saturday); }
::boost::gregorian::date scheduler::last_sunday() const    { return nth_weekday(schedule::last, weekday::Sunday); }

}  // namespace meetup
