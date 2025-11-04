#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

static std::int32_t days_in_month(std::int32_t year, std::int32_t month)
{
    // month is expected to be in range 1..12
    switch (month) {
        case 1: {
            return 31;
        }
        case 2: {
            const bool leap = ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0));
            return (leap ? 29 : 28);
        }
        case 3: {
            return 31;
        }
        case 4: {
            return 30;
        }
        case 5: {
            return 31;
        }
        case 6: {
            return 30;
        }
        case 7: {
            return 31;
        }
        case 8: {
            return 31;
        }
        case 9: {
            return 30;
        }
        case 10: {
            return 31;
        }
        case 11: {
            return 30;
        }
        case 12: {
            return 31;
        }
        default: {
            throw std::out_of_range("month out of range");
        }
    }
}

static std::int32_t month_offset(std::int32_t month)
{
    // Offsets for Sakamoto's algorithm: Jan..Dec -> {0,3,2,5,0,3,5,1,4,6,2,4}
    switch (month) {
        case 1: {
            return 0;
        }
        case 2: {
            return 3;
        }
        case 3: {
            return 2;
        }
        case 4: {
            return 5;
        }
        case 5: {
            return 0;
        }
        case 6: {
            return 3;
        }
        case 7: {
            return 5;
        }
        case 8: {
            return 1;
        }
        case 9: {
            return 4;
        }
        case 10: {
            return 6;
        }
        case 11: {
            return 2;
        }
        case 12: {
            return 4;
        }
        default: {
            throw std::out_of_range("month out of range");
        }
    }
}

static weekday weekday_from_ymd(std::int32_t year, std::int32_t month, std::int32_t day)
{
    // Sakamoto's algorithm returns 0=Sunday..6=Saturday
    std::int32_t y = year;
    if (month < 3) {
        y = (y - 1);
    } else {
        // no-op
    }

    const std::int32_t t = month_offset(month);
    const std::int32_t w = (y + (y / 4) - (y / 100) + (y / 400) + t + day) % 7;

    switch (w) {
        case 0: {
            return weekday::sunday;
        }
        case 1: {
            return weekday::monday;
        }
        case 2: {
            return weekday::tuesday;
        }
        case 3: {
            return weekday::wednesday;
        }
        case 4: {
            return weekday::thursday;
        }
        case 5: {
            return weekday::friday;
        }
        case 6: {
            return weekday::saturday;
        }
        default: {
            // Unreachable, but keep a safe default
            return weekday::monday;
        }
    }
}

static bool weekdays_equal(weekday a, weekday b)
{
    return (a == b);
}

scheduler::scheduler(std::int32_t year, std::int32_t month) noexcept
    : y_(year), m_(month)
{
}

std::int32_t scheduler::year() const noexcept
{
    return y_;
}

std::int32_t scheduler::month() const noexcept
{
    return m_;
}

static boost::gregorian::date make_date(std::int32_t y, std::int32_t m, std::int32_t d)
{
    return boost::gregorian::date(static_cast<int>(y), static_cast<int>(m), static_cast<int>(d));
}

// Teenth weekday helpers
boost::gregorian::date scheduler::monteenth() const
{
    return make_date(y_, m_, day(weekday::monday, schedule::teenth));
}
boost::gregorian::date scheduler::tuesteenth() const
{
    return make_date(y_, m_, day(weekday::tuesday, schedule::teenth));
}
boost::gregorian::date scheduler::wednesteenth() const
{
    return make_date(y_, m_, day(weekday::wednesday, schedule::teenth));
}
boost::gregorian::date scheduler::thursteenth() const
{
    return make_date(y_, m_, day(weekday::thursday, schedule::teenth));
}
boost::gregorian::date scheduler::friteenth() const
{
    return make_date(y_, m_, day(weekday::friday, schedule::teenth));
}
boost::gregorian::date scheduler::saturteenth() const
{
    return make_date(y_, m_, day(weekday::saturday, schedule::teenth));
}
boost::gregorian::date scheduler::sunteenth() const
{
    return make_date(y_, m_, day(weekday::sunday, schedule::teenth));
}

