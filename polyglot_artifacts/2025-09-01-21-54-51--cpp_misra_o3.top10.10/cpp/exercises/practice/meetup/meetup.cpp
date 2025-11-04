#include "meetup.h"

#include <array>
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

/* ------------------------------------------------------------------------- */
/*  Helper: number of days in each month (non-leap year).                     */
/* ------------------------------------------------------------------------- */
static constexpr std::array<std::uint8_t, 12U> days_in_month_common{
    31U, 28U, 31U, 30U, 31U, 30U, 31U, 31U, 30U, 31U, 30U, 31U};

/* ------------------------------------------------------------------------- */
/*  Helper: determine whether the supplied year is a leap year.              */
/* ------------------------------------------------------------------------- */
static constexpr bool is_leap_year(std::int32_t y) noexcept
{
    return ((y % static_cast<std::int32_t>(4)) == static_cast<std::int32_t>(0)) &&
           (((y % static_cast<std::int32_t>(100)) != static_cast<std::int32_t>(0)) ||
            ((y % static_cast<std::int32_t>(400)) == static_cast<std::int32_t>(0)));
}

/* ------------------------------------------------------------------------- */
/*  Helper: days in (year, month).                                           */
/* ------------------------------------------------------------------------- */
static std::uint8_t days_in_month(std::int32_t y, std::uint8_t m)
{
    if((m < static_cast<std::uint8_t>(1U)) || (m > static_cast<std::uint8_t>(12U)))
    {
        throw std::invalid_argument("month out of range");
    }

    std::uint8_t dim = days_in_month_common[static_cast<std::size_t>(m - static_cast<std::uint8_t>(1U))];

    if((m == static_cast<std::uint8_t>(2U)) && is_leap_year(y))
    {
        dim = static_cast<std::uint8_t>(29U);
    }

    return dim;
}

/* ------------------------------------------------------------------------- */
/*  Helper: weekday for a given Gregorian date (Zeller’s congruence).        */
/*         Returns values in the range 0-6, mapping to Weekday::monday…      */
/* ------------------------------------------------------------------------- */
static Weekday day_of_week(std::int32_t y, std::uint8_t m, std::uint8_t d)
{
    std::int32_t yy = y;
    std::int32_t mm = static_cast<std::int32_t>(m);

    if(mm < static_cast<std::int32_t>(3))
    {
        mm += static_cast<std::int32_t>(12);
        --yy;
    }

    const std::int32_t K = yy % static_cast<std::int32_t>(100);
    const std::int32_t J = yy / static_cast<std::int32_t>(100);

    const std::int32_t h = (static_cast<std::int32_t>(d) +
                            ((static_cast<std::int32_t>(13) * (mm + static_cast<std::int32_t>(1))) /
                             static_cast<std::int32_t>(5)) +
                            K +
                            (K / static_cast<std::int32_t>(4)) +
                            (J / static_cast<std::int32_t>(4)) +
                            (static_cast<std::int32_t>(5) * J)) %
                           static_cast<std::int32_t>(7);
    /* Zeller: 0=Saturday, 1=Sunday, … 6=Friday.  Convert so 0=Monday.       */
    /* Convert: Zeller (0 = Saturday, 1 = Sunday, 2 = Monday, …, 6 = Friday)
     * to our Weekday enum (0 = Monday, …, 5 = Saturday, 6 = Sunday).
     * Adding 5 and taking modulo 7 achieves the required rotation.
     */
    const std::int32_t weekday_idx =
        (h + static_cast<std::int32_t>(5)) % static_cast<std::int32_t>(7);

    return static_cast<Weekday>(weekday_idx);
}

/* ------------------------------------------------------------------------- */
/*  Public API – calculate the requested meetup day.                         */
/* ------------------------------------------------------------------------- */
date meetup_day(std::int32_t  year,
                std::uint8_t  month,
                Weekday       weekday,
                Schedule      schedule)
{
    const std::uint8_t dim = days_in_month(year, month);
    std::uint8_t       target_day = static_cast<std::uint8_t>(0U);

    /* ------------------------------ TEENTH -------------------------------- */
    if(schedule == Schedule::teenth)
    {
        for(std::uint8_t d = static_cast<std::uint8_t>(13U);
            d <= static_cast<std::uint8_t>(19U);
            ++d)
        {
            if(day_of_week(year, month, d) == weekday)
            {
                target_day = d;
                break;
            }
        }
    }
    /* ------------------------------- LAST --------------------------------- */
    else if(schedule == Schedule::last)
    {
        for(std::int32_t d = static_cast<std::int32_t>(dim);
            d >= static_cast<std::int32_t>(1);
            --d)
        {
            if(day_of_week(year, month, static_cast<std::uint8_t>(d)) == weekday)
            {
                target_day = static_cast<std::uint8_t>(d);
                break;
            }
        }
    }
    /* ------------------ ORDINAL (first/second/third/fourth) --------------- */
    else
    {
        std::uint8_t first_occurrence_offset = static_cast<std::uint8_t>(0U);

        for(std::uint8_t d = static_cast<std::uint8_t>(1U);
            d <= static_cast<std::uint8_t>(7U);
            ++d)
        {
            if(day_of_week(year, month, d) == weekday)
            {
                first_occurrence_offset =
                    static_cast<std::uint8_t>(d - static_cast<std::uint8_t>(1U));
                break;
            }
        }

        std::uint8_t ordinal = static_cast<std::uint8_t>(0U);
        switch(schedule)
        {
            case Schedule::first:
                ordinal = static_cast<std::uint8_t>(0U);
                break;
            case Schedule::second:
                ordinal = static_cast<std::uint8_t>(1U);
                break;
            case Schedule::third:
                ordinal = static_cast<std::uint8_t>(2U);
                break;
            case Schedule::fourth:
                ordinal = static_cast<std::uint8_t>(3U);
                break;
            default: /* fifth and other invalid ordinals                      */
                throw std::invalid_argument("unsupported schedule");
        }

        target_day = static_cast<std::uint8_t>(
            first_occurrence_offset + static_cast<std::uint8_t>(1U) +
            (ordinal * static_cast<std::uint8_t>(7U)));

        if(target_day > dim)
        {
            throw std::invalid_argument("date does not exist");
        }
    }

    return date{year, month, target_day};
}

