#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

scheduler::scheduler(std::int32_t year, std::uint32_t month) noexcept
    : m_first_day{year,
                  static_cast<std::uint16_t>(month),
                  static_cast<std::uint16_t>(1)}
{
}

boost::gregorian::date
scheduler::day(boost::gregorian::greg_weekday requested_weekday,
               schedule                      requested_schedule) const noexcept
{
    const std::int32_t    year_val  = static_cast<std::int32_t>(m_first_day.year());
    const std::uint16_t   month_val = static_cast<std::uint16_t>(m_first_day.month().as_number());

    const std::uint16_t   last_day_of_month =
        boost::gregorian::gregorian_calendar::end_of_month_day(year_val, month_val);

    if (requested_schedule == schedule::teenth) {
        for (std::uint16_t d = static_cast<std::uint16_t>(13); d <= static_cast<std::uint16_t>(19); ++d) {
            const boost::gregorian::date current_day{year_val, month_val, d};

            if (current_day.day_of_week() == requested_weekday) {
                return current_day;
            }
        }
    } else if ((requested_schedule == schedule::first)  ||
               (requested_schedule == schedule::second) ||
               (requested_schedule == schedule::third)  ||
               (requested_schedule == schedule::fourth)) {
        const std::uint8_t target_index =
            static_cast<std::uint8_t>(requested_schedule); /* first == 0U, second == 1U, etc. */
        std::uint8_t       found_index = 0U;

        for (std::uint16_t d = static_cast<std::uint16_t>(1); d <= last_day_of_month; ++d) {
            const boost::gregorian::date current_day{year_val, month_val, d};

            if (current_day.day_of_week() == requested_weekday) {
                if (found_index == target_index) {
                    return current_day;
                }
                ++found_index;
            }
        }
    } else { /* requested_schedule == schedule::last */
        for (std::uint16_t d = last_day_of_month; d >= static_cast<std::uint16_t>(1); --d) {
            const boost::gregorian::date current_day{year_val, month_val, d};

            if (current_day.day_of_week() == requested_weekday) {
                return current_day;
            }

            if (d == static_cast<std::uint16_t>(1)) {
                break; /* prevent wrap-around */
            }
        }
    }

    return boost::gregorian::date{}; /* invalid date – should never reach here with valid input */
}

/* helper to shorten calls */
static boost::gregorian::greg_weekday weekday(boost::date_time::weekdays wd) noexcept
{
    return boost::gregorian::greg_weekday{wd};
}

/* teenth */
boost::gregorian::date scheduler::monteenth()   const { return day(weekday(boost::date_time::Monday),    schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth()  const { return day(weekday(boost::date_time::Tuesday),   schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth()const { return day(weekday(boost::date_time::Wednesday), schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return day(weekday(boost::date_time::Thursday),  schedule::teenth); }
boost::gregorian::date scheduler::friteenth()   const { return day(weekday(boost::date_time::Friday),    schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return day(weekday(boost::date_time::Saturday),  schedule::teenth); }
boost::gregorian::date scheduler::sunteenth()   const { return day(weekday(boost::date_time::Sunday),    schedule::teenth); }

/* first */
boost::gregorian::date scheduler::first_monday()    const { return day(weekday(boost::date_time::Monday),    schedule::first); }
boost::gregorian::date scheduler::first_tuesday()   const { return day(weekday(boost::date_time::Tuesday),   schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return day(weekday(boost::date_time::Wednesday), schedule::first); }
boost::gregorian::date scheduler::first_thursday()  const { return day(weekday(boost::date_time::Thursday),  schedule::first); }
boost::gregorian::date scheduler::first_friday()    const { return day(weekday(boost::date_time::Friday),    schedule::first); }
boost::gregorian::date scheduler::first_saturday()  const { return day(weekday(boost::date_time::Saturday),  schedule::first); }
boost::gregorian::date scheduler::first_sunday()    const { return day(weekday(boost::date_time::Sunday),    schedule::first); }

/* second */
boost::gregorian::date scheduler::second_monday()    const { return day(weekday(boost::date_time::Monday),    schedule::second); }
boost::gregorian::date scheduler::second_tuesday()   const { return day(weekday(boost::date_time::Tuesday),   schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return day(weekday(boost::date_time::Wednesday), schedule::second); }
boost::gregorian::date scheduler::second_thursday()  const { return day(weekday(boost::date_time::Thursday),  schedule::second); }
boost::gregorian::date scheduler::second_friday()    const { return day(weekday(boost::date_time::Friday),    schedule::second); }
boost::gregorian::date scheduler::second_saturday()  const { return day(weekday(boost::date_time::Saturday),  schedule::second); }
boost::gregorian::date scheduler::second_sunday()    const { return day(weekday(boost::date_time::Sunday),    schedule::second); }

/* third */
boost::gregorian::date scheduler::third_monday()    const { return day(weekday(boost::date_time::Monday),    schedule::third); }
boost::gregorian::date scheduler::third_tuesday()   const { return day(weekday(boost::date_time::Tuesday),   schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return day(weekday(boost::date_time::Wednesday), schedule::third); }
boost::gregorian::date scheduler::third_thursday()  const { return day(weekday(boost::date_time::Thursday),  schedule::third); }
boost::gregorian::date scheduler::third_friday()    const { return day(weekday(boost::date_time::Friday),    schedule::third); }
boost::gregorian::date scheduler::third_saturday()  const { return day(weekday(boost::date_time::Saturday),  schedule::third); }
boost::gregorian::date scheduler::third_sunday()    const { return day(weekday(boost::date_time::Sunday),    schedule::third); }

/* fourth */
boost::gregorian::date scheduler::fourth_monday()    const { return day(weekday(boost::date_time::Monday),    schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday()   const { return day(weekday(boost::date_time::Tuesday),   schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return day(weekday(boost::date_time::Wednesday), schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday()  const { return day(weekday(boost::date_time::Thursday),  schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday()    const { return day(weekday(boost::date_time::Friday),    schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday()  const { return day(weekday(boost::date_time::Saturday),  schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday()    const { return day(weekday(boost::date_time::Sunday),    schedule::fourth); }

/* last */
boost::gregorian::date scheduler::last_monday()    const { return day(weekday(boost::date_time::Monday),    schedule::last); }
boost::gregorian::date scheduler::last_tuesday()   const { return day(weekday(boost::date_time::Tuesday),   schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return day(weekday(boost::date_time::Wednesday), schedule::last); }
boost::gregorian::date scheduler::last_thursday()  const { return day(weekday(boost::date_time::Thursday),  schedule::last); }
boost::gregorian::date scheduler::last_friday()    const { return day(weekday(boost::date_time::Friday),    schedule::last); }
boost::gregorian::date scheduler::last_saturday()  const { return day(weekday(boost::date_time::Saturday),  schedule::last); }
boost::gregorian::date scheduler::last_sunday()    const { return day(weekday(boost::date_time::Sunday),    schedule::last); }

} /* namespace meetup */
