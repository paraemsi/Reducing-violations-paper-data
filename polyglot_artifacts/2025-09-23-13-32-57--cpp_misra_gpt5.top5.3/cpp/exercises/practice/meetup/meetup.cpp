#include "meetup.h"

#include <stdexcept>

namespace meetup {

namespace {
    // Ensure arithmetic remains in fixed-width signed integers.

    constexpr bool is_leap_year(std::int32_t year) noexcept
    {
        // Leap year if divisible by 400 or (divisible by 4 and not by 100)
        return ((((year % static_cast<std::int32_t>(4)) == static_cast<std::int32_t>(0)) &&
                 ((year % static_cast<std::int32_t>(100)) != static_cast<std::int32_t>(0))) ||
                ((year % static_cast<std::int32_t>(400)) == static_cast<std::int32_t>(0)));
    }

    constexpr std::int32_t days_in_month(std::int32_t year, std::int32_t month)
    {
        if ((month < static_cast<std::int32_t>(1)) || (month > static_cast<std::int32_t>(12))) {
            throw std::out_of_range("month must be 1..12");
        }

        switch (month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                return static_cast<std::int32_t>(31);
            case 4:
            case 6:
            case 9:
            case 11:
                return static_cast<std::int32_t>(30);
            case 2:
                return is_leap_year(year) ? static_cast<std::int32_t>(29) : static_cast<std::int32_t>(28);
            default:
                // Unreachable due to earlier range check; keep for completeness.
                throw std::out_of_range("invalid month");
        }
    }

    // Zeller's congruence to compute weekday; result mapped to Monday=0..Sunday=6.
    constexpr std::int32_t weekday_index(std::int32_t year, std::int32_t month, std::int32_t day_of_month)
    {
        // Adjust months so that March=3..January=13, February=14 with year-1
        std::int32_t y = year;
        std::int32_t m = month;
        if (m <= static_cast<std::int32_t>(2)) {
            m = static_cast<std::int32_t>(m + static_cast<std::int32_t>(12));
            y = static_cast<std::int32_t>(y - static_cast<std::int32_t>(1));
        }

        const std::int32_t K = static_cast<std::int32_t>(y % static_cast<std::int32_t>(100));  // year of the century
        const std::int32_t J = static_cast<std::int32_t>(y / static_cast<std::int32_t>(100));  // zero-based century

        const std::int32_t term1 = day_of_month;
        const std::int32_t term2 = static_cast<std::int32_t>((static_cast<std::int32_t>(13) * (m + static_cast<std::int32_t>(1))) / static_cast<std::int32_t>(5));
        const std::int32_t term3 = K;
        const std::int32_t term4 = static_cast<std::int32_t>(K / static_cast<std::int32_t>(4));
        const std::int32_t term5 = static_cast<std::int32_t>(J / static_cast<std::int32_t>(4));
        const std::int32_t term6 = static_cast<std::int32_t>(static_cast<std::int32_t>(5) * J);

        const std::int32_t sum = (((((term1 + term2) + term3) + term4) + term5) + term6);
        const std::int32_t h = static_cast<std::int32_t>(sum % static_cast<std::int32_t>(7)); // 0=Sat,1=Sun,2=Mon,...6=Fri

        // Map Zeller (Sat=0..Fri=6) to Monday=0..Sunday=6
        const std::int32_t monday_index = static_cast<std::int32_t>((h + static_cast<std::int32_t>(5)) % static_cast<std::int32_t>(7));
        return monday_index;
    }

    constexpr std::int32_t weekday_to_index(weekday wd) noexcept
    {
        return static_cast<std::int32_t>(wd);
    }

