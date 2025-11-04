#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

namespace {
    std::uint32_t weekday_to_index(weekday wd) noexcept {
        switch (wd) {
            case weekday::sunday: {
                return 0U;
            }
            case weekday::monday: {
                return 1U;
            }
            case weekday::tuesday: {
                return 2U;
            }
            case weekday::wednesday: {
                return 3U;
            }
            case weekday::thursday: {
                return 4U;
            }
            case weekday::friday: {
                return 5U;
            }
            case weekday::saturday: {
                return 6U;
            }
            default: {
                return 0U;
            }
        }
    }
}  // namespace

scheduler::scheduler(std::int32_t year, std::uint32_t month) noexcept
    : year_{year}, month_{month} {}

boost::gregorian::date scheduler::day(weekday wd, schedule sch) const {
    const std::int32_t y = year_;
    const std::uint32_t m = month_;

    const boost::gregorian::date first{static_cast<int>(y), static_cast<int>(m), 1};
    const std::uint32_t first_enc = static_cast<std::uint32_t>(first.day_of_week().as_number());
    const std::uint32_t target_enc = weekday_to_index(wd);

    if (sch == schedule::teenth) {
        for (std::uint32_t d = 13U; d <= 19U; ++d) {
            const boost::gregorian::date cur{static_cast<int>(y), static_cast<int>(m), static_cast<int>(d)};
            const std::uint32_t cur_enc = static_cast<std::uint32_t>(cur.day_of_week().as_number());
            if (cur_enc == target_enc) {
                return cur;
            }
        }
    } else if ((sch == schedule::first) || (sch == schedule::second) || (sch == schedule::third) || (sch == schedule::fourth)) {
        const std::uint32_t n = (sch == schedule::first) ? 0U
                              : ((sch == schedule::second) ? 1U
                              : ((sch == schedule::third) ? 2U : 3U));

        const std::uint32_t first_delta = ((target_enc + 7U) - first_enc) % 7U;
        const std::uint32_t day1 = 1U + first_delta;
        const std::uint32_t dayn = day1 + (7U * n);
        return boost::gregorian::date{static_cast<int>(y), static_cast<int>(m), static_cast<int>(dayn)};
    } else {
        const std::int32_t last_dom = static_cast<std::int32_t>(boost::gregorian::gregorian_calendar::end_of_month_day(static_cast<int>(y), static_cast<int>(m)));
        const boost::gregorian::date last{static_cast<int>(y), static_cast<int>(m), static_cast<int>(last_dom)};
        const std::uint32_t last_enc = static_cast<std::uint32_t>(last.day_of_week().as_number());
        const std::uint32_t back_delta = ((last_enc + 7U) - target_enc) % 7U;
        const std::int32_t meet_dom = last_dom - static_cast<std::int32_t>(back_delta);
        return boost::gregorian::date{static_cast<int>(y), static_cast<int>(m), static_cast<int>(meet_dom)};
    }

    return first;
}

boost::gregorian::date scheduler::monteenth() const {
    return day(weekday::monday, schedule::teenth);
}

boost::gregorian::date scheduler::tuesteenth() const {
    return day(weekday::tuesday, schedule::teenth);
}

boost::gregorian::date scheduler::wednesteenth() const {
    return day(weekday::wednesday, schedule::teenth);
}

boost::gregorian::date scheduler::thursteenth() const {
    return day(weekday::thursday, schedule::teenth);
}

boost::gregorian::date scheduler::friteenth() const {
    return day(weekday::friday, schedule::teenth);
}

boost::gregorian::date scheduler::saturteenth() const {
    return day(weekday::saturday, schedule::teenth);
}

boost::gregorian::date scheduler::sunteenth() const {
    return day(weekday::sunday, schedule::teenth);
}

boost::gregorian::date scheduler::first_monday() const {
    return day(weekday::monday, schedule::first);
}

boost::gregorian::date scheduler::first_tuesday() const {
    return day(weekday::tuesday, schedule::first);
}

boost::gregorian::date scheduler::first_wednesday() const {
    return day(weekday::wednesday, schedule::first);
}

boost::gregorian::date scheduler::first_thursday() const {
    return day(weekday::thursday, schedule::first);
}

boost::gregorian::date scheduler::first_friday() const {
    return day(weekday::friday, schedule::first);
}

boost::gregorian::date scheduler::first_saturday() const {
    return day(weekday::saturday, schedule::first);
}

boost::gregorian::date scheduler::first_sunday() const {
    return day(weekday::sunday, schedule::first);
}

boost::gregorian::date scheduler::second_monday() const {
    return day(weekday::monday, schedule::second);
}

boost::gregorian::date scheduler::second_tuesday() const {
    return day(weekday::tuesday, schedule::second);
}

boost::gregorian::date scheduler::second_wednesday() const {
    return day(weekday::wednesday, schedule::second);
}

boost::gregorian::date scheduler::second_thursday() const {
    return day(weekday::thursday, schedule::second);
}

boost::gregorian::date scheduler::second_friday() const {
    return day(weekday::friday, schedule::second);
}

boost::gregorian::date scheduler::second_saturday() const {
    return day(weekday::saturday, schedule::second);
}

boost::gregorian::date scheduler::second_sunday() const {
    return day(weekday::sunday, schedule::second);
}

boost::gregorian::date scheduler::third_monday() const {
    return day(weekday::monday, schedule::third);
}

boost::gregorian::date scheduler::third_tuesday() const {
    return day(weekday::tuesday, schedule::third);
}

boost::gregorian::date scheduler::third_wednesday() const {
    return day(weekday::wednesday, schedule::third);
}

boost::gregorian::date scheduler::third_thursday() const {
    return day(weekday::thursday, schedule::third);
}

boost::gregorian::date scheduler::third_friday() const {
    return day(weekday::friday, schedule::third);
}

boost::gregorian::date scheduler::third_saturday() const {
    return day(weekday::saturday, schedule::third);
}

boost::gregorian::date scheduler::third_sunday() const {
    return day(weekday::sunday, schedule::third);
}

boost::gregorian::date scheduler::fourth_monday() const {
    return day(weekday::monday, schedule::fourth);
}

boost::gregorian::date scheduler::fourth_tuesday() const {
    return day(weekday::tuesday, schedule::fourth);
}

boost::gregorian::date scheduler::fourth_wednesday() const {
    return day(weekday::wednesday, schedule::fourth);
}

boost::gregorian::date scheduler::fourth_thursday() const {
    return day(weekday::thursday, schedule::fourth);
}

boost::gregorian::date scheduler::fourth_friday() const {
    return day(weekday::friday, schedule::fourth);
}

boost::gregorian::date scheduler::fourth_saturday() const {
    return day(weekday::saturday, schedule::fourth);
}

boost::gregorian::date scheduler::fourth_sunday() const {
    return day(weekday::sunday, schedule::fourth);
}

boost::gregorian::date scheduler::last_monday() const {
    return day(weekday::monday, schedule::last);
}

boost::gregorian::date scheduler::last_tuesday() const {
    return day(weekday::tuesday, schedule::last);
}

boost::gregorian::date scheduler::last_wednesday() const {
    return day(weekday::wednesday, schedule::last);
}

boost::gregorian::date scheduler::last_thursday() const {
    return day(weekday::thursday, schedule::last);
}

boost::gregorian::date scheduler::last_friday() const {
    return day(weekday::friday, schedule::last);
}

boost::gregorian::date scheduler::last_saturday() const {
    return day(weekday::saturday, schedule::last);
}

boost::gregorian::date scheduler::last_sunday() const {
    return day(weekday::sunday, schedule::last);
}

}  // namespace meetup
