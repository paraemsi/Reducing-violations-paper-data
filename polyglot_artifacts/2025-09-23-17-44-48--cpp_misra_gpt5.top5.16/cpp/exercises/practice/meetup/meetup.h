#ifndef MEETUP_H
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

enum class weekday : std::int32_t {
    sunday = 0,
    monday = 1,
    tuesday = 2,
    wednesday = 3,
    thursday = 4,
    friday = 5,
    saturday = 6
};

enum class schedule : std::int32_t {
    first = 0,
    second = 1,
    third = 2,
    fourth = 3,
    last = 4,
    teenth = 5
};

class scheduler {
public:
    scheduler(std::int32_t year, std::uint32_t month) noexcept;
    boost::gregorian::date day(weekday wd, schedule sch) const;

    // teenth
    boost::gregorian::date monteenth() const;
    boost::gregorian::date tuesteenth() const;
    boost::gregorian::date wednesteenth() const;
    boost::gregorian::date thursteenth() const;
    boost::gregorian::date friteenth() const;
    boost::gregorian::date saturteenth() const;
    boost::gregorian::date sunteenth() const;

    // first
    boost::gregorian::date first_monday() const;
    boost::gregorian::date first_tuesday() const;
    boost::gregorian::date first_wednesday() const;
    boost::gregorian::date first_thursday() const;
    boost::gregorian::date first_friday() const;
    boost::gregorian::date first_saturday() const;
    boost::gregorian::date first_sunday() const;

    // second
    boost::gregorian::date second_monday() const;
    boost::gregorian::date second_tuesday() const;
    boost::gregorian::date second_wednesday() const;
    boost::gregorian::date second_thursday() const;
    boost::gregorian::date second_friday() const;
    boost::gregorian::date second_saturday() const;
    boost::gregorian::date second_sunday() const;

    // third
    boost::gregorian::date third_monday() const;
    boost::gregorian::date third_tuesday() const;
    boost::gregorian::date third_wednesday() const;
    boost::gregorian::date third_thursday() const;
    boost::gregorian::date third_friday() const;
    boost::gregorian::date third_saturday() const;
    boost::gregorian::date third_sunday() const;

    // fourth
    boost::gregorian::date fourth_monday() const;
    boost::gregorian::date fourth_tuesday() const;
    boost::gregorian::date fourth_wednesday() const;
    boost::gregorian::date fourth_thursday() const;
    boost::gregorian::date fourth_friday() const;
    boost::gregorian::date fourth_saturday() const;
    boost::gregorian::date fourth_sunday() const;

    // last
    boost::gregorian::date last_monday() const;
    boost::gregorian::date last_tuesday() const;
    boost::gregorian::date last_wednesday() const;
    boost::gregorian::date last_thursday() const;
    boost::gregorian::date last_friday() const;
    boost::gregorian::date last_saturday() const;
    boost::gregorian::date last_sunday() const;

private:
    std::int32_t year_;
    std::uint32_t month_;
};

}  // namespace meetup

#endif // MEETUP_H
