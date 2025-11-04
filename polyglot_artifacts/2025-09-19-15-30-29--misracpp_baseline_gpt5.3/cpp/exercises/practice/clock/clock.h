#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    static clock at(int hour, int minute = 0);
    clock plus(int minutes) const;
    clock minus(int minutes) const;
    operator std::string() const;
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

private:
    explicit clock(int total_minutes);
    static int normalize(int total_minutes);
    int minutes_; // minutes since midnight [0, 1440)
};

std::string to_string(const clock& c);
 
}  // namespace date_independent

#endif // CLOCK_H
