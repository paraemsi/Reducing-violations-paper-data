#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>
#include <ostream>

namespace date_independent {

using minutes_t = std::int32_t;

// A simple time-of-day class without any date component.
class clock
{
public:
    // Factory method: create a clock set to the given hour / minute.
    static clock at(minutes_t hour,
                    minutes_t minute = minutes_t{0});

    // Return a new Clock advanced by the supplied minute offset.
    clock add_minutes(minutes_t minutes) const;

    // Alias required by tests: behave the same as add_minutes.
    clock plus(minutes_t minutes) const;

    // “HH:MM” string representation with leading zeros.
    std::string to_string() const;

    // Implicit conversion helper used by unit tests.
    operator std::string() const;

    // Symmetrical equality operator (non-member, but declared friend).
    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

    // Stream insertion – used only for diagnostics, respects MISRA symmetrical rule exemptions.
    friend std::ostream& operator<<(std::ostream& os, const clock& c);

private:
    explicit clock(minutes_t totalMinutes);

    minutes_t m_totalMinutes; // Minutes since 00:00, range [0, 1439].

    static constexpr minutes_t minutes_per_day =
        minutes_t{24} * minutes_t{60};
};

}  // namespace date_independent

#endif // CLOCK_H
