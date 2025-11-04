#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Create a clock set to the given hour and minute (minute defaults to 0)
    static clock at(int hour, int minute = 0);

    // Return a new clock advanced by the given number of minutes
    clock plus(int minutes) const;

    // Return a new clock rewound by the given number of minutes
    clock minus(int minutes) const;

    // Format as "HH:MM"
    operator std::string() const;

    // Clocks are equal if they represent the same time of day
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

    explicit clock(int hour, int minute);

private:
    static int normalize_minutes(int total_minutes);
    int minutes_;
};

}  // namespace date_independent

#endif // CLOCK_H
