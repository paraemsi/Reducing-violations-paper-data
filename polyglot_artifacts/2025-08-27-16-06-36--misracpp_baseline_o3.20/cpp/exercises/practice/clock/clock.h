#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock initialized to the provided hour and minute.
    clock(int hour, int minute = 0);

    // Return a new clock that is this clock plus the given minutes.
    clock plus(int mins) const;

    // Return a new clock that is this clock minus the given minutes.
    clock minus(int mins) const;

    // Return a "HH:MM" representation of the time.
    std::string str() const;
    // Alias kept for compatibility with some test suites.
    std::string to_string() const;

    // Implicit conversion to std::string so `std::string(clock)` works in tests.
    operator std::string() const;

    // Factory method required by the tests (usage: clock::at(h, m)).
    static clock at(int hour, int minute = 0);

    // Compare two clocks for equality.
    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    // Minutes elapsed since 00:00 in the range [0, 1440).
    int total_minutes;
};

// Convenience factory function used by the canonical tests.
clock at(int hour, int minute = 0);

}  // namespace date_independent

#endif // CLOCK_H
