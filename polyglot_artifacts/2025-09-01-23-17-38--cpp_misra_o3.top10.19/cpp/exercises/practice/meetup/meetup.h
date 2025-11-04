#if !defined(MEETUP_H)
#define MEETUP_H

#include <chrono>
#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

// Enumeration describing which occurrence in the month is requested
enum class schedule : std::uint8_t
{
    first,
    second,
    third,
    fourth,
    last,
    teenth
};

// Return the exact calendar day for the requested meetup.
//
// Parameters:
//  • year    –  four-digit year, e.g. std::chrono::year{2025}
//  • month   –  calendar month, e.g. std::chrono::month{9}
//  • weekday –  target weekday (std::chrono::weekday{4} == Thursday)
//  • sched   –  which occurrence (first, second, …, teenth)
//
// The function is noexcept and always returns a valid
// std::chrono::year_month_day that falls inside the given month.
#define MEETUP_INTERNAL_DECLARE(prefix)                                   \
    boost::gregorian::date prefix##_monday() const noexcept;              \
    boost::gregorian::date prefix##_tuesday() const noexcept;             \
    boost::gregorian::date prefix##_wednesday() const noexcept;           \
    boost::gregorian::date prefix##_thursday() const noexcept;            \
    boost::gregorian::date prefix##_friday() const noexcept;              \
    boost::gregorian::date prefix##_saturday() const noexcept;            \
    boost::gregorian::date prefix##_sunday() const noexcept;

/*
 * Class `scheduler`
 * -----------------
 * Calculates specific meetup dates inside the supplied `month`/`year`
 * combination, following the Exercism specification.
 */
class scheduler
{
public:
    scheduler(const boost::gregorian::greg_month & month, std::int32_t year) noexcept;

    /* “teenth” helpers */
    boost::gregorian::date monteenth() const noexcept;
    boost::gregorian::date tuesteenth() const noexcept;
    boost::gregorian::date wednesteenth() const noexcept;
    boost::gregorian::date thursteenth() const noexcept;
    boost::gregorian::date friteenth() const noexcept;
    boost::gregorian::date saturteenth() const noexcept;
    boost::gregorian::date sunteenth() const noexcept;

    /* ordinal helpers */
    MEETUP_INTERNAL_DECLARE(first)
    MEETUP_INTERNAL_DECLARE(second)
    MEETUP_INTERNAL_DECLARE(third)
    MEETUP_INTERNAL_DECLARE(fourth)
    MEETUP_INTERNAL_DECLARE(last)

private:
    boost::gregorian::greg_month m_month;
    std::int32_t                 m_year;

    boost::gregorian::date on(schedule sched,
                              const boost::gregorian::greg_weekday & weekday) const noexcept;
};

#undef MEETUP_INTERNAL_DECLARE

/* ------------------------------------------------------------------
 *  Boost-based scheduler implementation
 * ------------------------------------------------------------------ */

namespace {

static std::uint32_t days_in_month_boost(std::int32_t year,
                                         const boost::gregorian::greg_month & month) noexcept
{
    const unsigned short dim =
        boost::gregorian::gregorian_calendar::end_of_month_day(
            static_cast<unsigned short>(year),
            month.as_number());

    return static_cast<std::uint32_t>(dim);
}

} // unnamed namespace

/* ---- scheduler : ctor ------------------------------------------ */
inline scheduler::scheduler(const boost::gregorian::greg_month & month,
                            std::int32_t year) noexcept
    : m_month(month),
      m_year(year)
{
}

