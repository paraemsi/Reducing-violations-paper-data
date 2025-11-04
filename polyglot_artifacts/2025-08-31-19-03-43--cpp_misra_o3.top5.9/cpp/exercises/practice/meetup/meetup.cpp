#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

namespace {

/* Helper that returns a boost::gregorian::date for the requested rule */
[[nodiscard]] boost::gregorian::date
calculate_date(std::int32_t const          year,
               std::uint32_t const         month,
               boost::date_time::weekdays  weekday,
               schedule                    sch) noexcept
{
    using boost::gregorian::date;
    using boost::gregorian::gregorian_calendar;

    /* Number of days in the requested month */
    std::uint32_t const dim =
        static_cast<std::uint32_t>(gregorian_calendar::end_of_month_day(year, month));

    if (sch == schedule::teenth) {
        for (std::uint32_t d = 13U; d <= 19U; ++d) {
            date const candidate{year, month, d};
            if (candidate.day_of_week().as_number() ==
                static_cast<unsigned>(weekday)) {
                return candidate;
            }
        }
    } else if (sch == schedule::last) {
        date const last_of_month{year, month, dim};
        std::uint32_t const last_wd =
            static_cast<std::uint32_t>(last_of_month.day_of_week().as_number());
        std::uint32_t const target_wd =
            static_cast<std::uint32_t>(weekday);

        std::uint32_t const offset =
            (last_wd + 7U - target_wd) % 7U;
        std::uint32_t const day_num = dim - offset;
        return date{year, month, day_num};
    } else { /* first .. fourth */
        std::uint32_t const week_index =
            static_cast<std::uint32_t>(sch); /* first == 0 */

        date const first_of_month{year, month, 1U};
        std::uint32_t const first_wd =
            static_cast<std::uint32_t>(first_of_month.day_of_week().as_number());
        std::uint32_t const target_wd =
            static_cast<std::uint32_t>(weekday);

        std::uint32_t const offset =
            (target_wd + 7U - first_wd) % 7U;
        std::uint32_t const day_num = 1U + offset + (week_index * 7U);
        return date{year, month, day_num};
    }

    /* Valid inputs guarantee a result prior to this point */
    return boost::gregorian::date{}; /* default invalid date */
}

} /* unnamed namespace */

scheduler::scheduler(boost::gregorian::months_of_year month,
                     std::int32_t                     year) noexcept
    : m_year(year),
      m_month(static_cast<std::uint32_t>(month))
{
}

boost::gregorian::date
scheduler::calculate(boost::date_time::weekdays wd,
                     schedule                    sch) const noexcept
{
    return calculate_date(m_year, m_month, wd, sch);
}

/* teenth */
boost::gregorian::date scheduler::monteenth() const noexcept
{
    return calculate(boost::date_time::Monday, schedule::teenth);
}
boost::gregorian::date scheduler::tuesteenth() const noexcept
{
    return calculate(boost::date_time::Tuesday, schedule::teenth);
}
boost::gregorian::date scheduler::wednesteenth() const noexcept
{
    return calculate(boost::date_time::Wednesday, schedule::teenth);
}
boost::gregorian::date scheduler::thursteenth() const noexcept
{
    return calculate(boost::date_time::Thursday, schedule::teenth);
}
boost::gregorian::date scheduler::friteenth() const noexcept
{
    return calculate(boost::date_time::Friday, schedule::teenth);
}
boost::gregorian::date scheduler::saturteenth() const noexcept
{
    return calculate(boost::date_time::Saturday, schedule::teenth);
}
boost::gregorian::date scheduler::sunteenth() const noexcept
{
    return calculate(boost::date_time::Sunday, schedule::teenth);
}

/* first */
boost::gregorian::date scheduler::first_monday() const noexcept
{
    return calculate(boost::date_time::Monday, schedule::first);
}
boost::gregorian::date scheduler::first_tuesday() const noexcept
{
    return calculate(boost::date_time::Tuesday, schedule::first);
}
boost::gregorian::date scheduler::first_wednesday() const noexcept
{
    return calculate(boost::date_time::Wednesday, schedule::first);
}
boost::gregorian::date scheduler::first_thursday() const noexcept
{
    return calculate(boost::date_time::Thursday, schedule::first);
}
boost::gregorian::date scheduler::first_friday() const noexcept
{
    return calculate(boost::date_time::Friday, schedule::first);
}
boost::gregorian::date scheduler::first_saturday() const noexcept
{
    return calculate(boost::date_time::Saturday, schedule::first);
}
boost::gregorian::date scheduler::first_sunday() const noexcept
{
    return calculate(boost::date_time::Sunday, schedule::first);
}

