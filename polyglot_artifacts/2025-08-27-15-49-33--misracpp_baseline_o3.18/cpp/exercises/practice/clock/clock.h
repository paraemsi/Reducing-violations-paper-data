#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>
#include <ostream>

namespace date_independent {

class Clock {
public:
    // Factory: create a clock at given hour/minute (minute defaults to 0)
    static Clock at(int hour, int minute = 0);

    // Return a new clock advanced by the supplied minutes
    Clock plus(int minutes) const;

    // Return a new clock reversed by the supplied minutes
    Clock minus(int minutes) const;

    // String representation "HH:MM"
    std::string to_string() const;

    // Implicit conversion so tests can do: std::string(clock::at(...))
    operator std::string() const { return to_string(); }

    // Equality / inequality
    bool operator==(const Clock &other) const;
    bool operator!=(const Clock &other) const { return !(*this == other); }

private:
    // Minutes from midnight, always kept in range [0, 1439]
    int minutes_from_midnight_;

    explicit Clock(int total_minutes);

    // Normalise minutes_from_midnight_ into valid range
    static int normalise(int total_minutes);
};

// Alias expected by the test suite (lower-case `clock`)
using clock = Clock;

// Stream insertion helper so tests can do: std::cout << clock;
inline std::ostream &operator<<(std::ostream &os, const Clock &clock) {
    return os << clock.to_string();
}

}  // namespace date_independent

#endif // CLOCK_H
