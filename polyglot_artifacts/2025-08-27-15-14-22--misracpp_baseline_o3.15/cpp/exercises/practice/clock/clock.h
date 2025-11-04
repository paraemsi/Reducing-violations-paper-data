#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

/*
 * A simple 24-hour clock that is independent of any particular date.
 *
 * Usage example:
 *   Clock c = Clock::at(10, 30);  // 10:30
 *   c.plus(40);                   // 11:10
 *   std::cout << c.to_string();   // "11:10"
 */
class Clock {
public:
    // Factory method – default minute is 0 so Clock::at(8) is 08:00
    static Clock at(int hour, int minute = 0) { return Clock(hour, minute); }

    // Add / subtract minutes (negative input allowed).  Modifies the clock
    // in-place and returns *this to allow chaining.
    Clock& plus(int minutes);
    Clock& minus(int minutes) { return plus(-minutes); }

    // String representation in HH:MM format, zero-padded.
    std::string to_string() const;
    // Allow implicit conversion so tests can do: std::string(clock)
    operator std::string() const { return to_string(); }

    // Equality / inequality – two clocks are equal when they show the same time.
    bool operator==(const Clock& other) const { return minutes_ == other.minutes_; }
    bool operator!=(const Clock& other) const { return !(*this == other); }

    // Total minutes in a 24-hour day. Made public so helper functions can use it.
    inline static constexpr int kDayMinutes = 24 * 60;

private:
    explicit Clock(int hour, int minute);

    // minutes since 00:00, always in [0, 1439]
    int minutes_;
};

using clock = Clock;   // alias expected by the tests

}  // namespace date_independent

#endif // CLOCK_H
