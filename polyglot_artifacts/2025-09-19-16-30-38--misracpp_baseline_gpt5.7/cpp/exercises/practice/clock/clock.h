#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    clock(int hour, int minute = 0);
    static clock at(int hour, int minute = 0);
    clock plus(int minute) const;
    clock minus(int minute) const;
    std::string to_string() const;
    operator std::string() const;
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

private:
    int minutes_;  // minutes since midnight, normalized to [0, 1440)
    static int normalize_minutes(int total_minutes);
};

}  // namespace date_independent

#endif // CLOCK_H
