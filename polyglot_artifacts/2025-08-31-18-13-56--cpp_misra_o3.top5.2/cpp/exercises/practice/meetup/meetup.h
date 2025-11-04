#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

using date = boost::gregorian::date;

class scheduler
{
public:
    scheduler(std::int32_t year, std::uint32_t month) noexcept;

    /* - - - “teenth” queries - - - */
    [[nodiscard]] date monteenth() const noexcept;
    [[nodiscard]] date tuesteenth() const noexcept;
    [[nodiscard]] date wednesteenth() const noexcept;
    [[nodiscard]] date thursteenth() const noexcept;
    [[nodiscard]] date friteenth() const noexcept;
    [[nodiscard]] date saturteenth() const noexcept;
    [[nodiscard]] date sunteenth() const noexcept;

    /* - - - ordinal queries (first … fourth) - - - */
    [[nodiscard]] date first_monday() const;
    [[nodiscard]] date first_tuesday() const;
    [[nodiscard]] date first_wednesday() const;
    [[nodiscard]] date first_thursday() const;
    [[nodiscard]] date first_friday() const;
    [[nodiscard]] date first_saturday() const;
    [[nodiscard]] date first_sunday() const;

    [[nodiscard]] date second_monday() const;
    [[nodiscard]] date second_tuesday() const;
    [[nodiscard]] date second_wednesday() const;
    [[nodiscard]] date second_thursday() const;
    [[nodiscard]] date second_friday() const;
    [[nodiscard]] date second_saturday() const;
    [[nodiscard]] date second_sunday() const;

    [[nodiscard]] date third_monday() const;
    [[nodiscard]] date third_tuesday() const;
    [[nodiscard]] date third_wednesday() const;
    [[nodiscard]] date third_thursday() const;
    [[nodiscard]] date third_friday() const;
    [[nodiscard]] date third_saturday() const;
    [[nodiscard]] date third_sunday() const;

    [[nodiscard]] date fourth_monday() const;
    [[nodiscard]] date fourth_tuesday() const;
    [[nodiscard]] date fourth_wednesday() const;
    [[nodiscard]] date fourth_thursday() const;
    [[nodiscard]] date fourth_friday() const;
    [[nodiscard]] date fourth_saturday() const;
    [[nodiscard]] date fourth_sunday() const;

    /* - - - “last” queries - - - */
    [[nodiscard]] date last_monday() const;
    [[nodiscard]] date last_tuesday() const;
    [[nodiscard]] date last_wednesday() const;
    [[nodiscard]] date last_thursday() const;
    [[nodiscard]] date last_friday() const;
    [[nodiscard]] date last_saturday() const;
    [[nodiscard]] date last_sunday() const;

private:
    std::int32_t  m_year;
    std::uint32_t m_month;

    [[nodiscard]] date teenth(const boost::gregorian::greg_weekday& wd) const;
    [[nodiscard]] date nth(std::uint8_t index, const boost::gregorian::greg_weekday& wd) const;
    [[nodiscard]] date last(const boost::gregorian::greg_weekday& wd) const;
};

}  // namespace meetup

#endif // MEETUP_H
