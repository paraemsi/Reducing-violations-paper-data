#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

namespace clock {

class Clock {
public:
    // Construct a clock at hour:minute
    explicit Clock(int hour, int minute);

    // Add minutes to the clock
    Clock plus(int minutes) const noexcept;

    // Subtract minutes from the clock
    Clock minus(int minutes) const noexcept;

    // String representation in "HH:MM" format
    std::string to_string() const noexcept;

    // Equality operator
    bool operator==(const Clock& other) const noexcept;

private:
    int hour_;
    int minute_;
    void normalize();
};

// Factory function to create a clock at a given time
inline Clock at(int hour, int minute) {
    return Clock(hour, minute);
}

} // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
