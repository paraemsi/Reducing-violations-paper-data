#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
#include <cstdint>

namespace meetup {

scheduler::scheduler(std::int32_t year, std::uint32_t month) noexcept
    : m_year(year), m_month(month) { }

/* helper functions confined to this translation unit */
namespace {

using boost::date_time::weekdays;
using boost::gregorian::date;

static date teenth(const std::int32_t year, const std::uint32_t month,
                   const weekdays wd)
{
    for (std::uint32_t d = static_cast<std::uint32_t>(13U);
         d <= static_cast<std::uint32_t>(19U);
         ++d) {
        const date candidate{static_cast<int>(year),
                             static_cast<unsigned short>(month),
                             static_cast<unsigned short>(d)};
        if (candidate.day_of_week().as_number() ==
            static_cast<unsigned>(wd)) {
            return candidate;
        }
    }
    throw std::logic_error("teenth weekday not found");
}

static date nth(const std::int32_t year,
                const std::uint32_t month,
                const weekdays wd,
                const std::int32_t n)
{
    std::int32_t counter = static_cast<std::int32_t>(0);
    const std::uint32_t last_day =
        static_cast<std::uint32_t>(
            boost::gregorian::gregorian_calendar::end_of_month_day(
                static_cast<int>(year),
                static_cast<int>(month)));

    for (std::uint32_t d = static_cast<std::uint32_t>(1U);
         d <= last_day;
         ++d) {
        const date candidate{static_cast<int>(year),
                             static_cast<unsigned short>(month),
                             static_cast<unsigned short>(d)};
        if (candidate.day_of_week().as_number() ==
            static_cast<unsigned>(wd)) {
            ++counter;
            if (counter == n) {
                return candidate;
            }
        }
    }
    throw std::logic_error("nth weekday not found");
}

static date last(const std::int32_t year,
                 const std::uint32_t month,
                 const weekdays wd)
{
    std::int32_t d = static_cast<std::int32_t>(
        boost::gregorian::gregorian_calendar::end_of_month_day(
            static_cast<int>(year),
            static_cast<int>(month)));

    for (; d >= static_cast<std::int32_t>(1); --d) {
        const date candidate{static_cast<int>(year),
                             static_cast<unsigned short>(month),
                             static_cast<unsigned short>(d)};
        if (candidate.day_of_week().as_number() ==
            static_cast<unsigned>(wd)) {
            return candidate;
        }
    }
    throw std::logic_error("last weekday not found");
}

}  // unnamed namespace

/* ---------- public API wrappers ---------- */

/* map lowercase identifiers used in the public API to the Boost weekday
 * enumerators.  These are `constexpr` so no storage is produced.           */
static constexpr weekdays monday   {boost::date_time::Monday};
static constexpr weekdays tuesday  {boost::date_time::Tuesday};
static constexpr weekdays wednesday{boost::date_time::Wednesday};
static constexpr weekdays thursday {boost::date_time::Thursday};
static constexpr weekdays friday   {boost::date_time::Friday};
static constexpr weekdays saturday {boost::date_time::Saturday};
static constexpr weekdays sunday   {boost::date_time::Sunday};

#define WRAPPER_T(_name_, _wd_) \
    date scheduler::_name_##teenth() const { return teenth(m_year, m_month, _wd_); }

WRAPPER_T(mon,  monday)
WRAPPER_T(tues, tuesday)
WRAPPER_T(wednes, wednesday)
WRAPPER_T(thurs, thursday)
WRAPPER_T(fri,  friday)
WRAPPER_T(satur, saturday)
WRAPPER_T(sun,  sunday)

#undef WRAPPER_T

#define WRAPPER_N(_pref_, _wd_, _n_) \
    date scheduler::_pref_##_##_wd_() const { \
        return nth(m_year, m_month, _wd_, static_cast<std::int32_t>(_n_)); \
    }

#define FIRST(_wd_)  WRAPPER_N(first,  _wd_, 1)
#define SECOND(_wd_) WRAPPER_N(second, _wd_, 2)
#define THIRD(_wd_)  WRAPPER_N(third,  _wd_, 3)
#define FOURTH(_wd_) WRAPPER_N(fourth, _wd_, 4)

FIRST(monday)   SECOND(monday)   THIRD(monday)   FOURTH(monday)
FIRST(tuesday)  SECOND(tuesday)  THIRD(tuesday)  FOURTH(tuesday)
FIRST(wednesday) SECOND(wednesday) THIRD(wednesday) FOURTH(wednesday)
FIRST(thursday) SECOND(thursday) THIRD(thursday) FOURTH(thursday)
FIRST(friday)   SECOND(friday)   THIRD(friday)   FOURTH(friday)
FIRST(saturday) SECOND(saturday) THIRD(saturday) FOURTH(saturday)
FIRST(sunday)   SECOND(sunday)   THIRD(sunday)   FOURTH(sunday)

#undef FIRST
#undef SECOND
#undef THIRD
#undef FOURTH
#undef WRAPPER_N

#define WRAPPER_L(_wd_) \
    date scheduler::last_##_wd_() const { return last(m_year, m_month, _wd_); }

WRAPPER_L(monday)
WRAPPER_L(tuesday)
WRAPPER_L(wednesday)
WRAPPER_L(thursday)
WRAPPER_L(friday)
WRAPPER_L(saturday)
WRAPPER_L(sunday)

#undef WRAPPER_L

}  // namespace meetup
