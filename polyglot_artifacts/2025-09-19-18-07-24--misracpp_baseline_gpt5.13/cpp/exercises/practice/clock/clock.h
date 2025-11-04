#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock set at given hour/minute (minute defaults to 0)
    static clock at(int hour, int minute = 0);

    // Return a new clock offset by the given minutes (can be negative)
    clock plus(int minutes) const;

    // Convert to "HH:MM" 24-hour format
    explicit operator std::string() const;

    // Clocks representing the same time are equal
    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    explicit clock(int total_minutes); // total minutes since 00:00, may be unnormalized
    int minutes_; // normalized to [0, 1440)
};

}  // namespace date_independent

#endif // CLOCK_H
