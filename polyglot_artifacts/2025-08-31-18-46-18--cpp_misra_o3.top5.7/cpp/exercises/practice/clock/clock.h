#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>
#include <iosfwd>   /* forward declaration for std::ostream */

namespace date_independent {

/* Alias providing a fixed-width signed integral type that satisfies MISRA
 * rule “do not use the names of the standard signed integer types” outside
 * of this definition. */
using minutes_t = std::int32_t;

class Clock
{
public:
    static Clock at(minutes_t hour,
                    minutes_t minute = static_cast<minutes_t>(0)) noexcept;

    Clock plus(minutes_t minutes) const noexcept;
    Clock minus(minutes_t minutes) const noexcept;

    bool operator==(const Clock& other) const noexcept;
    bool operator!=(const Clock& other) const noexcept;

    std::string to_string() const;

    /* Allow direct initialisation of std::string from a Clock object, e.g.
     * std::string s = string(clock);  — required by the test-suite. */
    explicit operator std::string() const;

    /* Stream insertion, declared here so that unit-tests have a visible
     * declaration before use; the definition lives in clock.cpp */
    friend std::ostream& operator<<(std::ostream& os,
                                    const Clock&       clock);

private:
    explicit Clock(minutes_t normalizedMinutes) noexcept;

    static constexpr minutes_t MINUTES_IN_DAY =
        (static_cast<minutes_t>(24) * static_cast<minutes_t>(60));

    minutes_t m_minutesOfDay;
};

/* Convenience free-function wrapper placed in the `clock` sub-namespace to
 * satisfy the unit-tests’ expected symbol layout. */
namespace clock {

inline Clock at(minutes_t hour,
                minutes_t minute = static_cast<minutes_t>(0)) noexcept
{
    return Clock::at(hour, minute);
}

} // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
