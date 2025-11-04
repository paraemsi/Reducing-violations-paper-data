#include "meetup.h"
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

#if 0
auto day(std::int32_t yr, std::uint8_t mon, std::chrono::weekday weekday_target,
         schedule schedule_target) -> std::chrono::year_month_day
{
    using std::chrono::day;
    using std::chrono::month;
    using std::chrono::year;
    using std::chrono::sys_days;
    using std::chrono::year_month_day;
    using std::chrono::year_month_day_last;
    using std::chrono::weekday;

    /* first day of the requested month */
    const sys_days first_day{year{yr} / month{mon} / day{static_cast<unsigned>(1U)}};
    const weekday   first_weekday{first_day};

    const std::uint8_t target_enc = static_cast<std::uint8_t>(weekday_target.c_encoding());
    const std::uint8_t first_enc  = static_cast<std::uint8_t>(first_weekday.c_encoding());

    std::uint8_t day_value{0U};

    switch (schedule_target) {
    case schedule::first:
    case schedule::second:
    case schedule::third:
    case schedule::fourth:
    {
        const std::uint8_t occurrence_index = static_cast<std::uint8_t>(schedule_target);
        const std::uint8_t offset =
            static_cast<std::uint8_t>(((7U + target_enc) - first_enc) % 7U);

        day_value =
            static_cast<std::uint8_t>(1U + offset + (occurrence_index * 7U));
        break;
    }
    case schedule::teenth:
    {
        const sys_days teenth_first{year{yr} / month{mon} / day{static_cast<unsigned>(13U)}};
        const weekday   teenth_wd{teenth_first};
        const std::uint8_t teenth_enc =
            static_cast<std::uint8_t>(teenth_wd.c_encoding());

        const std::uint8_t teenth_offset =
            static_cast<std::uint8_t>(((7U + target_enc) - teenth_enc) % 7U);

        day_value =
            static_cast<std::uint8_t>(13U + teenth_offset);
        break;
    }
    case schedule::last:
    {
        const year_month_day_last last_day_struct{
            year{yr} / month{mon} / std::chrono::last};

        const std::uint8_t days_in_month =
            static_cast<std::uint8_t>(static_cast<unsigned>(last_day_struct.day()));

        const sys_days last_sys_day{
            year{yr} / month{mon} / day{static_cast<unsigned>(days_in_month)}};
        const weekday   last_weekday{last_sys_day};
        const std::uint8_t last_enc =
            static_cast<std::uint8_t>(last_weekday.c_encoding());

        const std::uint8_t backward =
            static_cast<std::uint8_t>(((7U + last_enc) - target_enc) % 7U);

        day_value =
            static_cast<std::uint8_t>(days_in_month - backward);
        break;
    }
    default:
        /* should be unreachable */
        day_value = static_cast<std::uint8_t>(1U);
        break;
    }

    return year{yr} / month{mon} / day{static_cast<unsigned>(day_value)};
}
#endif

/* -------------------------------------------------------------------------- */
/* Scheduler implementation                                                   */
/* -------------------------------------------------------------------------- */

scheduler::scheduler(boost::gregorian::months_of_year mon, std::int32_t yr) noexcept
    : month_{mon}, year_{yr}
{
}

auto scheduler::compute_day(schedule sched,
                             boost::gregorian::greg_weekday weekday_target) const
    -> boost::gregorian::date
{
    using boost::gregorian::date;
    using boost::gregorian::gregorian_calendar;

    if (sched == schedule::teenth) {
        for (std::uint8_t d = static_cast<std::uint8_t>(13U);
             d <= static_cast<std::uint8_t>(19U); ++d) {
            const date candidate{static_cast<std::int32_t>(year_), month_,
                                 static_cast<unsigned short>(d)};
            if (candidate.day_of_week() == weekday_target) {
                return candidate;
            }
        }
    } else if (sched == schedule::last) {
        const std::int32_t last_dom =
            static_cast<std::int32_t>(gregorian_calendar::end_of_month_day(
                year_, static_cast<unsigned short>(month_)));
        for (std::int32_t d = last_dom; d >= (last_dom - 6); --d) {
            const date candidate{static_cast<std::int32_t>(year_), month_,
                                 static_cast<unsigned short>(d)};
            if (candidate.day_of_week() == weekday_target) {
                return candidate;
            }
        }
    } else { /* first, second, third, fourth */
        const date first_dom{static_cast<std::int32_t>(year_), month_,
                             static_cast<unsigned short>(1U)};
        const std::uint8_t first_dow =
            static_cast<std::uint8_t>(first_dom.day_of_week().as_number());
        const std::uint8_t target_dow =
            static_cast<std::uint8_t>(weekday_target.as_number());

        const std::uint8_t offset =
            static_cast<std::uint8_t>(((7U + target_dow) - first_dow) % 7U);
        const std::uint8_t occurrence_index =
            static_cast<std::uint8_t>(sched);

        const std::uint8_t day_val =
            static_cast<std::uint8_t>(1U + offset + (occurrence_index * 7U));

        return date{static_cast<std::int32_t>(year_), month_,
                    static_cast<unsigned short>(day_val)};
    }

    /* unreachable but required for MISRA compliance */
    return boost::gregorian::date{};
}

