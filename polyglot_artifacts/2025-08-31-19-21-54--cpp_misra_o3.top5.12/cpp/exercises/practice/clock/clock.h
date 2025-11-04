#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock {
public:
    using minute_type = std::int32_t;

    // Factory function to build a clock at the requested time
    static clock at(minute_type hours, minute_type minutes = 0);

    // Construct directly – kept public to ease testing
    explicit clock(minute_type hours, minute_type minutes = 0);

    // Add / subtract minutes – non-mutating, returns a new Clock
    [[nodiscard]] clock plus(minute_type minutes) const;
    [[nodiscard]] clock minus(minute_type minutes) const;

    // String representation "HH:MM"
    [[nodiscard]] std::string to_string() const;
    operator std::string() const;

    // Equality operators
    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    minute_type total_minutes_;              // minutes after midnight [0, 1439]

    static minute_type normalise(minute_type minutes);
};

}  // namespace date_independent

#endif // CLOCK_H
