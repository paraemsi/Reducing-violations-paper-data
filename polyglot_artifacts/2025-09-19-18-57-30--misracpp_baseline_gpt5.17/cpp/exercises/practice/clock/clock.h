#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock;

bool operator==(const clock& lhs, const clock& rhs);
bool operator!=(const clock& lhs, const clock& rhs);

class clock {
public:
    // Create a clock at the given hour and optional minute (defaults to 0).
    static clock at(int hour, int minute = 0);

    // Return a new clock offset by the given number of minutes.
    clock plus(int minutes) const;

    // Return a new clock offset backwards by the given number of minutes.
    clock minus(int minutes) const;

    // Render the clock time in HH:MM (24-hour) format.
    std::string str() const;
    explicit operator std::string() const;

    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    explicit clock(int total_minutes);

    // minutes since midnight in the range [0, 1439]
    int minutes_;

    static int normalize_minutes(int total);
};

}  // namespace date_independent

#endif // CLOCK_H