/* ---- scheduler : core helper ----------------------------------- */
inline boost::gregorian::date scheduler::on(schedule sched,
                                            const boost::gregorian::greg_weekday & weekday) const noexcept
{
    const std::int32_t year_val {m_year};
    const boost::gregorian::greg_month month_val {m_month};

    switch (sched) {
        case schedule::teenth:
        {
            for (std::uint32_t d {13U}; d <= 19U; ++d) {
                const boost::gregorian::date current {year_val, month_val.as_number(),
                                                      static_cast<unsigned short>(d)};
                if (current.day_of_week() == weekday) {
                    return current;
                }
            }
            break;
        }

        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth:
        {
            const std::uint32_t ordinal {static_cast<std::uint32_t>(sched)};
            const boost::gregorian::date first_of_month {year_val, month_val.as_number(), 1U};

            const std::uint32_t first_wd {
                static_cast<std::uint32_t>(first_of_month.day_of_week().as_number())};
            const std::uint32_t target_wd {
                static_cast<std::uint32_t>(weekday.as_number())};

            const std::uint32_t offset {(7U + target_wd - first_wd) % 7U};
            const std::uint32_t day_value {1U + offset + (ordinal * 7U)};

            return boost::gregorian::date {year_val, month_val.as_number(),
                                           static_cast<unsigned short>(day_value)};
        }

        case schedule::last:
        {
            const std::uint32_t dim {days_in_month_boost(year_val, month_val)};
            const boost::gregorian::date last_day {year_val, month_val.as_number(),
                                                   static_cast<unsigned short>(dim)};

            const std::uint32_t last_wd {
                static_cast<std::uint32_t>(last_day.day_of_week().as_number())};
            const std::uint32_t target_wd {
                static_cast<std::uint32_t>(weekday.as_number())};

            const std::uint32_t backward {(7U + last_wd - target_wd) % 7U};
            const std::uint32_t day_value {dim - backward};

            return boost::gregorian::date {year_val, month_val.as_number(),
                                           static_cast<unsigned short>(day_value)};
        }

        default:
            break;
    }

    return boost::gregorian::date {boost::gregorian::not_a_date_time};
}

/* ---- small helpers generated via macro ------------------------- */
#define MEETUP_HELPER(name, sched_enum, wd)                                         \
    inline boost::gregorian::date scheduler::name() const noexcept                  \
    {                                                                               \
        return on(schedule::sched_enum, boost::gregorian::greg_weekday(wd));        \
    }

MEETUP_HELPER(monteenth,  teenth,  boost::date_time::Monday)
MEETUP_HELPER(tuesteenth, teenth,  boost::date_time::Tuesday)
MEETUP_HELPER(wednesteenth, teenth, boost::date_time::Wednesday)
MEETUP_HELPER(thursteenth, teenth,  boost::date_time::Thursday)
MEETUP_HELPER(friteenth,  teenth,  boost::date_time::Friday)
MEETUP_HELPER(saturteenth, teenth, boost::date_time::Saturday)
MEETUP_HELPER(sunteenth,  teenth,  boost::date_time::Sunday)

MEETUP_HELPER(first_monday,    first,  boost::date_time::Monday)
MEETUP_HELPER(first_tuesday,   first,  boost::date_time::Tuesday)
MEETUP_HELPER(first_wednesday, first,  boost::date_time::Wednesday)
MEETUP_HELPER(first_thursday,  first,  boost::date_time::Thursday)
MEETUP_HELPER(first_friday,    first,  boost::date_time::Friday)
MEETUP_HELPER(first_saturday,  first,  boost::date_time::Saturday)
MEETUP_HELPER(first_sunday,    first,  boost::date_time::Sunday)

MEETUP_HELPER(second_monday,    second,  boost::date_time::Monday)
MEETUP_HELPER(second_tuesday,   second,  boost::date_time::Tuesday)
MEETUP_HELPER(second_wednesday, second,  boost::date_time::Wednesday)
MEETUP_HELPER(second_thursday,  second,  boost::date_time::Thursday)
MEETUP_HELPER(second_friday,    second,  boost::date_time::Friday)
MEETUP_HELPER(second_saturday,  second,  boost::date_time::Saturday)
MEETUP_HELPER(second_sunday,    second,  boost::date_time::Sunday)

MEETUP_HELPER(third_monday,    third,  boost::date_time::Monday)
MEETUP_HELPER(third_tuesday,   third,  boost::date_time::Tuesday)
MEETUP_HELPER(third_wednesday, third,  boost::date_time::Wednesday)
MEETUP_HELPER(third_thursday,  third,  boost::date_time::Thursday)
MEETUP_HELPER(third_friday,    third,  boost::date_time::Friday)
MEETUP_HELPER(third_saturday,  third,  boost::date_time::Saturday)
MEETUP_HELPER(third_sunday,    third,  boost::date_time::Sunday)

