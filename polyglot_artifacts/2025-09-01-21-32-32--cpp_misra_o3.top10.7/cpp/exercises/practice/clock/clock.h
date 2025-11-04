#ifndef CLOCK_H
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock
{
public:
    /* Factory function to create a clock at the specified hour / minute. */
    static auto at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) -> Clock;

    /* Add minutes (positive or negative) and return a new Clock instance. */
    [[nodiscard]] auto plus(std::int32_t minute_delta) const -> Clock;

    /* Subtract minutes (positive or negative) and return a new Clock instance. */
    [[nodiscard]] auto minus(std::int32_t minute_delta) const -> Clock;

    /* Return a "HH:MM" representation of the current time. */
    [[nodiscard]] auto to_string() const -> std::string;
    /* Allow direct‐initialisation of std::string from a Clock instance.   */
    explicit operator std::string() const { return to_string(); }

    /* Equality – implemented as free (friend) functions for symmetry. */
    friend auto operator==(const Clock& lhs, const Clock& rhs) -> bool;
    friend auto operator!=(const Clock& lhs, const Clock& rhs) -> bool;

private:
    explicit Clock(std::int32_t total_minutes) : total_minutes_{total_minutes} {}

    /* Normalise the stored minute count to the range [0, 1439]. */
    static auto normalise(std::int32_t minutes) -> std::int32_t;

    std::int32_t total_minutes_{static_cast<std::int32_t>(0)};
};

/* Wrapper namespace required by unit-tests – provides the free at() factory. */
namespace clock
{
inline auto at(std::int32_t hour,
               std::int32_t minute = static_cast<std::int32_t>(0)) -> Clock
{
    return Clock::at(hour, minute);
}
}  // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
