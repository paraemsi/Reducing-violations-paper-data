#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>
#include <ostream>
#include <cstdint>

namespace date_independent {

class Clock {
public:
    // Factory function – mirrors Exercism API but keeps ctor explicit
    static Clock at(int hour, int minute = 0);

    // Basic value-type operations
    Clock plus(int minutes) const;
    Clock minus(int minutes) const;

    std::string to_string() const;

    // Enable implicit conversion so the tests can do: std::string(date_independent::clock::at(...))
    operator std::string() const { return to_string(); }

    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const { return !(*this == other); }

private:
    explicit Clock(int total_minutes);       // minutes since 00:00, always 0-1439
    static int normalize(int hour, int minute);
    static int wrap(int total_minutes);      // helper to keep 0-1439

    int16_t m_total_minutes;                 // fits 0-1439
};

std::ostream& operator<<(std::ostream& os, const Clock& clock);

// Lower-case alias expected by the unit tests
using clock = Clock;

}  // namespace date_independent

#endif // CLOCK_H
