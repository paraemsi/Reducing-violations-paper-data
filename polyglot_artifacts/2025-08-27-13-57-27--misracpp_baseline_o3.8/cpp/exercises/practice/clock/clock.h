#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class Clock {
public:
    // Factory method to construct a clock at a specific hour/minute
    static Clock at(int hour, int minute = 0);

    // Public constructor expected by the tests
    Clock(int hour, int minute = 0);

    // Mutating arithmetic
    Clock plus(int delta_minutes) const;   // add minutes (can be negative)
    Clock minus(int delta_minutes) const;  // subtract minutes (can be negative)

    // String representation in HH:MM format
    std::string str() const;               // internal helper
    std::string to_string() const;         // public API expected by tests
    operator std::string() const;          // implicit conversion helper

    // Equality comparison
    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const { return !(*this == other); }

private:
    explicit Clock(int total_minutes);          // internal constructor
    static int mod(int value, int modulus);     // positive modulo helper

    static constexpr int minutes_in_day = 24 * 60;
    int minutes_;   // minutes since 00:00 in range [0, minutes_in_day)
};

namespace clock {
    // Adapter namespace expected by the tests
    inline Clock at(int hour, int minute = 0) {
        return Clock::at(hour, minute);
    }
}  // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