MEETUP_HELPER(fourth_monday,    fourth,  boost::date_time::Monday)
MEETUP_HELPER(fourth_tuesday,   fourth,  boost::date_time::Tuesday)
MEETUP_HELPER(fourth_wednesday, fourth,  boost::date_time::Wednesday)
MEETUP_HELPER(fourth_thursday,  fourth,  boost::date_time::Thursday)
MEETUP_HELPER(fourth_friday,    fourth,  boost::date_time::Friday)
MEETUP_HELPER(fourth_saturday,  fourth,  boost::date_time::Saturday)
MEETUP_HELPER(fourth_sunday,    fourth,  boost::date_time::Sunday)

MEETUP_HELPER(last_monday,    last,  boost::date_time::Monday)
MEETUP_HELPER(last_tuesday,   last,  boost::date_time::Tuesday)
MEETUP_HELPER(last_wednesday, last,  boost::date_time::Wednesday)
MEETUP_HELPER(last_thursday,  last,  boost::date_time::Thursday)
MEETUP_HELPER(last_friday,    last,  boost::date_time::Friday)
MEETUP_HELPER(last_saturday,  last,  boost::date_time::Saturday)
MEETUP_HELPER(last_sunday,    last,  boost::date_time::Sunday)

#undef MEETUP_HELPER

}  // namespace meetup
 // End of in-header implementation block

// ------------------------------------------------------------------
//  New Boost-based implementation
// ------------------------------------------------------------------
#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

// Forward declaration present in the header
// ------------------------------------------------------------------
#if 0
//  Helpers
// ------------------------------------------------------------------
namespace {

static std::uint32_t days_in_month(std::int32_t year,
                                   const boost::gregorian::greg_month & month) noexcept
{
    const unsigned short dim =
        boost::gregorian::gregorian_calendar::end_of_month_day(
            static_cast<unsigned short>(year),
            month.as_number());

    return static_cast<std::uint32_t>(dim);
}

} // unnamed namespace

// ------------------------------------------------------------------
//  scheduler – construction
// ------------------------------------------------------------------
scheduler::scheduler(const boost::gregorian::greg_month & month,
                     std::int32_t year) noexcept
    : m_month(month),
      m_year(year)
{
}

// ------------------------------------------------------------------
//  Core calculation
// ------------------------------------------------------------------
boost::gregorian::date
scheduler::on(schedule sched,
              const boost::gregorian::greg_weekday & weekday) const noexcept
{
    const std::int32_t year_val {m_year};
    const boost::gregorian::greg_month month_val {m_month};

    switch (sched) {
        case schedule::teenth:
        {
            for (std::uint32_t d {13U}; d <= 19U; ++d) {
                const boost::gregorian::date current {year_val, month_val.as_number(),
                                                      static_cast<unsigned short>(d)};
                if (current.day_of_week() == weekday) {
                    return current;
                }
            }
            break; /* defensive – logic guarantees a return */
        }

        case schedule::first:
        case schedule::second:
        case schedule::third:
        case schedule::fourth:
        {
            const std::uint32_t ordinal {static_cast<std::uint32_t>(sched)};  // 0-based
            const boost::gregorian::date first_of_month {year_val, month_val.as_number(), 1U};

            const std::uint32_t first_wd {
                static_cast<std::uint32_t>(first_of_month.day_of_week().as_number())};
            const std::uint32_t target_wd {
                static_cast<std::uint32_t>(weekday.as_number())};

            const std::uint32_t offset {(7U + target_wd - first_wd) % 7U};
            const std::uint32_t day_value {1U + offset + (ordinal * 7U)};

            return boost::gregorian::date {year_val, month_val.as_number(),
                                           static_cast<unsigned short>(day_value)};
        }

        case schedule::last:
        {
            const std::uint32_t dim {days_in_month(year_val, month_val)};
            const boost::gregorian::date last_day {year_val, month_val.as_number(),
                                                   static_cast<unsigned short>(dim)};

            const std::uint32_t last_wd {
                static_cast<std::uint32_t>(last_day.day_of_week().as_number())};
            const std::uint32_t target_wd {
                static_cast<std::uint32_t>(weekday.as_number())};

            const std::uint32_t backward {(7U + last_wd - target_wd) % 7U};
            const std::uint32_t day_value {dim - backward};

            return boost::gregorian::date {year_val, month_val.as_number(),
                                           static_cast<unsigned short>(day_value)};
        }

        default:
            break;
    }

    /* Should never reach – return "not_a_date_time" sentinel */
    return boost::gregorian::date {boost::gregorian::not_a_date_time};
}

