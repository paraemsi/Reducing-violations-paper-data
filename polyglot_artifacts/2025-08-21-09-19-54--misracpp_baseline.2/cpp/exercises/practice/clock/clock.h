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

    // Static factory method to construct a clock at a given time
    static clock at(int hour, int minute);

    // String representation in "HH:MM" format
    std::string to_string() const;

    // Equality operator
    friend bool operator==(const clock& lhs, const clock& rhs);

private:
    int hour_;
    int minute_;
    void normalize();
};

}  // namespace date_independent

#endif // CLOCK_H
