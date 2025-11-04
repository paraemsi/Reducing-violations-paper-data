#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

/**
 * A simple 24-hour clock that is independent of any particular date.
 * Internally the time is stored as minutes since midnight in the range [0, 1439].
 */
class clock {
public:
    /**
     * Construct a clock set to the given hour/minute.
     * Values outside their normal ranges are allowed and will be normalised.
     *
     *   Clock c = Clock::at(25, -160);   //   22:20
     */
    static clock at(int hour, int minute = 0);

    /**
     * Return a new clock that is this clock plus @p minutes.
     */
    clock plus(int minutes) const;

    /**
     * Return a new clock that is this clock minus @p minutes.
     */
    clock minus(int minutes) const;

    /**
     * Return the canonical "HH:MM" representation (always two digits each).
     */
    std::string to_string() const;
    operator std::string() const { return to_string(); }

    /* Equality operators – two clocks are equal when they show the same time. */
    bool operator==(const clock& other) const  { return minutes_ == other.minutes_; }
    bool operator!=(const clock& other) const  { return !(*this == other); }

private:
    explicit clock(int minutes_since_midnight)
        : minutes_{normalise(minutes_since_midnight)} {}

    /* Normalise an arbitrary minute count into the range [0, 1439]. */
    static int normalise(int minutes);

    int minutes_;  // minutes since midnight, always kept normalised
};

}  // namespace date_independent

#endif // CLOCK_H
