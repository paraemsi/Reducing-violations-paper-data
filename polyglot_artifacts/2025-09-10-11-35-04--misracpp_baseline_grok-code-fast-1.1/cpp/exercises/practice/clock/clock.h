#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
private:
    int hours;
    int minutes;
    void normalize();

public:
    clock(int h, int m);
    static clock at(int hour, int minute);
    clock plus(int minutes) const;
    clock minus(int minutes) const;
    bool operator==(const clock& other) const;
    std::string to_string() const;
};

}  // namespace date_independent

#endif // CLOCK_H
