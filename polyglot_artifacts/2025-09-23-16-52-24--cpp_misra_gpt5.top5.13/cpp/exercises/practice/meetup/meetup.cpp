#include "meetup.h"

#include <stdexcept>

namespace meetup {

namespace {

inline boost::gregorian::date make_date(const std::int32_t year,
                                        const std::uint32_t month,
                                        const std::uint32_t day)
{
    if ((month < 1U) || (month > 12U)) {
        throw std::out_of_range("Month must be in 1..12");
    }
    if ((day < 1U) || (day > 31U)) {
        throw std::out_of_range("Day must be in 1..31");
    }
    return boost::gregorian::date(
        static_cast<int>(year),
        static_cast<int>(month),
        static_cast<int>(day)
    );
}

inline bool is_weekday_match(const std::int32_t year,
                             const std::uint32_t month,
                             const std::uint32_t day,
                             const boost::date_time::weekdays target)
{
    const boost::gregorian::date d = make_date(year, month, day);
    const boost::gregorian::greg_weekday gw{target};
    return (d.day_of_week() == gw);
}

inline boost::gregorian::date compute_teenth(const std::int32_t year,
                                             const std::uint32_t month,
                                             const boost::date_time::weekdays target)
{
    for (std::uint32_t ui = 13U; (ui <= 19U); ++ui) {
        if (is_weekday_match(year, month, ui, target)) {
            return make_date(year, month, ui);
        }
    }
    throw std::logic_error("No teenth weekday found for the given month/year");
}

inline boost::gregorian::date compute_last(const std::int32_t year,
                                           const std::uint32_t month,
                                           const boost::date_time::weekdays target)
{
    const std::int32_t last_dom_i = boost::gregorian::gregorian_calendar::end_of_month_day(
        static_cast<int>(year),
        static_cast<int>(month)
    );
    if (last_dom_i <= 0) {
        throw std::logic_error("Invalid last day of month");
    }
    std::uint32_t dval = static_cast<std::uint32_t>(last_dom_i);

    for (std::uint32_t step = 0U; (step < 7U); ++step) {
        if (is_weekday_match(year, month, dval, target)) {
            return make_date(year, month, dval);
        }
        if (dval == 0U) {
            break;
        }
        --dval;
    }
    throw std::logic_error("No last weekday found for the given month/year");
}

inline boost::gregorian::date compute_nth(const std::int32_t year,
                                          const std::uint32_t month,
                                          const boost::date_time::weekdays target,
                                          const std::uint32_t ordinal) // 1=first, 2=second, 3=third, 4=fourth
{
    std::uint32_t first_match_day = 0U;
    for (std::uint32_t ui = 1U; (ui <= 7U); ++ui) {
        if (is_weekday_match(year, month, ui, target)) {
            first_match_day = ui;
            break;
        }
    }

    if (first_match_day == 0U) {
        throw std::logic_error("Failed to find first weekday occurrence");
    }

    const std::int32_t last_dom_i = boost::gregorian::gregorian_calendar::end_of_month_day(
        static_cast<int>(year),
        static_cast<int>(month)
    );
    if (last_dom_i <= 0) {
        throw std::logic_error("Invalid last day of month");
    }
    const std::uint32_t last_dom = static_cast<std::uint32_t>(last_dom_i);

    const std::uint32_t offset_weeks = (ordinal - 1U);
    const std::uint32_t nth_dom = (first_match_day + (offset_weeks * 7U));

    if ((nth_dom < 1U) || (nth_dom > last_dom)) {
        throw std::out_of_range("Requested nth weekday is out of range for the month");
    }

    return make_date(year, month, nth_dom);
}

} // namespace

scheduler::scheduler(std::int32_t year, std::uint32_t month) noexcept
    : year_{year}
    , month_{month}
{
}

// Teenth
boost::gregorian::date scheduler::monteenth() const
{
    return compute_teenth(year_, month_, boost::date_time::Monday);
}

boost::gregorian::date scheduler::tuesteenth() const
{
    return compute_teenth(year_, month_, boost::date_time::Tuesday);
}

boost::gregorian::date scheduler::wednesteenth() const
{
    return compute_teenth(year_, month_, boost::date_time::Wednesday);
}

boost::gregorian::date scheduler::thursteenth() const
{
    return compute_teenth(year_, month_, boost::date_time::Thursday);
}

boost::gregorian::date scheduler::friteenth() const
{
    return compute_teenth(year_, month_, boost::date_time::Friday);
}

boost::gregorian::date scheduler::saturteenth() const
{
    return compute_teenth(year_, month_, boost::date_time::Saturday);
}

boost::gregorian::date scheduler::sunteenth() const
{
    return compute_teenth(year_, month_, boost::date_time::Sunday);
}

// First
boost::gregorian::date scheduler::first_monday() const
{
    return compute_nth(year_, month_, boost::date_time::Monday, 1U);
}

boost::gregorian::date scheduler::first_tuesday() const
{
    return compute_nth(year_, month_, boost::date_time::Tuesday, 1U);
}

boost::gregorian::date scheduler::first_wednesday() const
{
    return compute_nth(year_, month_, boost::date_time::Wednesday, 1U);
}

boost::gregorian::date scheduler::first_thursday() const
{
    return compute_nth(year_, month_, boost::date_time::Thursday, 1U);
}

boost::gregorian::date scheduler::first_friday() const
{
    return compute_nth(year_, month_, boost::date_time::Friday, 1U);
}

boost::gregorian::date scheduler::first_saturday() const
{
    return compute_nth(year_, month_, boost::date_time::Saturday, 1U);
}

boost::gregorian::date scheduler::first_sunday() const
{
    return compute_nth(year_, month_, boost::date_time::Sunday, 1U);
}

// Second
boost::gregorian::date scheduler::second_monday() const
{
    return compute_nth(year_, month_, boost::date_time::Monday, 2U);
}

boost::gregorian::date scheduler::second_tuesday() const
{
    return compute_nth(year_, month_, boost::date_time::Tuesday, 2U);
}

boost::gregorian::date scheduler::second_wednesday() const
{
    return compute_nth(year_, month_, boost::date_time::Wednesday, 2U);
}

boost::gregorian::date scheduler::second_thursday() const
{
    return compute_nth(year_, month_, boost::date_time::Thursday, 2U);
}

boost::gregorian::date scheduler::second_friday() const
{
    return compute_nth(year_, month_, boost::date_time::Friday, 2U);
}

boost::gregorian::date scheduler::second_saturday() const
{
    return compute_nth(year_, month_, boost::date_time::Saturday, 2U);
}

boost::gregorian::date scheduler::second_sunday() const
{
    return compute_nth(year_, month_, boost::date_time::Sunday, 2U);
}

// Third
boost::gregorian::date scheduler::third_monday() const
{
    return compute_nth(year_, month_, boost::date_time::Monday, 3U);
}

boost::gregorian::date scheduler::third_tuesday() const
{
    return compute_nth(year_, month_, boost::date_time::Tuesday, 3U);
}

boost::gregorian::date scheduler::third_wednesday() const
{
    return compute_nth(year_, month_, boost::date_time::Wednesday, 3U);
}

boost::gregorian::date scheduler::third_thursday() const
{
    return compute_nth(year_, month_, boost::date_time::Thursday, 3U);
}

boost::gregorian::date scheduler::third_friday() const
{
    return compute_nth(year_, month_, boost::date_time::Friday, 3U);
}

boost::gregorian::date scheduler::third_saturday() const
{
    return compute_nth(year_, month_, boost::date_time::Saturday, 3U);
}

boost::gregorian::date scheduler::third_sunday() const
{
    return compute_nth(year_, month_, boost::date_time::Sunday, 3U);
}

// Fourth
boost::gregorian::date scheduler::fourth_monday() const
{
    return compute_nth(year_, month_, boost::date_time::Monday, 4U);
}

boost::gregorian::date scheduler::fourth_tuesday() const
{
    return compute_nth(year_, month_, boost::date_time::Tuesday, 4U);
}

boost::gregorian::date scheduler::fourth_wednesday() const
{
    return compute_nth(year_, month_, boost::date_time::Wednesday, 4U);
}

boost::gregorian::date scheduler::fourth_thursday() const
{
    return compute_nth(year_, month_, boost::date_time::Thursday, 4U);
}

boost::gregorian::date scheduler::fourth_friday() const
{
    return compute_nth(year_, month_, boost::date_time::Friday, 4U);
}

boost::gregorian::date scheduler::fourth_saturday() const
{
    return compute_nth(year_, month_, boost::date_time::Saturday, 4U);
}

boost::gregorian::date scheduler::fourth_sunday() const
{
    return compute_nth(year_, month_, boost::date_time::Sunday, 4U);
}

// Last
boost::gregorian::date scheduler::last_monday() const
{
    return compute_last(year_, month_, boost::date_time::Monday);
}

boost::gregorian::date scheduler::last_tuesday() const
{
    return compute_last(year_, month_, boost::date_time::Tuesday);
}

boost::gregorian::date scheduler::last_wednesday() const
{
    return compute_last(year_, month_, boost::date_time::Wednesday);
}

boost::gregorian::date scheduler::last_thursday() const
{
    return compute_last(year_, month_, boost::date_time::Thursday);
}

boost::gregorian::date scheduler::last_friday() const
{
    return compute_last(year_, month_, boost::date_time::Friday);
}

boost::gregorian::date scheduler::last_saturday() const
{
    return compute_last(year_, month_, boost::date_time::Saturday);
}

boost::gregorian::date scheduler::last_sunday() const
{
    return compute_last(year_, month_, boost::date_time::Sunday);
}

}  // namespace meetup
