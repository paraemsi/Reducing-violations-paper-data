#include "meetup.h"

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::days;
using boost::gregorian::months_of_year;
using boost::date_time::weekdays;

/* constructor */
scheduler::scheduler(months_of_year month, std::int32_t year) noexcept
    : m_year(year), m_month(month)
{
}

/* helpers */
date scheduler::nth_weekday(weekdays target, std::uint32_t n) const
{
    const date first_day{static_cast<date::year_type>(m_year), m_month, 1U};

    const std::uint32_t first_wd =
        static_cast<std::uint32_t>(first_day.day_of_week().as_number());
    const std::uint32_t target_wd = static_cast<std::uint32_t>(target);

    const std::uint32_t delta = (target_wd + 7U - first_wd) % 7U;

    const auto span = static_cast<long>((delta + (7U * (n - 1U))));
    date result = first_day + days(span);

    return result;
}

date scheduler::last_weekday(weekdays target) const
{
    const bool is_december = (m_month == months_of_year::Dec);

    const months_of_year next_month =
        static_cast<months_of_year>((static_cast<std::uint32_t>(m_month) % 12U) + 1U);

    const std::int32_t next_year = m_year + (is_december ? 1 : 0);

    const date first_of_next{static_cast<date::year_type>(next_year), next_month, 1U};
    const date last_of_month = first_of_next - days(1);

    const std::uint32_t last_wd =
        static_cast<std::uint32_t>(last_of_month.day_of_week().as_number());
    const std::uint32_t target_wd = static_cast<std::uint32_t>(target);

    const std::uint32_t delta = (last_wd + 7U - target_wd) % 7U;

    date result = last_of_month - days(static_cast<long>(delta));

    return result;
}

date scheduler::teenth_weekday(weekdays target) const
{
    date d{static_cast<date::year_type>(m_year), m_month, 13U};

    for(std::uint32_t i = 0U; i < 7U; ++i)
    {
        if(static_cast<weekdays>(d.day_of_week().as_number()) == target)
        {
            return d;
        }
        d = d + days(1);
    }

    /* logically unreachable */
    return d;
}

/* teenth wrappers */
date scheduler::monteenth() const      { return teenth_weekday(weekdays::Monday); }
date scheduler::tuesteenth() const     { return teenth_weekday(weekdays::Tuesday); }
date scheduler::wednesteenth() const   { return teenth_weekday(weekdays::Wednesday); }
date scheduler::thursteenth() const    { return teenth_weekday(weekdays::Thursday); }
date scheduler::friteenth() const      { return teenth_weekday(weekdays::Friday); }
date scheduler::saturteenth() const    { return teenth_weekday(weekdays::Saturday); }
date scheduler::sunteenth() const      { return teenth_weekday(weekdays::Sunday); }

/* first */
date scheduler::first_monday() const      { return nth_weekday(weekdays::Monday, 1U); }
date scheduler::first_tuesday() const     { return nth_weekday(weekdays::Tuesday, 1U); }
date scheduler::first_wednesday() const   { return nth_weekday(weekdays::Wednesday, 1U); }
date scheduler::first_thursday() const    { return nth_weekday(weekdays::Thursday, 1U); }
date scheduler::first_friday() const      { return nth_weekday(weekdays::Friday, 1U); }
date scheduler::first_saturday() const    { return nth_weekday(weekdays::Saturday, 1U); }
date scheduler::first_sunday() const      { return nth_weekday(weekdays::Sunday, 1U); }

/* second */
date scheduler::second_monday() const     { return nth_weekday(weekdays::Monday, 2U); }
date scheduler::second_tuesday() const    { return nth_weekday(weekdays::Tuesday, 2U); }
date scheduler::second_wednesday() const  { return nth_weekday(weekdays::Wednesday, 2U); }
date scheduler::second_thursday() const   { return nth_weekday(weekdays::Thursday, 2U); }
date scheduler::second_friday() const     { return nth_weekday(weekdays::Friday, 2U); }
date scheduler::second_saturday() const   { return nth_weekday(weekdays::Saturday, 2U); }
date scheduler::second_sunday() const     { return nth_weekday(weekdays::Sunday, 2U); }

/* third */
date scheduler::third_monday() const      { return nth_weekday(weekdays::Monday, 3U); }
date scheduler::third_tuesday() const     { return nth_weekday(weekdays::Tuesday, 3U); }
date scheduler::third_wednesday() const   { return nth_weekday(weekdays::Wednesday, 3U); }
date scheduler::third_thursday() const    { return nth_weekday(weekdays::Thursday, 3U); }
date scheduler::third_friday() const      { return nth_weekday(weekdays::Friday, 3U); }
date scheduler::third_saturday() const    { return nth_weekday(weekdays::Saturday, 3U); }
date scheduler::third_sunday() const      { return nth_weekday(weekdays::Sunday, 3U); }

/* fourth */
date scheduler::fourth_monday() const     { return nth_weekday(weekdays::Monday, 4U); }
date scheduler::fourth_tuesday() const    { return nth_weekday(weekdays::Tuesday, 4U); }
date scheduler::fourth_wednesday() const  { return nth_weekday(weekdays::Wednesday, 4U); }
date scheduler::fourth_thursday() const   { return nth_weekday(weekdays::Thursday, 4U); }
date scheduler::fourth_friday() const     { return nth_weekday(weekdays::Friday, 4U); }
date scheduler::fourth_saturday() const   { return nth_weekday(weekdays::Saturday, 4U); }
date scheduler::fourth_sunday() const     { return nth_weekday(weekdays::Sunday, 4U); }

/* last */
date scheduler::last_monday() const       { return last_weekday(weekdays::Monday); }
date scheduler::last_tuesday() const      { return last_weekday(weekdays::Tuesday); }
date scheduler::last_wednesday() const    { return last_weekday(weekdays::Wednesday); }
date scheduler::last_thursday() const     { return last_weekday(weekdays::Thursday); }
date scheduler::last_friday() const       { return last_weekday(weekdays::Friday); }
date scheduler::last_saturday() const     { return last_weekday(weekdays::Saturday); }
date scheduler::last_sunday() const       { return last_weekday(weekdays::Sunday); }

}  // namespace meetup
