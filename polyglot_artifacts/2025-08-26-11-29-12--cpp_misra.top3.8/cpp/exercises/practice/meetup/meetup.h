#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <string>

namespace meetup {

typedef std::int32_t year_t;
typedef std::uint8_t month_t;
typedef std::uint8_t day_t;

// Forward declaration of scheduler class
class scheduler {
public:
    scheduler(year_t year, month_t month);

    day_t monteenth() const;
    day_t tuesteenth() const;
    day_t wednesteenth() const;
    day_t thursteenth() const;
    day_t friteenth() const;
    day_t saturteenth() const;
    day_t sunteenth() const;

    day_t first_monday() const;
    day_t first_tuesday() const;
    day_t first_wednesday() const;
    day_t first_thursday() const;
    day_t first_friday() const;
    day_t first_saturday() const;
    day_t first_sunday() const;

    day_t second_monday() const;
    day_t second_tuesday() const;
    day_t second_wednesday() const;
    day_t second_thursday() const;
    day_t second_friday() const;
    day_t second_saturday() const;
    day_t second_sunday() const;

    day_t third_monday() const;
    day_t third_tuesday() const;
    day_t third_wednesday() const;
    day_t third_thursday() const;
    day_t third_friday() const;
    day_t third_saturday() const;
    day_t third_sunday() const;

    day_t fourth_monday() const;
    day_t fourth_tuesday() const;
    day_t fourth_wednesday() const;
    day_t fourth_thursday() const;
    day_t fourth_friday() const;
    day_t fourth_saturday() const;
    day_t fourth_sunday() const;

    day_t last_monday() const;
    day_t last_tuesday() const;
    day_t last_wednesday() const;
    day_t last_thursday() const;
    day_t last_friday() const;
    day_t last_saturday() const;
    day_t last_sunday() const;

private:
    month_t m_month;
    year_t m_year;
};

}  // namespace meetup

#endif // MEETUP_H
