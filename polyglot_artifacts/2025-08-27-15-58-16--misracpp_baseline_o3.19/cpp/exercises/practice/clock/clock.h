#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {
namespace clock {

class Clock {
public:
    // Factory method to construct a clock at HH:MM
    // Implemented as free function clock::at declared below.

    // Return a new clock that is this clock plus the supplied minutes
    Clock plus(int minutes) const;

    // Return a new clock that is this clock minus the supplied minutes
    Clock minus(int minutes) const;

    // String representation in HH:MM format
    std::string to_string() const;
    operator std::string() const { return to_string(); }

    // Equality comparison
    bool operator==(const Clock& other) const;
    bool operator!=(const Clock& other) const { return !(*this == other); }

    // Allow the free function at() to construct Clock instances
    friend Clock at(int hour, int minute);

private:
    explicit Clock(int total_minutes); // total minutes since 00:00
    int minutes_;                      // always kept in range [0, 1439]

    static int normalize(int minutes); // helper to wrap minutes into one day
};

Clock at(int hour, int minute = 0);

}  // namespace clock
}  // namespace date_independent

#endif // CLOCK_H
