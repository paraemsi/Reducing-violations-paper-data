#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
#include <cstdint>

namespace meetup {

/* -----------------------------------------------------------------------------
 *  scheduler implementation
 * -------------------------------------------------------------------------- */

scheduler::scheduler(boost::gregorian::greg_month month,
                     std::int32_t                year) noexcept
    : m_month(month), m_year(year)
{
}

auto scheduler::meetup_day(boost::gregorian::greg_weekday weekday,
                           schedule                       which) const
    -> boost::gregorian::date
{
    const boost::gregorian::date first_of_month{
        m_year,
        static_cast<unsigned short>(m_month),
        static_cast<unsigned short>(1U)};

    switch (which)
    {
        case schedule::teenth:
        {
            for (std::uint16_t d = 13U; d <= 19U; ++d)
            {
                const boost::gregorian::date candidate{
                    m_year,
                    static_cast<unsigned short>(m_month),
                    static_cast<unsigned short>(d)};
                if (candidate.day_of_week() == weekday)
                {
                    return candidate;
                }
            }
            throw std::logic_error("No teenth day found");
        }

        case schedule::last:
        {
            const unsigned short last_dom =
                static_cast<unsigned short>(
                    boost::gregorian::gregorian_calendar::end_of_month_day(
                        static_cast<int>(m_year),
                        static_cast<int>(m_month)));

            const boost::gregorian::date last_date{
                m_year,
                static_cast<unsigned short>(m_month),
                last_dom};

            const unsigned short diff =
                static_cast<unsigned short>(
                    (last_date.day_of_week().as_number() + 7U
                     - weekday.as_number()) % 7U);

            return last_date - boost::gregorian::days{diff};
        }

        default:
        {
            const std::uint8_t idx =
                static_cast<std::uint8_t>(
                    static_cast<std::uint8_t>(which) - 1U);

            const unsigned short offset =
                static_cast<unsigned short>(
                    (weekday.as_number() + 7U
                     - first_of_month.day_of_week().as_number()) % 7U);

            const unsigned short day =
                static_cast<unsigned short>(1U + offset + (7U * idx));

            return boost::gregorian::date{
                m_year,
                static_cast<unsigned short>(m_month),
                day};
        }
    }

    throw std::logic_error("Invalid schedule type");
}

/* Helper macro to reduce repetition */
#define MEETUP_GEN(NAME, WD_ENUM, SCH)                                                \
    auto scheduler::NAME() const -> boost::gregorian::date                            \
    {                                                                                 \
        /*  Build a greg_weekday from the Boost weekday enumerator value              \
         *  (e.g. boost::date_time::Monday).                                          \
         *  Using boost::gregorian::WD_ENUM directly is invalid — that name lives     \
         *  only in boost::date_time::weekdays.                                       \
         */                                                                           \
        const boost::gregorian::greg_weekday wd_obj{boost::date_time::WD_ENUM};       \
        return meetup_day(wd_obj, schedule::SCH);                                     \
    }

MEETUP_GEN(monteenth, Monday, teenth)
MEETUP_GEN(tuesteenth, Tuesday, teenth)
MEETUP_GEN(wednesteenth, Wednesday, teenth)
MEETUP_GEN(thursteenth, Thursday, teenth)
MEETUP_GEN(friteenth, Friday, teenth)
MEETUP_GEN(saturteenth, Saturday, teenth)
MEETUP_GEN(sunteenth, Sunday, teenth)

MEETUP_GEN(first_monday, Monday, first)
MEETUP_GEN(first_tuesday, Tuesday, first)
MEETUP_GEN(first_wednesday, Wednesday, first)
MEETUP_GEN(first_thursday, Thursday, first)
MEETUP_GEN(first_friday, Friday, first)
MEETUP_GEN(first_saturday, Saturday, first)
MEETUP_GEN(first_sunday, Sunday, first)

MEETUP_GEN(second_monday, Monday, second)
MEETUP_GEN(second_tuesday, Tuesday, second)
MEETUP_GEN(second_wednesday, Wednesday, second)
MEETUP_GEN(second_thursday, Thursday, second)
MEETUP_GEN(second_friday, Friday, second)
MEETUP_GEN(second_saturday, Saturday, second)
MEETUP_GEN(second_sunday, Sunday, second)

MEETUP_GEN(third_monday, Monday, third)
MEETUP_GEN(third_tuesday, Tuesday, third)
MEETUP_GEN(third_wednesday, Wednesday, third)
MEETUP_GEN(third_thursday, Thursday, third)
MEETUP_GEN(third_friday, Friday, third)
MEETUP_GEN(third_saturday, Saturday, third)
MEETUP_GEN(third_sunday, Sunday, third)

MEETUP_GEN(fourth_monday, Monday, fourth)
MEETUP_GEN(fourth_tuesday, Tuesday, fourth)
MEETUP_GEN(fourth_wednesday, Wednesday, fourth)
MEETUP_GEN(fourth_thursday, Thursday, fourth)
MEETUP_GEN(fourth_friday, Friday, fourth)
MEETUP_GEN(fourth_saturday, Saturday, fourth)
MEETUP_GEN(fourth_sunday, Sunday, fourth)

MEETUP_GEN(last_monday, Monday, last)
MEETUP_GEN(last_tuesday, Tuesday, last)
MEETUP_GEN(last_wednesday, Wednesday, last)
MEETUP_GEN(last_thursday, Thursday, last)
MEETUP_GEN(last_friday, Friday, last)
MEETUP_GEN(last_saturday, Saturday, last)
MEETUP_GEN(last_sunday, Sunday, last)

#undef MEETUP_GEN

} // namespace meetup