/* Teenth methods */
auto scheduler::monteenth() const -> boost::gregorian::date
{
    return compute_day(schedule::teenth,
                       boost::gregorian::greg_weekday(boost::gregorian::Monday));
}

auto scheduler::tuesteenth() const -> boost::gregorian::date
{
    return compute_day(schedule::teenth,
                       boost::gregorian::greg_weekday(boost::gregorian::Tuesday));
}

auto scheduler::wednesteenth() const -> boost::gregorian::date
{
    return compute_day(schedule::teenth,
                       boost::gregorian::greg_weekday(boost::gregorian::Wednesday));
}

auto scheduler::thursteenth() const -> boost::gregorian::date
{
    return compute_day(schedule::teenth,
                       boost::gregorian::greg_weekday(boost::gregorian::Thursday));
}

auto scheduler::friteenth() const -> boost::gregorian::date
{
    return compute_day(schedule::teenth,
                       boost::gregorian::greg_weekday(boost::gregorian::Friday));
}

auto scheduler::saturteenth() const -> boost::gregorian::date
{
    return compute_day(schedule::teenth,
                       boost::gregorian::greg_weekday(boost::gregorian::Saturday));
}

auto scheduler::sunteenth() const -> boost::gregorian::date
{
    return compute_day(schedule::teenth,
                       boost::gregorian::greg_weekday(boost::gregorian::Sunday));
}

/* Helper to generate repeated methods */
#define MEETUP_DEFINE_NTH_METHOD(NTH, SCHED_ENUM)                                      \
auto scheduler::NTH##_monday() const -> boost::gregorian::date                        \
{                                                                                     \
    return compute_day(schedule::SCHED_ENUM,                                          \
                       boost::gregorian::greg_weekday(boost::gregorian::Monday));     \
}                                                                                     \
auto scheduler::NTH##_tuesday() const -> boost::gregorian::date                       \
{                                                                                     \
    return compute_day(schedule::SCHED_ENUM,                                          \
                       boost::gregorian::greg_weekday(boost::gregorian::Tuesday));    \
}                                                                                     \
auto scheduler::NTH##_wednesday() const -> boost::gregorian::date                     \
{                                                                                     \
    return compute_day(schedule::SCHED_ENUM,                                          \
                       boost::gregorian::greg_weekday(boost::gregorian::Wednesday));  \
}                                                                                     \
auto scheduler::NTH##_thursday() const -> boost::gregorian::date                      \
{                                                                                     \
    return compute_day(schedule::SCHED_ENUM,                                          \
                       boost::gregorian::greg_weekday(boost::gregorian::Thursday));   \
}                                                                                     \
auto scheduler::NTH##_friday() const -> boost::gregorian::date                        \
{                                                                                     \
    return compute_day(schedule::SCHED_ENUM,                                          \
                       boost::gregorian::greg_weekday(boost::gregorian::Friday));     \
}                                                                                     \
auto scheduler::NTH##_saturday() const -> boost::gregorian::date                      \
{                                                                                     \
    return compute_day(schedule::SCHED_ENUM,                                          \
                       boost::gregorian::greg_weekday(boost::gregorian::Saturday));   \
}                                                                                     \
auto scheduler::NTH##_sunday() const -> boost::gregorian::date                        \
{                                                                                     \
    return compute_day(schedule::SCHED_ENUM,                                          \
                       boost::gregorian::greg_weekday(boost::gregorian::Sunday));     \
}

MEETUP_DEFINE_NTH_METHOD(first, first)
MEETUP_DEFINE_NTH_METHOD(second, second)
MEETUP_DEFINE_NTH_METHOD(third, third)
MEETUP_DEFINE_NTH_METHOD(fourth, fourth)
MEETUP_DEFINE_NTH_METHOD(last, last)

#undef MEETUP_DEFINE_NTH_METHOD

}  // namespace meetup
