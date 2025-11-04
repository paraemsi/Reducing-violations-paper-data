#include "meetup.h"

#include <algorithm>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {

/* Return number of days in the given month */
[[nodiscard]] auto days_in_month(std::int32_t year,
                                 std::uint8_t month) -> std::uint8_t
{
    const unsigned short md =
        boost::gregorian::gregorian_calendar::end_of_month_day(
            static_cast<int>(year),
            static_cast<unsigned short>(month));
    return static_cast<std::uint8_t>(md);
}

} // namespace

scheduler::scheduler(boost::gregorian::months_of_year month,
                     std::int32_t year) noexcept
    : year_{ year },
      month_{ static_cast<std::uint8_t>(month) }
{
}

auto scheduler::day(const boost::gregorian::greg_weekday &day_of_week,
                    schedule week) const -> boost::gregorian::date
{
    const std::uint8_t dim = days_in_month(year_, month_);

    std::vector<std::uint8_t> candidates{};
    candidates.reserve(static_cast<std::size_t>(dim));

    for(std::uint8_t d = static_cast<std::uint8_t>(1U); d <= dim; ++d)
    {
        const boost::gregorian::date current{
            static_cast<int>(year_),
            static_cast<unsigned short>(month_),
            static_cast<unsigned short>(d)
        };
        const boost::gregorian::greg_weekday wd{ current.day_of_week() };
        if(wd == day_of_week)
        {
            candidates.push_back(d);
        }
    }


    std::uint8_t selected_day = static_cast<std::uint8_t>(1U);

    switch(week)
    {
        case schedule::first:
        {
            selected_day = candidates.at(0U);
            break;
        }
        case schedule::second:
        {
            selected_day = candidates.at(1U);
            break;
        }
        case schedule::third:
        {
            selected_day = candidates.at(2U);
            break;
        }
        case schedule::fourth:
        {
            selected_day = candidates.at(3U);
            break;
        }
        case schedule::last:
        {
            selected_day = candidates.back();
            break;
        }
        case schedule::teenth:
        {
            const auto itr = std::find_if(
                candidates.begin(),
                candidates.end(),
                [](std::uint8_t d) noexcept
                {
                    return ((d >= static_cast<std::uint8_t>(13U)) &&
                            (d <= static_cast<std::uint8_t>(19U)));
                });
            if(itr != candidates.end())
            {
                selected_day = *itr;
            }
            break;
        }
        default:
        {
            break;
        }
    }

    return boost::gregorian::date{
        static_cast<int>(year_),
        static_cast<unsigned short>(month_),
        static_cast<unsigned short>(selected_day)
    };
}

/* Convenience helpers */
#define MEETUP_DEFINE_FUNC(name, weekday_const, sched)                          \
    auto scheduler::name() const -> boost::gregorian::date                     \
    {                                                                          \
        return day(                                                            \
            boost::gregorian::greg_weekday{ boost::date_time::weekday_const }, \
            sched);                                                            \
    }

MEETUP_DEFINE_FUNC(monteenth, Monday, schedule::teenth)
MEETUP_DEFINE_FUNC(tuesteenth, Tuesday, schedule::teenth)
MEETUP_DEFINE_FUNC(wednesteenth, Wednesday, schedule::teenth)
MEETUP_DEFINE_FUNC(thursteenth, Thursday, schedule::teenth)
MEETUP_DEFINE_FUNC(friteenth, Friday, schedule::teenth)
MEETUP_DEFINE_FUNC(saturteenth, Saturday, schedule::teenth)
MEETUP_DEFINE_FUNC(sunteenth, Sunday, schedule::teenth)

MEETUP_DEFINE_FUNC(first_monday, Monday, schedule::first)
MEETUP_DEFINE_FUNC(first_tuesday, Tuesday, schedule::first)
MEETUP_DEFINE_FUNC(first_wednesday, Wednesday, schedule::first)
MEETUP_DEFINE_FUNC(first_thursday, Thursday, schedule::first)
MEETUP_DEFINE_FUNC(first_friday, Friday, schedule::first)
MEETUP_DEFINE_FUNC(first_saturday, Saturday, schedule::first)
MEETUP_DEFINE_FUNC(first_sunday, Sunday, schedule::first)

MEETUP_DEFINE_FUNC(second_monday, Monday, schedule::second)
MEETUP_DEFINE_FUNC(second_tuesday, Tuesday, schedule::second)
MEETUP_DEFINE_FUNC(second_wednesday, Wednesday, schedule::second)
MEETUP_DEFINE_FUNC(second_thursday, Thursday, schedule::second)
MEETUP_DEFINE_FUNC(second_friday, Friday, schedule::second)
MEETUP_DEFINE_FUNC(second_saturday, Saturday, schedule::second)
MEETUP_DEFINE_FUNC(second_sunday, Sunday, schedule::second)

MEETUP_DEFINE_FUNC(third_monday, Monday, schedule::third)
MEETUP_DEFINE_FUNC(third_tuesday, Tuesday, schedule::third)
MEETUP_DEFINE_FUNC(third_wednesday, Wednesday, schedule::third)
MEETUP_DEFINE_FUNC(third_thursday, Thursday, schedule::third)
MEETUP_DEFINE_FUNC(third_friday, Friday, schedule::third)
MEETUP_DEFINE_FUNC(third_saturday, Saturday, schedule::third)
MEETUP_DEFINE_FUNC(third_sunday, Sunday, schedule::third)

MEETUP_DEFINE_FUNC(fourth_monday, Monday, schedule::fourth)
MEETUP_DEFINE_FUNC(fourth_tuesday, Tuesday, schedule::fourth)
MEETUP_DEFINE_FUNC(fourth_wednesday, Wednesday, schedule::fourth)
MEETUP_DEFINE_FUNC(fourth_thursday, Thursday, schedule::fourth)
MEETUP_DEFINE_FUNC(fourth_friday, Friday, schedule::fourth)
MEETUP_DEFINE_FUNC(fourth_saturday, Saturday, schedule::fourth)
MEETUP_DEFINE_FUNC(fourth_sunday, Sunday, schedule::fourth)

MEETUP_DEFINE_FUNC(last_monday, Monday, schedule::last)
MEETUP_DEFINE_FUNC(last_tuesday, Tuesday, schedule::last)
MEETUP_DEFINE_FUNC(last_wednesday, Wednesday, schedule::last)
MEETUP_DEFINE_FUNC(last_thursday, Thursday, schedule::last)
MEETUP_DEFINE_FUNC(last_friday, Friday, schedule::last)
MEETUP_DEFINE_FUNC(last_saturday, Saturday, schedule::last)
MEETUP_DEFINE_FUNC(last_sunday, Sunday, schedule::last)

#undef MEETUP_DEFINE_FUNC

}  // namespace meetup
