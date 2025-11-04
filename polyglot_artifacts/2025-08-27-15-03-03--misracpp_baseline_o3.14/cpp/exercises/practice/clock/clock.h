#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class Clock {
public:
    // Factory method to create a clock set at `hour`:`minute`
    static Clock at(int hour, int minute = 0);

    // Return a new Clock advanced by `minute` minutes
    Clock plus(int minute) const;

    // Return a new Clock moved backwards by `minute` minutes
    Clock minus(int minute) const;

    // Render the time in "HH:MM" format
    std::string to_string() const;
    // Implicit conversion to std::string so `std::string(clock)` works
    operator std::string() const;

    // Equality operators – two clocks are equal when they show the same time
    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const;

private:
    explicit Clock(int total_minutes);

    // Store time as minutes since midnight, in the range [0, 1439]
    int total_minutes_;

    static int normalize(int minutes);
};

using clock = Clock;

}  // namespace date_independent

#endif // CLOCK_H
