#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

using hour_t = std::int32_t;
using minute_t = std::int32_t;

class clock
{
public:
    clock(hour_t hour, minute_t minute);

    static clock at(hour_t hour, minute_t minute);

    clock add_minutes(minute_t minutes) const;
    clock subtract_minutes(minute_t minutes) const;

    clock plus(minute_t minutes) const { return add_minutes(minutes); }
    clock minus(minute_t minutes) const { return subtract_minutes(minutes); }

    std::string to_string() const;

    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

private:
    hour_t m_hour;
    minute_t m_minute;

    static constexpr hour_t HOURS_PER_DAY = static_cast<hour_t>(24);
    static constexpr minute_t MINUTES_PER_HOUR = static_cast<minute_t>(60);
    static constexpr minute_t MINUTES_PER_DAY = static_cast<minute_t>(HOURS_PER_DAY * MINUTES_PER_HOUR);

    static void normalize(hour_t& hour, minute_t& minute);
};

}  // namespace date_independent

#endif // CLOCK_H
