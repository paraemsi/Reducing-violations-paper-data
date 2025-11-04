#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using boost::gregorian::date;
using boost::gregorian::greg_weekday;

/* -------------------------------------------------------------------------*/
namespace {

[[nodiscard]] std::uint32_t max_days_in_month(std::uint32_t year,
                                              std::uint32_t month) {
    return static_cast<std::uint32_t>(
        boost::gregorian::gregorian_calendar::end_of_month_day(year, month));
}

}  // namespace
/* -------------------------------------------------------------------------*/

scheduler::scheduler(std::int32_t year, std::uint32_t month) noexcept
    : m_year{year}, m_month{month} {}

/* helpers -----------------------------------------------------------------*/
[[nodiscard]] date scheduler::make_date(std::uint32_t day) const {
    return date{static_cast<date::year_type>(m_year),
                static_cast<date::month_type>(m_month),
                static_cast<date::day_type>(day)};
}

[[nodiscard]] date scheduler::make_teenth(const greg_weekday & wd) const {
    for (std::uint32_t d{13U}; d <= 19U; ++d) {
        date const cur{make_date(d)};
        if (cur.day_of_week() == wd) {
            return cur;
        }
    }
    return make_date(13U); /* logically unreachable */
}

[[nodiscard]] date scheduler::make_nth(const greg_weekday & wd,
                                       std::uint32_t        n) const {
    std::uint32_t count{0U};
    std::uint32_t const last_day{max_days_in_month(static_cast<std::uint32_t>(m_year),
                                                   m_month)};
    for (std::uint32_t d{1U}; d <= last_day; ++d) {
        date const cur{make_date(d)};
        if (cur.day_of_week() == wd) {
            ++count;
            if (count == n) {
                return cur;
            }
        }
    }
    return make_date(1U); /* fallback */
}

[[nodiscard]] date scheduler::make_last(const greg_weekday & wd) const {
    std::uint32_t const last_day{max_days_in_month(static_cast<std::uint32_t>(m_year),
                                                   m_month)};
    for (std::uint32_t d{last_day}; d >= 1U; --d) {
        date const cur{make_date(d)};
        if (cur.day_of_week() == wd) {
            return cur;
        }
        if (d == 1U) {
            break;
        }
    }
    return make_date(1U); /* fallback */
}

/* teenth -------------------------------------------------------------------*/
date scheduler::monteenth() const { return make_teenth(greg_weekday{1}); }
date scheduler::tuesteenth() const { return make_teenth(greg_weekday{2}); }
date scheduler::wednesteenth() const { return make_teenth(greg_weekday{3}); }
date scheduler::thursteenth() const { return make_teenth(greg_weekday{4}); }
date scheduler::friteenth() const { return make_teenth(greg_weekday{5}); }
date scheduler::saturteenth() const { return make_teenth(greg_weekday{6}); }
date scheduler::sunteenth() const { return make_teenth(greg_weekday{0}); }

/* first --------------------------------------------------------------------*/
date scheduler::first_monday() const { return make_nth(greg_weekday{1}, 1U); }
date scheduler::first_tuesday() const { return make_nth(greg_weekday{2}, 1U); }
date scheduler::first_wednesday() const { return make_nth(greg_weekday{3}, 1U); }
date scheduler::first_thursday() const { return make_nth(greg_weekday{4}, 1U); }
date scheduler::first_friday() const { return make_nth(greg_weekday{5}, 1U); }
date scheduler::first_saturday() const { return make_nth(greg_weekday{6}, 1U); }
date scheduler::first_sunday() const { return make_nth(greg_weekday{0}, 1U); }

/* second -------------------------------------------------------------------*/
date scheduler::second_monday() const { return make_nth(greg_weekday{1}, 2U); }
date scheduler::second_tuesday() const { return make_nth(greg_weekday{2}, 2U); }
date scheduler::second_wednesday() const { return make_nth(greg_weekday{3}, 2U); }
date scheduler::second_thursday() const { return make_nth(greg_weekday{4}, 2U); }
date scheduler::second_friday() const { return make_nth(greg_weekday{5}, 2U); }
date scheduler::second_saturday() const { return make_nth(greg_weekday{6}, 2U); }
date scheduler::second_sunday() const { return make_nth(greg_weekday{0}, 2U); }

/* third --------------------------------------------------------------------*/
date scheduler::third_monday() const { return make_nth(greg_weekday{1}, 3U); }
date scheduler::third_tuesday() const { return make_nth(greg_weekday{2}, 3U); }
date scheduler::third_wednesday() const { return make_nth(greg_weekday{3}, 3U); }
date scheduler::third_thursday() const { return make_nth(greg_weekday{4}, 3U); }
date scheduler::third_friday() const { return make_nth(greg_weekday{5}, 3U); }
date scheduler::third_saturday() const { return make_nth(greg_weekday{6}, 3U); }
date scheduler::third_sunday() const { return make_nth(greg_weekday{0}, 3U); }

