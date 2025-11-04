#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>
#include <ostream>

namespace date_independent {

using minutes_t = std::int32_t;

/*
 * Clock represents a time of day without any date information.
 * Internally it stores the number of minutes since midnight in the
 * range [0, 1439].  All arithmetic is performed modulo 24 h.
 */
class Clock
{
public:
    // Factory function – creates a normalised Clock
    static Clock at(minutes_t hour, minutes_t minute = 0) noexcept;

    [[nodiscard]] Clock plus(minutes_t minute_delta) const noexcept;
    [[nodiscard]] Clock minus(minutes_t minute_delta) const noexcept;

    [[nodiscard]] std::string str() const;
    [[nodiscard]] std::string to_string() const { return str(); }

    // implicit conversion – lets std::string s = Clock{}; or std::string(Clock{})
    operator std::string() const { return str(); }

    friend bool operator==(const Clock& lhs, const Clock& rhs) noexcept;
    friend bool operator!=(const Clock& lhs, const Clock& rhs) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Clock& clk);

private:
    explicit Clock(minutes_t minutes_since_midnight) noexcept;

    static constexpr minutes_t minutes_per_day_ { (static_cast<minutes_t>(24) * static_cast<minutes_t>(60)) };

    static minutes_t normalise(minutes_t minutes) noexcept;

    minutes_t minutes_since_midnight_;
};

namespace clock
{
inline Clock at(minutes_t hour, minutes_t minute = static_cast<minutes_t>(0)) noexcept
{
    return Clock::at(hour, minute);
}
}  // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
