#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>

namespace meetup {

// ---------- scheduler implementation ----------------------------------------

scheduler::scheduler(const boost::gregorian::months_of_year month,
                     const std::int32_t                    year) noexcept
    : month_(month),
      year_(year)
{
}

// --------------- helpers -----------------------------------------------------

auto scheduler::nth_weekday(const boost::gregorian::greg_weekday& wd,
                            const std::uint8_t                    nth) const
    -> boost::gregorian::date
{
    /*  first day of given month */
    const boost::gregorian::date first_day {static_cast<int>(year_),
                                            month_,
                                            1};

    /*  distance (0-6) to requested weekday */
    const std::uint8_t first_dow  {static_cast<std::uint8_t>(first_day.day_of_week())};
    const std::uint8_t target_dow {static_cast<std::uint8_t>(wd.as_number())};
    const std::uint8_t diff {static_cast<std::uint8_t>((target_dow + (7U - first_dow)) % 7U)};

    const std::uint8_t days_to_add {(diff + (7U * (nth - 1U)))};

    return first_day + boost::gregorian::days(days_to_add);
}

auto scheduler::last_weekday(const boost::gregorian::greg_weekday& wd) const
    -> boost::gregorian::date
{
    /*  get first day of next month then step back */
    const auto next_month {month_ == boost::gregorian::Dec
                               ? boost::gregorian::Jan
                               : static_cast<boost::gregorian::months_of_year>(
                                     static_cast<unsigned>(month_) + 1U)};

    const std::int32_t next_year {(month_ == boost::gregorian::Dec) ? (year_ + 1) : year_};

    const boost::gregorian::date first_next {static_cast<int>(next_year),
                                             next_month,
                                             1};

    /*  walk backwards until weekday matches */
    for (boost::gregorian::date d {first_next - boost::gregorian::days(1)};
         /* always true – will return inside */
         true;
         d -= boost::gregorian::days(1))
    {
        if (wd == d.day_of_week()) {
            return d;
        }
    }
    /*  logically unreachable */
    throw std::logic_error("last_weekday computation failed");
}

auto scheduler::teenth_weekday(const boost::gregorian::greg_weekday& wd) const
    -> boost::gregorian::date
{
    for (std::uint8_t day {13U}; (day <= 19U); ++day) {
        const boost::gregorian::date current {static_cast<int>(year_),
                                              month_,
                                              static_cast<unsigned short>(day)};
        if (wd == current.day_of_week()) {
            return current;
        }
    }
    throw std::logic_error("teenth weekday not found");
}

// --------------- “teenth” public wrappers ------------------------------------

#define MEETUP_IMPL_TEENTH(fn_name, weekday_enum)               \
    auto scheduler::fn_name() const -> boost::gregorian::date   \
    {                                                           \
        return teenth_weekday(boost::gregorian::weekday_enum);  \
    }

MEETUP_IMPL_TEENTH(monteenth, Monday)
MEETUP_IMPL_TEENTH(tuesteenth, Tuesday)
MEETUP_IMPL_TEENTH(wednesteenth, Wednesday)
MEETUP_IMPL_TEENTH(thursteenth, Thursday)
MEETUP_IMPL_TEENTH(friteenth, Friday)
MEETUP_IMPL_TEENTH(saturteenth, Saturday)
MEETUP_IMPL_TEENTH(sunteenth, Sunday)

#undef MEETUP_IMPL_TEENTH

// --------------- first-fourth & last wrappers --------------------------------

#define MEETUP_IMPL_NTH(prefix, n_idx, fname, weekday_enum)                     \
    auto scheduler::prefix##_##fname() const -> boost::gregorian::date          \
    {                                                                           \
        return nth_weekday(boost::gregorian::weekday_enum,                      \
                           static_cast<std::uint8_t>(n_idx));                  \
    }

#define MEETUP_IMPL_NTH_SET(prefix, n_idx)                                      \
    MEETUP_IMPL_NTH(prefix, n_idx, monday, Monday)                              \
    MEETUP_IMPL_NTH(prefix, n_idx, tuesday, Tuesday)                            \
    MEETUP_IMPL_NTH(prefix, n_idx, wednesday, Wednesday)                        \
    MEETUP_IMPL_NTH(prefix, n_idx, thursday, Thursday)                          \
    MEETUP_IMPL_NTH(prefix, n_idx, friday, Friday)                              \
    MEETUP_IMPL_NTH(prefix, n_idx, saturday, Saturday)                          \
    MEETUP_IMPL_NTH(prefix, n_idx, sunday, Sunday)

MEETUP_IMPL_NTH_SET(first, 1U)
MEETUP_IMPL_NTH_SET(second, 2U)
MEETUP_IMPL_NTH_SET(third, 3U)
MEETUP_IMPL_NTH_SET(fourth, 4U)

#undef MEETUP_IMPL_NTH_SET
#undef MEETUP_IMPL_NTH

#define MEETUP_IMPL_LAST(fname, weekday_enum)                                     \
    auto scheduler::last_##fname() const -> boost::gregorian::date               \
    {                                                                            \
        return last_weekday(boost::gregorian::weekday_enum);                     \
    }

MEETUP_IMPL_LAST(monday, Monday)
MEETUP_IMPL_LAST(tuesday, Tuesday)
MEETUP_IMPL_LAST(wednesday, Wednesday)
MEETUP_IMPL_LAST(thursday, Thursday)
MEETUP_IMPL_LAST(friday, Friday)
MEETUP_IMPL_LAST(saturday, Saturday)
MEETUP_IMPL_LAST(sunday, Sunday)

#undef MEETUP_IMPL_LAST

} // namespace meetup
