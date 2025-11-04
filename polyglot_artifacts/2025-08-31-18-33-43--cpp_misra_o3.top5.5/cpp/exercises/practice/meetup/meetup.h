#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

/* Enumeration describing which occurrence of the weekday is requested */
enum class schedule : std::uint8_t
{
    first  = 1U,
    second = 2U,
    third  = 3U,
    fourth = 4U,
    last   = 5U,
    teenth = 6U
};

/*  Calculate the exact meetup day
 *  year   : four-digit year (e.g. 2025)
 *  month  : 1–12 (January == 1)
 *  day_of_week : desired weekday (std::chrono::Sunday == 0 …)
 *  schedule_type : which occurrence in the month
 *  Returns a std::chrono::year_month_day representing the requested date.
 */
class scheduler
{
public:
    scheduler(boost::gregorian::greg_month month,
              std::int32_t                year) noexcept;

    /* “teenth” helpers */
    auto monteenth() const -> boost::gregorian::date;
    auto tuesteenth() const -> boost::gregorian::date;
    auto wednesteenth() const -> boost::gregorian::date;
    auto thursteenth() const -> boost::gregorian::date;
    auto friteenth() const -> boost::gregorian::date;
    auto saturteenth() const -> boost::gregorian::date;
    auto sunteenth() const -> boost::gregorian::date;

    /* first … fourth and last helpers */
    auto first_monday() const -> boost::gregorian::date;
    auto first_tuesday() const -> boost::gregorian::date;
    auto first_wednesday() const -> boost::gregorian::date;
    auto first_thursday() const -> boost::gregorian::date;
    auto first_friday() const -> boost::gregorian::date;
    auto first_saturday() const -> boost::gregorian::date;
    auto first_sunday() const -> boost::gregorian::date;

    auto second_monday() const -> boost::gregorian::date;
    auto second_tuesday() const -> boost::gregorian::date;
    auto second_wednesday() const -> boost::gregorian::date;
    auto second_thursday() const -> boost::gregorian::date;
    auto second_friday() const -> boost::gregorian::date;
    auto second_saturday() const -> boost::gregorian::date;
    auto second_sunday() const -> boost::gregorian::date;

    auto third_monday() const -> boost::gregorian::date;
    auto third_tuesday() const -> boost::gregorian::date;
    auto third_wednesday() const -> boost::gregorian::date;
    auto third_thursday() const -> boost::gregorian::date;
    auto third_friday() const -> boost::gregorian::date;
    auto third_saturday() const -> boost::gregorian::date;
    auto third_sunday() const -> boost::gregorian::date;

    auto fourth_monday() const -> boost::gregorian::date;
    auto fourth_tuesday() const -> boost::gregorian::date;
    auto fourth_wednesday() const -> boost::gregorian::date;
    auto fourth_thursday() const -> boost::gregorian::date;
    auto fourth_friday() const -> boost::gregorian::date;
    auto fourth_saturday() const -> boost::gregorian::date;
    auto fourth_sunday() const -> boost::gregorian::date;

    auto last_monday() const -> boost::gregorian::date;
    auto last_tuesday() const -> boost::gregorian::date;
    auto last_wednesday() const -> boost::gregorian::date;
    auto last_thursday() const -> boost::gregorian::date;
    auto last_friday() const -> boost::gregorian::date;
    auto last_saturday() const -> boost::gregorian::date;
    auto last_sunday() const -> boost::gregorian::date;

private:
    auto meetup_day(boost::gregorian::greg_weekday weekday,
                    schedule                       which) const
        -> boost::gregorian::date;

    boost::gregorian::greg_month m_month;
    std::int32_t                 m_year;
};

} // namespace meetup

#endif // MEETUP_H
