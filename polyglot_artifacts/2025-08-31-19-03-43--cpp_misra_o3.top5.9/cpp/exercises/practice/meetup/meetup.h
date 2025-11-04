#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

enum class schedule : std::uint8_t {
    first,
    second,
    third,
    fourth,
    last,
    teenth
};

class scheduler
{
public:
    scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept;

    /* teenth */
    [[nodiscard]] boost::gregorian::date monteenth()   const noexcept;
    [[nodiscard]] boost::gregorian::date tuesteenth()  const noexcept;
    [[nodiscard]] boost::gregorian::date wednesteenth() const noexcept;
    [[nodiscard]] boost::gregorian::date thursteenth() const noexcept;
    [[nodiscard]] boost::gregorian::date friteenth()   const noexcept;
    [[nodiscard]] boost::gregorian::date saturteenth() const noexcept;
    [[nodiscard]] boost::gregorian::date sunteenth()   const noexcept;

    /* first */
    [[nodiscard]] boost::gregorian::date first_monday()    const noexcept;
    [[nodiscard]] boost::gregorian::date first_tuesday()   const noexcept;
    [[nodiscard]] boost::gregorian::date first_wednesday() const noexcept;
    [[nodiscard]] boost::gregorian::date first_thursday()  const noexcept;
    [[nodiscard]] boost::gregorian::date first_friday()    const noexcept;
    [[nodiscard]] boost::gregorian::date first_saturday()  const noexcept;
    [[nodiscard]] boost::gregorian::date first_sunday()    const noexcept;

    /* second */
    [[nodiscard]] boost::gregorian::date second_monday()    const noexcept;
    [[nodiscard]] boost::gregorian::date second_tuesday()   const noexcept;
    [[nodiscard]] boost::gregorian::date second_wednesday() const noexcept;
    [[nodiscard]] boost::gregorian::date second_thursday()  const noexcept;
    [[nodiscard]] boost::gregorian::date second_friday()    const noexcept;
    [[nodiscard]] boost::gregorian::date second_saturday()  const noexcept;
    [[nodiscard]] boost::gregorian::date second_sunday()    const noexcept;

    /* third */
    [[nodiscard]] boost::gregorian::date third_monday()    const noexcept;
    [[nodiscard]] boost::gregorian::date third_tuesday()   const noexcept;
    [[nodiscard]] boost::gregorian::date third_wednesday() const noexcept;
    [[nodiscard]] boost::gregorian::date third_thursday()  const noexcept;
    [[nodiscard]] boost::gregorian::date third_friday()    const noexcept;
    [[nodiscard]] boost::gregorian::date third_saturday()  const noexcept;
    [[nodiscard]] boost::gregorian::date third_sunday()    const noexcept;

    /* fourth */
    [[nodiscard]] boost::gregorian::date fourth_monday()    const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_tuesday()   const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_wednesday() const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_thursday()  const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_friday()    const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_saturday()  const noexcept;
    [[nodiscard]] boost::gregorian::date fourth_sunday()    const noexcept;

    /* last */
    [[nodiscard]] boost::gregorian::date last_monday()    const noexcept;
    [[nodiscard]] boost::gregorian::date last_tuesday()   const noexcept;
    [[nodiscard]] boost::gregorian::date last_wednesday() const noexcept;
    [[nodiscard]] boost::gregorian::date last_thursday()  const noexcept;
    [[nodiscard]] boost::gregorian::date last_friday()    const noexcept;
    [[nodiscard]] boost::gregorian::date last_saturday()  const noexcept;
    [[nodiscard]] boost::gregorian::date last_sunday()    const noexcept;

private:
    [[nodiscard]] boost::gregorian::date calculate(boost::date_time::weekdays wd,
                                                   schedule                sch) const noexcept;

    std::int32_t  m_year;
    std::uint32_t m_month;
};


}  // namespace meetup

#endif // MEETUP_H
