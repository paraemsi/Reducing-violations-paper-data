#if !defined(CLOCK_H)
#define CLOCK_H
#include <string>
#include <ostream>

namespace date_independent {

class clock {
public:
    // Factory method to create a clock at given hour and minute
    static clock at(int hour, int minute = 0);

    // Add or subtract minutes, returning a new clock
    clock plus(int minutes) const;
    clock minus(int minutes) const;

    // Equality comparison
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const { return !(*this == other); }

    // String representation: "HH:MM"
    std::string to_string() const;

    // Stream insertion support  e.g.  std::cout << clk;
    friend std::ostream& operator<<(std::ostream& os, const clock& c);

    // Allow tests to obtain a std::string via static_cast<std::string>(clock)
    explicit operator std::string() const;

private:
    explicit clock(int total_minutes);      // expects un-normalized minutes
    static int normalize(int total_minutes);
    int minutes_;                           // 0 <= minutes_ < 1440
};

}  // namespace date_independent

#endif // CLOCK_H
