#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

enum class weekday : std::uint8_t {
    sunday   = 0U,
    monday   = 1U,
    tuesday  = 2U,
    wednesday= 3U,
    thursday = 4U,
    friday   = 5U,
    saturday = 6U
};

enum class schedule : std::uint8_t {
    first  = 1U,
    second = 2U,
    third  = 3U,
    fourth = 4U,
    last   = 5U,   // placeholder value; handled specially
    teenth = 6U    // placeholder value; handled specially
};

/**
 * \brief Compute the exact meetup date that satisfies the given constraints.
 *
 * \param year     Four-digit year (e.g. 2025)
 * \param month    Calendar month in the range 1-12
 * \param wd       Desired weekday
 * \param sch      Desired schedule (first, second, …, teenth)
 *
 * \return A std::chrono::year_month_day representing the meetup date.
 *
 * \throws std::invalid_argument for invalid year/month arguments.
 * \throws std::logic_error      if the requested meetup day does not exist.
 */
class scheduler
{
public:
    scheduler(boost::gregorian::greg_month month, std::int32_t year) noexcept;

    [[nodiscard]] boost::gregorian::date monteenth()       const;
    [[nodiscard]] boost::gregorian::date tuesteenth()      const;
    [[nodiscard]] boost::gregorian::date wednesteenth()    const;
    [[nodiscard]] boost::gregorian::date thursteenth()     const;
    [[nodiscard]] boost::gregorian::date friteenth()       const;
    [[nodiscard]] boost::gregorian::date saturteenth()     const;
    [[nodiscard]] boost::gregorian::date sunteenth()       const;

    [[nodiscard]] boost::gregorian::date first_monday()    const;
    [[nodiscard]] boost::gregorian::date first_tuesday()   const;
    [[nodiscard]] boost::gregorian::date first_wednesday() const;
    [[nodiscard]] boost::gregorian::date first_thursday()  const;
    [[nodiscard]] boost::gregorian::date first_friday()    const;
    [[nodiscard]] boost::gregorian::date first_saturday()  const;
    [[nodiscard]] boost::gregorian::date first_sunday()    const;

    [[nodiscard]] boost::gregorian::date second_monday()    const;
    [[nodiscard]] boost::gregorian::date second_tuesday()   const;
    [[nodiscard]] boost::gregorian::date second_wednesday() const;
    [[nodiscard]] boost::gregorian::date second_thursday()  const;
    [[nodiscard]] boost::gregorian::date second_friday()    const;
    [[nodiscard]] boost::gregorian::date second_saturday()  const;
    [[nodiscard]] boost::gregorian::date second_sunday()    const;

    [[nodiscard]] boost::gregorian::date third_monday()    const;
    [[nodiscard]] boost::gregorian::date third_tuesday()   const;
    [[nodiscard]] boost::gregorian::date third_wednesday() const;
    [[nodiscard]] boost::gregorian::date third_thursday()  const;
    [[nodiscard]] boost::gregorian::date third_friday()    const;
    [[nodiscard]] boost::gregorian::date third_saturday()  const;
    [[nodiscard]] boost::gregorian::date third_sunday()    const;

    [[nodiscard]] boost::gregorian::date fourth_monday()    const;
    [[nodiscard]] boost::gregorian::date fourth_tuesday()   const;
    [[nodiscard]] boost::gregorian::date fourth_wednesday() const;
    [[nodiscard]] boost::gregorian::date fourth_thursday()  const;
    [[nodiscard]] boost::gregorian::date fourth_friday()    const;
    [[nodiscard]] boost::gregorian::date fourth_saturday()  const;
    [[nodiscard]] boost::gregorian::date fourth_sunday()    const;

    [[nodiscard]] boost::gregorian::date last_monday()    const;
    [[nodiscard]] boost::gregorian::date last_tuesday()   const;
    [[nodiscard]] boost::gregorian::date last_wednesday() const;
    [[nodiscard]] boost::gregorian::date last_thursday()  const;
    [[nodiscard]] boost::gregorian::date last_friday()    const;
    [[nodiscard]] boost::gregorian::date last_saturday()  const;
    [[nodiscard]] boost::gregorian::date last_sunday()    const;

private:
    boost::gregorian::greg_month m_month;
    std::int32_t                 m_year;

    [[nodiscard]] boost::gregorian::date
    nth_weekday(std::uint8_t nth, boost::date_time::weekdays wd) const;

    [[nodiscard]] boost::gregorian::date
    teenth_weekday(boost::date_time::weekdays wd) const;

    [[nodiscard]] boost::gregorian::date
    last_weekday(boost::date_time::weekdays wd) const;
};

// turn off in-header implementation, moved to cpp
#if 0  // implementation moved to cpp

// ----------  new scheduler implementation ------------------

scheduler::scheduler(boost::gregorian::greg_month month, std::int32_t year) noexcept
    : m_month{month}, m_year{year}
{
    /* constructor body intentionally empty */
}

boost::gregorian::date
scheduler::teenth_weekday(boost::date_time::weekdays wd) const
{
    for(std::uint32_t d = 13U; d <= 19U; ++d)
    {
        const boost::gregorian::date current{m_year, m_month, static_cast<unsigned short>(d)};
        if(current.day_of_week().as_number() == static_cast<unsigned short>(wd))
        {
            return current;
        }
    }
    throw std::logic_error("requested teenth weekday does not exist");
}

