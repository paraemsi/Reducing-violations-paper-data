#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock at hour:minute
    explicit clock(int hour, int minute);

    // Construct a clock at hour:minute (static factory)
    static clock at(int hour, int minute);

    // Add minutes to the clock
    clock plus(int minutes) const;

    // Subtract minutes from the clock
    clock minus(int minutes) const;

    // String representation in "HH:MM" format
    std::string to_string() const;

private:
    int hour_;
    int minute_;
    void normalize();

public:
    // Equality operator
    friend bool operator==(const clock& lhs, const clock& rhs);

private:
    int hour_;
    int minute_;
    void normalize();
};

}  // namespace date_independent

#endif // CLOCK_H
