#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock with given hour and minute
    explicit clock(int hour, int minute);

    // Add minutes to the clock
    clock plus(int minutes) const;

    // Subtract minutes from the clock
    clock minus(int minutes) const;

    // Construct a clock at a specific hour and minute (static factory)
    static clock at(int hour, int minute);

    // String representation in "HH:MM" format
    operator std::string() const;

    // Equality operator
    friend bool operator==(const clock& lhs, const clock& rhs);

    int hour() const { return hour_; }
    int minute() const { return minute_; }
private:
    int hour_;
    int minute_;
    void normalize();
};

}  // namespace date_independent

#endif // CLOCK_H
