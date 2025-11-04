#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

typedef std::int32_t hour_t;
typedef std::int32_t minute_t;

namespace clock {

class clock {
public:
    static clock at(hour_t hour, minute_t minute);

    clock plus(minute_t minutes) const;
    clock minus(minute_t minutes) const;

    std::string to_string() const;

    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

    explicit clock(hour_t hour, minute_t minute);

private:
    hour_t m_hour;
    minute_t m_minute;

    static constexpr hour_t HOURS_PER_DAY = 24;
    static constexpr minute_t MINUTES_PER_HOUR = 60;
    static constexpr minute_t MINUTES_PER_DAY = HOURS_PER_DAY * MINUTES_PER_HOUR;

    static void normalize(hour_t& hour, minute_t& minute);
};

} // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
