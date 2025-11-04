#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

namespace {
    [[nodiscard]] auto forward_diff(std::int32_t target_wd, std::int32_t current_wd) -> std::int32_t {
        const std::int32_t delta = ((target_wd + 7) - current_wd);
        const std::int32_t mod = (delta % 7);
        return mod;
    }

    [[nodiscard]] auto backward_diff(std::int32_t current_wd, std::int32_t target_wd) -> std::int32_t {
        const std::int32_t delta = ((current_wd + 7) - target_wd);
        const std::int32_t mod = (delta % 7);
        return mod;
    }
}  // namespace

scheduler::scheduler(boost::gregorian::months_of_year month, std::int32_t year)
    : month_(month), year_(year) {}

auto scheduler::teenth(boost::date_time::weekdays wd) const -> boost::gregorian::date {
    const boost::gregorian::date base{year_, month_, 13};
    const std::int32_t base_wd = static_cast<std::int32_t>(base.day_of_week().as_number()); // 0=Sun..6=Sat
    const std::int32_t target_wd = static_cast<std::int32_t>(wd);
    const std::int32_t delta = forward_diff(target_wd, base_wd);
    const boost::gregorian::date result = base + boost::gregorian::days(static_cast<long>(delta));
    return result;
}

auto scheduler::nth(std::uint32_t n, boost::date_time::weekdays wd) const -> boost::gregorian::date {
    const boost::gregorian::date first{year_, month_, 1};
    const std::int32_t first_wd = static_cast<std::int32_t>(first.day_of_week().as_number()); // 0=Sun..6=Sat
    const std::int32_t target_wd = static_cast<std::int32_t>(wd);
    const std::int32_t offset = forward_diff(target_wd, first_wd);
    const std::int32_t day = (1 + offset) + (static_cast<std::int32_t>((n - 1U)) * 7);
    const boost::gregorian::date result{year_, month_, day};
    return result;
}

auto scheduler::last(boost::date_time::weekdays wd) const -> boost::gregorian::date {
    const std::uint16_t last_dom =
        boost::gregorian::gregorian_calendar::end_of_month_day(year_, month_);
    const boost::gregorian::date end{year_, month_, last_dom};
    const std::int32_t end_wd = static_cast<std::int32_t>(end.day_of_week().as_number()); // 0=Sun..6=Sat
    const std::int32_t target_wd = static_cast<std::int32_t>(wd);
    const std::int32_t back = backward_diff(end_wd, target_wd);
    const boost::gregorian::date result = end - boost::gregorian::days(static_cast<long>(back));
    return result;
}

// teenth methods
auto scheduler::monteenth() const -> boost::gregorian::date {
    return teenth(boost::date_time::Monday);
}
auto scheduler::tuesteenth() const -> boost::gregorian::date {
    return teenth(boost::date_time::Tuesday);
}
auto scheduler::wednesteenth() const -> boost::gregorian::date {
    return teenth(boost::date_time::Wednesday);
}
auto scheduler::thursteenth() const -> boost::gregorian::date {
    return teenth(boost::date_time::Thursday);
}
auto scheduler::friteenth() const -> boost::gregorian::date {
    return teenth(boost::date_time::Friday);
}
auto scheduler::saturteenth() const -> boost::gregorian::date {
    return teenth(boost::date_time::Saturday);
}
auto scheduler::sunteenth() const -> boost::gregorian::date {
    return teenth(boost::date_time::Sunday);
}

// first
auto scheduler::first_monday() const -> boost::gregorian::date {
    return nth(1U, boost::date_time::Monday);
}
auto scheduler::first_tuesday() const -> boost::gregorian::date {
    return nth(1U, boost::date_time::Tuesday);
}
auto scheduler::first_wednesday() const -> boost::gregorian::date {
    return nth(1U, boost::date_time::Wednesday);
}
auto scheduler::first_thursday() const -> boost::gregorian::date {
    return nth(1U, boost::date_time::Thursday);
}
auto scheduler::first_friday() const -> boost::gregorian::date {
    return nth(1U, boost::date_time::Friday);
}
auto scheduler::first_saturday() const -> boost::gregorian::date {
    return nth(1U, boost::date_time::Saturday);
}
auto scheduler::first_sunday() const -> boost::gregorian::date {
    return nth(1U, boost::date_time::Sunday);
}

