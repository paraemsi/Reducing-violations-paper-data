#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Factory: construct a clock normalised to 24-hour time.
    static clock at(int hour, int minute = 0);

    // Return a new clock advanced by the given minutes.
    clock plus(int minute) const;

    // Return a new clock rewound by the given minutes.
    clock minus(int minute) const;

    // Canonical "HH:MM" representation.
    std::string to_string() const;

    // Implicit conversion to canonical "HH:MM" string.
    operator std::string() const;

    // Equality – two clocks are equal when they show the same time.
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

private:
    // Construct a clock normalised to 24-hour time (used internally).
    explicit clock(int hour, int minute = 0);

    // Minutes after midnight in the range [0, 1439].
    int minutes_;

    // Helper to normalise any minute count into the range [0, 1439].
    static int normalize(int minutes);
};

}  // namespace date_independent

#endif // CLOCK_H
