#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <string>

namespace meetup {

using year_t = std::int32_t;
using month_t = std::uint8_t;
using day_t = std::uint8_t;

class scheduler {
public:
    scheduler(month_t month, year_t year) noexcept;

    day_t monteenth() const noexcept;
    day_t tuesteenth() const noexcept;
    day_t wednesteenth() const noexcept;
    day_t thursteenth() const noexcept;
    day_t friteenth() const noexcept;
    day_t saturteenth() const noexcept;
    day_t sunteenth() const noexcept;

    day_t first_monday() const;
    day_t first_tuesday() const;
    day_t first_wednesday() const;
    day_t first_thursday() const;
    day_t first_friday() const;
    day_t first_saturday() const;
    day_t first_sunday() const;

    day_t second_monday() const noexcept;
    day_t second_tuesday() const noexcept;
    day_t second_wednesday() const noexcept;
    day_t second_thursday() const noexcept;
    day_t second_friday() const noexcept;
    day_t second_saturday() const noexcept;
    day_t second_sunday() const noexcept;

    day_t third_monday() const noexcept;
    day_t third_tuesday() const noexcept;
    day_t third_wednesday() const noexcept;
    day_t third_thursday() const noexcept;
    day_t third_friday() const noexcept;
    day_t third_saturday() const noexcept;
    day_t third_sunday() const noexcept;

    day_t fourth_monday() const noexcept;
    day_t fourth_tuesday() const noexcept;
    day_t fourth_wednesday() const noexcept;
    day_t fourth_thursday() const noexcept;
    day_t fourth_friday() const noexcept;
    day_t fourth_saturday() const noexcept;
    day_t fourth_sunday() const noexcept;

    day_t last_monday() const noexcept;
    day_t last_tuesday() const noexcept;
    day_t last_wednesday() const noexcept;
    day_t last_thursday() const noexcept;
    day_t last_friday() const noexcept;
    day_t last_saturday() const noexcept;
    day_t last_sunday() const noexcept;

private:
    month_t m_month;
    year_t m_year;
    day_t get_day(std::uint8_t weekday, std::uint8_t n) const noexcept;
    day_t get_teenth(std::uint8_t weekday) const noexcept;
    day_t get_last(std::uint8_t weekday) const noexcept;
};

}  // namespace meetup

#endif // MEETUP_H
