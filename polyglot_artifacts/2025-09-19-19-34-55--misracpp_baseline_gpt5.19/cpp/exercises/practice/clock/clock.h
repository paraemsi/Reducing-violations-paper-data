#if !defined(CLOCK_H)
#define CLOCK_H

#include <ostream>
#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock at hour:minute (minute can be any integer; value is normalized)
    clock(int hour, int minute);

    // Factory helper to match expected usage: clock::at(h, m)
    static clock at(int hour, int minute = 0);

    // Return a new clock advanced by the given number of minutes (can be negative)
    clock plus(int minutes) const;

    // Return a new clock rewound by the given number of minutes
    clock minus(int minutes) const;

    // Return time formatted as "HH:MM"
    std::string to_string() const;

    // Implicit conversion to std::string to support string(clock)
    operator std::string() const;

    // Equality: two clocks are equal if they represent the same time of day
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

private:
    int minutes_;  // minutes since midnight in [0, 1439]

    static int normalize(int total_minutes);
};

std::ostream& operator<<(std::ostream& os, const clock& c);

}  // namespace date_independent

#endif // CLOCK_H