/* fourth -------------------------------------------------------------------*/
date scheduler::fourth_monday() const { return make_nth(greg_weekday{1}, 4U); }
date scheduler::fourth_tuesday() const { return make_nth(greg_weekday{2}, 4U); }
date scheduler::fourth_wednesday() const { return make_nth(greg_weekday{3}, 4U); }
date scheduler::fourth_thursday() const { return make_nth(greg_weekday{4}, 4U); }
date scheduler::fourth_friday() const { return make_nth(greg_weekday{5}, 4U); }
date scheduler::fourth_saturday() const { return make_nth(greg_weekday{6}, 4U); }
date scheduler::fourth_sunday() const { return make_nth(greg_weekday{0}, 4U); }

/* last ---------------------------------------------------------------------*/
date scheduler::last_monday() const { return make_last(greg_weekday{1}); }
date scheduler::last_tuesday() const { return make_last(greg_weekday{2}); }
date scheduler::last_wednesday() const { return make_last(greg_weekday{3}); }
date scheduler::last_thursday() const { return make_last(greg_weekday{4}); }
date scheduler::last_friday() const { return make_last(greg_weekday{5}); }
date scheduler::last_saturday() const { return make_last(greg_weekday{6}); }
date scheduler::last_sunday() const { return make_last(greg_weekday{0}); }

}  // namespace meetup

#if 0
std::chrono::year_month_day
scheduler::make_nth(const std::chrono::weekday & wd,
                    std::uint32_t                 n) const {
    using std::chrono::weekday;
    using std::chrono::year_month_day;
    using std::chrono::sys_days;

    std::uint32_t count{static_cast<std::uint32_t>(0U)};

    for (std::uint32_t d{static_cast<std::uint32_t>(1U)};
         d <= static_cast<std::uint32_t>(31U); ++d) {
        year_month_day const ymd{m_year_month / d};
        if (!(ymd.ok())) {
            break;
        }
        if ((weekday{sys_days{ymd}}) == wd) {
            ++count;
            if (count == n) {
                return ymd;
            }
        }
    }

    /* fallback – should never be hit for valid input */
    return m_year_month / static_cast<std::uint32_t>(1U);
}

std::chrono::year_month_day
scheduler::make_last(const std::chrono::weekday & wd) const {
    using std::chrono::weekday;
    using std::chrono::year_month_day;
    using std::chrono::sys_days;

    for (std::uint32_t d{static_cast<std::uint32_t>(31U)};
         d > static_cast<std::uint32_t>(0U); --d) {
        year_month_day const ymd{m_year_month / d};
        if (!(ymd.ok())) {
            continue;
        }
        if ((weekday{sys_days{ymd}}) == wd) {
            return ymd;
        }
    }

    /* fallback */
    return m_year_month / static_cast<std::uint32_t>(1U);
}

/* teenth -------------------------------------------------------------------*/
std::chrono::year_month_day scheduler::monteenth() const {
    return make_teenth(std::chrono::Monday);
}
std::chrono::year_month_day scheduler::tuesteenth() const {
    return make_teenth(std::chrono::Tuesday);
}
std::chrono::year_month_day scheduler::wednesteenth() const {
    return make_teenth(std::chrono::Wednesday);
}
std::chrono::year_month_day scheduler::thursteenth() const {
    return make_teenth(std::chrono::Thursday);
}
std::chrono::year_month_day scheduler::friteenth() const {
    return make_teenth(std::chrono::Friday);
}
std::chrono::year_month_day scheduler::saturteenth() const {
    return make_teenth(std::chrono::Saturday);
}
std::chrono::year_month_day scheduler::sunteenth() const {
    return make_teenth(std::chrono::Sunday);
}

/* first --------------------------------------------------------------------*/
std::chrono::year_month_day scheduler::first_monday() const {
    return make_nth(std::chrono::Monday, static_cast<std::uint32_t>(1U));
}
std::chrono::year_month_day scheduler::first_tuesday() const {
    return make_nth(std::chrono::Tuesday, static_cast<std::uint32_t>(1U));
}
std::chrono::year_month_day scheduler::first_wednesday() const {
    return make_nth(std::chrono::Wednesday, static_cast<std::uint32_t>(1U));
}
std::chrono::year_month_day scheduler::first_thursday() const {
    return make_nth(std::chrono::Thursday, static_cast<std::uint32_t>(1U));
}
std::chrono::year_month_day scheduler::first_friday() const {
    return make_nth(std::chrono::Friday, static_cast<std::uint32_t>(1U));
}
std::chrono::year_month_day scheduler::first_saturday() const {
    return make_nth(std::chrono::Saturday, static_cast<std::uint32_t>(1U));
}
std::chrono::year_month_day scheduler::first_sunday() const {
    return make_nth(std::chrono::Sunday, static_cast<std::uint32_t>(1U));
}

