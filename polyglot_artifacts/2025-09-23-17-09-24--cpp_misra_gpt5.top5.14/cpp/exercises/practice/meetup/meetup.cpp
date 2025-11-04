#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

namespace {
    std::int32_t to_boost_weekday_number(weekday wd) noexcept {
        switch (wd) {
            case weekday::monday: {
                return static_cast<std::int32_t>(1);
            }
            case weekday::tuesday: {
                return static_cast<std::int32_t>(2);
            }
            case weekday::wednesday: {
                return static_cast<std::int32_t>(3);
            }
            case weekday::thursday: {
                return static_cast<std::int32_t>(4);
            }
            case weekday::friday: {
                return static_cast<std::int32_t>(5);
            }
            case weekday::saturday: {
                return static_cast<std::int32_t>(6);
            }
            case weekday::sunday:
            default: {
                return static_cast<std::int32_t>(0);
            }
        }
    }
}  // unnamed namespace

scheduler::scheduler(std::int32_t year, std::int32_t month) noexcept
    : m_year(year),
      m_month(month) {
}

boost::gregorian::date scheduler::day(weekday wd, schedule sch) const {
    const std::int32_t desired = to_boost_weekday_number(wd);

    if (sch == schedule::teenth) {
        for (std::int32_t d = static_cast<std::int32_t>(13);
             d <= static_cast<std::int32_t>(19);
             d = static_cast<std::int32_t>(d + static_cast<std::int32_t>(1))) {
            const boost::gregorian::date ymd{
                static_cast<int>(m_year),
                static_cast<int>(m_month),
                static_cast<int>(d)
            };
            const std::int32_t w = static_cast<std::int32_t>(ymd.day_of_week().as_number());
            if (w == desired) {
                return ymd;
            }
        }
    } else if ((sch == schedule::first) || (sch == schedule::second) ||
               (sch == schedule::third) || (sch == schedule::fourth)) {
        const boost::gregorian::date first{
            static_cast<int>(m_year),
            static_cast<int>(m_month),
            static_cast<int>(1)
        };
        const std::int32_t first_wd = static_cast<std::int32_t>(first.day_of_week().as_number());
        std::int32_t offset = static_cast<std::int32_t>(desired - first_wd);
        offset = static_cast<std::int32_t>(((offset % static_cast<std::int32_t>(7)) + static_cast<std::int32_t>(7)) % static_cast<std::int32_t>(7));

        std::int32_t week_index = static_cast<std::int32_t>(0);
        if (sch == schedule::first) {
            week_index = static_cast<std::int32_t>(0);
        } else if (sch == schedule::second) {
            week_index = static_cast<std::int32_t>(1);
        } else if (sch == schedule::third) {
            week_index = static_cast<std::int32_t>(2);
        } else {
            week_index = static_cast<std::int32_t>(3);
        }

        const std::int32_t dom =
            static_cast<std::int32_t>(1) +
            offset +
            (static_cast<std::int32_t>(7) * week_index);

        return boost::gregorian::date{
            static_cast<int>(m_year),
            static_cast<int>(m_month),
            static_cast<int>(dom)
        };
    } else {
        // last
        std::int32_t next_month = m_month;
        std::int32_t next_year = m_year;
        if (m_month == static_cast<std::int32_t>(12)) {
            next_month = static_cast<std::int32_t>(1);
            next_year = static_cast<std::int32_t>(m_year + static_cast<std::int32_t>(1));
        } else {
            next_month = static_cast<std::int32_t>(m_month + static_cast<std::int32_t>(1));
        }

        const boost::gregorian::date first_next{
            static_cast<int>(next_year),
            static_cast<int>(next_month),
            static_cast<int>(1)
        };
        const boost::gregorian::date last_day =
            first_next - boost::gregorian::days{static_cast<long>(1)};
        const std::int32_t last_wd = static_cast<std::int32_t>(last_day.day_of_week().as_number());

        std::int32_t back = static_cast<std::int32_t>(last_wd - desired);
        back = static_cast<std::int32_t>(((back % static_cast<std::int32_t>(7)) + static_cast<std::int32_t>(7)) % static_cast<std::int32_t>(7));

        const boost::gregorian::date target =
            last_day - boost::gregorian::days{static_cast<long>(back)};

        return target;
    }

    // Fallback (should be unreachable for valid inputs)
    return boost::gregorian::date{
        static_cast<int>(m_year),
        static_cast<int>(m_month),
        static_cast<int>(1)
    };
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

boost::gregorian::date scheduler::first_monday() const { return day(weekday::monday, schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const { return day(weekday::tuesday, schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return day(weekday::wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const { return day(weekday::thursday, schedule::first); }
boost::gregorian::date scheduler::first_friday() const { return day(weekday::friday, schedule::first); }
boost::gregorian::date scheduler::first_saturday() const { return day(weekday::saturday, schedule::first); }
boost::gregorian::date scheduler::first_sunday() const { return day(weekday::sunday, schedule::first); }

boost::gregorian::date scheduler::second_monday() const { return day(weekday::monday, schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const { return day(weekday::tuesday, schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return day(weekday::wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const { return day(weekday::thursday, schedule::second); }
boost::gregorian::date scheduler::second_friday() const { return day(weekday::friday, schedule::second); }
boost::gregorian::date scheduler::second_saturday() const { return day(weekday::saturday, schedule::second); }
boost::gregorian::date scheduler::second_sunday() const { return day(weekday::sunday, schedule::second); }

boost::gregorian::date scheduler::third_monday() const { return day(weekday::monday, schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const { return day(weekday::tuesday, schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return day(weekday::wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const { return day(weekday::thursday, schedule::third); }
boost::gregorian::date scheduler::third_friday() const { return day(weekday::friday, schedule::third); }
boost::gregorian::date scheduler::third_saturday() const { return day(weekday::saturday, schedule::third); }
boost::gregorian::date scheduler::third_sunday() const { return day(weekday::sunday, schedule::third); }

boost::gregorian::date scheduler::fourth_monday() const { return day(weekday::monday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return day(weekday::tuesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return day(weekday::wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return day(weekday::thursday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return day(weekday::friday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return day(weekday::saturday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return day(weekday::sunday, schedule::fourth); }

boost::gregorian::date scheduler::last_monday() const { return day(weekday::monday, schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const { return day(weekday::tuesday, schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return day(weekday::wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const { return day(weekday::thursday, schedule::last); }
boost::gregorian::date scheduler::last_friday() const { return day(weekday::friday, schedule::last); }
boost::gregorian::date scheduler::last_saturday() const { return day(weekday::saturday, schedule::last); }
boost::gregorian::date scheduler::last_sunday() const { return day(weekday::sunday, schedule::last); }

}  // namespace meetup
