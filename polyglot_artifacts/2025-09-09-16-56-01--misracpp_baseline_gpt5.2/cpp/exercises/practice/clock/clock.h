#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Factory to create a clock at given hour and minute (minute defaults to 0).
    static clock at(int hour, int minute = 0) noexcept;

    // Return a new clock advanced by the given number of minutes.
    // Negative values move the time backwards.
    clock plus(int minutes) const noexcept;

    // Return a new clock moved backwards by the given number of minutes.
    // Negative values move the time forwards.
    clock minus(int minutes) const noexcept;

    // String representation in HH:MM (24-hour) format.
    std::string str() const;

    // Convenient implicit conversion to std::string using str().
    operator std::string() const { return str(); }

    friend bool operator==(const clock& lhs, const clock& rhs) noexcept {
        return lhs.mins_ == rhs.mins_;
    }
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept {
        return !(lhs == rhs);
    }

private:
    explicit clock(int total_minutes) noexcept;
    static int normalize(int minutes) noexcept;

    int mins_; // minutes since 00:00, normalized to [0, 1440)
};

}  // namespace date_independent

#endif // CLOCK_H