#if 0
auto meetup_day(std::int32_t year,
                std::uint8_t month,
                const std::chrono::weekday& day_of_week,
                schedule schedule_type) -> std::chrono::year_month_day
{
    const auto first_of_month =
        std::chrono::year_month_day{std::chrono::year{year},
                                    std::chrono::month{month},
                                    std::chrono::day{1U}};

    const std::chrono::sys_days first_of_month_sys{first_of_month};

    switch (schedule_type)
    {
        case schedule::teenth:
        {
            for (std::uint8_t d = 13U; d <= 19U; ++d)
            {
                const auto current =
                    std::chrono::year_month_day{std::chrono::year{year},
                                                std::chrono::month{month},
                                                std::chrono::day{d}};
                if (std::chrono::weekday{current} == day_of_week)
                {
                    return current;
                }
            }
            break; /* fall-through avoided – loop guarantees return */
        }

        case schedule::last:
        {
            /* Determine the last day of the month using sys_days arithmetic */
            const auto first_of_next_month =
                first_of_month + std::chrono::months{1};

            const std::chrono::sys_days first_of_next_month_sys{first_of_next_month};

            const std::chrono::sys_days last_day_sys =
                first_of_next_month_sys - std::chrono::days{1};

            const std::chrono::year_month_day last_day_ymd{last_day_sys};

            const std::chrono::weekday last_wd{last_day_ymd};

            const std::uint8_t diff =
                static_cast<std::uint8_t>(
                    (static_cast<std::uint8_t>(last_wd.c_encoding()) + 7U
                     - static_cast<std::uint8_t>(day_of_week.c_encoding())) % 7U);

            const std::chrono::sys_days result_sys =
                last_day_sys - std::chrono::days{diff};

            const std::chrono::year_month_day result_ymd{result_sys};

            return result_ymd;
        }

        default: /* first, second, third, fourth */
        {
            const std::uint8_t n =
                static_cast<std::uint8_t>(static_cast<std::uint8_t>(schedule_type) - 1U);

            const std::chrono::weekday first_wd{first_of_month};

            const std::uint8_t offset =
                static_cast<std::uint8_t>(
                    (static_cast<std::uint8_t>(day_of_week.c_encoding()) + 7U
                     - static_cast<std::uint8_t>(first_wd.c_encoding())) % 7U);

            const std::chrono::sys_days result_sys =
                first_of_month_sys + std::chrono::days{offset + (7U * n)};

            const std::chrono::year_month_day result_ymd{result_sys};

            if (result_ymd.month() != first_of_month.month())
            {
                throw std::logic_error("Requested date does not exist in this month");
            }

            return result_ymd;
        }
    }

    throw std::logic_error("Invalid schedule type");
}

} // namespace meetup
#endif // DISABLED_ALTERNATE_CHRONO_IMPL