    std::int32_t nth_weekday_of_month(std::int32_t year, std::int32_t month, std::int32_t target_index, std::int32_t n)
    {
        const std::int32_t wday_first = weekday_index(year, month, static_cast<std::int32_t>(1));
        const std::int32_t delta = static_cast<std::int32_t>((target_index - wday_first));
        const std::int32_t delta_norm = static_cast<std::int32_t>(((delta % static_cast<std::int32_t>(7)) + static_cast<std::int32_t>(7)) % static_cast<std::int32_t>(7));
        const std::int32_t first_occurrence = static_cast<std::int32_t>(static_cast<std::int32_t>(1) + delta_norm);
        const std::int32_t result_day = static_cast<std::int32_t>(first_occurrence + (static_cast<std::int32_t>(7) * static_cast<std::int32_t>(n - static_cast<std::int32_t>(1))));
        return result_day;
    }

} // namespace

std::int32_t day(std::int32_t year, std::int32_t month, weekday wd, schedule sched)
{
    if ((month < static_cast<std::int32_t>(1)) || (month > static_cast<std::int32_t>(12))) {
        throw std::out_of_range("month must be 1..12");
    }

    const std::int32_t dim = days_in_month(year, month);
    const std::int32_t target_idx = weekday_to_index(wd);

    switch (sched) {
        case schedule::teenth: {
            for (std::int32_t d = static_cast<std::int32_t>(13); d <= static_cast<std::int32_t>(19); d = static_cast<std::int32_t>(d + static_cast<std::int32_t>(1))) {
                if (weekday_index(year, month, d) == target_idx) {
                    return d;
                }
            }
            // Should never happen because each weekday occurs exactly once in 13..19
            throw std::logic_error("no teenth day found");
        }
        case schedule::last: {
            const std::int32_t w_last = weekday_index(year, month, dim);
            const std::int32_t delta_back = static_cast<std::int32_t>(((w_last - target_idx) % static_cast<std::int32_t>(7) + static_cast<std::int32_t>(7)) % static_cast<std::int32_t>(7));
            const std::int32_t d = static_cast<std::int32_t>(dim - delta_back);
            return d;
        }
        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth: {
            const std::int32_t n =
                (sched == schedule::first)  ? static_cast<std::int32_t>(1) :
                (sched == schedule::second) ? static_cast<std::int32_t>(2) :
                (sched == schedule::third)  ? static_cast<std::int32_t>(3) :
                                              static_cast<std::int32_t>(4);
            const std::int32_t d = nth_weekday_of_month(year, month, target_idx, n);
            if ((d < static_cast<std::int32_t>(1)) || (d > dim)) {
                throw std::out_of_range("computed day out of range");
            }
            return d;
        }
        default: {
            throw std::invalid_argument("unsupported schedule");
        }
    }
}

namespace {

// Build a boost::gregorian::date from year, month, day with explicit conversions.
inline boost::gregorian::date make_date(std::int32_t year,
                                        const boost::gregorian::greg_month& month,
                                        std::int32_t day) {
    return boost::gregorian::date(
        static_cast<int>(year),
        static_cast<int>(month.as_number()),
        static_cast<int>(day)
    );
}

inline boost::gregorian::date teenth_date(std::int32_t year,
                                          const boost::gregorian::greg_month& month,
                                          boost::date_time::weekdays wd) {
    for (std::int32_t d = static_cast<std::int32_t>(13);
         d <= static_cast<std::int32_t>(19);
         d = static_cast<std::int32_t>(d + static_cast<std::int32_t>(1))) {
        const boost::gregorian::date dt = make_date(year, month, d);
        const std::int32_t dow = static_cast<std::int32_t>(dt.day_of_week().as_number());
        const std::int32_t target = static_cast<std::int32_t>(wd);
        if (dow == target) {
            return dt;
        }
    }
    throw std::logic_error("no teenth day found"); // Should be unreachable
}

inline boost::gregorian::date nth_weekday_date(std::int32_t year,
                                               const boost::gregorian::greg_month& month,
                                               boost::date_time::weekdays wd,
                                               std::int32_t n) {
    const boost::gregorian::date first = make_date(year, month, static_cast<std::int32_t>(1));
    const std::int32_t first_idx = static_cast<std::int32_t>(first.day_of_week().as_number());
    const std::int32_t target_idx = static_cast<std::int32_t>(wd);
    const std::int32_t delta = static_cast<std::int32_t>((target_idx - first_idx));
    const std::int32_t delta_norm = static_cast<std::int32_t>(((delta % static_cast<std::int32_t>(7)) + static_cast<std::int32_t>(7)) % static_cast<std::int32_t>(7));
    const std::int32_t d = static_cast<std::int32_t>(
        static_cast<std::int32_t>(1) + delta_norm + (static_cast<std::int32_t>(7) * static_cast<std::int32_t>(n - static_cast<std::int32_t>(1)))
    );
    const std::int32_t dim = days_in_month(year, static_cast<std::int32_t>(month.as_number()));
    if ((d < static_cast<std::int32_t>(1)) || (d > dim)) {
        throw std::out_of_range("computed day out of range");
    }
    return make_date(year, month, d);
}

inline boost::gregorian::date last_weekday_date(std::int32_t year,
                                                const boost::gregorian::greg_month& month,
                                                boost::date_time::weekdays wd) {
    const std::int32_t dim = days_in_month(year, static_cast<std::int32_t>(month.as_number()));
    const boost::gregorian::date last = make_date(year, month, dim);
    const std::int32_t last_idx = static_cast<std::int32_t>(last.day_of_week().as_number());
    const std::int32_t target_idx = static_cast<std::int32_t>(wd);
    const std::int32_t delta_back = static_cast<std::int32_t>(((last_idx - target_idx) % static_cast<std::int32_t>(7) + static_cast<std::int32_t>(7)) % static_cast<std::int32_t>(7));
    const std::int32_t d = static_cast<std::int32_t>(dim - delta_back);
    return make_date(year, month, d);
}

} // anonymous namespace

// ---- scheduler implementation ----

scheduler::scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept
    : month_(boost::gregorian::greg_month(month)), year_(year) {}

// Teenth
boost::gregorian::date scheduler::monteenth() const {
    return teenth_date(year_, month_, boost::date_time::Monday);
}
boost::gregorian::date scheduler::tuesteenth() const {
    return teenth_date(year_, month_, boost::date_time::Tuesday);
}
boost::gregorian::date scheduler::wednesteenth() const {
    return teenth_date(year_, month_, boost::date_time::Wednesday);
}
boost::gregorian::date scheduler::thursteenth() const {
    return teenth_date(year_, month_, boost::date_time::Thursday);
}
boost::gregorian::date scheduler::friteenth() const {
    return teenth_date(year_, month_, boost::date_time::Friday);
}
boost::gregorian::date scheduler::saturteenth() const {
    return teenth_date(year_, month_, boost::date_time::Saturday);
}
boost::gregorian::date scheduler::sunteenth() const {
    return teenth_date(year_, month_, boost::date_time::Sunday);
}

// First
boost::gregorian::date scheduler::first_monday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Monday, static_cast<std::int32_t>(1));
}
boost::gregorian::date scheduler::first_tuesday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Tuesday, static_cast<std::int32_t>(1));
}
boost::gregorian::date scheduler::first_wednesday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Wednesday, static_cast<std::int32_t>(1));
}
boost::gregorian::date scheduler::first_thursday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Thursday, static_cast<std::int32_t>(1));
}
boost::gregorian::date scheduler::first_friday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Friday, static_cast<std::int32_t>(1));
}
boost::gregorian::date scheduler::first_saturday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Saturday, static_cast<std::int32_t>(1));
}
boost::gregorian::date scheduler::first_sunday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Sunday, static_cast<std::int32_t>(1));
}

