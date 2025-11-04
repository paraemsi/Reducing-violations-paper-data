#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
private:
    int minutes;
    
    // Private constructor to enforce creation through at()
    clock(int total_minutes);
    
public:
    static clock at(int hours, int minutes = 0);
    clock plus(int minutes_to_add) const;
    clock minus(int minutes_to_subtract) const;
    operator std::string() const;
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;
};

}  // namespace date_independent

#endif // CLOCK_H
