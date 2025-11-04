#include "meetup.h"

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

#if 0   /* Legacy implementation disabled */
auto day(std::int32_t year,
         std::uint32_t month,
         std::chrono::weekday const& weekday,
         schedule const meeting_schedule) -> std::chrono::year_month_day
{

    const auto y = std::chrono::year{year};
    const auto m = std::chrono::month{month};

    if (meeting_schedule == schedule::teenth)
    {
        for (std::uint32_t d_val = 13U; d_val <= 19U; ++d_val)
        {
            const auto candidate = std::chrono::year_month_day{y, m, std::chrono::day{d_val}};
            if (std::chrono::weekday{candidate} == weekday)
            {
                return candidate;
            }
        }
    }
    else if (meeting_schedule == schedule::last)
    {
        const auto last_dom =
            std::chrono::year_month_day_last{y, std::chrono::month_day_last{m}}.day();

        const auto last_date = std::chrono::year_month_day{y, m, last_dom};
        const auto last_wd   = std::chrono::weekday{last_date};

        const std::uint32_t offset =
            (static_cast<std::uint32_t>(last_wd.c_encoding()) + 7U
             - static_cast<std::uint32_t>(weekday.c_encoding())) %
            7U;

        const auto target_day =
            std::chrono::day{static_cast<unsigned>(static_cast<unsigned>(last_dom) - offset)};

        return std::chrono::year_month_day{y, m, target_day};
    }
    else
    {
        std::uint32_t index = 0U;
        switch (meeting_schedule)
        {
            case schedule::first:  index = 0U; break;
            case schedule::second: index = 1U; break;
            case schedule::third:  index = 2U; break;
            case schedule::fourth: index = 3U; break;
            case schedule::fifth:  index = 4U; break;
            default:               index = 0U; break;
        }

        const auto first_date = std::chrono::year_month_day{y, m, std::chrono::day{1U}};
        const auto first_wd   = std::chrono::weekday{first_date};

        const std::uint32_t diff =
            (static_cast<std::uint32_t>(weekday.c_encoding()) + 7U
             - static_cast<std::uint32_t>(first_wd.c_encoding())) %
            7U;

        const std::uint32_t day_value = 1U + diff + (7U * index);

        return std::chrono::year_month_day{y, m, std::chrono::day{day_value}};
    }

    /* Should never be reached; added to silence potential compiler warnings */
    return std::chrono::year_month_day{};
}
#endif /* legacy code */

scheduler::scheduler(boost::gregorian::greg_month month, std::int32_t year) noexcept
    : m_month(month),
      m_year(year)
{
}

auto scheduler::compute(schedule const sched,
                        boost::date_time::weekdays const wd) const -> boost::gregorian::date
{
    using boost::gregorian::date;
    using boost::gregorian::greg_weekday;
    using boost::gregorian::gregorian_calendar;

    if (sched == schedule::teenth)
    {
        for (std::uint32_t d = 13U; d <= 19U; ++d)
        {
            const date candidate(static_cast<std::int32_t>(m_year),
                                 static_cast<unsigned>(m_month.as_number()),
                                 static_cast<unsigned>(d));
            if (candidate.day_of_week() == greg_weekday(wd))
            {
                return candidate;
            }
        }
    }
    else if (sched == schedule::last)
    {
        const unsigned last_dom =
            gregorian_calendar::end_of_month_day(static_cast<std::int32_t>(m_year),
                                                 static_cast<unsigned>(m_month.as_number()));

        const date last_date(static_cast<std::int32_t>(m_year),
                             static_cast<unsigned>(m_month.as_number()),
                             last_dom);

        const std::uint32_t offset =
            static_cast<std::uint32_t>(last_date.day_of_week().as_number() + 7U
                                       - static_cast<std::uint32_t>(greg_weekday(wd).as_number())) %
            7U;

        return last_date - boost::gregorian::days(offset);
    }
    else
    {
        const date first_date(static_cast<std::int32_t>(m_year),
                              static_cast<unsigned>(m_month.as_number()),
                              1U);

        const std::uint32_t diff =
            static_cast<std::uint32_t>(greg_weekday(wd).as_number() + 7U
                                       - static_cast<std::uint32_t>(first_date.day_of_week().as_number())) %
            7U;

        std::uint32_t index = 0U;
        switch (sched)
        {
            case schedule::first:  index = 0U; break;
            case schedule::second: index = 1U; break;
            case schedule::third:  index = 2U; break;
            case schedule::fourth: index = 3U; break;
            case schedule::fifth:  index = 4U; break;
            default:               index = 0U; break;
        }

        const std::uint32_t day_value = 1U + diff + (7U * index);

        return date(static_cast<std::int32_t>(m_year),
                    static_cast<unsigned>(m_month.as_number()),
                    day_value);
    }

    /* Should never be reached */
    return boost::gregorian::date(boost::gregorian::not_a_date_time);
}

