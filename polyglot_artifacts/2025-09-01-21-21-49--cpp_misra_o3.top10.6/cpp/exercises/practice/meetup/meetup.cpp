#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {
// Convert schedule to zero-based week index (first → 0, … fourth → 3)
[[nodiscard]] std::uint32_t week_index(const schedule sc) {
    switch (sc) {
        case schedule::first:  { return static_cast<std::uint32_t>(0U); }
        case schedule::second: { return static_cast<std::uint32_t>(1U); }
        case schedule::third:  { return static_cast<std::uint32_t>(2U); }
        case schedule::fourth: { return static_cast<std::uint32_t>(3U); }
        default:               { return static_cast<std::uint32_t>(0U); } // not reached
    }
}
} // namespace

scheduler::scheduler(const std::int32_t yr, const std::uint32_t mon)
    : year_{yr},
      month_{mon}
{
    if ((month_ < static_cast<std::uint32_t>(1U)) ||
        (month_ > static_cast<std::uint32_t>(12U))) {
        throw std::out_of_range("month must be in 1..12");
    }
}

boost::gregorian::date scheduler::get_day(const boost::date_time::weekdays target_wd,
                                          const schedule                   sc) const
{
    const boost::gregorian::greg_weekday target_wd_obj{target_wd};

    /* Handle 'teenth' */
    if (sc == schedule::teenth) {
        for (std::uint32_t d = static_cast<std::uint32_t>(13U);
             d <= static_cast<std::uint32_t>(19U);
             ++d) {
            const boost::gregorian::date curr{
                static_cast<boost::gregorian::date::year_type>(year_),
                static_cast<boost::gregorian::date::month_type>(month_),
                static_cast<boost::gregorian::date::day_type>(d)};
            if (curr.day_of_week() == target_wd_obj) {
                return curr;
            }
        }
    }
    /* Handle ordinal weeks */
    else if ((sc == schedule::first) || (sc == schedule::second) ||
             (sc == schedule::third) || (sc == schedule::fourth)) {
        const std::uint32_t idx = week_index(sc);

        for (std::uint32_t d = static_cast<std::uint32_t>(1U);
             d <= static_cast<std::uint32_t>(7U);
             ++d) {
            const boost::gregorian::date curr{
                static_cast<boost::gregorian::date::year_type>(year_),
                static_cast<boost::gregorian::date::month_type>(month_),
                static_cast<boost::gregorian::date::day_type>(d)};
            if (curr.day_of_week() == target_wd_obj) {
                const std::uint32_t result_day =
                    d + (idx * static_cast<std::uint32_t>(7U));
                return boost::gregorian::date{
                    static_cast<boost::gregorian::date::year_type>(year_),
                    static_cast<boost::gregorian::date::month_type>(month_),
                    static_cast<boost::gregorian::date::day_type>(result_day)};
            }
        }
    }
    /* Handle 'last' */
    else if (sc == schedule::last) {
        const std::uint32_t last_dom =
            static_cast<std::uint32_t>(
                boost::gregorian::gregorian_calendar::end_of_month_day(
                    static_cast<std::uint16_t>(year_),
                    static_cast<std::uint16_t>(month_)));

        for (std::uint32_t offset = static_cast<std::uint32_t>(0U);
             offset < static_cast<std::uint32_t>(7U);
             ++offset) {
            const std::uint32_t d = last_dom - offset;
            const boost::gregorian::date curr{
                static_cast<boost::gregorian::date::year_type>(year_),
                static_cast<boost::gregorian::date::month_type>(month_),
                static_cast<boost::gregorian::date::day_type>(d)};
            if (curr.day_of_week() == target_wd_obj) {
                return curr;
            }
        }
    }

    throw std::logic_error("Requested meetup date does not exist");
}

/* teenth helpers */
boost::gregorian::date scheduler::monteenth() const {
    return get_day(boost::date_time::Monday, schedule::teenth);
}
boost::gregorian::date scheduler::tuesteenth() const {
    return get_day(boost::date_time::Tuesday, schedule::teenth);
}
boost::gregorian::date scheduler::wednesteenth() const {
    return get_day(boost::date_time::Wednesday, schedule::teenth);
}
boost::gregorian::date scheduler::thursteenth() const {
    return get_day(boost::date_time::Thursday, schedule::teenth);
}
boost::gregorian::date scheduler::friteenth() const {
    return get_day(boost::date_time::Friday, schedule::teenth);
}
boost::gregorian::date scheduler::saturteenth() const {
    return get_day(boost::date_time::Saturday, schedule::teenth);
}
boost::gregorian::date scheduler::sunteenth() const {
    return get_day(boost::date_time::Sunday, schedule::teenth);
}

/* first week */
boost::gregorian::date scheduler::first_monday() const { return get_day(boost::date_time::Monday, schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const { return get_day(boost::date_time::Thursday, schedule::first); }
boost::gregorian::date scheduler::first_friday() const { return get_day(boost::date_time::Friday, schedule::first); }
boost::gregorian::date scheduler::first_saturday() const { return get_day(boost::date_time::Saturday, schedule::first); }
boost::gregorian::date scheduler::first_sunday() const { return get_day(boost::date_time::Sunday, schedule::first); }

/* second week */
boost::gregorian::date scheduler::second_monday() const { return get_day(boost::date_time::Monday, schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const { return get_day(boost::date_time::Thursday, schedule::second); }
boost::gregorian::date scheduler::second_friday() const { return get_day(boost::date_time::Friday, schedule::second); }
boost::gregorian::date scheduler::second_saturday() const { return get_day(boost::date_time::Saturday, schedule::second); }
boost::gregorian::date scheduler::second_sunday() const { return get_day(boost::date_time::Sunday, schedule::second); }

/* third week */
boost::gregorian::date scheduler::third_monday() const { return get_day(boost::date_time::Monday, schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const { return get_day(boost::date_time::Thursday, schedule::third); }
boost::gregorian::date scheduler::third_friday() const { return get_day(boost::date_time::Friday, schedule::third); }
boost::gregorian::date scheduler::third_saturday() const { return get_day(boost::date_time::Saturday, schedule::third); }
boost::gregorian::date scheduler::third_sunday() const { return get_day(boost::date_time::Sunday, schedule::third); }

/* fourth week */
boost::gregorian::date scheduler::fourth_monday() const { return get_day(boost::date_time::Monday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return get_day(boost::date_time::Thursday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return get_day(boost::date_time::Friday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return get_day(boost::date_time::Saturday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return get_day(boost::date_time::Sunday, schedule::fourth); }

/* last week */
boost::gregorian::date scheduler::last_monday() const { return get_day(boost::date_time::Monday, schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const { return get_day(boost::date_time::Tuesday, schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return get_day(boost::date_time::Wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const { return get_day(boost::date_time::Thursday, schedule::last); }
boost::gregorian::date scheduler::last_friday() const { return get_day(boost::date_time::Friday, schedule::last); }
boost::gregorian::date scheduler::last_saturday() const { return get_day(boost::date_time::Saturday, schedule::last); }
boost::gregorian::date scheduler::last_sunday() const { return get_day(boost::date_time::Sunday, schedule::last); }

}  // namespace meetup
