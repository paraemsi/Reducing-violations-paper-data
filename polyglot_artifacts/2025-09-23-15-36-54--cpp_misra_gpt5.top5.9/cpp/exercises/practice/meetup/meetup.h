#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace meetup {

// Alias to the Boost Gregorian date used by the public API and tests.
using date = boost::gregorian::date;

// Weekday enumeration: Sunday = 0 ... Saturday = 6
enum class weekday : std::int32_t {
    sunday = 0,
    monday = 1,
    tuesday = 2,
    wednesday = 3,
    thursday = 4,
    friday = 5,
    saturday = 6
};

// Schedule within a month
enum class schedule : std::int32_t {
    first = 1,
    second = 2,
    third = 3,
    fourth = 4,
    last = 5,
    teenth = 6
};

// A simple scheduler bound to a specific month and year.
class scheduler {
public:
    // Construct a scheduler for a given year and month (1..12).
    // Behavior is undefined for months outside 1..12.
    explicit scheduler(std::int32_t const year, std::int32_t const month) noexcept;

    // Compute the day-of-month (1..31) for the given weekday and schedule.
    // It is guaranteed that a valid day exists for the given inputs.
    [[nodiscard]] std::int32_t meetup_day(weekday const wd, schedule const sch) const noexcept;

    // Alias of meetup_day for convenience.
    [[nodiscard]] std::int32_t day(weekday const wd, schedule const sch) const noexcept;

    // Teenth days
    [[nodiscard]] date monteenth() const noexcept;
    [[nodiscard]] date tuesteenth() const noexcept;
    [[nodiscard]] date wednesteenth() const noexcept;
    [[nodiscard]] date thursteenth() const noexcept;
    [[nodiscard]] date friteenth() const noexcept;
    [[nodiscard]] date saturteenth() const noexcept;
    [[nodiscard]] date sunteenth() const noexcept;

    // First occurrences
    [[nodiscard]] date first_monday() const noexcept;
    [[nodiscard]] date first_tuesday() const noexcept;
    [[nodiscard]] date first_wednesday() const noexcept;
    [[nodiscard]] date first_thursday() const noexcept;
    [[nodiscard]] date first_friday() const noexcept;
    [[nodiscard]] date first_saturday() const noexcept;
    [[nodiscard]] date first_sunday() const noexcept;

    // Second occurrences
    [[nodiscard]] date second_monday() const noexcept;
    [[nodiscard]] date second_tuesday() const noexcept;
    [[nodiscard]] date second_wednesday() const noexcept;
    [[nodiscard]] date second_thursday() const noexcept;
    [[nodiscard]] date second_friday() const noexcept;
    [[nodiscard]] date second_saturday() const noexcept;
    [[nodiscard]] date second_sunday() const noexcept;

    // Third occurrences
    [[nodiscard]] date third_monday() const noexcept;
    [[nodiscard]] date third_tuesday() const noexcept;
    [[nodiscard]] date third_wednesday() const noexcept;
    [[nodiscard]] date third_thursday() const noexcept;
    [[nodiscard]] date third_friday() const noexcept;
    [[nodiscard]] date third_saturday() const noexcept;
    [[nodiscard]] date third_sunday() const noexcept;

    // Fourth occurrences
    [[nodiscard]] date fourth_monday() const noexcept;
    [[nodiscard]] date fourth_tuesday() const noexcept;
    [[nodiscard]] date fourth_wednesday() const noexcept;
    [[nodiscard]] date fourth_thursday() const noexcept;
    [[nodiscard]] date fourth_friday() const noexcept;
    [[nodiscard]] date fourth_saturday() const noexcept;
    [[nodiscard]] date fourth_sunday() const noexcept;

    // Last occurrences
    [[nodiscard]] date last_monday() const noexcept;
    [[nodiscard]] date last_tuesday() const noexcept;
    [[nodiscard]] date last_wednesday() const noexcept;
    [[nodiscard]] date last_thursday() const noexcept;
    [[nodiscard]] date last_friday() const noexcept;
    [[nodiscard]] date last_saturday() const noexcept;
    [[nodiscard]] date last_sunday() const noexcept;

private:
    std::int32_t const year_;
    std::int32_t const month_;
};

// Free function variant: compute the day-of-month directly.
[[nodiscard]] std::int32_t meetup_day(std::int32_t const year, std::int32_t const month, weekday const wd, schedule const sch) noexcept;

}  // namespace meetup

#endif // MEETUP_H
