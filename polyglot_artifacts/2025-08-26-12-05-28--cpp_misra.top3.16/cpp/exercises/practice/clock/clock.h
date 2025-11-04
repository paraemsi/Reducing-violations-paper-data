#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

typedef std::int_least8_t hour_t;
typedef std::int_least16_t minute_t;

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

    static constexpr hour_t HOURS_PER_DAY = static_cast<hour_t>(24);
    static constexpr minute_t MINUTES_PER_HOUR = static_cast<minute_t>(60);
    static constexpr minute_t MINUTES_PER_DAY = static_cast<minute_t>(HOURS_PER_DAY * MINUTES_PER_HOUR);

    static void normalize(hour_t& hour, minute_t& minute);
};

namespace clock {
    Clock at(hour_t hour, minute_t minute);

    class clock_proxy {
    public:
        explicit clock_proxy(const Clock& c) : m_clock(c) {}

        clock_proxy plus(minute_t minutes) const {
            return clock_proxy(m_clock.add_minutes(minutes));
        }

        clock_proxy minus(minute_t minutes) const {
            return clock_proxy(m_clock.subtract_minutes(minutes));
        }

        operator std::string() const {
            return m_clock.to_string();
        }

        bool operator==(const clock_proxy& other) const {
            return m_clock == other.m_clock;
        }
        bool operator!=(const clock_proxy& other) const {
            return m_clock != other.m_clock;
        }

    private:
        Clock m_clock;
    };
} // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
