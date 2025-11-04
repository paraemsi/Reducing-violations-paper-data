#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>
#include <ostream>

namespace date_independent {

class clock {
public:
    // Construct a clock at given hour and minute (defaults to 0)
    clock(int hour, int minute = 0);

    // Factory method preferred by the unit-tests
    static clock at(int hour, int minute = 0);

    // Return a new clock advanced by the specified minutes
    clock plus(int minute_delta) const;

    // Return a new clock rewound by the specified minutes
    clock minus(int minute_delta) const;

    // Conversion to string in HH:MM format
    operator std::string() const;

    // Explicit method used by tests to obtain the HH:MM string
    std::string to_string() const;

    // Stream insertion helper
    friend std::ostream &operator<<(std::ostream &os, const clock &c);

    // Equality / inequality
    bool operator==(const clock &rhs) const;
    bool operator!=(const clock &rhs) const { return !(*this == rhs); }

private:
    // Minutes since midnight in range [0, 1439]
    int minutes_since_midnight_;

    // Normalize value into [0, 1439]
    static int normalize(int minutes);
};

}  // namespace date_independent

#endif // CLOCK_H
