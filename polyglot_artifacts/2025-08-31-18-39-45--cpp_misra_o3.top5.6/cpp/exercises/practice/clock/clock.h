#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

/*
 * Clock represents a wall-clock time with minute resolution
 * independent of any particular date.  Internally it stores the
 * number of minutes elapsed since 00:00.
 */
class Clock
{
public:
    // Factory method – constructs a Clock set to {hour}:{minute}
    // Minutes may be outside the conventional 0-59 range; the
    // resulting time is wrapped onto a 24-hour day.
    static Clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0));

    // Adds a signed minute offset (positive to advance, negative to
    // rewind) and returns *this for call chaining.
    Clock plus(std::int32_t minute_delta) const;
    Clock minus(std::int32_t minute_delta) const;

    // Formats the time as HH:MM using a 24-hour clock.
    [[nodiscard]] std::string to_string() const;

    // Implicit conversion helper so that std::string(Clock) works in the tests.
    operator std::string() const;

    // Two clocks are equal when they represent the same instant.
    friend bool operator==(const Clock& lhs, const Clock& rhs);
    friend bool operator!=(const Clock& lhs, const Clock& rhs);

private:
    explicit Clock(std::int32_t total_minutes);

    // Normalises an arbitrary minute value into the range [0, 1439].
    static std::int32_t wrap(std::int32_t minutes);

    std::int32_t m_total_minutes; // minutes since 00:00 in range [0, 1439]
};

// Provide a lowercase alias so the tests can refer to date_independent::clock.
using clock = Clock;

}  // namespace date_independent

#endif // CLOCK_H
