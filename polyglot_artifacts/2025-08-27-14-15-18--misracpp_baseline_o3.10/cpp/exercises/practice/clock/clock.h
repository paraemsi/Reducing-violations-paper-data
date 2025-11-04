#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class Clock {
public:
    // Factory method to build a clock at the given hour / minute.
    // Minutes are optional and default to 0.
    static Clock at(int hour, int minute = 0);

    // Return a new Clock offset by the supplied minutes.
    Clock plus(int minutes) const;
    Clock minus(int minutes) const;

    // String representation in "HH:MM" 24-hour format.
    std::string to_string() const;

    // Equality operators – clocks are equal if they show the same time.
    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const { return !(*this == other); }

    // Allow implicit conversion to std::string so that
    //   std::string(Clock)  -> "HH:MM"
    operator std::string() const { return to_string(); }

private:
    explicit Clock(int total_minutes);     // ctor stores normalised minutes
    static int normalise(int total_minutes);

    int minutes_;  // minutes after midnight, guaranteed 0-1439 inclusive
};

// Alias with lowercase name expected by the tests.
using clock = Clock;

}  // namespace date_independent

#endif // CLOCK_H