boost::gregorian::date
scheduler::nth_weekday(std::uint8_t nth, boost::date_time::weekdays wd) const
{
    if((nth == 0U) || (nth > 4U))
    {
        throw std::invalid_argument("nth must be 1-4");
    }

    const boost::gregorian::date first{m_year, m_month, 1U};
    const unsigned short first_wd{first.day_of_week().as_number()};
    const unsigned short target_wd{static_cast<unsigned short>(wd)};

    const unsigned short offset{static_cast<unsigned short>(
        (static_cast<int>(target_wd) - static_cast<int>(first_wd) + 7) % 7)};

    const unsigned short day_num{
        static_cast<unsigned short>(1U + offset + (7U * (nth - 1U)))};

    try
    {
        return boost::gregorian::date{m_year, m_month, day_num};
    }
    catch(const std::exception&)
    {
        throw std::logic_error("requested nth weekday does not exist");
    }
}

boost::gregorian::date
scheduler::last_weekday(boost::date_time::weekdays wd) const
{
    const unsigned short last_dom{
        boost::gregorian::gregorian_calendar::end_of_month_day(
            static_cast<int>(m_year),
            m_month.as_number())};

    for(std::int32_t d = static_cast<std::int32_t>(last_dom); d > 0; --d)
    {
        const boost::gregorian::date current{m_year, m_month, static_cast<unsigned short>(d)};
        if(current.day_of_week().as_number() == static_cast<unsigned short>(wd))
        {
            return current;
        }
    }
    throw std::logic_error("requested last weekday does not exist");
}

// Helper macro to generate the trivial one-liners.
#define MEETUP_DEFINE(name, expr) \
boost::gregorian::date scheduler::name() const { return (expr); }

MEETUP_DEFINE(monteenth,  teenth_weekday(boost::date_time::Monday))
MEETUP_DEFINE(tuesteenth, teenth_weekday(boost::date_time::Tuesday))
MEETUP_DEFINE(wednesteenth, teenth_weekday(boost::date_time::Wednesday))
MEETUP_DEFINE(thursteenth, teenth_weekday(boost::date_time::Thursday))
MEETUP_DEFINE(friteenth,  teenth_weekday(boost::date_time::Friday))
MEETUP_DEFINE(saturteenth, teenth_weekday(boost::date_time::Saturday))
MEETUP_DEFINE(sunteenth,  teenth_weekday(boost::date_time::Sunday))

MEETUP_DEFINE(first_monday,    nth_weekday(1U, boost::date_time::Monday))
MEETUP_DEFINE(first_tuesday,   nth_weekday(1U, boost::date_time::Tuesday))
MEETUP_DEFINE(first_wednesday, nth_weekday(1U, boost::date_time::Wednesday))
MEETUP_DEFINE(first_thursday,  nth_weekday(1U, boost::date_time::Thursday))
MEETUP_DEFINE(first_friday,    nth_weekday(1U, boost::date_time::Friday))
MEETUP_DEFINE(first_saturday,  nth_weekday(1U, boost::date_time::Saturday))
MEETUP_DEFINE(first_sunday,    nth_weekday(1U, boost::date_time::Sunday))

MEETUP_DEFINE(second_monday,    nth_weekday(2U, boost::date_time::Monday))
MEETUP_DEFINE(second_tuesday,   nth_weekday(2U, boost::date_time::Tuesday))
MEETUP_DEFINE(second_wednesday, nth_weekday(2U, boost::date_time::Wednesday))
MEETUP_DEFINE(second_thursday,  nth_weekday(2U, boost::date_time::Thursday))
MEETUP_DEFINE(second_friday,    nth_weekday(2U, boost::date_time::Friday))
MEETUP_DEFINE(second_saturday,  nth_weekday(2U, boost::date_time::Saturday))
MEETUP_DEFINE(second_sunday,    nth_weekday(2U, boost::date_time::Sunday))

MEETUP_DEFINE(third_monday,    nth_weekday(3U, boost::date_time::Monday))
MEETUP_DEFINE(third_tuesday,   nth_weekday(3U, boost::date_time::Tuesday))
MEETUP_DEFINE(third_wednesday, nth_weekday(3U, boost::date_time::Wednesday))
MEETUP_DEFINE(third_thursday,  nth_weekday(3U, boost::date_time::Thursday))
MEETUP_DEFINE(third_friday,    nth_weekday(3U, boost::date_time::Friday))
MEETUP_DEFINE(third_saturday,  nth_weekday(3U, boost::date_time::Saturday))
MEETUP_DEFINE(third_sunday,    nth_weekday(3U, boost::date_time::Sunday))

MEETUP_DEFINE(fourth_monday,    nth_weekday(4U, boost::date_time::Monday))
MEETUP_DEFINE(fourth_tuesday,   nth_weekday(4U, boost::date_time::Tuesday))
MEETUP_DEFINE(fourth_wednesday, nth_weekday(4U, boost::date_time::Wednesday))
MEETUP_DEFINE(fourth_thursday,  nth_weekday(4U, boost::date_time::Thursday))
MEETUP_DEFINE(fourth_friday,    nth_weekday(4U, boost::date_time::Friday))
MEETUP_DEFINE(fourth_saturday,  nth_weekday(4U, boost::date_time::Saturday))
MEETUP_DEFINE(fourth_sunday,    nth_weekday(4U, boost::date_time::Sunday))

MEETUP_DEFINE(last_monday,    last_weekday(boost::date_time::Monday))
MEETUP_DEFINE(last_tuesday,   last_weekday(boost::date_time::Tuesday))
MEETUP_DEFINE(last_wednesday, last_weekday(boost::date_time::Wednesday))
MEETUP_DEFINE(last_thursday,  last_weekday(boost::date_time::Thursday))
MEETUP_DEFINE(last_friday,    last_weekday(boost::date_time::Friday))
MEETUP_DEFINE(last_saturday,  last_weekday(boost::date_time::Saturday))
MEETUP_DEFINE(last_sunday,    last_weekday(boost::date_time::Sunday))

#undef MEETUP_DEFINE
#endif  // implementation moved to cpp

}  // namespace meetup

#endif // MEETUP_H
