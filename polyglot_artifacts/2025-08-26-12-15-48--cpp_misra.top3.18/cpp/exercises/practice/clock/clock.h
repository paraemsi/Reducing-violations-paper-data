#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

using hour_t = std::int8_t;
using minute_t = std::int16_t;

class Clock {
public:
    Clock(hour_t hour, minute_t minute);

    Clock add_minutes(minute_t minutes) const;
    Clock subtract_minutes(minute_t minutes) const;

    std::string to_string() const;

    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const;

    // For compatibility with test expectations
    Clock plus(minute_t minutes) const { return add_minutes(minutes); }

private:
    hour_t m_hour;
    minute_t m_minute;

    static constexpr hour_t HOURS_PER_DAY = static_cast<hour_t>(24);
    static constexpr minute_t MINUTES_PER_HOUR = static_cast<minute_t>(60);
    static constexpr minute_t MINUTES_PER_DAY = static_cast<minute_t>(HOURS_PER_DAY * MINUTES_PER_HOUR);

    static void normalize(hour_t& hour, minute_t& minute);
    // Prevent narrowing conversions in static const expressions
    // (no additional code needed, just a comment for MISRA)
};

namespace clock {
    inline Clock at(hour_t hour, minute_t minute) {
        return Clock(hour, minute);
    }
} // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
