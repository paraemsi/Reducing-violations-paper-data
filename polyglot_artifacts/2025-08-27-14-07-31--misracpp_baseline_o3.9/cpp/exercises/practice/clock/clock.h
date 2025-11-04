#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>
#include <ostream>

namespace date_independent {

class Clock {
public:
    // Factory: create a clock for the given hour / minute pair
    static Clock at(int hour, int minute = 0);

    // Return a new clock offset by the given minutes
    Clock plus(int minutes) const;
    Clock minus(int minutes) const;

    // Format as "HH:MM"
    std::string to_string() const;
    operator std::string() const;  // implicit conversion, allows std::string(clock)

    // Equality
    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const;

private:
    explicit Clock(int total_minutes);     // total_minutes already normalised
    int minutes_;                          // minutes since 00:00, 0-1439
};

namespace clock {
// free helper so tests can call date_independent::clock::at(...)
inline Clock at(int hour, int minute = 0) {
    return Clock::at(hour, minute);
}
}  // namespace clock

// Stream insertion helper
std::ostream& operator<<(std::ostream& os, const Clock& clock);

}  // namespace date_independent

#endif // CLOCK_H