// First weekday helpers
boost::gregorian::date scheduler::first_monday() const
{
    return make_date(y_, m_, day(weekday::monday, schedule::first));
}
boost::gregorian::date scheduler::first_tuesday() const
{
    return make_date(y_, m_, day(weekday::tuesday, schedule::first));
}
boost::gregorian::date scheduler::first_wednesday() const
{
    return make_date(y_, m_, day(weekday::wednesday, schedule::first));
}
boost::gregorian::date scheduler::first_thursday() const
{
    return make_date(y_, m_, day(weekday::thursday, schedule::first));
}
boost::gregorian::date scheduler::first_friday() const
{
    return make_date(y_, m_, day(weekday::friday, schedule::first));
}
boost::gregorian::date scheduler::first_saturday() const
{
    return make_date(y_, m_, day(weekday::saturday, schedule::first));
}
boost::gregorian::date scheduler::first_sunday() const
{
    return make_date(y_, m_, day(weekday::sunday, schedule::first));
}

// Second weekday helpers
boost::gregorian::date scheduler::second_monday() const
{
    return make_date(y_, m_, day(weekday::monday, schedule::second));
}
boost::gregorian::date scheduler::second_tuesday() const
{
    return make_date(y_, m_, day(weekday::tuesday, schedule::second));
}
boost::gregorian::date scheduler::second_wednesday() const
{
    return make_date(y_, m_, day(weekday::wednesday, schedule::second));
}
boost::gregorian::date scheduler::second_thursday() const
{
    return make_date(y_, m_, day(weekday::thursday, schedule::second));
}
boost::gregorian::date scheduler::second_friday() const
{
    return make_date(y_, m_, day(weekday::friday, schedule::second));
}
boost::gregorian::date scheduler::second_saturday() const
{
    return make_date(y_, m_, day(weekday::saturday, schedule::second));
}
boost::gregorian::date scheduler::second_sunday() const
{
    return make_date(y_, m_, day(weekday::sunday, schedule::second));
}

// Third weekday helpers
boost::gregorian::date scheduler::third_monday() const
{
    return make_date(y_, m_, day(weekday::monday, schedule::third));
}
boost::gregorian::date scheduler::third_tuesday() const
{
    return make_date(y_, m_, day(weekday::tuesday, schedule::third));
}
boost::gregorian::date scheduler::third_wednesday() const
{
    return make_date(y_, m_, day(weekday::wednesday, schedule::third));
}
boost::gregorian::date scheduler::third_thursday() const
{
    return make_date(y_, m_, day(weekday::thursday, schedule::third));
}
boost::gregorian::date scheduler::third_friday() const
{
    return make_date(y_, m_, day(weekday::friday, schedule::third));
}
boost::gregorian::date scheduler::third_saturday() const
{
    return make_date(y_, m_, day(weekday::saturday, schedule::third));
}
boost::gregorian::date scheduler::third_sunday() const
{
    return make_date(y_, m_, day(weekday::sunday, schedule::third));
}

// Fourth weekday helpers
boost::gregorian::date scheduler::fourth_monday() const
{
    return make_date(y_, m_, day(weekday::monday, schedule::fourth));
}
boost::gregorian::date scheduler::fourth_tuesday() const
{
    return make_date(y_, m_, day(weekday::tuesday, schedule::fourth));
}
boost::gregorian::date scheduler::fourth_wednesday() const
{
    return make_date(y_, m_, day(weekday::wednesday, schedule::fourth));
}
boost::gregorian::date scheduler::fourth_thursday() const
{
    return make_date(y_, m_, day(weekday::thursday, schedule::fourth));
}
boost::gregorian::date scheduler::fourth_friday() const
{
    return make_date(y_, m_, day(weekday::friday, schedule::fourth));
}
boost::gregorian::date scheduler::fourth_saturday() const
{
    return make_date(y_, m_, day(weekday::saturday, schedule::fourth));
}
boost::gregorian::date scheduler::fourth_sunday() const
{
    return make_date(y_, m_, day(weekday::sunday, schedule::fourth));
}

