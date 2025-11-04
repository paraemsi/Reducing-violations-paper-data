#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

using int32 = std::int32_t;
using uint8 = std::uint8_t;

enum class weekday : uint8 {
    monday = 0U,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday
};

enum class schedule : uint8 {
    first = 0U,
    second,
    third,
    fourth,
    teenth,
    last
};

struct date final
{
    int32 year;
    uint8 month;
    uint8 day;
};

[[nodiscard]] date meetup_day(int32 year,
                              uint8 month,
                              weekday      wd,
                              schedule     sc);

class scheduler final
{
public:
    scheduler(boost::gregorian::months_of_year month, int32 year) noexcept;

    [[nodiscard]] boost::gregorian::date monteenth()   const;
    [[nodiscard]] boost::gregorian::date tuesteenth()  const;
    [[nodiscard]] boost::gregorian::date wednesteenth() const;
    [[nodiscard]] boost::gregorian::date thursteenth() const;
    [[nodiscard]] boost::gregorian::date friteenth()   const;
    [[nodiscard]] boost::gregorian::date saturteenth() const;
    [[nodiscard]] boost::gregorian::date sunteenth()   const;

    [[nodiscard]] boost::gregorian::date first_monday()      const;
    [[nodiscard]] boost::gregorian::date first_tuesday()     const;
    [[nodiscard]] boost::gregorian::date first_wednesday()   const;
    [[nodiscard]] boost::gregorian::date first_thursday()    const;
    [[nodiscard]] boost::gregorian::date first_friday()      const;
    [[nodiscard]] boost::gregorian::date first_saturday()    const;
    [[nodiscard]] boost::gregorian::date first_sunday()      const;

    [[nodiscard]] boost::gregorian::date second_monday()     const;
    [[nodiscard]] boost::gregorian::date second_tuesday()    const;
    [[nodiscard]] boost::gregorian::date second_wednesday()  const;
    [[nodiscard]] boost::gregorian::date second_thursday()   const;
    [[nodiscard]] boost::gregorian::date second_friday()     const;
    [[nodiscard]] boost::gregorian::date second_saturday()   const;
    [[nodiscard]] boost::gregorian::date second_sunday()     const;

    [[nodiscard]] boost::gregorian::date third_monday()      const;
    [[nodiscard]] boost::gregorian::date third_tuesday()     const;
    [[nodiscard]] boost::gregorian::date third_wednesday()   const;
    [[nodiscard]] boost::gregorian::date third_thursday()    const;
    [[nodiscard]] boost::gregorian::date third_friday()      const;
    [[nodiscard]] boost::gregorian::date third_saturday()    const;
    [[nodiscard]] boost::gregorian::date third_sunday()      const;

    [[nodiscard]] boost::gregorian::date fourth_monday()     const;
    [[nodiscard]] boost::gregorian::date fourth_tuesday()    const;
    [[nodiscard]] boost::gregorian::date fourth_wednesday()  const;
    [[nodiscard]] boost::gregorian::date fourth_thursday()   const;
    [[nodiscard]] boost::gregorian::date fourth_friday()     const;
    [[nodiscard]] boost::gregorian::date fourth_saturday()   const;
    [[nodiscard]] boost::gregorian::date fourth_sunday()     const;

    [[nodiscard]] boost::gregorian::date last_monday()       const;
    [[nodiscard]] boost::gregorian::date last_tuesday()      const;
    [[nodiscard]] boost::gregorian::date last_wednesday()    const;
    [[nodiscard]] boost::gregorian::date last_thursday()     const;
    [[nodiscard]] boost::gregorian::date last_friday()       const;
    [[nodiscard]] boost::gregorian::date last_saturday()     const;
    [[nodiscard]] boost::gregorian::date last_sunday()       const;

private:
    [[nodiscard]] boost::gregorian::date compute(schedule sc, weekday wd) const;

    boost::gregorian::months_of_year m_month;
    int32                            m_year;
};

}  // namespace meetup

#endif // MEETUP_H
