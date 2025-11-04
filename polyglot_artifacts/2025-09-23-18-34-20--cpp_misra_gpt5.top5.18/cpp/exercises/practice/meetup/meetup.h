#if !defined(MEETUP_H)
#define MEETUP_H

#include <cstdint>

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
    explicit scheduler(std::int32_t year, std::int32_t month) noexcept;

    // Returns the day of the month (1..31) that matches the given weekday and schedule.
    std::int32_t day(weekday wd, schedule sch) const noexcept;

    // Convenience methods expected by tests

    // teenth
    std::int32_t monteenth() const noexcept;
    std::int32_t tuesteenth() const noexcept;
    std::int32_t wednesteenth() const noexcept;
    std::int32_t thursteenth() const noexcept;
    std::int32_t friteenth() const noexcept;
    std::int32_t saturteenth() const noexcept;
    std::int32_t sunteenth() const noexcept;

    // first
    std::int32_t first_monday() const noexcept;
    std::int32_t first_tuesday() const noexcept;
    std::int32_t first_wednesday() const noexcept;
    std::int32_t first_thursday() const noexcept;
    std::int32_t first_friday() const noexcept;
    std::int32_t first_saturday() const noexcept;
    std::int32_t first_sunday() const noexcept;

    // second
    std::int32_t second_monday() const noexcept;
    std::int32_t second_tuesday() const noexcept;
    std::int32_t second_wednesday() const noexcept;
    std::int32_t second_thursday() const noexcept;
    std::int32_t second_friday() const noexcept;
    std::int32_t second_saturday() const noexcept;
    std::int32_t second_sunday() const noexcept;

    // third
    std::int32_t third_monday() const noexcept;
    std::int32_t third_tuesday() const noexcept;
    std::int32_t third_wednesday() const noexcept;
    std::int32_t third_thursday() const noexcept;
    std::int32_t third_friday() const noexcept;
    std::int32_t third_saturday() const noexcept;
    std::int32_t third_sunday() const noexcept;

    // fourth
    std::int32_t fourth_monday() const noexcept;
    std::int32_t fourth_tuesday() const noexcept;
    std::int32_t fourth_wednesday() const noexcept;
    std::int32_t fourth_thursday() const noexcept;
    std::int32_t fourth_friday() const noexcept;
    std::int32_t fourth_saturday() const noexcept;
    std::int32_t fourth_sunday() const noexcept;

    // last
    std::int32_t last_monday() const noexcept;
    std::int32_t last_tuesday() const noexcept;
    std::int32_t last_wednesday() const noexcept;
    std::int32_t last_thursday() const noexcept;
    std::int32_t last_friday() const noexcept;
    std::int32_t last_saturday() const noexcept;
    std::int32_t last_sunday() const noexcept;

private:
    std::int32_t year_;
    std::int32_t month_;
};

// Convenience free function: compute directly without constructing a scheduler.
std::int32_t day(std::int32_t year, std::int32_t month, weekday wd, schedule sch) noexcept;

}  // namespace meetup

#endif // MEETUP_H
