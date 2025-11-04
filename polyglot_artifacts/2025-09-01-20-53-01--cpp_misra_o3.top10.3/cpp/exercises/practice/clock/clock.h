#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

using minute_type = std::int32_t;

class Clock
{
public:
    /* Factory to construct a Clock at the given hour / minute (24-hour
     * notation). Negative or out-of-range values wrap around the 24-hour
     * day. */
    static Clock at(minute_type hour,
                    minute_type minute = static_cast<minute_type>(0)) noexcept;

    /* Return a new Clock advanced by the supplied number of minutes. */
    Clock plus(minute_type minutes) const noexcept;

    /* Return a new Clock moved backwards by the supplied number of minutes. */
    Clock minus(minute_type minutes) const noexcept;

    /* “HH:MM” string representation, zero-padded. */
    std::string to_string() const;

    /* Implicit conversion helper expected by some test suites. */
    operator std::string() const { return to_string(); }

    /* Symmetrical equality operators ‑- implemented as non-member friends
     * to respect MISRA guidance. */
    friend bool operator==(const Clock& lhs, const Clock& rhs) noexcept;
    friend bool operator!=(const Clock& lhs, const Clock& rhs) noexcept;

private:
    explicit Clock(minute_type total_minutes) noexcept;

    /* Stored as minutes elapsed since 00:00.  Always in the range [0, 1439]. */
    minute_type minutes_since_midnight_{static_cast<minute_type>(0)};
};

namespace clock
{
inline Clock at(minute_type hour,
                minute_type minute = static_cast<minute_type>(0)) noexcept
{
    return Clock::at(hour, minute);
}
} // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
