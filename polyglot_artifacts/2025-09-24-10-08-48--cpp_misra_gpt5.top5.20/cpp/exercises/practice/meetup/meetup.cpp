#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>
#include <stdexcept>

namespace meetup {

namespace {

// Helper to construct a boost date with explicit, safe casts.
static boost::gregorian::date make_date(std::int32_t y, std::uint16_t m, std::uint16_t d)
{
    return boost::gregorian::date{
        static_cast<int>(y),
        static_cast<int>(m),
        static_cast<int>(d)
    };
}

// Compute the nth (1-4) occurrence of a weekday in a given year/month.
static boost::gregorian::date nth_weekday_of_month(std::int32_t y,
                                                   std::uint16_t m,
                                                   boost::date_time::weekdays wd,
                                                   std::uint32_t n)
{
    const boost::gregorian::date first{make_date(y, m, static_cast<std::uint16_t>(1U))};
    const std::int32_t first_num = static_cast<std::int32_t>(first.day_of_week().as_number());
    const std::int32_t target_num = static_cast<std::int32_t>(wd);

    std::int32_t diff = (target_num - first_num);
    if ((diff < static_cast<std::int32_t>(0))) {
        diff = (diff + static_cast<std::int32_t>(7));
    }

    const std::int32_t day_val = (static_cast<std::int32_t>(1) + diff + (static_cast<std::int32_t>(7) * static_cast<std::int32_t>(n - static_cast<std::uint32_t>(1U))));
    const std::uint16_t eom = static_cast<std::uint16_t>(boost::gregorian::gregorian_calendar::end_of_month_day(
        static_cast<int>(y),
        static_cast<unsigned short>(m)
    ));
    if ((day_val > static_cast<std::int32_t>(eom))) {
        // Should not occur for n in 1..4 and valid months, but guard anyway.
        throw std::out_of_range("Requested nth weekday exceeds month length");
    }
    return make_date(y, m, static_cast<std::uint16_t>(day_val));
}

// Compute the last occurrence of a weekday in a given year/month.
static boost::gregorian::date last_weekday_of_month(std::int32_t y,
                                                    std::uint16_t m,
                                                    boost::date_time::weekdays wd)
{
    const std::uint16_t eom = static_cast<std::uint16_t>(boost::gregorian::gregorian_calendar::end_of_month_day(
        static_cast<int>(y),
        static_cast<unsigned short>(m)
    ));
    const boost::gregorian::date last_day{make_date(y, m, static_cast<std::uint16_t>(eom))};
    const std::int32_t last_num = static_cast<std::int32_t>(last_day.day_of_week().as_number());
    const std::int32_t target_num = static_cast<std::int32_t>(wd);

    std::int32_t diff = (last_num - target_num);
    if ((diff < static_cast<std::int32_t>(0))) {
        diff = (diff + static_cast<std::int32_t>(7));
    }

    const std::int32_t day_val = (static_cast<std::int32_t>(eom) - diff);
    return make_date(y, m, static_cast<std::uint16_t>(day_val));
}

// Compute the teenth occurrence of a weekday in a given year/month.
static boost::gregorian::date teenth_weekday_of_month(std::int32_t y,
                                                      std::uint16_t m,
                                                      boost::date_time::weekdays wd)
{
    for (std::int32_t d = static_cast<std::int32_t>(13); (d <= static_cast<std::int32_t>(19)); ++d) {
        const boost::gregorian::date cur{make_date(y, m, static_cast<std::uint16_t>(d))};
        const std::int32_t cur_num = static_cast<std::int32_t>(cur.day_of_week().as_number());
        if ((cur_num == static_cast<std::int32_t>(wd))) {
            return cur;
        }
    }
    throw std::logic_error("No teenth weekday found");
}

} // anonymous namespace

scheduler::scheduler(std::int32_t year, std::uint16_t month) noexcept
    : year_{year}
    , month_{month}
{
    // No body needed; basic member initialization only.
}

boost::gregorian::date scheduler::monteenth() const
{
    return teenth_weekday_of_month(year_, month_, boost::date_time::Monday);
}

boost::gregorian::date scheduler::tuesteenth() const
{
    return teenth_weekday_of_month(year_, month_, boost::date_time::Tuesday);
}

boost::gregorian::date scheduler::wednesteenth() const
{
    return teenth_weekday_of_month(year_, month_, boost::date_time::Wednesday);
}

boost::gregorian::date scheduler::thursteenth() const
{
    return teenth_weekday_of_month(year_, month_, boost::date_time::Thursday);
}

boost::gregorian::date scheduler::friteenth() const
{
    return teenth_weekday_of_month(year_, month_, boost::date_time::Friday);
}

boost::gregorian::date scheduler::saturteenth() const
{
    return teenth_weekday_of_month(year_, month_, boost::date_time::Saturday);
}

boost::gregorian::date scheduler::sunteenth() const
{
    return teenth_weekday_of_month(year_, month_, boost::date_time::Sunday);
}

// First occurrences
boost::gregorian::date scheduler::first_monday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Monday, static_cast<std::uint32_t>(1U));
}
boost::gregorian::date scheduler::first_tuesday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Tuesday, static_cast<std::uint32_t>(1U));
}
boost::gregorian::date scheduler::first_wednesday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Wednesday, static_cast<std::uint32_t>(1U));
}
boost::gregorian::date scheduler::first_thursday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Thursday, static_cast<std::uint32_t>(1U));
}
boost::gregorian::date scheduler::first_friday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Friday, static_cast<std::uint32_t>(1U));
}
boost::gregorian::date scheduler::first_saturday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Saturday, static_cast<std::uint32_t>(1U));
}
boost::gregorian::date scheduler::first_sunday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Sunday, static_cast<std::uint32_t>(1U));
}

