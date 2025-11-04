#include <array>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>
#include <stdexcept>
#include "meetup.h"

namespace meetup {

/* constructor ------------------------------------------------------------ */
scheduler::scheduler(std::int32_t year, std::int32_t month)
    : m_year{year},
      m_month{month}
{
    if((month < static_cast<std::int32_t>(1)) || (month > static_cast<std::int32_t>(12))) {
        throw std::out_of_range("month must be in range 1..12");
    }
}

/* helpers ---------------------------------------------------------------- */
std::int32_t scheduler::days_in_month(std::int32_t year, std::int32_t month)
{
    static constexpr std::array<std::int32_t, 12U> month_lengths{
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    if(month == static_cast<std::int32_t>(2)) {
        bool leap{false};
        if((year % static_cast<std::int32_t>(4)) == static_cast<std::int32_t>(0)) {
            leap = ((year % static_cast<std::int32_t>(100)) != static_cast<std::int32_t>(0)) ||
                   ((year % static_cast<std::int32_t>(400)) == static_cast<std::int32_t>(0));
        }
        return leap ? static_cast<std::int32_t>(29) : month_lengths[1];
    }

    return month_lengths[static_cast<std::size_t>(month - static_cast<std::int32_t>(1))];
}

weekday scheduler::get_weekday(std::int32_t year, std::int32_t month, std::int32_t day)
{
    std::int32_t y{year};
    std::int32_t m{month};

    if(m <= static_cast<std::int32_t>(2)) {
        m += static_cast<std::int32_t>(12);
        --y;
    }

    const std::int32_t K{y % static_cast<std::int32_t>(100)};
    const std::int32_t J{y / static_cast<std::int32_t>(100)};

    const std::int32_t h{(day +
                          ((static_cast<std::int32_t>(13) * (m + static_cast<std::int32_t>(1))) /
                           static_cast<std::int32_t>(5)) +
                          K +
                          (K / static_cast<std::int32_t>(4)) +
                          (J / static_cast<std::int32_t>(4)) +
                          (static_cast<std::int32_t>(5) * J)) %
                         static_cast<std::int32_t>(7)};

    const std::int32_t d{(h + static_cast<std::int32_t>(6)) % static_cast<std::int32_t>(7)}; /* 0 = Sunday */

    return static_cast<weekday>(d);
}

boost::gregorian::date scheduler::find_day(weekday wd, schedule sch) const
{
    std::int32_t day{0};

    switch(sch) {
        case schedule::teenth:
            for(std::int32_t d{13}; d <= static_cast<std::int32_t>(19); ++d) {
                if(get_weekday(m_year, m_month, d) == wd) {
                    day = d;
                    break;
                }
            }
            break;

        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth: {
            const std::int32_t ordinal{static_cast<std::int32_t>(sch)};
            std::int32_t count{0};
            const std::int32_t dim{days_in_month(m_year, m_month)};
            for(std::int32_t d{1}; d <= dim; ++d) {
                if(get_weekday(m_year, m_month, d) == wd) {
                    ++count;
                    if(count == ordinal) {
                        day = d;
                        break;
                    }
                }
            }
            break;
        }

        case schedule::last: {
            for(std::int32_t d{days_in_month(m_year, m_month)};
                d >= static_cast<std::int32_t>(1);
                --d) {
                if(get_weekday(m_year, m_month, d) == wd) {
                    day = d;
                    break;
                }
            }
            break;
        }

        default:
            break;
    }

    if(day == static_cast<std::int32_t>(0)) {
        throw std::runtime_error("Requested date does not exist");
    }

    return boost::gregorian::date{m_year, m_month, day};
}

/* teenth ----------------------------------------------------------------- */
boost::gregorian::date scheduler::monteenth() const      { return find_day(weekday::monday,    schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth() const     { return find_day(weekday::tuesday,   schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth() const   { return find_day(weekday::wednesday, schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const    { return find_day(weekday::thursday,  schedule::teenth); }
boost::gregorian::date scheduler::friteenth() const      { return find_day(weekday::friday,    schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const    { return find_day(weekday::saturday,  schedule::teenth); }
boost::gregorian::date scheduler::sunteenth() const      { return find_day(weekday::sunday,    schedule::teenth); }

/* first ------------------------------------------------------------------ */
boost::gregorian::date scheduler::first_monday() const    { return find_day(weekday::monday,    schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const   { return find_day(weekday::tuesday,   schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return find_day(weekday::wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const  { return find_day(weekday::thursday,  schedule::first); }
boost::gregorian::date scheduler::first_friday() const    { return find_day(weekday::friday,    schedule::first); }
boost::gregorian::date scheduler::first_saturday() const  { return find_day(weekday::saturday,  schedule::first); }
boost::gregorian::date scheduler::first_sunday() const    { return find_day(weekday::sunday,    schedule::first); }

/* second ----------------------------------------------------------------- */
boost::gregorian::date scheduler::second_monday() const    { return find_day(weekday::monday,    schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const   { return find_day(weekday::tuesday,   schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return find_day(weekday::wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const  { return find_day(weekday::thursday,  schedule::second); }
boost::gregorian::date scheduler::second_friday() const    { return find_day(weekday::friday,    schedule::second); }
boost::gregorian::date scheduler::second_saturday() const  { return find_day(weekday::saturday,  schedule::second); }
boost::gregorian::date scheduler::second_sunday() const    { return find_day(weekday::sunday,    schedule::second); }

/* third ------------------------------------------------------------------ */
boost::gregorian::date scheduler::third_monday() const    { return find_day(weekday::monday,    schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const   { return find_day(weekday::tuesday,   schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return find_day(weekday::wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const  { return find_day(weekday::thursday,  schedule::third); }
boost::gregorian::date scheduler::third_friday() const    { return find_day(weekday::friday,    schedule::third); }
boost::gregorian::date scheduler::third_saturday() const  { return find_day(weekday::saturday,  schedule::third); }
boost::gregorian::date scheduler::third_sunday() const    { return find_day(weekday::sunday,    schedule::third); }

/* fourth ----------------------------------------------------------------- */
boost::gregorian::date scheduler::fourth_monday() const    { return find_day(weekday::monday,    schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const   { return find_day(weekday::tuesday,   schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return find_day(weekday::wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const  { return find_day(weekday::thursday,  schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const    { return find_day(weekday::friday,    schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const  { return find_day(weekday::saturday,  schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const    { return find_day(weekday::sunday,    schedule::fourth); }

/* last ------------------------------------------------------------------- */
boost::gregorian::date scheduler::last_monday() const    { return find_day(weekday::monday,    schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const   { return find_day(weekday::tuesday,   schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return find_day(weekday::wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const  { return find_day(weekday::thursday,  schedule::last); }
boost::gregorian::date scheduler::last_friday() const    { return find_day(weekday::friday,    schedule::last); }
boost::gregorian::date scheduler::last_saturday() const  { return find_day(weekday::saturday,  schedule::last); }
boost::gregorian::date scheduler::last_sunday() const    { return find_day(weekday::sunday,    schedule::last); }

}  // namespace meetup
