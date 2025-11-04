#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

class scheduler
{
public:
    scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept;

    /* teenth days */
    [[nodiscard]] boost::gregorian::date monteenth() const;
    [[nodiscard]] boost::gregorian::date tuesteenth() const;
    [[nodiscard]] boost::gregorian::date wednesteenth() const;
    [[nodiscard]] boost::gregorian::date thursteenth() const;
    [[nodiscard]] boost::gregorian::date friteenth() const;
    [[nodiscard]] boost::gregorian::date saturteenth() const;
    [[nodiscard]] boost::gregorian::date sunteenth() const;

    /* first */
    [[nodiscard]] boost::gregorian::date first_monday() const;
    [[nodiscard]] boost::gregorian::date first_tuesday() const;
    [[nodiscard]] boost::gregorian::date first_wednesday() const;
    [[nodiscard]] boost::gregorian::date first_thursday() const;
    [[nodiscard]] boost::gregorian::date first_friday() const;
    [[nodiscard]] boost::gregorian::date first_saturday() const;
    [[nodiscard]] boost::gregorian::date first_sunday() const;

    /* second */
    [[nodiscard]] boost::gregorian::date second_monday() const;
    [[nodiscard]] boost::gregorian::date second_tuesday() const;
    [[nodiscard]] boost::gregorian::date second_wednesday() const;
    [[nodiscard]] boost::gregorian::date second_thursday() const;
    [[nodiscard]] boost::gregorian::date second_friday() const;
    [[nodiscard]] boost::gregorian::date second_saturday() const;
    [[nodiscard]] boost::gregorian::date second_sunday() const;

    /* third */
    [[nodiscard]] boost::gregorian::date third_monday() const;
    [[nodiscard]] boost::gregorian::date third_tuesday() const;
    [[nodiscard]] boost::gregorian::date third_wednesday() const;
    [[nodiscard]] boost::gregorian::date third_thursday() const;
    [[nodiscard]] boost::gregorian::date third_friday() const;
    [[nodiscard]] boost::gregorian::date third_saturday() const;
    [[nodiscard]] boost::gregorian::date third_sunday() const;

    /* fourth */
    [[nodiscard]] boost::gregorian::date fourth_monday() const;
    [[nodiscard]] boost::gregorian::date fourth_tuesday() const;
    [[nodiscard]] boost::gregorian::date fourth_wednesday() const;
    [[nodiscard]] boost::gregorian::date fourth_thursday() const;
    [[nodiscard]] boost::gregorian::date fourth_friday() const;
    [[nodiscard]] boost::gregorian::date fourth_saturday() const;
    [[nodiscard]] boost::gregorian::date fourth_sunday() const;

    /* last */
    [[nodiscard]] boost::gregorian::date last_monday() const;
    [[nodiscard]] boost::gregorian::date last_tuesday() const;
    [[nodiscard]] boost::gregorian::date last_wednesday() const;
    [[nodiscard]] boost::gregorian::date last_thursday() const;
    [[nodiscard]] boost::gregorian::date last_friday() const;
    [[nodiscard]] boost::gregorian::date last_saturday() const;
    [[nodiscard]] boost::gregorian::date last_sunday() const;

private:
    std::int32_t m_year;
    boost::gregorian::months_of_year m_month;

    [[nodiscard]] boost::gregorian::date
    nth_weekday(boost::date_time::weekdays target, std::uint32_t n) const;

    [[nodiscard]] boost::gregorian::date
    last_weekday(boost::date_time::weekdays target) const;

    [[nodiscard]] boost::gregorian::date
    teenth_weekday(boost::date_time::weekdays target) const;
};

}  // namespace meetup

#endif // MEETUP_H
