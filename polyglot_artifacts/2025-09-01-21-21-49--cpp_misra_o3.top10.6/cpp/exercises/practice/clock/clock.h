#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock
{
public:
    // Factory to create a Clock set to the given time (defaults to HH:00).
    static Clock at(std::int32_t hour,
                    std::int32_t minute = static_cast<std::int32_t>(0));

    // Add minutes to this clock.
    Clock plus(std::int32_t minute_offset) const;

    // Subtract minutes from this clock.
    Clock minus(std::int32_t minute_offset) const;

    // Return the time as a zero-padded "HH:MM" string.
    [[nodiscard]] std::string to_string() const;

    // Explicit conversion to std::string so the object can be used
    // where a std::string is expected, e.g. std::string(Clock{})
    explicit operator std::string() const;

    // Symmetrical equality operators implemented as free friends.
    friend bool operator==(const Clock& lhs, const Clock& rhs);
    friend bool operator!=(const Clock& lhs, const Clock& rhs);

private:
    explicit Clock(std::int32_t total_minutes);

    // Normalise m_total_minutes into the range [0, kMinutesPerDay).
    void normalize();

    std::int32_t m_total_minutes;
    static constexpr std::int32_t kMinutesPerDay =
        static_cast<std::int32_t>(24 * 60); // 1440
};

}  // namespace date_independent


// Provide the API expected by the tests: date_independent::clock::at(...)
namespace date_independent::clock
{
using ::date_independent::Clock;

// Forward to the static factory of Clock.
inline Clock at(std::int32_t hour,
                std::int32_t minute = static_cast<std::int32_t>(0))
{
    return Clock::at(hour, minute);
}

}  // namespace date_independent::clock

#endif // CLOCK_H
