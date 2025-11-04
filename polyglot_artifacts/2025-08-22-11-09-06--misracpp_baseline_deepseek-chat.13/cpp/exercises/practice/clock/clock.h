#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
private:
    int minutes;
    clock(int total_minutes);
    
public:
    static clock at(int hour, int minute);
    clock plus(int minutes_to_add) const;
    clock minus(int minutes_to_subtract) const;
    operator std::string() const;
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;
};

}  // namespace date_independent

#endif // CLOCK_H
