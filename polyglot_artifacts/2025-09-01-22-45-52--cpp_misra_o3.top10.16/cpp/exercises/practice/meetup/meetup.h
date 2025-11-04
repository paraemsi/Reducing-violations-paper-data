#if !defined(MEETUP_H)
#define MEETUP_H

#include <chrono>
#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

enum class schedule : std::uint8_t
{
    first   = 0U,
    second  = 1U,
    third   = 2U,
    fourth  = 3U,
    last    = 4U,
    teenth  = 5U
};

class scheduler
{
public:
    scheduler(boost::gregorian::months_of_year month_in,
              std::int32_t                     year_in) noexcept;

    [[nodiscard]] boost::gregorian::date monteenth()   const;
    [[nodiscard]] boost::gregorian::date tuesteenth()  const;
    [[nodiscard]] boost::gregorian::date wednesteenth() const;
    [[nodiscard]] boost::gregorian::date thursteenth() const;
    [[nodiscard]] boost::gregorian::date friteenth()   const;
    [[nodiscard]] boost::gregorian::date saturteenth() const;
    [[nodiscard]] boost::gregorian::date sunteenth()   const;

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
    [[nodiscard]] boost::gregorian::date get_date(boost::gregorian::greg_weekday wd,
                                                  schedule                         which) const;

    std::int32_t                     m_year;
    boost::gregorian::months_of_year m_month;
};


}  // namespace meetup

#endif // MEETUP_H
