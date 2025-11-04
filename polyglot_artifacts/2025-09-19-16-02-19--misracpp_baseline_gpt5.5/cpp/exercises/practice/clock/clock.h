#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    clock(int hour, int minute = 0);
    static clock at(int hour, int minute = 0);
    clock plus(int minutes) const;
    clock minus(int minutes) const;
    operator std::string() const;
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

private:
    int total_minutes_; // normalized minutes in [0, 1440)
    static int normalize(int hour, int minute);
};

}  // namespace date_independent

#endif // CLOCK_H
