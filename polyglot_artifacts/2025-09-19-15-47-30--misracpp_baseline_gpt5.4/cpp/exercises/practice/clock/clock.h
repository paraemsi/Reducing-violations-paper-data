#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock at the given hour/minute (24-hour time).
    static clock at(int hour, int minute = 0) noexcept;

    // Return a new clock that is this time plus the given minutes.
    clock plus(int minutes) const noexcept;

    // Return a new clock that is this time minus the given minutes.
    clock minus(int minutes) const noexcept;

    // Return the time formatted as "HH:MM".
    std::string str() const;

    // Implicit conversion to std::string to support string(clock)
    operator std::string() const { return str(); }

    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;

private:
    explicit clock(int total_minutes) noexcept;  // expects normalized minutes
    static int normalize(int total_minutes) noexcept;

    int minutes_{0};  // minutes since midnight in range [0, 1440)
};

}  // namespace date_independent

#endif // CLOCK_H