/* second */
boost::gregorian::date scheduler::second_monday() const noexcept
{
    return calculate(boost::date_time::Monday, schedule::second);
}
boost::gregorian::date scheduler::second_tuesday() const noexcept
{
    return calculate(boost::date_time::Tuesday, schedule::second);
}
boost::gregorian::date scheduler::second_wednesday() const noexcept
{
    return calculate(boost::date_time::Wednesday, schedule::second);
}
boost::gregorian::date scheduler::second_thursday() const noexcept
{
    return calculate(boost::date_time::Thursday, schedule::second);
}
boost::gregorian::date scheduler::second_friday() const noexcept
{
    return calculate(boost::date_time::Friday, schedule::second);
}
boost::gregorian::date scheduler::second_saturday() const noexcept
{
    return calculate(boost::date_time::Saturday, schedule::second);
}
boost::gregorian::date scheduler::second_sunday() const noexcept
{
    return calculate(boost::date_time::Sunday, schedule::second);
}

/* third */
boost::gregorian::date scheduler::third_monday() const noexcept
{
    return calculate(boost::date_time::Monday, schedule::third);
}
boost::gregorian::date scheduler::third_tuesday() const noexcept
{
    return calculate(boost::date_time::Tuesday, schedule::third);
}
boost::gregorian::date scheduler::third_wednesday() const noexcept
{
    return calculate(boost::date_time::Wednesday, schedule::third);
}
boost::gregorian::date scheduler::third_thursday() const noexcept
{
    return calculate(boost::date_time::Thursday, schedule::third);
}
boost::gregorian::date scheduler::third_friday() const noexcept
{
    return calculate(boost::date_time::Friday, schedule::third);
}
boost::gregorian::date scheduler::third_saturday() const noexcept
{
    return calculate(boost::date_time::Saturday, schedule::third);
}
boost::gregorian::date scheduler::third_sunday() const noexcept
{
    return calculate(boost::date_time::Sunday, schedule::third);
}

/* fourth */
boost::gregorian::date scheduler::fourth_monday() const noexcept
{
    return calculate(boost::date_time::Monday, schedule::fourth);
}
boost::gregorian::date scheduler::fourth_tuesday() const noexcept
{
    return calculate(boost::date_time::Tuesday, schedule::fourth);
}
boost::gregorian::date scheduler::fourth_wednesday() const noexcept
{
    return calculate(boost::date_time::Wednesday, schedule::fourth);
}
boost::gregorian::date scheduler::fourth_thursday() const noexcept
{
    return calculate(boost::date_time::Thursday, schedule::fourth);
}
boost::gregorian::date scheduler::fourth_friday() const noexcept
{
    return calculate(boost::date_time::Friday, schedule::fourth);
}
boost::gregorian::date scheduler::fourth_saturday() const noexcept
{
    return calculate(boost::date_time::Saturday, schedule::fourth);
}
boost::gregorian::date scheduler::fourth_sunday() const noexcept
{
    return calculate(boost::date_time::Sunday, schedule::fourth);
}

/* last */
boost::gregorian::date scheduler::last_monday() const noexcept
{
    return calculate(boost::date_time::Monday, schedule::last);
}
boost::gregorian::date scheduler::last_tuesday() const noexcept
{
    return calculate(boost::date_time::Tuesday, schedule::last);
}
boost::gregorian::date scheduler::last_wednesday() const noexcept
{
    return calculate(boost::date_time::Wednesday, schedule::last);
}
boost::gregorian::date scheduler::last_thursday() const noexcept
{
    return calculate(boost::date_time::Thursday, schedule::last);
}
boost::gregorian::date scheduler::last_friday() const noexcept
{
    return calculate(boost::date_time::Friday, schedule::last);
}
boost::gregorian::date scheduler::last_saturday() const noexcept
{
    return calculate(boost::date_time::Saturday, schedule::last);
}
boost::gregorian::date scheduler::last_sunday() const noexcept
{
    return calculate(boost::date_time::Sunday, schedule::last);
}

} /* namespace meetup */
