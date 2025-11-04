#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock with given hour and minute
    explicit clock(int hour, int minute);

    // Static factory method to construct a clock at a given time
    static clock at(int hour, int minute);

    // Add minutes to the clock
    clock plus(int minutes) const;

    // Subtract minutes from the clock
    clock minus(int minutes) const;

    // String representation in HH:MM format
    std::string to_string() const;

    // Equality operator
    bool operator==(const clock& other) const;

    // Not-equal operator for completeness
    bool operator!=(const clock& other) const { return !(*this == other); }

private:
    int hour_;
    int minute_;
    void normalize();
};

}  // namespace date_independent

#endif // CLOCK_H
