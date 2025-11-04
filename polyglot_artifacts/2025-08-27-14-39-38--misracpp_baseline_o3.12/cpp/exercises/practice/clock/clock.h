#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock set to the supplied hour / minute (minute defaults to 0)
    explicit clock(int hour, int minute = 0);

    // Factory helper – preferred way for the tests to create a clock
    static clock at(int hour, int minute = 0);

    // Return a new clock offset forward by the given number of minutes
    clock plus(int minutes) const;

    // Return a new clock offset backward by the given number of minutes
    clock minus(int minutes) const;

    // Return time in 24-hour "HH:MM" format
    std::string to_string() const;

    // Allow implicit conversion to std::string (for convenience in tests)
    operator std::string() const;

    // Equality operators (defined as non-member friends to avoid ambiguity)
    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    int m_total_minutes;                  // minutes since 00:00, in range [0,1439]
    static int normalize(int minutes);    // helper to wrap minutes into one day
};

}  // namespace date_independent

#endif // CLOCK_H
