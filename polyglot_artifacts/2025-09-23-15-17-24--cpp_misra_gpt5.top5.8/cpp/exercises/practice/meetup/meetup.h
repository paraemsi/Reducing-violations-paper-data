#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

// Weekday enumeration: Sunday = 0 ... Saturday = 6
enum class weekday : std::uint8_t {
    sunday = 0U,
    monday = 1U,
    tuesday = 2U,
    wednesday = 3U,
    thursday = 4U,
    friday = 5U,
    saturday = 6U
};

// Which occurrence in the month to select
enum class schedule : std::uint8_t {
    first = 0U,
    second = 1U,
    third = 2U,
    fourth = 3U,
    last = 4U,
    teenth = 5U
};

// Simple date POD type
struct date {
    std::int32_t year;
    std::int32_t month; // 1..12
    std::int32_t day;   // 1..31
};

// Compute the meetup date for a given year/month, weekday and schedule.
// Returns a {year, month, day} triple.
date meetup_day(std::int32_t year, std::int32_t month, weekday wd, schedule sch);

// Scheduler API expected by tests
class scheduler {
public:
    scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept;

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
    boost::gregorian::months_of_year month_;
    std::int32_t year_;

    boost::gregorian::date nth_weekday(std::uint8_t n, boost::date_time::weekdays wd) const;
    boost::gregorian::date last_weekday(boost::date_time::weekdays wd) const;
    boost::gregorian::date teenth_weekday(boost::date_time::weekdays wd) const;
};

}  // namespace meetup

#endif // MEETUP_H