/* ------------------------------------------------------------------------- */
/*  scheduler – implementation                                               */
/* ------------------------------------------------------------------------- */
scheduler::scheduler(boost::gregorian::months_of_year month,
                     std::int32_t                       year) noexcept
    : m_year(year),
      m_month(static_cast<std::uint8_t>(
          static_cast<std::uint16_t>(month))) /* Boost enum → uint8_t   */
{
}

/* Internal helper converting meetup_day() to Boost date ------------------- */
boost::gregorian::date
scheduler::make_date(Weekday weekday, Schedule schedule) const
{
    const date d = meetup_day(m_year, m_month, weekday, schedule);

    return boost::gregorian::date(
        static_cast<boost::gregorian::date::year_type>(d.year),
        static_cast<std::uint16_t>(d.month),
        static_cast<std::uint16_t>(d.day));
}

/* ---- teenth ------------------------------------------------------------- */
boost::gregorian::date scheduler::monteenth()   const { return make_date(Weekday::monday,    Schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth()  const { return make_date(Weekday::tuesday,   Schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth()const { return make_date(Weekday::wednesday, Schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return make_date(Weekday::thursday,  Schedule::teenth); }
boost::gregorian::date scheduler::friteenth()   const { return make_date(Weekday::friday,    Schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return make_date(Weekday::saturday,  Schedule::teenth); }
boost::gregorian::date scheduler::sunteenth()   const { return make_date(Weekday::sunday,    Schedule::teenth); }

/* ---- first -------------------------------------------------------------- */
boost::gregorian::date scheduler::first_monday()    const { return make_date(Weekday::monday,    Schedule::first); }
boost::gregorian::date scheduler::first_tuesday()   const { return make_date(Weekday::tuesday,   Schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return make_date(Weekday::wednesday, Schedule::first); }
boost::gregorian::date scheduler::first_thursday()  const { return make_date(Weekday::thursday,  Schedule::first); }
boost::gregorian::date scheduler::first_friday()    const { return make_date(Weekday::friday,    Schedule::first); }
boost::gregorian::date scheduler::first_saturday()  const { return make_date(Weekday::saturday,  Schedule::first); }
boost::gregorian::date scheduler::first_sunday()    const { return make_date(Weekday::sunday,    Schedule::first); }

/* ---- second ------------------------------------------------------------- */
boost::gregorian::date scheduler::second_monday()    const { return make_date(Weekday::monday,    Schedule::second); }
boost::gregorian::date scheduler::second_tuesday()   const { return make_date(Weekday::tuesday,   Schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return make_date(Weekday::wednesday, Schedule::second); }
boost::gregorian::date scheduler::second_thursday()  const { return make_date(Weekday::thursday,  Schedule::second); }
boost::gregorian::date scheduler::second_friday()    const { return make_date(Weekday::friday,    Schedule::second); }
boost::gregorian::date scheduler::second_saturday()  const { return make_date(Weekday::saturday,  Schedule::second); }
boost::gregorian::date scheduler::second_sunday()    const { return make_date(Weekday::sunday,    Schedule::second); }

/* ---- third -------------------------------------------------------------- */
boost::gregorian::date scheduler::third_monday()    const { return make_date(Weekday::monday,    Schedule::third); }
boost::gregorian::date scheduler::third_tuesday()   const { return make_date(Weekday::tuesday,   Schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return make_date(Weekday::wednesday, Schedule::third); }
boost::gregorian::date scheduler::third_thursday()  const { return make_date(Weekday::thursday,  Schedule::third); }
boost::gregorian::date scheduler::third_friday()    const { return make_date(Weekday::friday,    Schedule::third); }
boost::gregorian::date scheduler::third_saturday()  const { return make_date(Weekday::saturday,  Schedule::third); }
boost::gregorian::date scheduler::third_sunday()    const { return make_date(Weekday::sunday,    Schedule::third); }

/* ---- fourth ------------------------------------------------------------- */
boost::gregorian::date scheduler::fourth_monday()    const { return make_date(Weekday::monday,    Schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday()   const { return make_date(Weekday::tuesday,   Schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return make_date(Weekday::wednesday, Schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday()  const { return make_date(Weekday::thursday,  Schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday()    const { return make_date(Weekday::friday,    Schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday()  const { return make_date(Weekday::saturday,  Schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday()    const { return make_date(Weekday::sunday,    Schedule::fourth); }

/* ---- last --------------------------------------------------------------- */
boost::gregorian::date scheduler::last_monday()    const { return make_date(Weekday::monday,    Schedule::last); }
boost::gregorian::date scheduler::last_tuesday()   const { return make_date(Weekday::tuesday,   Schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return make_date(Weekday::wednesday, Schedule::last); }
boost::gregorian::date scheduler::last_thursday()  const { return make_date(Weekday::thursday,  Schedule::last); }
boost::gregorian::date scheduler::last_friday()    const { return make_date(Weekday::friday,    Schedule::last); }
boost::gregorian::date scheduler::last_saturday()  const { return make_date(Weekday::saturday,  Schedule::last); }
boost::gregorian::date scheduler::last_sunday()    const { return make_date(Weekday::sunday,    Schedule::last); }

}  // namespace meetup