// Second
boost::gregorian::date scheduler::second_monday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Monday, static_cast<std::int32_t>(2));
}
boost::gregorian::date scheduler::second_tuesday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Tuesday, static_cast<std::int32_t>(2));
}
boost::gregorian::date scheduler::second_wednesday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Wednesday, static_cast<std::int32_t>(2));
}
boost::gregorian::date scheduler::second_thursday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Thursday, static_cast<std::int32_t>(2));
}
boost::gregorian::date scheduler::second_friday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Friday, static_cast<std::int32_t>(2));
}
boost::gregorian::date scheduler::second_saturday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Saturday, static_cast<std::int32_t>(2));
}
boost::gregorian::date scheduler::second_sunday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Sunday, static_cast<std::int32_t>(2));
}

// Third
boost::gregorian::date scheduler::third_monday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Monday, static_cast<std::int32_t>(3));
}
boost::gregorian::date scheduler::third_tuesday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Tuesday, static_cast<std::int32_t>(3));
}
boost::gregorian::date scheduler::third_wednesday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Wednesday, static_cast<std::int32_t>(3));
}
boost::gregorian::date scheduler::third_thursday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Thursday, static_cast<std::int32_t>(3));
}
boost::gregorian::date scheduler::third_friday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Friday, static_cast<std::int32_t>(3));
}
boost::gregorian::date scheduler::third_saturday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Saturday, static_cast<std::int32_t>(3));
}
boost::gregorian::date scheduler::third_sunday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Sunday, static_cast<std::int32_t>(3));
}

// Fourth
boost::gregorian::date scheduler::fourth_monday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Monday, static_cast<std::int32_t>(4));
}
boost::gregorian::date scheduler::fourth_tuesday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Tuesday, static_cast<std::int32_t>(4));
}
boost::gregorian::date scheduler::fourth_wednesday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Wednesday, static_cast<std::int32_t>(4));
}
boost::gregorian::date scheduler::fourth_thursday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Thursday, static_cast<std::int32_t>(4));
}
boost::gregorian::date scheduler::fourth_friday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Friday, static_cast<std::int32_t>(4));
}
boost::gregorian::date scheduler::fourth_saturday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Saturday, static_cast<std::int32_t>(4));
}
boost::gregorian::date scheduler::fourth_sunday() const {
    return nth_weekday_date(year_, month_, boost::date_time::Sunday, static_cast<std::int32_t>(4));
}

// Last
boost::gregorian::date scheduler::last_monday() const {
    return last_weekday_date(year_, month_, boost::date_time::Monday);
}
boost::gregorian::date scheduler::last_tuesday() const {
    return last_weekday_date(year_, month_, boost::date_time::Tuesday);
}
boost::gregorian::date scheduler::last_wednesday() const {
    return last_weekday_date(year_, month_, boost::date_time::Wednesday);
}
boost::gregorian::date scheduler::last_thursday() const {
    return last_weekday_date(year_, month_, boost::date_time::Thursday);
}
boost::gregorian::date scheduler::last_friday() const {
    return last_weekday_date(year_, month_, boost::date_time::Friday);
}
boost::gregorian::date scheduler::last_saturday() const {
    return last_weekday_date(year_, month_, boost::date_time::Saturday);
}
boost::gregorian::date scheduler::last_sunday() const {
    return last_weekday_date(year_, month_, boost::date_time::Sunday);
}

}  // namespace meetup