// second
auto scheduler::second_monday() const -> boost::gregorian::date {
    return nth(2U, boost::date_time::Monday);
}
auto scheduler::second_tuesday() const -> boost::gregorian::date {
    return nth(2U, boost::date_time::Tuesday);
}
auto scheduler::second_wednesday() const -> boost::gregorian::date {
    return nth(2U, boost::date_time::Wednesday);
}
auto scheduler::second_thursday() const -> boost::gregorian::date {
    return nth(2U, boost::date_time::Thursday);
}
auto scheduler::second_friday() const -> boost::gregorian::date {
    return nth(2U, boost::date_time::Friday);
}
auto scheduler::second_saturday() const -> boost::gregorian::date {
    return nth(2U, boost::date_time::Saturday);
}
auto scheduler::second_sunday() const -> boost::gregorian::date {
    return nth(2U, boost::date_time::Sunday);
}

// third
auto scheduler::third_monday() const -> boost::gregorian::date {
    return nth(3U, boost::date_time::Monday);
}
auto scheduler::third_tuesday() const -> boost::gregorian::date {
    return nth(3U, boost::date_time::Tuesday);
}
auto scheduler::third_wednesday() const -> boost::gregorian::date {
    return nth(3U, boost::date_time::Wednesday);
}
auto scheduler::third_thursday() const -> boost::gregorian::date {
    return nth(3U, boost::date_time::Thursday);
}
auto scheduler::third_friday() const -> boost::gregorian::date {
    return nth(3U, boost::date_time::Friday);
}
auto scheduler::third_saturday() const -> boost::gregorian::date {
    return nth(3U, boost::date_time::Saturday);
}
auto scheduler::third_sunday() const -> boost::gregorian::date {
    return nth(3U, boost::date_time::Sunday);
}

// fourth
auto scheduler::fourth_monday() const -> boost::gregorian::date {
    return nth(4U, boost::date_time::Monday);
}
auto scheduler::fourth_tuesday() const -> boost::gregorian::date {
    return nth(4U, boost::date_time::Tuesday);
}
auto scheduler::fourth_wednesday() const -> boost::gregorian::date {
    return nth(4U, boost::date_time::Wednesday);
}
auto scheduler::fourth_thursday() const -> boost::gregorian::date {
    return nth(4U, boost::date_time::Thursday);
}
auto scheduler::fourth_friday() const -> boost::gregorian::date {
    return nth(4U, boost::date_time::Friday);
}
auto scheduler::fourth_saturday() const -> boost::gregorian::date {
    return nth(4U, boost::date_time::Saturday);
}
auto scheduler::fourth_sunday() const -> boost::gregorian::date {
    return nth(4U, boost::date_time::Sunday);
}

// last
auto scheduler::last_monday() const -> boost::gregorian::date {
    return last(boost::date_time::Monday);
}
auto scheduler::last_tuesday() const -> boost::gregorian::date {
    return last(boost::date_time::Tuesday);
}
auto scheduler::last_wednesday() const -> boost::gregorian::date {
    return last(boost::date_time::Wednesday);
}
auto scheduler::last_thursday() const -> boost::gregorian::date {
    return last(boost::date_time::Thursday);
}
auto scheduler::last_friday() const -> boost::gregorian::date {
    return last(boost::date_time::Friday);
}
auto scheduler::last_saturday() const -> boost::gregorian::date {
    return last(boost::date_time::Saturday);
}
auto scheduler::last_sunday() const -> boost::gregorian::date {
    return last(boost::date_time::Sunday);
}

}  // namespace meetup
