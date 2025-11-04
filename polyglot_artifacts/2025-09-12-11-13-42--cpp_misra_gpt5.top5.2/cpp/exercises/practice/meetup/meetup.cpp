#include "meetup.h"

namespace meetup {

namespace {

boost::gregorian::greg_weekday to_boost_weekday(weekday wd) noexcept
{
    switch (wd) {
        case weekday::monday: {
            return boost::gregorian::greg_weekday{boost::date_time::weekdays::Monday};
        }
        case weekday::tuesday: {
            return boost::gregorian::greg_weekday{boost::date_time::weekdays::Tuesday};
        }
        case weekday::wednesday: {
            return boost::gregorian::greg_weekday{boost::date_time::weekdays::Wednesday};
        }
        case weekday::thursday: {
            return boost::gregorian::greg_weekday{boost::date_time::weekdays::Thursday};
        }
        case weekday::friday: {
            return boost::gregorian::greg_weekday{boost::date_time::weekdays::Friday};
        }
        case weekday::saturday: {
            return boost::gregorian::greg_weekday{boost::date_time::weekdays::Saturday};
        }
        case weekday::sunday: {
            return boost::gregorian::greg_weekday{boost::date_time::weekdays::Sunday};
        }
        default: {
            return boost::gregorian::greg_weekday{boost::date_time::weekdays::Sunday};
        }
    }
}

boost::gregorian::date teenth_weekday(std::int32_t year, std::int32_t month, weekday wd)
{
    const boost::gregorian::greg_weekday desired{to_boost_weekday(wd)};
    for (std::int32_t d = 13; d <= 19; ++d) {
        const boost::gregorian::date ymd{static_cast<int>(year), static_cast<int>(month), static_cast<int>(d)};
        const boost::gregorian::greg_weekday w{ymd.day_of_week()};
        if (w.as_number() == desired.as_number()) {
            return ymd;
        }
    }
    // Unreachable by problem guarantees; return 13th as a safe fallback.
    return boost::gregorian::date{static_cast<int>(year), static_cast<int>(month), 13};
}

boost::gregorian::date nth_weekday_in_month(std::int32_t year, std::int32_t month, weekday wd, std::int32_t n)
{
    const boost::gregorian::date first{static_cast<int>(year), static_cast<int>(month), 1};
    const boost::gregorian::greg_weekday desired{to_boost_weekday(wd)};
    const std::int32_t f{static_cast<std::int32_t>(first.day_of_week().as_number())};
    const std::int32_t d{static_cast<std::int32_t>(desired.as_number())};
    const std::int32_t first_offset{static_cast<std::int32_t>(((d - f) + 7) % 7)};
    const std::int32_t day_num{static_cast<std::int32_t>((1 + first_offset) + (7 * (n - 1)))};
    return boost::gregorian::date{static_cast<int>(year), static_cast<int>(month), static_cast<int>(day_num)};
}

boost::gregorian::date last_weekday_in_month(std::int32_t year, std::int32_t month, weekday wd)
{
    const std::int32_t last_dom{
        static_cast<std::int32_t>(boost::gregorian::gregorian_calendar::end_of_month_day(static_cast<int>(year), static_cast<int>(month)))
    };
    const boost::gregorian::date last_date{static_cast<int>(year), static_cast<int>(month), static_cast<int>(last_dom)};
    const boost::gregorian::greg_weekday desired{to_boost_weekday(wd)};
    const std::int32_t lw{static_cast<std::int32_t>(last_date.day_of_week().as_number())};
    const std::int32_t dw{static_cast<std::int32_t>(desired.as_number())};
    const std::int32_t back_offset{static_cast<std::int32_t>(((lw - dw) + 7) % 7)};
    const std::int32_t target_dom{static_cast<std::int32_t>((last_dom - static_cast<std::int32_t>(back_offset)))};
    return boost::gregorian::date{static_cast<int>(year), static_cast<int>(month), static_cast<int>(target_dom)};
}

}  // namespace

scheduler::scheduler(std::int32_t year, std::int32_t month) noexcept
    : year_{year}
    , month_{month}
{
}

boost::gregorian::date scheduler::day(weekday wd, schedule sched) const
{
    if (sched == schedule::teenth) {
        return teenth_weekday(year_, month_, wd);
    }

    if ((sched == schedule::first) || (sched == schedule::second) || (sched == schedule::third) || (sched == schedule::fourth)) {
        std::int32_t n = 1;
        if (sched == schedule::second) {
            n = 2;
        } else if (sched == schedule::third) {
            n = 3;
        } else if (sched == schedule::fourth) {
            n = 4;
        } else {
            n = 1;
        }
        return nth_weekday_in_month(year_, month_, wd, n);
    }

    // schedule::last
    return last_weekday_in_month(year_, month_, wd);
}

// teenth
boost::gregorian::date scheduler::monteenth() const { return day(weekday::monday, schedule::teenth); }
boost::gregorian::date scheduler::tuesteenth() const { return day(weekday::tuesday, schedule::teenth); }
boost::gregorian::date scheduler::wednesteenth() const { return day(weekday::wednesday, schedule::teenth); }
boost::gregorian::date scheduler::thursteenth() const { return day(weekday::thursday, schedule::teenth); }
boost::gregorian::date scheduler::friteenth() const { return day(weekday::friday, schedule::teenth); }
boost::gregorian::date scheduler::saturteenth() const { return day(weekday::saturday, schedule::teenth); }
boost::gregorian::date scheduler::sunteenth() const { return day(weekday::sunday, schedule::teenth); }

// first
boost::gregorian::date scheduler::first_monday() const { return day(weekday::monday, schedule::first); }
boost::gregorian::date scheduler::first_tuesday() const { return day(weekday::tuesday, schedule::first); }
boost::gregorian::date scheduler::first_wednesday() const { return day(weekday::wednesday, schedule::first); }
boost::gregorian::date scheduler::first_thursday() const { return day(weekday::thursday, schedule::first); }
boost::gregorian::date scheduler::first_friday() const { return day(weekday::friday, schedule::first); }
boost::gregorian::date scheduler::first_saturday() const { return day(weekday::saturday, schedule::first); }
boost::gregorian::date scheduler::first_sunday() const { return day(weekday::sunday, schedule::first); }

// second
boost::gregorian::date scheduler::second_monday() const { return day(weekday::monday, schedule::second); }
boost::gregorian::date scheduler::second_tuesday() const { return day(weekday::tuesday, schedule::second); }
boost::gregorian::date scheduler::second_wednesday() const { return day(weekday::wednesday, schedule::second); }
boost::gregorian::date scheduler::second_thursday() const { return day(weekday::thursday, schedule::second); }
boost::gregorian::date scheduler::second_friday() const { return day(weekday::friday, schedule::second); }
boost::gregorian::date scheduler::second_saturday() const { return day(weekday::saturday, schedule::second); }
boost::gregorian::date scheduler::second_sunday() const { return day(weekday::sunday, schedule::second); }

// third
boost::gregorian::date scheduler::third_monday() const { return day(weekday::monday, schedule::third); }
boost::gregorian::date scheduler::third_tuesday() const { return day(weekday::tuesday, schedule::third); }
boost::gregorian::date scheduler::third_wednesday() const { return day(weekday::wednesday, schedule::third); }
boost::gregorian::date scheduler::third_thursday() const { return day(weekday::thursday, schedule::third); }
boost::gregorian::date scheduler::third_friday() const { return day(weekday::friday, schedule::third); }
boost::gregorian::date scheduler::third_saturday() const { return day(weekday::saturday, schedule::third); }
boost::gregorian::date scheduler::third_sunday() const { return day(weekday::sunday, schedule::third); }

// fourth
boost::gregorian::date scheduler::fourth_monday() const { return day(weekday::monday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_tuesday() const { return day(weekday::tuesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_wednesday() const { return day(weekday::wednesday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_thursday() const { return day(weekday::thursday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_friday() const { return day(weekday::friday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_saturday() const { return day(weekday::saturday, schedule::fourth); }
boost::gregorian::date scheduler::fourth_sunday() const { return day(weekday::sunday, schedule::fourth); }

// last
boost::gregorian::date scheduler::last_monday() const { return day(weekday::monday, schedule::last); }
boost::gregorian::date scheduler::last_tuesday() const { return day(weekday::tuesday, schedule::last); }
boost::gregorian::date scheduler::last_wednesday() const { return day(weekday::wednesday, schedule::last); }
boost::gregorian::date scheduler::last_thursday() const { return day(weekday::thursday, schedule::last); }
boost::gregorian::date scheduler::last_friday() const { return day(weekday::friday, schedule::last); }
boost::gregorian::date scheduler::last_saturday() const { return day(weekday::saturday, schedule::last); }
boost::gregorian::date scheduler::last_sunday() const { return day(weekday::sunday, schedule::last); }

}  // namespace meetup
