#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock
{
public:
    /* Factory method to create a clock at the given time */
    static Clock at(std::int32_t hour, std::int32_t minute = 0) noexcept;

    /* Add minutes to the current clock (negative allowed). */
    Clock plus(std::int32_t minute_delta) const noexcept;

    /* Subtract minutes from the current clock (negative allowed). */
    Clock minus(std::int32_t minute_delta) const noexcept;

    /* Return the time as “HH:MM”. */
    std::string to_string() const;

    /* Allow implicit/explicit conversion to std::string for test-code convenience */
    explicit operator std::string() const { return to_string(); }

    /* Equality – implemented as non-member friends to keep symmetry. */
    friend bool operator==(const Clock& lhs, const Clock& rhs) noexcept;
    friend bool operator!=(const Clock& lhs, const Clock& rhs) noexcept;

private:
    explicit Clock(std::int32_t minute_of_day) noexcept;
    void normalize() noexcept;

    /* Minutes since 00:00, always in the range 0-1439. */
    std::int32_t m_minute_of_day;
};

/* Provide the lowercase alias expected by the unit tests */
using clock = Clock;

}  // namespace date_independent

#endif // CLOCK_H
