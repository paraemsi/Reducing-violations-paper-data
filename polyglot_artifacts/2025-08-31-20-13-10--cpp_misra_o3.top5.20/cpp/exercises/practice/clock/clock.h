#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>
#include <ostream>

namespace date_independent {

class Clock
{
public:
    /* Create a Clock set to `hour`:`minute` (default 0) */
    static Clock at(std::int32_t hour, std::int32_t minute = 0);

    /* Add `minute` minutes to this Clock and return *this */
    Clock& plus(std::int32_t minute);

    /* Subtract `minute` minutes from this Clock and return *this */
    Clock& minus(std::int32_t minute);

    /* Return time formatted as "HH:MM" */
    [[nodiscard]] std::string to_string() const;

    /* Implicit conversion to std::string delegates to to_string() */
    operator std::string() const;

    /* Equality ‑ two clocks represent the same instant when their
       normalised minutes-of-day match. */
    friend bool operator==(const Clock& lhs, const Clock& rhs);
    friend bool operator!=(const Clock& lhs, const Clock& rhs);

    /* Stream insertion */
    friend std::ostream& operator<<(std::ostream& os, const Clock& clk);

private:
    explicit Clock(std::int32_t minute_of_day);

    /* Normalise the supplied minutes so the result is in [0, 1440) */
    static std::int32_t normalise(std::int32_t minute);

    static constexpr std::int32_t MINUTES_PER_DAY = 24 * 60;

    std::int32_t m_minutes; /* minutes elapsed since 00:00, always normalised */
};

/* Provide the lowercase alias expected by the test-suite.
   This keeps the public API unchanged while satisfying the
   required date_independent::clock spelling. */
using clock = Clock;

}  // namespace date_independent

#endif // CLOCK_H
