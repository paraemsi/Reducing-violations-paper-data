#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

/*
 * A simple time-only clock supporting addition and subtraction of minutes.
 * The class stores the number of minutes elapsed since 00:00 and keeps
 * the value normalised to the range [0, 1439].  Two Clock objects are
 * equal when they denote the same time of day.
 */
class Clock
{
public:
    // Factory that creates a Clock at the requested time (hour : minute).
    static Clock at(std::int32_t hour, std::int32_t minute = 0) noexcept;

    // Return a new Clock advanced by the specified number of minutes.
    Clock plus(std::int32_t minutes) const noexcept;

    // Return a new Clock moved back by the specified number of minutes.
    Clock minus(std::int32_t minutes) const noexcept;

    // Render the time as "HH:MM".
    std::string to_string() const;

    // Implicit conversion to std::string
    operator std::string() const noexcept;

    // Compare two clocks for equality.
    bool operator==(const Clock& other) const noexcept;
    bool operator!=(const Clock& other) const noexcept;

private:
    explicit Clock(std::int32_t total_minutes) noexcept;

    std::int32_t m_total_minutes;   // minutes after midnight, 0-1439
};

// Provide a namespace-level API expected by the tests.
namespace clock
{
    inline Clock at(std::int32_t hour, std::int32_t minute = 0) noexcept
    {
        return Clock::at(hour, minute);
    }
} // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