// Second occurrences
boost::gregorian::date scheduler::second_monday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Monday, static_cast<std::uint32_t>(2U));
}
boost::gregorian::date scheduler::second_tuesday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Tuesday, static_cast<std::uint32_t>(2U));
}
boost::gregorian::date scheduler::second_wednesday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Wednesday, static_cast<std::uint32_t>(2U));
}
boost::gregorian::date scheduler::second_thursday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Thursday, static_cast<std::uint32_t>(2U));
}
boost::gregorian::date scheduler::second_friday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Friday, static_cast<std::uint32_t>(2U));
}
boost::gregorian::date scheduler::second_saturday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Saturday, static_cast<std::uint32_t>(2U));
}
boost::gregorian::date scheduler::second_sunday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Sunday, static_cast<std::uint32_t>(2U));
}

// Third occurrences
boost::gregorian::date scheduler::third_monday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Monday, static_cast<std::uint32_t>(3U));
}
boost::gregorian::date scheduler::third_tuesday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Tuesday, static_cast<std::uint32_t>(3U));
}
boost::gregorian::date scheduler::third_wednesday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Wednesday, static_cast<std::uint32_t>(3U));
}
boost::gregorian::date scheduler::third_thursday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Thursday, static_cast<std::uint32_t>(3U));
}
boost::gregorian::date scheduler::third_friday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Friday, static_cast<std::uint32_t>(3U));
}
boost::gregorian::date scheduler::third_saturday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Saturday, static_cast<std::uint32_t>(3U));
}
boost::gregorian::date scheduler::third_sunday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Sunday, static_cast<std::uint32_t>(3U));
}

// Fourth occurrences
boost::gregorian::date scheduler::fourth_monday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Monday, static_cast<std::uint32_t>(4U));
}
boost::gregorian::date scheduler::fourth_tuesday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Tuesday, static_cast<std::uint32_t>(4U));
}
boost::gregorian::date scheduler::fourth_wednesday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Wednesday, static_cast<std::uint32_t>(4U));
}
boost::gregorian::date scheduler::fourth_thursday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Thursday, static_cast<std::uint32_t>(4U));
}
boost::gregorian::date scheduler::fourth_friday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Friday, static_cast<std::uint32_t>(4U));
}
boost::gregorian::date scheduler::fourth_saturday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Saturday, static_cast<std::uint32_t>(4U));
}
boost::gregorian::date scheduler::fourth_sunday() const
{
    return nth_weekday_of_month(year_, month_, boost::date_time::Sunday, static_cast<std::uint32_t>(4U));
}

// Last occurrences
boost::gregorian::date scheduler::last_monday() const
{
    return last_weekday_of_month(year_, month_, boost::date_time::Monday);
}
boost::gregorian::date scheduler::last_tuesday() const
{
    return last_weekday_of_month(year_, month_, boost::date_time::Tuesday);
}
boost::gregorian::date scheduler::last_wednesday() const
{
    return last_weekday_of_month(year_, month_, boost::date_time::Wednesday);
}
boost::gregorian::date scheduler::last_thursday() const
{
    return last_weekday_of_month(year_, month_, boost::date_time::Thursday);
}
boost::gregorian::date scheduler::last_friday() const
{
    return last_weekday_of_month(year_, month_, boost::date_time::Friday);
}
boost::gregorian::date scheduler::last_saturday() const
{
    return last_weekday_of_month(year_, month_, boost::date_time::Saturday);
}
boost::gregorian::date scheduler::last_sunday() const
{
    return last_weekday_of_month(year_, month_, boost::date_time::Sunday);
}

}  // namespace meetup
