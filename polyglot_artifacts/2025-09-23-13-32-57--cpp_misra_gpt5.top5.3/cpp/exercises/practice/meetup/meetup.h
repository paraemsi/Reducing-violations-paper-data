#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

enum class weekday : std::int32_t {
    Monday = 0,
    Tuesday = 1,
    Wednesday = 2,
    Thursday = 3,
    Friday = 4,
    Saturday = 5,
    Sunday = 6
};

enum class schedule : std::int32_t {
    first = 1,
    second = 2,
    third = 3,
    fourth = 4,
    last = -1,
    teenth = 0
};

// Lowercase aliases to support alternative test conventions.
constexpr weekday monday = weekday::Monday;
constexpr weekday tuesday = weekday::Tuesday;
constexpr weekday wednesday = weekday::Wednesday;
constexpr weekday thursday = weekday::Thursday;
constexpr weekday friday = weekday::Friday;
constexpr weekday saturday = weekday::Saturday;
constexpr weekday sunday = weekday::Sunday;


/**
 * Returns the day-of-month for the requested meetup.
 * Retained for compatibility with alternative test suites.
 */
std::int32_t day(std::int32_t year, std::int32_t month, weekday wd, schedule sched);

class scheduler {
public:
    explicit scheduler(boost::gregorian::months_of_year month, std::int32_t year) noexcept;

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

private:
    boost::gregorian::greg_month month_;
    std::int32_t year_;
};

}  // namespace meetup

#endif // MEETUP_H
