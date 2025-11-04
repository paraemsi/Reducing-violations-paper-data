#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class Clock {
public:
    // Construct a clock set to `hour`:`minute`
    static Clock at(int hour, int minute = 0);

    // Return a new clock offset by the supplied minutes
    Clock plus(int minutes) const;
    Clock minus(int minutes) const;

    // HH:MM 24-hour representation
    std::string to_string() const;

    // Allow implicit conversion to std::string so tests can call std::string(clock)
    operator std::string() const { return to_string(); }

    friend bool operator==(const Clock& lhs, const Clock& rhs);
    friend bool operator!=(const Clock& lhs, const Clock& rhs) {
        return !(lhs == rhs);
    }

private:
    explicit Clock(int minutes);            // minutes since 00:00, normalised
    static int normalize(int minutes);      // keep in range [0, 1440)

    int total_minutes_;
};

using clock = Clock;  // alias expected by the tests (lower-case `clock`)

}  // namespace date_independent

#endif // CLOCK_H
