#include "meetup.h"

namespace meetup {

scheduler::scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept
    : month_(month), year_(year) {}

// Private helpers

auto scheduler::first_of_month() const -> date_type {
    return date_type(static_cast<int>(year_), month_, static_cast<int>(1));
}

auto scheduler::teenth_weekday(boost::date_time::weekdays w) const -> date_type {
    date_type d(static_cast<int>(year_), static_cast<int>(month_), static_cast<int>(13));
    for (std::uint32_t i = static_cast<std::uint32_t>(0U);
         i < static_cast<std::uint32_t>(7U);
         i = static_cast<std::uint32_t>(i + static_cast<std::uint32_t>(1U)))
    {
        const std::uint32_t wd = static_cast<std::uint32_t>(d.day_of_week().as_number());
        if (wd == static_cast<std::uint32_t>(w)) {
            return d;
        }
        d = d + boost::gregorian::days(static_cast<int>(1));
    }
    return d;
}

auto scheduler::nth_weekday(boost::date_time::weekdays w, std::uint32_t n) const -> date_type {
    date_type d = first_of_month();
    while ((static_cast<std::uint32_t>(d.day_of_week().as_number())) != (static_cast<std::uint32_t>(w))) {
        d = d + boost::gregorian::days(static_cast<int>(1));
    }
    std::uint32_t k = static_cast<std::uint32_t>(0U);
    const std::uint32_t reps = static_cast<std::uint32_t>(n - static_cast<std::uint32_t>(1U));
    while (k < reps) {
        d = d + boost::gregorian::days(static_cast<int>(7));
        k = static_cast<std::uint32_t>(k + static_cast<std::uint32_t>(1U));
    }
    return d;
}

auto scheduler::last_weekday(boost::date_time::weekdays w) const -> date_type {
    // Compute the last day of the month: first day of next month minus one day
    const std::int32_t y = year_;
    const std::int32_t m = static_cast<std::int32_t>(month_);
    std::int32_t next_y = y;
    std::int32_t next_m = static_cast<std::int32_t>(m + static_cast<std::int32_t>(1));
    if (next_m > static_cast<std::int32_t>(12)) {
        next_m = static_cast<std::int32_t>(1);
        next_y = static_cast<std::int32_t>(y + static_cast<std::int32_t>(1));
    }

    date_type d_last(static_cast<int>(next_y), static_cast<int>(next_m), static_cast<int>(1));
    d_last = d_last - boost::gregorian::days(static_cast<int>(1));

    const std::uint32_t wl = static_cast<std::uint32_t>(d_last.day_of_week().as_number());
    const std::uint32_t wt = static_cast<std::uint32_t>(w);
    const std::uint32_t back =
        static_cast<std::uint32_t>((wl + (static_cast<std::uint32_t>(7U) - wt)) % static_cast<std::uint32_t>(7U));

    date_type result = d_last;
    std::uint32_t i = static_cast<std::uint32_t>(0U);
    while (i < back) {
        result = result - boost::gregorian::days(static_cast<int>(1));
        i = static_cast<std::uint32_t>(i + static_cast<std::uint32_t>(1U));
    }
    return result;
}

// Teenth
auto scheduler::monteenth() const -> date_type { return teenth_weekday(boost::date_time::Monday); }
auto scheduler::tuesteenth() const -> date_type { return teenth_weekday(boost::date_time::Tuesday); }
auto scheduler::wednesteenth() const -> date_type { return teenth_weekday(boost::date_time::Wednesday); }
auto scheduler::thursteenth() const -> date_type { return teenth_weekday(boost::date_time::Thursday); }
auto scheduler::friteenth() const -> date_type { return teenth_weekday(boost::date_time::Friday); }
auto scheduler::saturteenth() const -> date_type { return teenth_weekday(boost::date_time::Saturday); }
auto scheduler::sunteenth() const -> date_type { return teenth_weekday(boost::date_time::Sunday); }

// First
auto scheduler::first_monday() const -> date_type { return nth_weekday(boost::date_time::Monday, static_cast<std::uint32_t>(1U)); }
auto scheduler::first_tuesday() const -> date_type { return nth_weekday(boost::date_time::Tuesday, static_cast<std::uint32_t>(1U)); }
auto scheduler::first_wednesday() const -> date_type { return nth_weekday(boost::date_time::Wednesday, static_cast<std::uint32_t>(1U)); }
auto scheduler::first_thursday() const -> date_type { return nth_weekday(boost::date_time::Thursday, static_cast<std::uint32_t>(1U)); }
auto scheduler::first_friday() const -> date_type { return nth_weekday(boost::date_time::Friday, static_cast<std::uint32_t>(1U)); }
auto scheduler::first_saturday() const -> date_type { return nth_weekday(boost::date_time::Saturday, static_cast<std::uint32_t>(1U)); }
auto scheduler::first_sunday() const -> date_type { return nth_weekday(boost::date_time::Sunday, static_cast<std::uint32_t>(1U)); }

// Second
auto scheduler::second_monday() const -> date_type { return nth_weekday(boost::date_time::Monday, static_cast<std::uint32_t>(2U)); }
auto scheduler::second_tuesday() const -> date_type { return nth_weekday(boost::date_time::Tuesday, static_cast<std::uint32_t>(2U)); }
auto scheduler::second_wednesday() const -> date_type { return nth_weekday(boost::date_time::Wednesday, static_cast<std::uint32_t>(2U)); }
auto scheduler::second_thursday() const -> date_type { return nth_weekday(boost::date_time::Thursday, static_cast<std::uint32_t>(2U)); }
auto scheduler::second_friday() const -> date_type { return nth_weekday(boost::date_time::Friday, static_cast<std::uint32_t>(2U)); }
auto scheduler::second_saturday() const -> date_type { return nth_weekday(boost::date_time::Saturday, static_cast<std::uint32_t>(2U)); }
auto scheduler::second_sunday() const -> date_type { return nth_weekday(boost::date_time::Sunday, static_cast<std::uint32_t>(2U)); }

// Third
auto scheduler::third_monday() const -> date_type { return nth_weekday(boost::date_time::Monday, static_cast<std::uint32_t>(3U)); }
auto scheduler::third_tuesday() const -> date_type { return nth_weekday(boost::date_time::Tuesday, static_cast<std::uint32_t>(3U)); }
auto scheduler::third_wednesday() const -> date_type { return nth_weekday(boost::date_time::Wednesday, static_cast<std::uint32_t>(3U)); }
auto scheduler::third_thursday() const -> date_type { return nth_weekday(boost::date_time::Thursday, static_cast<std::uint32_t>(3U)); }
auto scheduler::third_friday() const -> date_type { return nth_weekday(boost::date_time::Friday, static_cast<std::uint32_t>(3U)); }
auto scheduler::third_saturday() const -> date_type { return nth_weekday(boost::date_time::Saturday, static_cast<std::uint32_t>(3U)); }
auto scheduler::third_sunday() const -> date_type { return nth_weekday(boost::date_time::Sunday, static_cast<std::uint32_t>(3U)); }

// Fourth
auto scheduler::fourth_monday() const -> date_type { return nth_weekday(boost::date_time::Monday, static_cast<std::uint32_t>(4U)); }
auto scheduler::fourth_tuesday() const -> date_type { return nth_weekday(boost::date_time::Tuesday, static_cast<std::uint32_t>(4U)); }
auto scheduler::fourth_wednesday() const -> date_type { return nth_weekday(boost::date_time::Wednesday, static_cast<std::uint32_t>(4U)); }
auto scheduler::fourth_thursday() const -> date_type { return nth_weekday(boost::date_time::Thursday, static_cast<std::uint32_t>(4U)); }
auto scheduler::fourth_friday() const -> date_type { return nth_weekday(boost::date_time::Friday, static_cast<std::uint32_t>(4U)); }
auto scheduler::fourth_saturday() const -> date_type { return nth_weekday(boost::date_time::Saturday, static_cast<std::uint32_t>(4U)); }
auto scheduler::fourth_sunday() const -> date_type { return nth_weekday(boost::date_time::Sunday, static_cast<std::uint32_t>(4U)); }

// Last
auto scheduler::last_monday() const -> date_type { return last_weekday(boost::date_time::Monday); }
auto scheduler::last_tuesday() const -> date_type { return last_weekday(boost::date_time::Tuesday); }
auto scheduler::last_wednesday() const -> date_type { return last_weekday(boost::date_time::Wednesday); }
auto scheduler::last_thursday() const -> date_type { return last_weekday(boost::date_time::Thursday); }
auto scheduler::last_friday() const -> date_type { return last_weekday(boost::date_time::Friday); }
auto scheduler::last_saturday() const -> date_type { return last_weekday(boost::date_time::Saturday); }
auto scheduler::last_sunday() const -> date_type { return last_weekday(boost::date_time::Sunday); }

}  // namespace meetup