/* second -------------------------------------------------------------------*/
std::chrono::year_month_day scheduler::second_monday() const {
    return make_nth(std::chrono::Monday, static_cast<std::uint32_t>(2U));
}
std::chrono::year_month_day scheduler::second_tuesday() const {
    return make_nth(std::chrono::Tuesday, static_cast<std::uint32_t>(2U));
}
std::chrono::year_month_day scheduler::second_wednesday() const {
    return make_nth(std::chrono::Wednesday, static_cast<std::uint32_t>(2U));
}
std::chrono::year_month_day scheduler::second_thursday() const {
    return make_nth(std::chrono::Thursday, static_cast<std::uint32_t>(2U));
}
std::chrono::year_month_day scheduler::second_friday() const {
    return make_nth(std::chrono::Friday, static_cast<std::uint32_t>(2U));
}
std::chrono::year_month_day scheduler::second_saturday() const {
    return make_nth(std::chrono::Saturday, static_cast<std::uint32_t>(2U));
}
std::chrono::year_month_day scheduler::second_sunday() const {
    return make_nth(std::chrono::Sunday, static_cast<std::uint32_t>(2U));
}

/* third --------------------------------------------------------------------*/
std::chrono::year_month_day scheduler::third_monday() const {
    return make_nth(std::chrono::Monday, static_cast<std::uint32_t>(3U));
}
std::chrono::year_month_day scheduler::third_tuesday() const {
    return make_nth(std::chrono::Tuesday, static_cast<std::uint32_t>(3U));
}
std::chrono::year_month_day scheduler::third_wednesday() const {
    return make_nth(std::chrono::Wednesday, static_cast<std::uint32_t>(3U));
}
std::chrono::year_month_day scheduler::third_thursday() const {
    return make_nth(std::chrono::Thursday, static_cast<std::uint32_t>(3U));
}
std::chrono::year_month_day scheduler::third_friday() const {
    return make_nth(std::chrono::Friday, static_cast<std::uint32_t>(3U));
}
std::chrono::year_month_day scheduler::third_saturday() const {
    return make_nth(std::chrono::Saturday, static_cast<std::uint32_t>(3U));
}
std::chrono::year_month_day scheduler::third_sunday() const {
    return make_nth(std::chrono::Sunday, static_cast<std::uint32_t>(3U));
}

/* fourth -------------------------------------------------------------------*/
std::chrono::year_month_day scheduler::fourth_monday() const {
    return make_nth(std::chrono::Monday, static_cast<std::uint32_t>(4U));
}
std::chrono::year_month_day scheduler::fourth_tuesday() const {
    return make_nth(std::chrono::Tuesday, static_cast<std::uint32_t>(4U));
}
std::chrono::year_month_day scheduler::fourth_wednesday() const {
    return make_nth(std::chrono::Wednesday, static_cast<std::uint32_t>(4U));
}
std::chrono::year_month_day scheduler::fourth_thursday() const {
    return make_nth(std::chrono::Thursday, static_cast<std::uint32_t>(4U));
}
std::chrono::year_month_day scheduler::fourth_friday() const {
    return make_nth(std::chrono::Friday, static_cast<std::uint32_t>(4U));
}
std::chrono::year_month_day scheduler::fourth_saturday() const {
    return make_nth(std::chrono::Saturday, static_cast<std::uint32_t>(4U));
}
std::chrono::year_month_day scheduler::fourth_sunday() const {
    return make_nth(std::chrono::Sunday, static_cast<std::uint32_t>(4U));
}

/* last ---------------------------------------------------------------------*/
std::chrono::year_month_day scheduler::last_monday() const {
    return make_last(std::chrono::Monday);
}
std::chrono::year_month_day scheduler::last_tuesday() const {
    return make_last(std::chrono::Tuesday);
}
std::chrono::year_month_day scheduler::last_wednesday() const {
    return make_last(std::chrono::Wednesday);
}
std::chrono::year_month_day scheduler::last_thursday() const {
    return make_last(std::chrono::Thursday);
}
std::chrono::year_month_day scheduler::last_friday() const {
    return make_last(std::chrono::Friday);
}
std::chrono::year_month_day scheduler::last_saturday() const {
    return make_last(std::chrono::Saturday);
}
std::chrono::year_month_day scheduler::last_sunday() const {
    return make_last(std::chrono::Sunday);
}

}  // namespace meetup
#endif /* legacy chrono implementation */
