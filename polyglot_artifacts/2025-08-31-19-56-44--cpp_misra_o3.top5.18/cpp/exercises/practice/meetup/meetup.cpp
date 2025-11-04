#include "meetup.h"

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

static auto is_leap_year(int32 year) noexcept -> bool
{
    return (((year % 400) == 0) || (((year % 4) == 0) && ((year % 100) != 0)));
}

static auto days_in_month(uint8 month, int32 year) -> uint8
{
    switch (month)
    {
        case 1U:  return 31U;
        case 2U:  return is_leap_year(year) ? 29U : 28U;
        case 3U:  return 31U;
        case 4U:  return 30U;
        case 5U:  return 31U;
        case 6U:  return 30U;
        case 7U:  return 31U;
        case 8U:  return 31U;
        case 9U:  return 30U;
        case 10U: return 31U;
        case 11U: return 30U;
        case 12U: return 31U;
        default:  throw std::invalid_argument("month must be in the range 1..12");
    }
}

static auto zeller_weekday(int32 year,
                           uint8 month,
                           uint8 day) -> weekday
{
    int32 y { year };
    int32 m { static_cast<int32>(month) };

    if (m < 3)
    {
        m = m + 12;
        y = y - 1;
    }

    const int32 k { y % 100 };
    const int32 j { y / 100 };

    const int32 h {
        (day
         + ((13 * (m + 1)) / 5)
         + k
         + (k / 4)
         + (j / 4)
         + (5 * j)) %
        7
    };

    switch (h)
    {
        case 0: return weekday::saturday;
        case 1: return weekday::sunday;
        case 2: return weekday::monday;
        case 3: return weekday::tuesday;
        case 4: return weekday::wednesday;
        case 5: return weekday::thursday;
        case 6: return weekday::friday;
        default: throw std::logic_error("invalid weekday value");
    }
}

auto meetup_day(int32 year,
                uint8 month,
                weekday      wd,
                schedule     sc) -> date
{
    const uint8 dim { days_in_month(month, year) };

    auto matches_weekday = [&](uint8 d) -> bool
    {
        return (zeller_weekday(year, month, d) == wd);
    };

    if (sc == schedule::teenth)
    {
        for (uint8 d { 13U }; d <= 19U; ++d)
        {
            if (matches_weekday(d))
            {
                return { year, month, d };
            }
        }
        throw std::logic_error("teenth day not found");
    }

    uint8 occurence_count { 0U };
    uint8 last_match      { 0U };

    for (uint8 d { 1U }; d <= dim; ++d)
    {
        if (matches_weekday(d))
        {
            ++occurence_count;
            last_match      = d;

            switch (sc)
            {
                case schedule::first:
                    if (occurence_count == 1U) { return { year, month, d }; }
                    break;

                case schedule::second:
                    if (occurence_count == 2U) { return { year, month, d }; }
                    break;

                case schedule::third:
                    if (occurence_count == 3U) { return { year, month, d }; }
                    break;

                case schedule::fourth:
                    if (occurence_count == 4U) { return { year, month, d }; }
                    break;

                case schedule::last:
                case schedule::teenth:
                default:
                    /* handled later */
                    break;
            }
        }
    }

    if (sc == schedule::last)
    {
        return { year, month, last_match };
    }

    throw std::logic_error("requested meetup day not found");
}

/*==============================================================================
 * scheduler
 *============================================================================*/
auto scheduler::compute(schedule sc, weekday wd) const -> boost::gregorian::date
{
    /* months_of_year is 1-based; explicit cast required */
    const uint8 m_val { static_cast<uint8>(m_month) };
    const date  d     { meetup_day(m_year, m_val, wd, sc) };

    return boost::gregorian::date(static_cast< int >(d.year),
                                  static_cast< unsigned >(d.month),
                                  static_cast< unsigned >(d.day));
}

scheduler::scheduler(boost::gregorian::months_of_year month, int32 year) noexcept
    : m_month(month),
      m_year(year)
{
}

#define MEETUP_GEN_NTH_METHOD(NTH, SCH)                                   \
    boost::gregorian::date scheduler::NTH##_monday() const  { return compute(schedule::SCH, weekday::monday); } \
    boost::gregorian::date scheduler::NTH##_tuesday() const { return compute(schedule::SCH, weekday::tuesday); } \
    boost::gregorian::date scheduler::NTH##_wednesday() const { return compute(schedule::SCH, weekday::wednesday); } \
    boost::gregorian::date scheduler::NTH##_thursday() const { return compute(schedule::SCH, weekday::thursday); } \
    boost::gregorian::date scheduler::NTH##_friday() const { return compute(schedule::SCH, weekday::friday); } \
    boost::gregorian::date scheduler::NTH##_saturday() const { return compute(schedule::SCH, weekday::saturday); } \
    boost::gregorian::date scheduler::NTH##_sunday() const { return compute(schedule::SCH, weekday::sunday); }

#define MEETUP_GEN_TEENTH_METHOD(PREFIX, WD) \
    boost::gregorian::date scheduler::PREFIX##teenth() const { return compute(schedule::teenth, weekday::WD); }

MEETUP_GEN_TEENTH_METHOD(mon , monday   )
MEETUP_GEN_TEENTH_METHOD(tues, tuesday  )
MEETUP_GEN_TEENTH_METHOD(wednes, wednesday)
MEETUP_GEN_TEENTH_METHOD(thurs, thursday )
MEETUP_GEN_TEENTH_METHOD(fri , friday   )
MEETUP_GEN_TEENTH_METHOD(satur, saturday )
MEETUP_GEN_TEENTH_METHOD(sun , sunday   )

MEETUP_GEN_NTH_METHOD(first , first )
MEETUP_GEN_NTH_METHOD(second, second)
MEETUP_GEN_NTH_METHOD(third , third )
MEETUP_GEN_NTH_METHOD(fourth, fourth)
MEETUP_GEN_NTH_METHOD(last  , last  )

#undef MEETUP_GEN_TEENTH_METHOD
#undef MEETUP_GEN_NTH_METHOD

}  // namespace meetup
