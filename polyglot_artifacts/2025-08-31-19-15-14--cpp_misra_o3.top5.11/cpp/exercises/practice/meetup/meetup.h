#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

//  Week selectors
enum class schedule : std::uint8_t {
    first  = 1U,
    second = 2U,
    third  = 3U,
    fourth = 4U,
    last   = 5U,
    teenth = 6U
};

/**
 *  A scheduler represents one calendar month of a given year.
 *  It offers convenience helpers such as `monteenth()`,
 *  `first_monday()`, `last_friday()`, etc., each of which
 *  returns a Boost `date` object that satisfies the request.
 */
class scheduler
{
public:
    scheduler(boost::gregorian::greg_month month, std::int32_t year) noexcept;

    //  Teenth helpers
    [[nodiscard]] boost::gregorian::date monteenth()   const;
    [[nodiscard]] boost::gregorian::date tuesteenth()  const;
    [[nodiscard]] boost::gregorian::date wednesteenth()const;
    [[nodiscard]] boost::gregorian::date thursteenth() const;
    [[nodiscard]] boost::gregorian::date friteenth()   const;
    [[nodiscard]] boost::gregorian::date saturteenth() const;
    [[nodiscard]] boost::gregorian::date sunteenth()   const;

    //  First-week helpers
    [[nodiscard]] boost::gregorian::date first_monday()    const;
    [[nodiscard]] boost::gregorian::date first_tuesday()   const;
    [[nodiscard]] boost::gregorian::date first_wednesday() const;
    [[nodiscard]] boost::gregorian::date first_thursday()  const;
    [[nodiscard]] boost::gregorian::date first_friday()    const;
    [[nodiscard]] boost::gregorian::date first_saturday()  const;
    [[nodiscard]] boost::gregorian::date first_sunday()    const;

    //  Second-week helpers
    [[nodiscard]] boost::gregorian::date second_monday()    const;
    [[nodiscard]] boost::gregorian::date second_tuesday()   const;
    [[nodiscard]] boost::gregorian::date second_wednesday() const;
    [[nodiscard]] boost::gregorian::date second_thursday()  const;
    [[nodiscard]] boost::gregorian::date second_friday()    const;
    [[nodiscard]] boost::gregorian::date second_saturday()  const;
    [[nodiscard]] boost::gregorian::date second_sunday()    const;

    //  Third-week helpers
    [[nodiscard]] boost::gregorian::date third_monday()    const;
    [[nodiscard]] boost::gregorian::date third_tuesday()   const;
    [[nodiscard]] boost::gregorian::date third_wednesday() const;
    [[nodiscard]] boost::gregorian::date third_thursday()  const;
    [[nodiscard]] boost::gregorian::date third_friday()    const;
    [[nodiscard]] boost::gregorian::date third_saturday()  const;
    [[nodiscard]] boost::gregorian::date third_sunday()    const;

    //  Fourth-week helpers
    [[nodiscard]] boost::gregorian::date fourth_monday()    const;
    [[nodiscard]] boost::gregorian::date fourth_tuesday()   const;
    [[nodiscard]] boost::gregorian::date fourth_wednesday() const;
    [[nodiscard]] boost::gregorian::date fourth_thursday()  const;
    [[nodiscard]] boost::gregorian::date fourth_friday()    const;
    [[nodiscard]] boost::gregorian::date fourth_saturday()  const;
    [[nodiscard]] boost::gregorian::date fourth_sunday()    const;

    //  Last-week helpers
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
    compute_date(schedule selector, std::uint8_t weekday_index) const;
};

}  // namespace meetup

#endif // MEETUP_H
