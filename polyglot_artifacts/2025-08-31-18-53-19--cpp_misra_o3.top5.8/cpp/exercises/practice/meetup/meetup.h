#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

enum class week_t : std::uint8_t {
    first,
    second,
    third,
    fourth,
    last,
    teenth
};

class scheduler {
public:
    scheduler(boost::gregorian::months_of_year month_param,
              std::int32_t                     year_param) noexcept;

    [[nodiscard]] boost::gregorian::date
    day(boost::date_time::weekdays weekday_param,
        week_t                     schedule_param) const;

    /* Teenth helpers */
    [[nodiscard]] boost::gregorian::date monteenth() const;
    [[nodiscard]] boost::gregorian::date tuesteenth() const;
    [[nodiscard]] boost::gregorian::date wednesteenth() const;
    [[nodiscard]] boost::gregorian::date thursteenth() const;
    [[nodiscard]] boost::gregorian::date friteenth() const;
    [[nodiscard]] boost::gregorian::date saturteenth() const;
    [[nodiscard]] boost::gregorian::date sunteenth() const;

    /* Week helpers */
    [[nodiscard]] boost::gregorian::date first_monday() const;
    [[nodiscard]] boost::gregorian::date first_tuesday() const;
    [[nodiscard]] boost::gregorian::date first_wednesday() const;
    [[nodiscard]] boost::gregorian::date first_thursday() const;
    [[nodiscard]] boost::gregorian::date first_friday() const;
    [[nodiscard]] boost::gregorian::date first_saturday() const;
    [[nodiscard]] boost::gregorian::date first_sunday() const;

    [[nodiscard]] boost::gregorian::date second_monday() const;
    [[nodiscard]] boost::gregorian::date second_tuesday() const;
    [[nodiscard]] boost::gregorian::date second_wednesday() const;
    [[nodiscard]] boost::gregorian::date second_thursday() const;
    [[nodiscard]] boost::gregorian::date second_friday() const;
    [[nodiscard]] boost::gregorian::date second_saturday() const;
    [[nodiscard]] boost::gregorian::date second_sunday() const;

    [[nodiscard]] boost::gregorian::date third_monday() const;
    [[nodiscard]] boost::gregorian::date third_tuesday() const;
    [[nodiscard]] boost::gregorian::date third_wednesday() const;
    [[nodiscard]] boost::gregorian::date third_thursday() const;
    [[nodiscard]] boost::gregorian::date third_friday() const;
    [[nodiscard]] boost::gregorian::date third_saturday() const;
    [[nodiscard]] boost::gregorian::date third_sunday() const;

    [[nodiscard]] boost::gregorian::date fourth_monday() const;
    [[nodiscard]] boost::gregorian::date fourth_tuesday() const;
    [[nodiscard]] boost::gregorian::date fourth_wednesday() const;
    [[nodiscard]] boost::gregorian::date fourth_thursday() const;
    [[nodiscard]] boost::gregorian::date fourth_friday() const;
    [[nodiscard]] boost::gregorian::date fourth_saturday() const;
    [[nodiscard]] boost::gregorian::date fourth_sunday() const;

    [[nodiscard]] boost::gregorian::date last_monday() const;
    [[nodiscard]] boost::gregorian::date last_tuesday() const;
    [[nodiscard]] boost::gregorian::date last_wednesday() const;
    [[nodiscard]] boost::gregorian::date last_thursday() const;
    [[nodiscard]] boost::gregorian::date last_friday() const;
    [[nodiscard]] boost::gregorian::date last_saturday() const;
    [[nodiscard]] boost::gregorian::date last_sunday() const;

private:
    std::int32_t                         year_;
    boost::gregorian::months_of_year     month_;
};

}  // namespace meetup

#endif // MEETUP_H
