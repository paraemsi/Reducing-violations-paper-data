#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>
#include <ostream>

namespace date_independent {

class Clock {
public:
    // Construct a clock at the specified hour and minute.
    Clock(int hour, int minute);

    // Return a new Clock advanced by the given number of minutes.
    Clock plus(int minutes) const;

    // Return a new Clock rewound by the given number of minutes.
    Clock minus(int minutes) const;

    // Return the time as a zero-padded "HH:MM" string.
    std::string str() const;

    // Equality operators compare normalized time.
    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const;

    // Implicit conversion to std::string for ease of use in tests.
    operator std::string() const;

private:
    // Minutes since 00:00, normalized to range [0, 1439].
    int total_minutes_;
};

namespace clock {
// Factory function returning a normalized Clock instance.
Clock at(int hour, int minute);
}  // namespace clock

// Stream insertion operator to print a Clock as "HH:MM".
std::ostream& operator<<(std::ostream& os, const Clock& clock);

}  // namespace date_independent

#endif // CLOCK_H
