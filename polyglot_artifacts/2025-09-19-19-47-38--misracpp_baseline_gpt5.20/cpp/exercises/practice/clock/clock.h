#ifndef DATE_INDEPENDENT_CLOCK_H
#define DATE_INDEPENDENT_CLOCK_H

#include <iosfwd>

#include <string>

namespace date_independent {

class clock {
public:
    // Default-construct to 00:00.
    clock() : minutes_{0} {}
    // Construct a clock at the given hour and minute (minute defaults to 0).
    static clock at(int hour, int minute = 0);

    // Return a new clock advanced by the given number of minutes.
    clock plus(int minutes) const;

    // Return a new clock moved back by the given number of minutes.
    clock minus(int minutes) const;

    // String representation "HH:MM".
    std::string str() const;

    // Allow implicit conversion to std::string for convenience.
    operator std::string() const { return str(); }

    // Equality and inequality compare normalized times.
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const { return !(*this == other); }

private:
    explicit clock(int total_minutes_normalized);
    static int normalize_minutes(int total_minutes); // ensures 0..1439

    int minutes_; // minutes since 00:00, normalized to [0, 1440)
};

std::ostream& operator<<(std::ostream& os, const clock& c);

}  // namespace date_independent

#endif // DATE_INDEPENDENT_CLOCK_H
