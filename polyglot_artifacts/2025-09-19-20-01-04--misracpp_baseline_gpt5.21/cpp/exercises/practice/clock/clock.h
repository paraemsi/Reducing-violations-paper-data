#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Construct a clock at hour:minute
    explicit clock(int hour, int minute = 0);

    // Factory for convenience
    static clock at(int hour, int minute = 0);

    // Return a new clock offset by minutes (positive or negative)
    clock plus(int minutes) const;
    clock minus(int minutes) const;

    // String representation "HH:MM"
    std::string str() const;
    operator std::string() const { return str(); }

    // Equality based on time of day
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const { return !(*this == other); }

private:
    // total minutes since 00:00 in range [0, 1440)
    int minutes_;
    static int normalize(int hour, int minute);
    explicit clock(int total_minutes, bool /*normalized_tag*/);
};

}  // namespace date_independent

#endif // CLOCK_H
