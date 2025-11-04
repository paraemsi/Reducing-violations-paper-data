#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock at hour:minute
    explicit clock(int hour, int minute);

    // Static factory method to construct a clock at hour:minute
    static clock at(int hour, int minute);

    // Add minutes to the clock
    [[nodiscard]] clock plus(int minutes) const;

    // Subtract minutes from the clock
    [[nodiscard]] clock minus(int minutes) const;

    // String representation in "HH:MM" format
    [[nodiscard]] std::string to_string() const;

    // Equality operator
    bool operator==(const clock& other) const;

    // Inequality operator
    bool operator!=(const clock& other) const;

private:
    int hour_;
    int minute_;
    void normalize();
};

}  // namespace date_independent

#endif // CLOCK_H
