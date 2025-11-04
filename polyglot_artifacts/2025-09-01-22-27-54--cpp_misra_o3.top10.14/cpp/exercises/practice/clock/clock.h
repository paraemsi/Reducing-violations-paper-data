#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock {
public:
    // Factory function to create a clock set to `hour` : `minute`
    static Clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0));

    // Return a new clock that is this clock plus the specified minutes
    [[nodiscard]] Clock add_minutes(std::int32_t minutes) const;

    // Convenience wrappers expected by public API
    [[nodiscard]] Clock plus(std::int32_t minutes) const;
    [[nodiscard]] Clock minus(std::int32_t minutes) const;

    // Implicit conversion to std::string
    [[nodiscard]] operator std::string() const;

    // String representation in the format "HH:MM"
    [[nodiscard]] std::string to_string() const;

    // Equality / inequality – implemented as non-member symmetrical operators
    friend bool operator==(const Clock& lhs, const Clock& rhs);
    friend bool operator!=(const Clock& lhs, const Clock& rhs);

private:
    explicit Clock(std::int32_t minutes_from_midnight);

    std::int32_t m_minutes;  // always in the range 0-1439 inclusive

    static constexpr std::int32_t MinutesPerHour = static_cast<std::int32_t>(60);
    static constexpr std::int32_t MinutesPerDay  =
        static_cast<std::int32_t>(24) * MinutesPerHour;

    static std::int32_t normalise(std::int32_t minutes);
};

namespace clock {

inline Clock at(std::int32_t hour,
               std::int32_t minute = static_cast<std::int32_t>(0))
{
    return Clock::at(hour, minute);
}

} // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
