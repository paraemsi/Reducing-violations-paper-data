#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>
#include <iosfwd>
#include <ostream>

namespace date_independent {

class Clock {
public:
    Clock(int hour, int minute = 0);

    Clock plus(int minutes) const;
    Clock minus(int minutes) const;

    std::string to_string() const;

    // implicit conversion helper used in the tests
    operator std::string() const { return to_string(); }

    // factory method expected by the tests
    static Clock at(int hour, int minute = 0) { return Clock(hour, minute); }

    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const { return !(*this == other); }

private:
    int minute_of_day_;               // value in range [0, 1439]
    static int normalize(int minutes); // helper to wrap minutes into valid range
};

using clock = Clock;


inline std::ostream& operator<<(std::ostream& os, const Clock& clk) {
    return os << clk.to_string();
}

}  // namespace date_independent

#endif // CLOCK_H
