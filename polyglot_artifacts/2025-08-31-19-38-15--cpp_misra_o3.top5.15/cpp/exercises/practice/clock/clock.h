#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class Clock
{
public:
    using minutes_t = std::int32_t;

    /* Construct a clock at a given hour / minute (minutes default to 0) */
    static Clock at(minutes_t hour, minutes_t minute = static_cast<minutes_t>(0));

    /* Return a new clock with the given minute offset (may be negative) */
    Clock plus(minutes_t minute_offset) const;

    /* Render the clock as "HH:MM" (24-hour, zero-padded) */
    std::string to_string() const;

    /* implicit conversion so `std::string(date_independent::clock::at(...))` works */
    explicit operator std::string() const { return to_string(); }

    /* Equality / inequality operators */
    bool operator==(Clock const& other) const;
    bool operator!=(Clock const& other) const;

private:
    explicit Clock(minutes_t total_minutes);

    /* Normalise any number of minutes to the range [0, 1440) */
    static minutes_t normalize(minutes_t total_minutes);

    minutes_t m_minutes;   /* minutes after midnight */
};

}  // namespace date_independent

namespace date_independent {
/* Provide a lowercase alias so tests can access `date_independent::clock::at` */
using clock = Clock;
}  // namespace date_independent

#endif // CLOCK_H