// Last weekday helpers
boost::gregorian::date scheduler::last_monday() const
{
    return make_date(y_, m_, day(weekday::monday, schedule::last));
}
boost::gregorian::date scheduler::last_tuesday() const
{
    return make_date(y_, m_, day(weekday::tuesday, schedule::last));
}
boost::gregorian::date scheduler::last_wednesday() const
{
    return make_date(y_, m_, day(weekday::wednesday, schedule::last));
}
boost::gregorian::date scheduler::last_thursday() const
{
    return make_date(y_, m_, day(weekday::thursday, schedule::last));
}
boost::gregorian::date scheduler::last_friday() const
{
    return make_date(y_, m_, day(weekday::friday, schedule::last));
}
boost::gregorian::date scheduler::last_saturday() const
{
    return make_date(y_, m_, day(weekday::saturday, schedule::last));
}
boost::gregorian::date scheduler::last_sunday() const
{
    return make_date(y_, m_, day(weekday::sunday, schedule::last));
}

std::int32_t scheduler::day(weekday wd, schedule sc) const
{
    if ((m_ < 1) || (m_ > 12)) {
        throw std::out_of_range("month out of range");
    } else {
        // continue
    }

    const std::int32_t dim = days_in_month(y_, m_);

    if (sc == schedule::teenth) {
        for (std::int32_t d = 13; d <= 19; ++d) {
            const weekday w = weekday_from_ymd(y_, m_, d);
            if (weekdays_equal(w, wd)) {
                return d;
            } else {
                // keep searching
            }
        }
        throw std::runtime_error("No teenth weekday found");
    } else if ((sc == schedule::first) || (sc == schedule::second) || (sc == schedule::third) || (sc == schedule::fourth)) {
        const std::int32_t first_dom = 1;
        const weekday w_first = weekday_from_ymd(y_, m_, first_dom);

        std::int32_t offset = 0;
        weekday w_iter = w_first;
        while (!weekdays_equal(w_iter, wd)) {
            offset = (offset + 1);
            // advance to next weekday
            switch (w_iter) {
                case weekday::monday: { w_iter = weekday::tuesday; break; }
                case weekday::tuesday: { w_iter = weekday::wednesday; break; }
                case weekday::wednesday: { w_iter = weekday::thursday; break; }
                case weekday::thursday: { w_iter = weekday::friday; break; }
                case weekday::friday: { w_iter = weekday::saturday; break; }
                case weekday::saturday: { w_iter = weekday::sunday; break; }
                case weekday::sunday: { w_iter = weekday::monday; break; }
                default: { w_iter = weekday::monday; break; }
            }
        }

        const std::int32_t first_match = (first_dom + offset);

        std::int32_t n = 0;
        if (sc == schedule::first) {
            n = 1;
        } else if (sc == schedule::second) {
            n = 2;
        } else if (sc == schedule::third) {
            n = 3;
        } else {
            n = 4;
        }

        const std::int32_t day_candidate = (first_match + ((n - 1) * 7));
        if (day_candidate > dim) {
            throw std::out_of_range("calculated day out of range for month");
        } else {
            return day_candidate;
        }
    } else if (sc == schedule::last) {
        for (std::int32_t d = dim; d >= (dim - 6); --d) {
            const weekday w = weekday_from_ymd(y_, m_, d);
            if (weekdays_equal(w, wd)) {
                return d;
            } else {
                // keep searching
            }
        }
        throw std::runtime_error("No last weekday found");
    } else {
        throw std::invalid_argument("Unknown schedule");
    }
}

}  // namespace meetup
