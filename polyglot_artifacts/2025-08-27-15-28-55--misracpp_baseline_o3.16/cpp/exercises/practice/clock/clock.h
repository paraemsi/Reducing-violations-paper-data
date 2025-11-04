#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>
#include <ostream>

namespace date_independent {

class Clock {
public:
    // Factory helper – mirrors exercism interface
    static Clock at(int hour, int minute = 0);

    // Modifiers
    Clock& plus(int minutes);
    Clock& minus(int minutes);

    // String representation, zero-padded “HH:MM”
    std::string to_string() const;

    // Allow implicit conversion so tests can do: std::string(clock)
    operator std::string() const { return to_string(); }

    // Equality / inequality
    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const { return !(*this == other); }

private:
    explicit Clock(int hour, int minute = 0);        // use at() for creation
    static int normalize(int minutes);               // keep 0‥1439

    int minutes_;                                    // minutes after midnight
};

using clock = Clock;   // alias expected by the tests

// stream insertion convenience
std::ostream& operator<<(std::ostream& os, const Clock& clk);

}  // namespace date_independent

#endif // CLOCK_H