// ------------------------------------------------------------------
//  Teenth helpers
// ------------------------------------------------------------------
boost::gregorian::date scheduler::monteenth()  const noexcept { return on(schedule::teenth,  boost::gregorian::greg_weekday(boost::date_time::Monday));    }
boost::gregorian::date scheduler::tuesteenth() const noexcept { return on(schedule::teenth,  boost::gregorian::greg_weekday(boost::date_time::Tuesday));   }
boost::gregorian::date scheduler::wednesteenth() const noexcept { return on(schedule::teenth,  boost::gregorian::greg_weekday(boost::date_time::Wednesday)); }
boost::gregorian::date scheduler::thursteenth() const noexcept { return on(schedule::teenth,  boost::gregorian::greg_weekday(boost::date_time::Thursday));  }
boost::gregorian::date scheduler::friteenth() const noexcept { return on(schedule::teenth,  boost::gregorian::greg_weekday(boost::date_time::Friday));    }
boost::gregorian::date scheduler::saturteenth() const noexcept { return on(schedule::teenth,  boost::gregorian::greg_weekday(boost::date_time::Saturday));  }
boost::gregorian::date scheduler::sunteenth() const noexcept { return on(schedule::teenth,  boost::gregorian::greg_weekday(boost::date_time::Sunday));    }

// ------------------------------------------------------------------
//  Ordinal helpers – generated via macro
// ------------------------------------------------------------------
#define MEETUP_DEFINE(prefix, ENUM)                                                                    \
    boost::gregorian::date scheduler::prefix##_monday()    const noexcept { return on(schedule::ENUM, boost::gregorian::greg_weekday(boost::date_time::Monday)); }    \
    boost::gregorian::date scheduler::prefix##_tuesday()   const noexcept { return on(schedule::ENUM, boost::gregorian::greg_weekday(boost::date_time::Tuesday)); }   \
    boost::gregorian::date scheduler::prefix##_wednesday() const noexcept { return on(schedule::ENUM, boost::gregorian::greg_weekday(boost::date_time::Wednesday)); } \
    boost::gregorian::date scheduler::prefix##_thursday()  const noexcept { return on(schedule::ENUM, boost::gregorian::greg_weekday(boost::date_time::Thursday)); }  \
    boost::gregorian::date scheduler::prefix##_friday()    const noexcept { return on(schedule::ENUM, boost::gregorian::greg_weekday(boost::date_time::Friday)); }    \
    boost::gregorian::date scheduler::prefix##_saturday()  const noexcept { return on(schedule::ENUM, boost::gregorian::greg_weekday(boost::date_time::Saturday)); }  \
    boost::gregorian::date scheduler::prefix##_sunday()    const noexcept { return on(schedule::ENUM, boost::gregorian::greg_weekday(boost::date_time::Sunday)); }

MEETUP_DEFINE(first,  first)
MEETUP_DEFINE(second, second)
MEETUP_DEFINE(third,  third)
MEETUP_DEFINE(fourth, fourth)
MEETUP_DEFINE(last,   last)

#undef MEETUP_DEFINE

} // namespace meetup
#endif /* MEETUP_DISABLE_INLINE_IMPLEMENTATION */

#endif // MEETUP_H
