#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>
#include <iosfwd>

namespace date_independent {

class clock {
public:
    // Factory method to create a clock at the specified hour and minute.
    static clock at(int hour, int minute = 0) noexcept;

    // Return a new clock advanced by the given number of minutes (can be negative).
    clock plus(int minutes) const noexcept;

    // Return the time as a zero-padded HH:MM string.
    std::string to_string() const;

    // Allow constructing std::string from a clock, e.g., string(clock).
    operator std::string() const;

    // Clocks are equal if they represent the same time of day.
    bool operator==(const clock& other) const noexcept;
    bool operator!=(const clock& other) const noexcept;

private:
    explicit clock(int total_minutes) noexcept;
    static int normalize(int total_minutes) noexcept;

    int minutes_from_midnight_;
};

std::ostream& operator<<(std::ostream& os, const clock& c);

}  // namespace date_independent

#endif // CLOCK_H
