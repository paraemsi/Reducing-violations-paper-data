#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock at hour:minute
    clock(int hour, int minute);

    // Add minutes to the clock
    clock plus(int minutes) const;

    // Subtract minutes from the clock
    clock minus(int minutes) const;

    // String representation in "HH:MM" format
    std::string to_string() const;

    // Equality operator
    static bool operator==(const clock& lhs, const clock& rhs);

    // Factory function to construct a clock at hour:minute
    static clock at(int hour, int minute);

private:
    int minutes_since_midnight_;
    static int normalize(int minutes);
};

}  // namespace date_independent

#endif // CLOCK_H
