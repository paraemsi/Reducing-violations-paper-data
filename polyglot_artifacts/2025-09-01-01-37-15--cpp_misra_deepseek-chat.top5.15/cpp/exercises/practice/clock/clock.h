#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

// Define a type alias for the integer type we'll use
using minute_t = std::int32_t;

class clock {
private:
    minute_t minutes_;

    explicit clock(minute_t minutes);
public:
    static clock at(int hours, int minutes);
    clock plus(int minutes) const;
    clock minus(int minutes) const;
    operator std::string() const;
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;
};

}  // namespace date_independent

#endif // CLOCK_H
