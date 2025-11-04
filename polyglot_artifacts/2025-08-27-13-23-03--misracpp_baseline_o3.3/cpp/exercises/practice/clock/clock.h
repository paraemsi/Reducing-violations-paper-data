#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Factory method to create a clock at the given hour/minute.
    // Values outside the conventional ranges will be normalised.
    static clock at(int hour, int minute = 0);

    // Return the time in 24-hour “HH:MM” format.
    std::string to_string() const;

    // Enable std::string(clock_instance) conversions used in tests
    operator std::string() const { return to_string(); }

    // Add minutes to the current time (non-mutating, returns a new Clock).
    clock plus(int minutes) const;

    // Subtract minutes from the current time (non-mutating, returns a new Clock).
    clock minus(int minutes) const;

    // Two clocks are equal when their times match.
    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs) { return !(lhs == rhs); }

private:
    explicit clock(int minutes_since_midnight);

    // Normalise minutes to the range [0, 1 440).
    static int normalise(int minutes);

    int minutes_;   // minutes since 00:00, always kept normalised
};

}  // namespace date_independent

#endif // CLOCK_H
