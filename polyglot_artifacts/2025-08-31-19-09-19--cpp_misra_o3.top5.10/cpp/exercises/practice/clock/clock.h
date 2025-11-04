#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock final {
public:
    // Factory: build a clock set to hour : minute (defaults to 0 minutes)
    static Clock at(std::int32_t hour, std::int32_t minute = 0) noexcept;

    // Add minutes (may be negative via caller)
    [[nodiscard]] Clock plus(std::int32_t minutes) const noexcept;

    // Subtract minutes
    [[nodiscard]] Clock minus(std::int32_t minutes) const noexcept;

    // “HH:MM” representation
    [[nodiscard]] std::string to_string() const;

    // Allow implicit conversion expected by many tests
    [[nodiscard]] operator std::string() const { return to_string(); }

    // Two clocks are equal when they point at the same minute of the day
    friend bool operator==(const Clock &lhs, const Clock &rhs) noexcept;
    /* Inequality – defined inline to avoid separate compilation unit
       Simply the logical negation of equality, keeps behaviour consistent. */
    friend bool operator!=(const Clock &lhs, const Clock &rhs) noexcept
    {
        return !(lhs == rhs);
    }

private:
    explicit Clock(std::int32_t totalMinutes) noexcept;

    static constexpr std::int32_t minutes_per_day = (24 * 60);
    static std::int32_t wrap(std::int32_t minutes) noexcept;

    std::int32_t minutes_{0};
};

namespace clock {
    using Clock = ::date_independent::Clock;

    inline Clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0)) noexcept
    {
        return Clock::at(hour, minute);
    }
}  // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
