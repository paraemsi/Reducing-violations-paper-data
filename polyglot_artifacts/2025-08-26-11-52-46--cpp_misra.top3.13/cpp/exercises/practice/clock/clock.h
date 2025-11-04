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

    clock plus(minute_t minutes) const;
    clock minus(minute_t minutes) const;

    std::string to_string() const;

    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

private:
    hour_t m_hour;
    minute_t m_minute;

    static constexpr hour_t hours_per_day = static_cast<hour_t>(24);
    static constexpr minute_t minutes_per_hour = static_cast<minute_t>(60);
    static constexpr minute_t minutes_per_day = static_cast<minute_t>(24 * 60);

    static minute_t normalize_minutes(minute_t minutes);
};

}  // namespace date_independent

#endif // CLOCK_H
