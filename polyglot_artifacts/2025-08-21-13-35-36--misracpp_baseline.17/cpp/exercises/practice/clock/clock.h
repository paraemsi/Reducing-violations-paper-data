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
    clock plus(int minutes) const noexcept;

    // Subtract minutes from the clock
    clock minus(int minutes) const noexcept;

    // String representation in "HH:MM" format
    std::string to_string() const noexcept;

    // Equality operator
    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;

private:
    int hour_;
    int minute_;
    void normalize();
};

}  // namespace date_independent

#endif // CLOCK_H
