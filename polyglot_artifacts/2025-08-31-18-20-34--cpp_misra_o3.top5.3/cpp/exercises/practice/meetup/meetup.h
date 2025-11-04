#if !defined(MEETUP_H)
#define MEETUP_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <cstdint>

namespace meetup {

/* Which week of the month is requested */
enum class schedule
{
    first,
    second,
    third,
    fourth,
    last,
    teenth
};

/* Provide dates for a specific month of a year */
class scheduler final
{
public:
    /* month, year (e.g. boost::gregorian::May, 2013) */
    scheduler(boost::gregorian::months_of_year month,
              std::int32_t                      year) noexcept;

    [[nodiscard]] boost::gregorian::date
    day(const boost::gregorian::greg_weekday &day_of_week,
        schedule                              week) const;

    /* Teenth helpers */
    [[nodiscard]] boost::gregorian::date monteenth() const;
    [[nodiscard]] boost::gregorian::date tuesteenth() const;
    [[nodiscard]] boost::gregorian::date wednesteenth() const;
    [[nodiscard]] boost::gregorian::date thursteenth() const;
    [[nodiscard]] boost::gregorian::date friteenth() const;
    [[nodiscard]] boost::gregorian::date saturteenth() const;
    [[nodiscard]] boost::gregorian::date sunteenth() const;

    /* First-through-fourth helpers */
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

    /* Last helpers */
    [[nodiscard]] boost::gregorian::date last_monday() const;
    [[nodiscard]] boost::gregorian::date last_tuesday() const;
    [[nodiscard]] boost::gregorian::date last_wednesday() const;
    [[nodiscard]] boost::gregorian::date last_thursday() const;
    [[nodiscard]] boost::gregorian::date last_friday() const;
    [[nodiscard]] boost::gregorian::date last_saturday() const;
    [[nodiscard]] boost::gregorian::date last_sunday() const;

private:
    std::int32_t year_;
    std::uint8_t month_;
};

}  // namespace meetup

#endif // MEETUP_H
