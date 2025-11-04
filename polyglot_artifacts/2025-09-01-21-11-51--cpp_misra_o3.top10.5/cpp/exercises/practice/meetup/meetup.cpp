#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

scheduler::scheduler(std::int32_t yr, std::uint32_t mth) noexcept
    : year_{yr}, month_{mth}
{
    /* nothing else to do */
}

boost::gregorian::date scheduler::teenth_day(boost::date_time::weekdays wd) const
{
    for(std::uint32_t d = 13U; d <= 19U; ++d)
    {
        const boost::gregorian::date candidate(static_cast<std::int32_t>(year_),
                                               static_cast<std::uint32_t>(month_),
                                               static_cast<std::uint32_t>(d));
        if(candidate.day_of_week() == wd)
        {
            return candidate;
        }
    }
    throw std::logic_error("teenth day not found");
}

boost::gregorian::date scheduler::nth_weekday(int ordinal,
                                              boost::date_time::weekdays wd) const
{
    if(ordinal < 1)
    {
        throw std::invalid_argument("ordinal must be >= 1");
    }

    const boost::gregorian::date first_of_month(static_cast<std::int32_t>(year_),
                                                static_cast<std::uint32_t>(month_),
                                                1U);

    const int first_wd = first_of_month.day_of_week().as_number();
    const int target   = static_cast<int>(wd);
    const int diff     = (target - first_wd + 7) % 7;

    std::uint32_t day =
        static_cast<std::uint32_t>(1 + diff + static_cast<int>((ordinal - 1) * 7));

    const std::uint32_t eom =
        static_cast<std::uint32_t>(
            boost::gregorian::gregorian_calendar::end_of_month_day(
                static_cast<std::int32_t>(year_),
                static_cast<unsigned short>(month_)));

    while(day > eom)
    {
        day = static_cast<std::uint32_t>(day - 7U);
    }

    return boost::gregorian::date(static_cast<std::int32_t>(year_),
                                  static_cast<std::uint32_t>(month_),
                                  day);
}

/* —— teenth —— */
boost::gregorian::date scheduler::monteenth()   const { return teenth_day(boost::date_time::Monday); }
boost::gregorian::date scheduler::tuesteenth()  const { return teenth_day(boost::date_time::Tuesday); }
boost::gregorian::date scheduler::wednesteenth() const { return teenth_day(boost::date_time::Wednesday); }
boost::gregorian::date scheduler::thursteenth() const { return teenth_day(boost::date_time::Thursday); }
boost::gregorian::date scheduler::friteenth()   const { return teenth_day(boost::date_time::Friday); }
boost::gregorian::date scheduler::saturteenth() const { return teenth_day(boost::date_time::Saturday); }
boost::gregorian::date scheduler::sunteenth()   const { return teenth_day(boost::date_time::Sunday); }

/* —— first —— */
boost::gregorian::date scheduler::first_monday()    const { return nth_weekday(1, boost::date_time::Monday); }
boost::gregorian::date scheduler::first_tuesday()   const { return nth_weekday(1, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::first_wednesday() const { return nth_weekday(1, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::first_thursday()  const { return nth_weekday(1, boost::date_time::Thursday); }
boost::gregorian::date scheduler::first_friday()    const { return nth_weekday(1, boost::date_time::Friday); }
boost::gregorian::date scheduler::first_saturday()  const { return nth_weekday(1, boost::date_time::Saturday); }
boost::gregorian::date scheduler::first_sunday()    const { return nth_weekday(1, boost::date_time::Sunday); }

/* —— second —— */
boost::gregorian::date scheduler::second_monday()    const { return nth_weekday(2, boost::date_time::Monday); }
boost::gregorian::date scheduler::second_tuesday()   const { return nth_weekday(2, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::second_wednesday() const { return nth_weekday(2, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::second_thursday()  const { return nth_weekday(2, boost::date_time::Thursday); }
boost::gregorian::date scheduler::second_friday()    const { return nth_weekday(2, boost::date_time::Friday); }
boost::gregorian::date scheduler::second_saturday()  const { return nth_weekday(2, boost::date_time::Saturday); }
boost::gregorian::date scheduler::second_sunday()    const { return nth_weekday(2, boost::date_time::Sunday); }

/* —— third —— */
boost::gregorian::date scheduler::third_monday()    const { return nth_weekday(3, boost::date_time::Monday); }
boost::gregorian::date scheduler::third_tuesday()   const { return nth_weekday(3, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::third_wednesday() const { return nth_weekday(3, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::third_thursday()  const { return nth_weekday(3, boost::date_time::Thursday); }
boost::gregorian::date scheduler::third_friday()    const { return nth_weekday(3, boost::date_time::Friday); }
boost::gregorian::date scheduler::third_saturday()  const { return nth_weekday(3, boost::date_time::Saturday); }
boost::gregorian::date scheduler::third_sunday()    const { return nth_weekday(3, boost::date_time::Sunday); }

/* —— fourth —— */
boost::gregorian::date scheduler::fourth_monday()    const { return nth_weekday(4, boost::date_time::Monday); }
boost::gregorian::date scheduler::fourth_tuesday()   const { return nth_weekday(4, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::fourth_wednesday() const { return nth_weekday(4, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::fourth_thursday()  const { return nth_weekday(4, boost::date_time::Thursday); }
boost::gregorian::date scheduler::fourth_friday()    const { return nth_weekday(4, boost::date_time::Friday); }
boost::gregorian::date scheduler::fourth_saturday()  const { return nth_weekday(4, boost::date_time::Saturday); }
boost::gregorian::date scheduler::fourth_sunday()    const { return nth_weekday(4, boost::date_time::Sunday); }

/* —— last —— */
boost::gregorian::date scheduler::last_monday()    const { return nth_weekday(5, boost::date_time::Monday); }
boost::gregorian::date scheduler::last_tuesday()   const { return nth_weekday(5, boost::date_time::Tuesday); }
boost::gregorian::date scheduler::last_wednesday() const { return nth_weekday(5, boost::date_time::Wednesday); }
boost::gregorian::date scheduler::last_thursday()  const { return nth_weekday(5, boost::date_time::Thursday); }
boost::gregorian::date scheduler::last_friday()    const { return nth_weekday(5, boost::date_time::Friday); }
boost::gregorian::date scheduler::last_saturday()  const { return nth_weekday(5, boost::date_time::Saturday); }
boost::gregorian::date scheduler::last_sunday()    const { return nth_weekday(5, boost::date_time::Sunday); }

}  // namespace meetup
