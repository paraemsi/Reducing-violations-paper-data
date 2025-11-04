#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

using hour_t = std::int32_t;
using minute_t = std::int32_t;

class Clock {
public:
    Clock(hour_t hour, minute_t minute);

    Clock add_minutes(minute_t minutes) const;
    Clock subtract_minutes(minute_t minutes) const;

    std::string to_string() const;

    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const;

private:
    hour_t m_hour;
    minute_t m_minute;

    static constexpr hour_t HOURS_PER_DAY = 24;
    static constexpr minute_t MINUTES_PER_HOUR = 60;
    static constexpr minute_t MINUTES_PER_DAY = HOURS_PER_DAY * MINUTES_PER_HOUR;

    static void normalize(hour_t& hour, minute_t& minute);
};

namespace clock {
    Clock at(hour_t hour, minute_t minute);
}

}  // namespace date_independent

#endif // CLOCK_H
