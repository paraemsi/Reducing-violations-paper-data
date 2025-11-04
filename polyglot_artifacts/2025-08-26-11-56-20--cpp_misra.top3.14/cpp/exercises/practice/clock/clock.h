#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

typedef std::int32_t hour_t;
typedef std::int32_t minute_t;

class clock {
public:
    static clock at(hour_t hour, minute_t minute);

    clock plus(minute_t minutes) const;
    clock minus(minute_t minutes) const;

    std::string to_string() const;
    operator std::string() const { return to_string(); }

    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

private:
    hour_t m_hour;
    minute_t m_minute;

    static void normalize(hour_t& hour, minute_t& minute);

    clock(hour_t hour, minute_t minute);
};

}  // namespace date_independent

#endif // CLOCK_H
