#if !defined(CLOCK_H)
#define CLOCK_H
#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock set to the given hour and minute (minute defaults to 0)
    clock(int hour, int minute = 0);

    // Factory method to create a clock at the given time
    static clock at(int hour, int minute = 0);

    // Return a new clock that is this clock plus the given minutes
    clock plus(int minutes) const;

    // Return a new clock that is this clock minus the given minutes
    clock minus(int minutes) const;

    // Return the time formatted as "HH:MM"
    std::string to_string() const;

    // Allow conversion to std::string:  std::string c = clock_instance;
    explicit operator std::string() const;

    // Equality comparison
    bool operator==(const clock& other) const;

    // Inequality comparison
    bool operator!=(const clock& other) const;

private:
    int minutes_;                       // minutes since 00:00, range 0-1439
    static int normalize(int minutes);  // helper to wrap into valid range
};

}  // namespace date_independent

#endif // CLOCK_H
