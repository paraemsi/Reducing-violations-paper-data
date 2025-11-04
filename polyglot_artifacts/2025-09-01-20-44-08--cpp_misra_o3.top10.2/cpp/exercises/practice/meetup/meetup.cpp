#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cassert>

namespace meetup {


scheduler::scheduler(std::int32_t year, std::uint32_t month) noexcept
    : m_year{year},
      m_month{month}
{
    // Precondition: month shall be in the range [1, 12]
    assert((month >= 1U) && (month <= 12U));
}

boost::gregorian::date
scheduler::get_day(boost::date_time::weekdays wd, schedule sc) const
{
    const boost::gregorian::date first_dom{
        static_cast<std::int32_t>(m_year),
        static_cast<unsigned>(m_month),
        1};

    const boost::date_time::weekdays first_wd{first_dom.day_of_week()};

    std::uint32_t day_num{1U};

    switch (sc)
    {
    case schedule::first:
    case schedule::second:
    case schedule::third:
    case schedule::fourth:
    {
        const std::uint32_t ordinal{static_cast<std::uint32_t>(sc)};
        const std::uint32_t delta{
            static_cast<std::uint32_t>((static_cast<std::uint32_t>(wd) + 7U -
                                        static_cast<std::uint32_t>(first_wd)) %
                                       7U)};
        day_num = (1U + delta) + (7U * (ordinal - 1U));
        break;
    }
    case schedule::teenth:
    {
        for (std::uint32_t d{13U}; d <= 19U; ++d)
        {
            const boost::gregorian::date ymd{
                static_cast<std::int32_t>(m_year),
                static_cast<unsigned>(m_month),
                static_cast<unsigned>(d)};
            if (ymd.day_of_week() == wd)
            {
                day_num = d;
                break;
            }
        }
        break;
    }
    case schedule::last:
    {
        const boost::gregorian::date last_dom{first_dom.end_of_month()};
        std::uint32_t                d{static_cast<std::uint32_t>(last_dom.day())};
        while (d > 0U)
        {
            const boost::gregorian::date ymd{
                static_cast<std::int32_t>(m_year),
                static_cast<unsigned>(m_month),
                static_cast<unsigned>(d)};
            if (ymd.day_of_week() == wd)
            {
                day_num = d;
                break;
            }
            --d;
        }
        break;
    }
    default:
        (void)0; // unreachable
    }

    return boost::gregorian::date{
        static_cast<std::int32_t>(m_year),
        static_cast<unsigned>(m_month),
        static_cast<unsigned>(day_num)};
}

boost::gregorian::date scheduler::monteenth() const { return get_day(boost::date_time::weekdays::Monday, schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth() const { return get_day(boost::date_time::weekdays::Tuesday, schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth() const { return get_day(boost::date_time::weekdays::Wednesday, schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return get_day(boost::date_time::weekdays::Thursday, schedule::teenth); }
boost::gregorian::date scheduler::friteenth() const { return get_day(boost::date_time::weekdays::Friday, schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return get_day(boost::date_time::weekdays::Saturday, schedule::teenth); }
boost::gregorian::date scheduler::sunteenth() const { return get_day(boost::date_time::weekdays::Sunday, schedule::teenth); }

boost::gregorian::date scheduler::first_monday() const { return get_day(boost::date_time::weekdays::Monday, schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const { return get_day(boost::date_time::weekdays::Tuesday, schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return get_day(boost::date_time::weekdays::Wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const { return get_day(boost::date_time::weekdays::Thursday, schedule::first); }
boost::gregorian::date scheduler::first_friday() const { return get_day(boost::date_time::weekdays::Friday, schedule::first); }
boost::gregorian::date scheduler::first_saturday() const { return get_day(boost::date_time::weekdays::Saturday, schedule::first); }
boost::gregorian::date scheduler::first_sunday() const { return get_day(boost::date_time::weekdays::Sunday, schedule::first); }

boost::gregorian::date scheduler::second_monday() const { return get_day(boost::date_time::weekdays::Monday, schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const { return get_day(boost::date_time::weekdays::Tuesday, schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return get_day(boost::date_time::weekdays::Wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const { return get_day(boost::date_time::weekdays::Thursday, schedule::second); }
boost::gregorian::date scheduler::second_friday() const { return get_day(boost::date_time::weekdays::Friday, schedule::second); }
boost::gregorian::date scheduler::second_saturday() const { return get_day(boost::date_time::weekdays::Saturday, schedule::second); }
boost::gregorian::date scheduler::second_sunday() const { return get_day(boost::date_time::weekdays::Sunday, schedule::second); }

boost::gregorian::date scheduler::third_monday() const { return get_day(boost::date_time::weekdays::Monday, schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const { return get_day(boost::date_time::weekdays::Tuesday, schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return get_day(boost::date_time::weekdays::Wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const { return get_day(boost::date_time::weekdays::Thursday, schedule::third); }
boost::gregorian::date scheduler::third_friday() const { return get_day(boost::date_time::weekdays::Friday, schedule::third); }
boost::gregorian::date scheduler::third_saturday() const { return get_day(boost::date_time::weekdays::Saturday, schedule::third); }
boost::gregorian::date scheduler::third_sunday() const { return get_day(boost::date_time::weekdays::Sunday, schedule::third); }

boost::gregorian::date scheduler::fourth_monday() const { return get_day(boost::date_time::weekdays::Monday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return get_day(boost::date_time::weekdays::Tuesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return get_day(boost::date_time::weekdays::Wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return get_day(boost::date_time::weekdays::Thursday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return get_day(boost::date_time::weekdays::Friday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return get_day(boost::date_time::weekdays::Saturday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return get_day(boost::date_time::weekdays::Sunday, schedule::fourth); }

boost::gregorian::date scheduler::last_monday() const { return get_day(boost::date_time::weekdays::Monday, schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const { return get_day(boost::date_time::weekdays::Tuesday, schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return get_day(boost::date_time::weekdays::Wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const { return get_day(boost::date_time::weekdays::Thursday, schedule::last); }
boost::gregorian::date scheduler::last_friday() const { return get_day(boost::date_time::weekdays::Friday, schedule::last); }
boost::gregorian::date scheduler::last_saturday() const { return get_day(boost::date_time::weekdays::Saturday, schedule::last); }
boost::gregorian::date scheduler::last_sunday() const { return get_day(boost::date_time::weekdays::Sunday, schedule::last); }

}  // namespace meetup