/* ---- teenth helpers ---- */
auto scheduler::monteenth() const -> boost::gregorian::date { return compute(schedule::teenth, boost::date_time::Monday); }
auto scheduler::tuesteenth() const -> boost::gregorian::date { return compute(schedule::teenth, boost::date_time::Tuesday); }
auto scheduler::wednesteenth() const -> boost::gregorian::date { return compute(schedule::teenth, boost::date_time::Wednesday); }
auto scheduler::thursteenth() const -> boost::gregorian::date { return compute(schedule::teenth, boost::date_time::Thursday); }
auto scheduler::friteenth() const -> boost::gregorian::date { return compute(schedule::teenth, boost::date_time::Friday); }
auto scheduler::saturteenth() const -> boost::gregorian::date { return compute(schedule::teenth, boost::date_time::Saturday); }
auto scheduler::sunteenth() const -> boost::gregorian::date { return compute(schedule::teenth, boost::date_time::Sunday); }

/* ---- first ---- */
auto scheduler::first_monday() const -> boost::gregorian::date { return compute(schedule::first, boost::date_time::Monday); }
auto scheduler::first_tuesday() const -> boost::gregorian::date { return compute(schedule::first, boost::date_time::Tuesday); }
auto scheduler::first_wednesday() const -> boost::gregorian::date { return compute(schedule::first, boost::date_time::Wednesday); }
auto scheduler::first_thursday() const -> boost::gregorian::date { return compute(schedule::first, boost::date_time::Thursday); }
auto scheduler::first_friday() const -> boost::gregorian::date { return compute(schedule::first, boost::date_time::Friday); }
auto scheduler::first_saturday() const -> boost::gregorian::date { return compute(schedule::first, boost::date_time::Saturday); }
auto scheduler::first_sunday() const -> boost::gregorian::date { return compute(schedule::first, boost::date_time::Sunday); }

/* ---- second ---- */
auto scheduler::second_monday() const -> boost::gregorian::date { return compute(schedule::second, boost::date_time::Monday); }
auto scheduler::second_tuesday() const -> boost::gregorian::date { return compute(schedule::second, boost::date_time::Tuesday); }
auto scheduler::second_wednesday() const -> boost::gregorian::date { return compute(schedule::second, boost::date_time::Wednesday); }
auto scheduler::second_thursday() const -> boost::gregorian::date { return compute(schedule::second, boost::date_time::Thursday); }
auto scheduler::second_friday() const -> boost::gregorian::date { return compute(schedule::second, boost::date_time::Friday); }
auto scheduler::second_saturday() const -> boost::gregorian::date { return compute(schedule::second, boost::date_time::Saturday); }
auto scheduler::second_sunday() const -> boost::gregorian::date { return compute(schedule::second, boost::date_time::Sunday); }

/* ---- third ---- */
auto scheduler::third_monday() const -> boost::gregorian::date { return compute(schedule::third, boost::date_time::Monday); }
auto scheduler::third_tuesday() const -> boost::gregorian::date { return compute(schedule::third, boost::date_time::Tuesday); }
auto scheduler::third_wednesday() const -> boost::gregorian::date { return compute(schedule::third, boost::date_time::Wednesday); }
auto scheduler::third_thursday() const -> boost::gregorian::date { return compute(schedule::third, boost::date_time::Thursday); }
auto scheduler::third_friday() const -> boost::gregorian::date { return compute(schedule::third, boost::date_time::Friday); }
auto scheduler::third_saturday() const -> boost::gregorian::date { return compute(schedule::third, boost::date_time::Saturday); }
auto scheduler::third_sunday() const -> boost::gregorian::date { return compute(schedule::third, boost::date_time::Sunday); }

/* ---- fourth ---- */
auto scheduler::fourth_monday() const -> boost::gregorian::date { return compute(schedule::fourth, boost::date_time::Monday); }
auto scheduler::fourth_tuesday() const -> boost::gregorian::date { return compute(schedule::fourth, boost::date_time::Tuesday); }
auto scheduler::fourth_wednesday() const -> boost::gregorian::date { return compute(schedule::fourth, boost::date_time::Wednesday); }
auto scheduler::fourth_thursday() const -> boost::gregorian::date { return compute(schedule::fourth, boost::date_time::Thursday); }
auto scheduler::fourth_friday() const -> boost::gregorian::date { return compute(schedule::fourth, boost::date_time::Friday); }
auto scheduler::fourth_saturday() const -> boost::gregorian::date { return compute(schedule::fourth, boost::date_time::Saturday); }
auto scheduler::fourth_sunday() const -> boost::gregorian::date { return compute(schedule::fourth, boost::date_time::Sunday); }

/* ---- last ---- */
auto scheduler::last_monday() const -> boost::gregorian::date { return compute(schedule::last, boost::date_time::Monday); }
auto scheduler::last_tuesday() const -> boost::gregorian::date { return compute(schedule::last, boost::date_time::Tuesday); }
auto scheduler::last_wednesday() const -> boost::gregorian::date { return compute(schedule::last, boost::date_time::Wednesday); }
auto scheduler::last_thursday() const -> boost::gregorian::date { return compute(schedule::last, boost::date_time::Thursday); }
auto scheduler::last_friday() const -> boost::gregorian::date { return compute(schedule::last, boost::date_time::Friday); }
auto scheduler::last_saturday() const -> boost::gregorian::date { return compute(schedule::last, boost::date_time::Saturday); }
auto scheduler::last_sunday() const -> boost::gregorian::date { return compute(schedule::last, boost::date_time::Sunday); }

}  // namespace meetup
