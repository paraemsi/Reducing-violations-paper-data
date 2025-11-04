#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock at hour:minute (24-hour clock). Normalized to 00:00..23:59.
    clock(int hour, int minute = 0);

    // Factory for convenience.
    static clock at(int hour, int minute = 0);

    // Return a new clock offset by the given number of minutes (can be negative).
    clock plus(int minutes) const;

    // Convert to HH:MM string.
    operator std::string() const;

    // Convenience named accessor for string conversion.
    std::string to_string() const;

    // Equality: two clocks are equal if they represent the same time of day.
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

private:
    int minutes_since_midnight_;
    static int normalize_minutes(int minutes);
};


}  // namespace date_independent

#endif // CLOCK_H
