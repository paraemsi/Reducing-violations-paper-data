#include "meetup.h"
#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

scheduler::scheduler(const boost::gregorian::months_of_year month,
                     const std::int32_t                     year) noexcept
    : month_{month}, year_{year} { }

boost::gregorian::date
scheduler::get_day(const boost::gregorian::greg_weekday weekday,
                   const schedule                      which) const {
    const std::uint32_t eom =
        static_cast<std::uint32_t>(
            boost::gregorian::gregorian_calendar::end_of_month_day(
                static_cast<unsigned short>(year_),
                static_cast<unsigned short>(month_)));

    auto make_date =
        [this](const std::uint32_t d) -> boost::gregorian::date {
            return boost::gregorian::date(
                static_cast<int>(year_),
                month_,
                static_cast<unsigned short>(d));
        };

    switch (which) {
    case schedule::teenth:
        for (std::uint32_t d = 13U; d <= 19U; ++d) {
            const boost::gregorian::date candidate { make_date(d) };
            if ((candidate.day_of_week() == weekday)) {
                return candidate;
            }
        }
        break;

    case schedule::first:
    case schedule::second:
    case schedule::third:
    case schedule::fourth: {
        std::uint32_t occurrence { 0U };
        const std::uint32_t target =
            static_cast<std::uint32_t>(which) + 1U;   /* enum order */
        for (std::uint32_t d = 1U; d <= eom; ++d) {
            const boost::gregorian::date candidate { make_date(d) };
            if ((candidate.day_of_week() == weekday)) {
                ++occurrence;
                if (occurrence == target) {
                    return candidate;
                }
            }
        }
        break;
    }

    case schedule::last: {
        for (std::int32_t d =
                 static_cast<std::int32_t>(eom); d >= 1; --d) {
            const boost::gregorian::date candidate {
                make_date(static_cast<std::uint32_t>(d)) };
            if ((candidate.day_of_week() == weekday)) {
                return candidate;
            }
        }
        break;
    }
    }

    throw std::logic_error("Invalid schedule specification");
}
/* ------------------------------------------------------------------------- */
/* Convenience wrappers – each simply forwards to get_day() with the proper
 * weekday and schedule.
 * ------------------------------------------------------------------------- */
#define MEETUP_WRAP(fn_name, wd_const, sched_val)                              \
    boost::gregorian::date scheduler::fn_name() const {                        \
        /* Wrap the entire call in parentheses to make evaluation order clear  \
         * and comply with MISRA precedence guidelines.                        */\
        return (get_day(                                                       \
            boost::gregorian::greg_weekday(                                    \
                boost::date_time::wd_const),                                   \
            schedule::sched_val));                                             \
    }

MEETUP_WRAP(monteenth, Monday,    teenth)
MEETUP_WRAP(tuesteenth, Tuesday,  teenth)
MEETUP_WRAP(wednesteenth, Wednesday, teenth)
MEETUP_WRAP(thursteenth, Thursday, teenth)
MEETUP_WRAP(friteenth, Friday,    teenth)
MEETUP_WRAP(saturteenth, Saturday, teenth)
MEETUP_WRAP(sunteenth, Sunday,    teenth)

/* first */
MEETUP_WRAP(first_monday,    Monday,    first)
MEETUP_WRAP(first_tuesday,   Tuesday,   first)
MEETUP_WRAP(first_wednesday, Wednesday, first)
MEETUP_WRAP(first_thursday,  Thursday,  first)
MEETUP_WRAP(first_friday,    Friday,    first)
MEETUP_WRAP(first_saturday,  Saturday,  first)
MEETUP_WRAP(first_sunday,    Sunday,    first)

/* second */
MEETUP_WRAP(second_monday,    Monday,    second)
MEETUP_WRAP(second_tuesday,   Tuesday,   second)
MEETUP_WRAP(second_wednesday, Wednesday, second)
MEETUP_WRAP(second_thursday,  Thursday,  second)
MEETUP_WRAP(second_friday,    Friday,    second)
MEETUP_WRAP(second_saturday,  Saturday,  second)
MEETUP_WRAP(second_sunday,    Sunday,    second)

/* third */
MEETUP_WRAP(third_monday,    Monday,    third)
MEETUP_WRAP(third_tuesday,   Tuesday,   third)
MEETUP_WRAP(third_wednesday, Wednesday, third)
MEETUP_WRAP(third_thursday,  Thursday,  third)
MEETUP_WRAP(third_friday,    Friday,    third)
MEETUP_WRAP(third_saturday,  Saturday,  third)
MEETUP_WRAP(third_sunday,    Sunday,    third)

/* fourth */
MEETUP_WRAP(fourth_monday,    Monday,    fourth)
MEETUP_WRAP(fourth_tuesday,   Tuesday,   fourth)
MEETUP_WRAP(fourth_wednesday, Wednesday, fourth)
MEETUP_WRAP(fourth_thursday,  Thursday,  fourth)
MEETUP_WRAP(fourth_friday,    Friday,    fourth)
MEETUP_WRAP(fourth_saturday,  Saturday,  fourth)
MEETUP_WRAP(fourth_sunday,    Sunday,    fourth)

/* last */
MEETUP_WRAP(last_monday,    Monday,    last)
MEETUP_WRAP(last_tuesday,   Tuesday,   last)
MEETUP_WRAP(last_wednesday, Wednesday, last)
MEETUP_WRAP(last_thursday,  Thursday,  last)
MEETUP_WRAP(last_friday,    Friday,    last)
MEETUP_WRAP(last_saturday,  Saturday,  last)
MEETUP_WRAP(last_sunday,    Sunday,    last)

#undef MEETUP_WRAP

}  // namespace meetup
