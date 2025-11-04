#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

class scheduler {
public:
    scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept;

    // Teenth weekdays
    boost::gregorian::date monteenth() const noexcept;
    boost::gregorian::date tuesteenth() const noexcept;
    boost::gregorian::date wednesteenth() const noexcept;
    boost::gregorian::date thursteenth() const noexcept;
    boost::gregorian::date friteenth() const noexcept;
    boost::gregorian::date saturteenth() const noexcept;
    boost::gregorian::date sunteenth() const noexcept;

    // First
    boost::gregorian::date first_monday() const noexcept;
    boost::gregorian::date first_tuesday() const noexcept;
    boost::gregorian::date first_wednesday() const noexcept;
    boost::gregorian::date first_thursday() const noexcept;
    boost::gregorian::date first_friday() const noexcept;
    boost::gregorian::date first_saturday() const noexcept;
    boost::gregorian::date first_sunday() const noexcept;

    // Second
    boost::gregorian::date second_monday() const noexcept;
    boost::gregorian::date second_tuesday() const noexcept;
    boost::gregorian::date second_wednesday() const noexcept;
    boost::gregorian::date second_thursday() const noexcept;
    boost::gregorian::date second_friday() const noexcept;
    boost::gregorian::date second_saturday() const noexcept;
    boost::gregorian::date second_sunday() const noexcept;

    // Third
    boost::gregorian::date third_monday() const noexcept;
    boost::gregorian::date third_tuesday() const noexcept;
    boost::gregorian::date third_wednesday() const noexcept;
    boost::gregorian::date third_thursday() const noexcept;
    boost::gregorian::date third_friday() const noexcept;
    boost::gregorian::date third_saturday() const noexcept;
    boost::gregorian::date third_sunday() const noexcept;

    // Fourth
    boost::gregorian::date fourth_monday() const noexcept;
    boost::gregorian::date fourth_tuesday() const noexcept;
    boost::gregorian::date fourth_wednesday() const noexcept;
    boost::gregorian::date fourth_thursday() const noexcept;
    boost::gregorian::date fourth_friday() const noexcept;
    boost::gregorian::date fourth_saturday() const noexcept;
    boost::gregorian::date fourth_sunday() const noexcept;

    // Last
    boost::gregorian::date last_monday() const noexcept;
    boost::gregorian::date last_tuesday() const noexcept;
    boost::gregorian::date last_wednesday() const noexcept;
    boost::gregorian::date last_thursday() const noexcept;
    boost::gregorian::date last_friday() const noexcept;
    boost::gregorian::date last_saturday() const noexcept;
    boost::gregorian::date last_sunday() const noexcept;

private:
    boost::gregorian::date find_teenth(boost::date_time::weekdays wd) const noexcept;
    boost::gregorian::date find_first(boost::date_time::weekdays wd) const noexcept;
    boost::gregorian::date find_nth(boost::date_time::weekdays wd, std::int32_t n) const noexcept;
    boost::gregorian::date find_last(boost::date_time::weekdays wd) const noexcept;

    const boost::gregorian::greg_month month_;
    const std::int32_t year_;
};

}  // namespace meetup

#endif // MEETUP_H
