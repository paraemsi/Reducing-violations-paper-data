#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

enum class Schedule {
    first,
    second,
    third,
    fourth,
    last,
    teenth
};

using year_t  = std::int32_t;
using month_t = std::uint32_t;
using date_t  = boost::gregorian::date;

class scheduler {
public:
    scheduler(year_t year, month_t month) noexcept;

    date_t get_day(boost::date_time::weekdays week_day, Schedule schedule) const;

    /* 'teenth' helpers */
    date_t monteenth() const;
    date_t tuesteenth() const;
    date_t wednesteenth() const;
    date_t thursteenth() const;
    date_t friteenth() const;
    date_t saturteenth() const;
    date_t sunteenth() const;

    /* first */
    date_t first_monday() const;
    date_t first_tuesday() const;
    date_t first_wednesday() const;
    date_t first_thursday() const;
    date_t first_friday() const;
    date_t first_saturday() const;
    date_t first_sunday() const;

    /* second */
    date_t second_monday() const;
    date_t second_tuesday() const;
    date_t second_wednesday() const;
    date_t second_thursday() const;
    date_t second_friday() const;
    date_t second_saturday() const;
    date_t second_sunday() const;

    /* third */
    date_t third_monday() const;
    date_t third_tuesday() const;
    date_t third_wednesday() const;
    date_t third_thursday() const;
    date_t third_friday() const;
    date_t third_saturday() const;
    date_t third_sunday() const;

    /* fourth */
    date_t fourth_monday() const;
    date_t fourth_tuesday() const;
    date_t fourth_wednesday() const;
    date_t fourth_thursday() const;
    date_t fourth_friday() const;
    date_t fourth_saturday() const;
    date_t fourth_sunday() const;

    /* last */
    date_t last_monday() const;
    date_t last_tuesday() const;
    date_t last_wednesday() const;
    date_t last_thursday() const;
    date_t last_friday() const;
    date_t last_saturday() const;
    date_t last_sunday() const;

private:
    year_t  m_year;
    month_t m_month;
};

}  // namespace meetup

#endif // MEETUP_H
