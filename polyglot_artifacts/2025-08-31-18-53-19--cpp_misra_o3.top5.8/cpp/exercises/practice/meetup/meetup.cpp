#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

scheduler::scheduler(boost::gregorian::months_of_year month_param,
                     std::int32_t                     year_param) noexcept
    : year_{year_param},
      month_{month_param} { }

boost::gregorian::date
scheduler::day(boost::date_time::weekdays weekday_param,
               week_t                     schedule_param) const
{
    const std::uint16_t month_number =
        static_cast<std::uint16_t>(month_);
    const std::uint16_t max_day =
        static_cast<std::uint16_t>(
            boost::gregorian::gregorian_calendar::end_of_month_day(
                static_cast<unsigned short>(year_),
                static_cast<unsigned short>(month_number)));

    auto match_weekday =
        [weekday_param](const boost::gregorian::date& d) noexcept -> bool
        {
            return (d.day_of_week() == weekday_param);
        };

    if(schedule_param == week_t::teenth) {
        for(std::uint16_t d = 13U; d <= 19U; ++d) {
            const boost::gregorian::date current{
                static_cast<unsigned short>(year_),
                static_cast<unsigned short>(month_number),
                static_cast<unsigned short>(d)};
            if(match_weekday(current)) {
                return current;
            }
        }
    } else if(schedule_param == week_t::last) {
        for(std::uint16_t offset = 0U; offset < 7U; ++offset) {
            const std::uint16_t d =
                static_cast<std::uint16_t>(max_day - offset);
            const boost::gregorian::date current{
                static_cast<unsigned short>(year_),
                static_cast<unsigned short>(month_number),
                static_cast<unsigned short>(d)};
            if(match_weekday(current)) {
                return current;
            }
        }
    } else {
        std::uint16_t first_match_day = 1U;
        for(std::uint16_t d = 1U; d <= 7U; ++d) {
            const boost::gregorian::date current{
                static_cast<unsigned short>(year_),
                static_cast<unsigned short>(month_number),
                static_cast<unsigned short>(d)};
            if(match_weekday(current)) {
                first_match_day = d;
                break;
            }
        }

        std::uint16_t week_index = 0U;
        switch(schedule_param) {
            case week_t::first:  week_index = 0U; break;
            case week_t::second: week_index = 1U; break;
            case week_t::third:  week_index = 2U; break;
            case week_t::fourth: week_index = 3U; break;
            default:             week_index = 0U; break;
        }

        std::uint16_t d =
            static_cast<std::uint16_t>(first_match_day + (week_index * 7U));
        if(d > max_day) {
            d = static_cast<std::uint16_t>(d - 7U);
        }
        return boost::gregorian::date{
            static_cast<unsigned short>(year_),
            static_cast<unsigned short>(month_number),
            static_cast<unsigned short>(d)};
    }

    /* Defensive fallback */
    return boost::gregorian::date{
        static_cast<unsigned short>(year_),
        static_cast<unsigned short>(month_number),
        static_cast<unsigned short>(1U)};
}

/* Convenience generators */
boost::gregorian::date scheduler::monteenth() const { return day(boost::date_time::Monday,    week_t::teenth); }
boost::gregorian::date scheduler::tuesteenth() const { return day(boost::date_time::Tuesday,   week_t::teenth); }
boost::gregorian::date scheduler::wednesteenth() const { return day(boost::date_time::Wednesday, week_t::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return day(boost::date_time::Thursday,  week_t::teenth); }
boost::gregorian::date scheduler::friteenth() const { return day(boost::date_time::Friday,    week_t::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return day(boost::date_time::Saturday,  week_t::teenth); }
boost::gregorian::date scheduler::sunteenth() const { return day(boost::date_time::Sunday,    week_t::teenth); }

#define MEETUP_WEEK_FUNCTION(prefix, enum_value) \
boost::gregorian::date scheduler::prefix##_monday() const    { return day(boost::date_time::Monday,    week_t::enum_value); } \
boost::gregorian::date scheduler::prefix##_tuesday() const   { return day(boost::date_time::Tuesday,   week_t::enum_value); } \
boost::gregorian::date scheduler::prefix##_wednesday() const { return day(boost::date_time::Wednesday, week_t::enum_value); } \
boost::gregorian::date scheduler::prefix##_thursday() const  { return day(boost::date_time::Thursday,  week_t::enum_value); } \
boost::gregorian::date scheduler::prefix##_friday() const    { return day(boost::date_time::Friday,    week_t::enum_value); } \
boost::gregorian::date scheduler::prefix##_saturday() const  { return day(boost::date_time::Saturday,  week_t::enum_value); } \
boost::gregorian::date scheduler::prefix##_sunday() const    { return day(boost::date_time::Sunday,    week_t::enum_value); }

MEETUP_WEEK_FUNCTION(first,  first);
MEETUP_WEEK_FUNCTION(second, second);
MEETUP_WEEK_FUNCTION(third,  third);
MEETUP_WEEK_FUNCTION(fourth, fourth);
MEETUP_WEEK_FUNCTION(last,   last);

#undef MEETUP_WEEK_FUNCTION

}  // namespace meetup
