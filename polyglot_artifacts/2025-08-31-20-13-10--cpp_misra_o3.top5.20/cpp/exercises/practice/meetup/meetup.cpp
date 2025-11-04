#include "meetup.h"

#include <cassert>      /* for assert */
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

/* Constructor implementation */
scheduler::scheduler(std::int32_t const year_in,
                     std::uint32_t const month_in) noexcept
    : m_year(year_in),
      m_month(month_in)
{
    /* Ensure the supplied month value is within the valid [1,12] range */
    assert((m_month >= static_cast<std::uint32_t>(1U)) &&
           (m_month <= static_cast<std::uint32_t>(12U)));
}

/* Helper: add a signed number of days to a Boost date */
static auto add_days(boost::gregorian::date const & base_date,
                     std::int32_t const           diff) -> boost::gregorian::date
{
    return base_date + boost::gregorian::days{diff};
}

/* Main public API */
auto scheduler::day(boost::gregorian::greg_weekday const weekday_in,
                    schedule const                     schedule_in) const
    -> boost::gregorian::date
{
    /* First day of the target month */
    auto const first_day =
        boost::gregorian::date{m_year,
                               static_cast<unsigned short>(m_month),
                               static_cast<unsigned short>(1U)};

    auto const first_wd_val =
        static_cast<std::int32_t>(first_day.day_of_week().as_number());
    auto const desired_wd_val =
        static_cast<std::int32_t>(weekday_in.as_number());

    auto const diff_to_first =
        static_cast<std::int32_t>(
            (desired_wd_val + 7 - first_wd_val) % 7);

    auto candidate = add_days(first_day, diff_to_first);

    switch (schedule_in) {
    case schedule::first: {
        return candidate;
    }

    case schedule::second: {
        return add_days(candidate, 7);
    }

    case schedule::third: {
        return add_days(candidate, 14);
    }

    case schedule::fourth: {
        return add_days(candidate, 21);
    }

    case schedule::teenth: {
        auto const thirteenth =
            boost::gregorian::date{m_year,
                                   static_cast<unsigned short>(m_month),
                                   static_cast<unsigned short>(13U)};
        for (std::int32_t i = 0; i < 7; ++i) {
            auto const d = add_days(thirteenth, i);
            if (d.day_of_week() == weekday_in) {
                return d;
            }
        }
        /* Defensive return; should never execute */
        return thirteenth;
    }

    case schedule::last: {
        auto const eom =
            static_cast<unsigned short>(
                boost::gregorian::gregorian_calendar::end_of_month_day(
                    m_year, static_cast<unsigned short>(m_month)));
        auto const last_day =
            boost::gregorian::date{m_year,
                                   static_cast<unsigned short>(m_month),
                                   eom};

        auto const last_wd_val =
            static_cast<std::int32_t>(last_day.day_of_week().as_number());
        auto const back_diff =
            static_cast<std::int32_t>((last_wd_val + 7 - desired_wd_val) % 7);

        return add_days(last_day, -back_diff);
    }

    default: {
        return candidate;
    }
    }
}


/* --------- Teenth helpers ---------------------------------------------- */
boost::gregorian::date scheduler::monteenth() const
{
    return day(boost::gregorian::Monday, schedule::teenth);
}
boost::gregorian::date scheduler::tuesteenth() const
{
    return day(boost::gregorian::Tuesday, schedule::teenth);
}
boost::gregorian::date scheduler::wednesteenth() const
{
    return day(boost::gregorian::Wednesday, schedule::teenth);
}
boost::gregorian::date scheduler::thursteenth() const
{
    return day(boost::gregorian::Thursday, schedule::teenth);
}
boost::gregorian::date scheduler::friteenth() const
{
    return day(boost::gregorian::Friday, schedule::teenth);
}
boost::gregorian::date scheduler::saturteenth() const
{
    return day(boost::gregorian::Saturday, schedule::teenth);
}
boost::gregorian::date scheduler::sunteenth() const
{
    return day(boost::gregorian::Sunday, schedule::teenth);
}

/* --------- First ------------------------------------------------------- */
boost::gregorian::date scheduler::first_monday() const { return day(boost::gregorian::Monday, schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const { return day(boost::gregorian::Tuesday, schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return day(boost::gregorian::Wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const { return day(boost::gregorian::Thursday, schedule::first); }
boost::gregorian::date scheduler::first_friday() const { return day(boost::gregorian::Friday, schedule::first); }
boost::gregorian::date scheduler::first_saturday() const { return day(boost::gregorian::Saturday, schedule::first); }
boost::gregorian::date scheduler::first_sunday() const { return day(boost::gregorian::Sunday, schedule::first); }

/* --------- Second ------------------------------------------------------ */
boost::gregorian::date scheduler::second_monday() const { return day(boost::gregorian::Monday, schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const { return day(boost::gregorian::Tuesday, schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return day(boost::gregorian::Wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const { return day(boost::gregorian::Thursday, schedule::second); }
boost::gregorian::date scheduler::second_friday() const { return day(boost::gregorian::Friday, schedule::second); }
boost::gregorian::date scheduler::second_saturday() const { return day(boost::gregorian::Saturday, schedule::second); }
boost::gregorian::date scheduler::second_sunday() const { return day(boost::gregorian::Sunday, schedule::second); }

/* --------- Third ------------------------------------------------------- */
boost::gregorian::date scheduler::third_monday() const { return day(boost::gregorian::Monday, schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const { return day(boost::gregorian::Tuesday, schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return day(boost::gregorian::Wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const { return day(boost::gregorian::Thursday, schedule::third); }
boost::gregorian::date scheduler::third_friday() const { return day(boost::gregorian::Friday, schedule::third); }
boost::gregorian::date scheduler::third_saturday() const { return day(boost::gregorian::Saturday, schedule::third); }
boost::gregorian::date scheduler::third_sunday() const { return day(boost::gregorian::Sunday, schedule::third); }

/* --------- Fourth ------------------------------------------------------ */
boost::gregorian::date scheduler::fourth_monday() const { return day(boost::gregorian::Monday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return day(boost::gregorian::Tuesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return day(boost::gregorian::Wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return day(boost::gregorian::Thursday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return day(boost::gregorian::Friday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return day(boost::gregorian::Saturday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return day(boost::gregorian::Sunday, schedule::fourth); }

/* --------- Last -------------------------------------------------------- */
boost::gregorian::date scheduler::last_monday() const { return day(boost::gregorian::Monday, schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const { return day(boost::gregorian::Tuesday, schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return day(boost::gregorian::Wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const { return day(boost::gregorian::Thursday, schedule::last); }
boost::gregorian::date scheduler::last_friday() const { return day(boost::gregorian::Friday, schedule::last); }
boost::gregorian::date scheduler::last_saturday() const { return day(boost::gregorian::Saturday, schedule::last); }
boost::gregorian::date scheduler::last_sunday() const { return day(boost::gregorian::Sunday, schedule::last); }

}  // namespace meetup
