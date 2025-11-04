#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock {
public:
    using minutes_t = std::int32_t;

    clock(minutes_t hour, minutes_t minute);
    static clock at(minutes_t hour, minutes_t minute = static_cast<minutes_t>(0));

    clock plus(minutes_t minute) const;
    clock minus(minutes_t minute) const;

    std::string to_string() const;
    explicit operator std::string() const;

    bool operator==(const clock& rhs) const;
    bool operator!=(const clock& rhs) const;

private:
    minutes_t minutes_since_midnight_;
};

}  // namespace date_independent

#endif // CLOCK_H
