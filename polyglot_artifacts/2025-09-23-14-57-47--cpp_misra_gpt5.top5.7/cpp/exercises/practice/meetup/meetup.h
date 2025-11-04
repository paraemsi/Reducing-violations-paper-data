#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

// Monday-based indexing: Monday = 0, ..., Sunday = 6
enum class weekday : std::uint8_t {
    monday = 0U,
    tuesday = 1U,
    wednesday = 2U,
    thursday = 3U,
    friday = 4U,
    saturday = 5U,
    sunday = 6U
};

enum class schedule : std::uint8_t {
    first = 1U,
    second = 2U,
    third = 3U,
    fourth = 4U,
    last = 5U,
    teenth = 6U
};

class scheduler {
public:
    scheduler(std::int32_t year, std::uint32_t month) noexcept;

    // Teenth occurrences
    boost::gregorian::date monteenth() const;
    boost::gregorian::date tuesteenth() const;
    boost::gregorian::date wednesteenth() const;
    boost::gregorian::date thursteenth() const;
    boost::gregorian::date friteenth() const;
    boost::gregorian::date saturteenth() const;
    boost::gregorian::date sunteenth() const;

    // First occurrences
    boost::gregorian::date first_monday() const;
    boost::gregorian::date first_tuesday() const;
    boost::gregorian::date first_wednesday() const;
    boost::gregorian::date first_thursday() const;
    boost::gregorian::date first_friday() const;
    boost::gregorian::date first_saturday() const;
    boost::gregorian::date first_sunday() const;

    // Second occurrences
    boost::gregorian::date second_monday() const;
    boost::gregorian::date second_tuesday() const;
    boost::gregorian::date second_wednesday() const;
    boost::gregorian::date second_thursday() const;
    boost::gregorian::date second_friday() const;
    boost::gregorian::date second_saturday() const;
    boost::gregorian::date second_sunday() const;

    // Third occurrences
    boost::gregorian::date third_monday() const;
    boost::gregorian::date third_tuesday() const;
    boost::gregorian::date third_wednesday() const;
    boost::gregorian::date third_thursday() const;
    boost::gregorian::date third_friday() const;
    boost::gregorian::date third_saturday() const;
    boost::gregorian::date third_sunday() const;

    // Fourth occurrences
    boost::gregorian::date fourth_monday() const;
    boost::gregorian::date fourth_tuesday() const;
    boost::gregorian::date fourth_wednesday() const;
    boost::gregorian::date fourth_thursday() const;
    boost::gregorian::date fourth_friday() const;
    boost::gregorian::date fourth_saturday() const;
    boost::gregorian::date fourth_sunday() const;

    // Last occurrences
    boost::gregorian::date last_monday() const;
    boost::gregorian::date last_tuesday() const;
    boost::gregorian::date last_wednesday() const;
    boost::gregorian::date last_thursday() const;
    boost::gregorian::date last_friday() const;
    boost::gregorian::date last_saturday() const;
    boost::gregorian::date last_sunday() const;

    // Generic API: Returns the day-of-month (1..31) for the requested weekday/schedule
    std::uint32_t day(weekday wd, schedule sc) const;

private:
    std::int32_t year_;
    std::uint32_t month_;
};

// Free function variant returning the day-of-month (1..31)
std::uint32_t day(std::int32_t year, std::uint32_t month, weekday wd, schedule sc);

}  // namespace meetup

#endif // MEETUP_H
