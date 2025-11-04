#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

// Weekday enumerator with Sunday as 0 to align with common calendar indexing
enum class weekday : std::uint32_t {
    Sunday    = 0U,
    Monday    = 1U,
    Tuesday   = 2U,
    Wednesday = 3U,
    Thursday  = 4U,
    Friday    = 5U,
    Saturday  = 6U
};

// Week specifier for the meetup
enum class schedule : std::uint32_t {
    first,
    second,
    third,
    fourth,
    last,
    teenth
};

// Schedules meetups for a given month/year.
class scheduler {
public:
    scheduler(std::uint32_t year, std::uint32_t month) noexcept;
    std::uint32_t day(weekday wd, schedule s) const noexcept;

    // teenth weekdays
    boost::gregorian::date monteenth() const noexcept;
    boost::gregorian::date tuesteenth() const noexcept;
    boost::gregorian::date wednesteenth() const noexcept;
    boost::gregorian::date thursteenth() const noexcept;
    boost::gregorian::date friteenth() const noexcept;
    boost::gregorian::date saturteenth() const noexcept;
    boost::gregorian::date sunteenth() const noexcept;

    // first weekdays
    boost::gregorian::date first_monday() const noexcept;
    boost::gregorian::date first_tuesday() const noexcept;
    boost::gregorian::date first_wednesday() const noexcept;
    boost::gregorian::date first_thursday() const noexcept;
    boost::gregorian::date first_friday() const noexcept;
    boost::gregorian::date first_saturday() const noexcept;
    boost::gregorian::date first_sunday() const noexcept;

    // second weekdays
    boost::gregorian::date second_monday() const noexcept;
    boost::gregorian::date second_tuesday() const noexcept;
    boost::gregorian::date second_wednesday() const noexcept;
    boost::gregorian::date second_thursday() const noexcept;
    boost::gregorian::date second_friday() const noexcept;
    boost::gregorian::date second_saturday() const noexcept;
    boost::gregorian::date second_sunday() const noexcept;

    // third weekdays
    boost::gregorian::date third_monday() const noexcept;
    boost::gregorian::date third_tuesday() const noexcept;
    boost::gregorian::date third_wednesday() const noexcept;
    boost::gregorian::date third_thursday() const noexcept;
    boost::gregorian::date third_friday() const noexcept;
    boost::gregorian::date third_saturday() const noexcept;
    boost::gregorian::date third_sunday() const noexcept;

    // fourth weekdays
    boost::gregorian::date fourth_monday() const noexcept;
    boost::gregorian::date fourth_tuesday() const noexcept;
    boost::gregorian::date fourth_wednesday() const noexcept;
    boost::gregorian::date fourth_thursday() const noexcept;
    boost::gregorian::date fourth_friday() const noexcept;
    boost::gregorian::date fourth_saturday() const noexcept;
    boost::gregorian::date fourth_sunday() const noexcept;

    // last weekdays
    boost::gregorian::date last_monday() const noexcept;
    boost::gregorian::date last_tuesday() const noexcept;
    boost::gregorian::date last_wednesday() const noexcept;
    boost::gregorian::date last_thursday() const noexcept;
    boost::gregorian::date last_friday() const noexcept;
    boost::gregorian::date last_saturday() const noexcept;
    boost::gregorian::date last_sunday() const noexcept;

private:
    std::uint32_t year_;
    std::uint32_t month_;
};

}  // namespace meetup

#endif // MEETUP_H
