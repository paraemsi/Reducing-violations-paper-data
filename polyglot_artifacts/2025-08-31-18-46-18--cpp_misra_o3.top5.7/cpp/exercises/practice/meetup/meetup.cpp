#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
#include <cstdint>

namespace meetup {

scheduler::scheduler(std::int32_t year, std::uint32_t month)
    : year_{year}, month_{month}
{
    if ((month_ >= 1U) && (month_ <= 12U)) {
        /* parameters verified */
    } else {
        throw std::invalid_argument("Invalid month value");
    }
}

boost::gregorian::date scheduler::day(boost::gregorian::greg_weekday weekday_requested,
                                      schedule                      when) const
{
    using boost::gregorian::date;
    using boost::gregorian::nth_day_of_the_week_in_month;
    using boost::gregorian::last_day_of_the_week_in_month;
    using boost::date_time::nth_kday_of_month;

    const std::int32_t     y = year_;
    const unsigned short   m = static_cast<unsigned short>(month_);

    /* month range was already validated in the ctor; guard defensively anyway */
    if (!((m >= static_cast<unsigned short>(1U)) && (m <= static_cast<unsigned short>(12U)))) {
        throw std::invalid_argument("Invalid month");
    }

    switch (when) {
        case schedule::teenth:
        {
            for (unsigned short d = static_cast<unsigned short>(13U);
                 d <= static_cast<unsigned short>(19U);
                 ++d) {
                const date current_date{y, m, d};
                if (current_date.day_of_week() == weekday_requested) {
                    return current_date;
                }
            }
            break; /* fall-through to throw below if not found – should be impossible */
        }

        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth:
        {
            nth_kday_of_month::nth_kday_enum nth_val{nth_kday_of_month::first};
            if (when == schedule::second) {
                nth_val = nth_kday_of_month::second;
            } else if (when == schedule::third) {
                nth_val = nth_kday_of_month::third;
            } else if (when == schedule::fourth) {
                nth_val = nth_kday_of_month::fourth;
            } else {
                /* already first */
            }

            nth_day_of_the_week_in_month rule(
                nth_val,
                static_cast<boost::date_time::weekdays>(weekday_requested.as_number()),
                m);

            return rule.get_date(y);
        }

        case schedule::last:
        {
            last_day_of_the_week_in_month rule(
                static_cast<boost::date_time::weekdays>(weekday_requested.as_number()),
                m);
            return rule.get_date(y);
        }

        default:
            break;
    }

    throw std::runtime_error("Requested meetup day not found");
}

/* Teenth helper methods */
boost::gregorian::date scheduler::monteenth()   const { return day(boost::gregorian::greg_weekday{boost::date_time::Monday},    schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth()  const { return day(boost::gregorian::greg_weekday{boost::date_time::Tuesday},   schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth()const { return day(boost::gregorian::greg_weekday{boost::date_time::Wednesday}, schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return day(boost::gregorian::greg_weekday{boost::date_time::Thursday},  schedule::teenth); }
boost::gregorian::date scheduler::friteenth()   const { return day(boost::gregorian::greg_weekday{boost::date_time::Friday},    schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return day(boost::gregorian::greg_weekday{boost::date_time::Saturday},  schedule::teenth); }
boost::gregorian::date scheduler::sunteenth()   const { return day(boost::gregorian::greg_weekday{boost::date_time::Sunday},    schedule::teenth); }

/* First weekday helpers */
boost::gregorian::date scheduler::first_monday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Monday},    schedule::first); }
boost::gregorian::date scheduler::first_tuesday()   const { return day(boost::gregorian::greg_weekday{boost::date_time::Tuesday},   schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return day(boost::gregorian::greg_weekday{boost::date_time::Wednesday}, schedule::first); }
boost::gregorian::date scheduler::first_thursday()  const { return day(boost::gregorian::greg_weekday{boost::date_time::Thursday},  schedule::first); }
boost::gregorian::date scheduler::first_friday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Friday},    schedule::first); }
boost::gregorian::date scheduler::first_saturday()  const { return day(boost::gregorian::greg_weekday{boost::date_time::Saturday},  schedule::first); }
boost::gregorian::date scheduler::first_sunday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Sunday},    schedule::first); }

/* Second weekday helpers */
boost::gregorian::date scheduler::second_monday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Monday},    schedule::second); }
boost::gregorian::date scheduler::second_tuesday()   const { return day(boost::gregorian::greg_weekday{boost::date_time::Tuesday},   schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return day(boost::gregorian::greg_weekday{boost::date_time::Wednesday}, schedule::second); }
boost::gregorian::date scheduler::second_thursday()  const { return day(boost::gregorian::greg_weekday{boost::date_time::Thursday},  schedule::second); }
boost::gregorian::date scheduler::second_friday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Friday},    schedule::second); }
boost::gregorian::date scheduler::second_saturday()  const { return day(boost::gregorian::greg_weekday{boost::date_time::Saturday},  schedule::second); }
boost::gregorian::date scheduler::second_sunday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Sunday},    schedule::second); }

/* Third weekday helpers */
boost::gregorian::date scheduler::third_monday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Monday},    schedule::third); }
boost::gregorian::date scheduler::third_tuesday()   const { return day(boost::gregorian::greg_weekday{boost::date_time::Tuesday},   schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return day(boost::gregorian::greg_weekday{boost::date_time::Wednesday}, schedule::third); }
boost::gregorian::date scheduler::third_thursday()  const { return day(boost::gregorian::greg_weekday{boost::date_time::Thursday},  schedule::third); }
boost::gregorian::date scheduler::third_friday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Friday},    schedule::third); }
boost::gregorian::date scheduler::third_saturday()  const { return day(boost::gregorian::greg_weekday{boost::date_time::Saturday},  schedule::third); }
boost::gregorian::date scheduler::third_sunday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Sunday},    schedule::third); }

/* Fourth weekday helpers */
boost::gregorian::date scheduler::fourth_monday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Monday},    schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday()   const { return day(boost::gregorian::greg_weekday{boost::date_time::Tuesday},   schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return day(boost::gregorian::greg_weekday{boost::date_time::Wednesday}, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday()  const { return day(boost::gregorian::greg_weekday{boost::date_time::Thursday},  schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Friday},    schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday()  const { return day(boost::gregorian::greg_weekday{boost::date_time::Saturday},  schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Sunday},    schedule::fourth); }

/* Last weekday helpers */
boost::gregorian::date scheduler::last_monday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Monday},    schedule::last); }
boost::gregorian::date scheduler::last_tuesday()   const { return day(boost::gregorian::greg_weekday{boost::date_time::Tuesday},   schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return day(boost::gregorian::greg_weekday{boost::date_time::Wednesday}, schedule::last); }
boost::gregorian::date scheduler::last_thursday()  const { return day(boost::gregorian::greg_weekday{boost::date_time::Thursday},  schedule::last); }
boost::gregorian::date scheduler::last_friday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Friday},    schedule::last); }
boost::gregorian::date scheduler::last_saturday()  const { return day(boost::gregorian::greg_weekday{boost::date_time::Saturday},  schedule::last); }
boost::gregorian::date scheduler::last_sunday()    const { return day(boost::gregorian::greg_weekday{boost::date_time::Sunday},    schedule::last); }

}  // namespace meetup
