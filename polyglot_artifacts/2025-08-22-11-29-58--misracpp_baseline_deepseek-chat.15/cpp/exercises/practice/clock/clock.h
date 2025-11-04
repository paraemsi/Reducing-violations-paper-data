#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
private:
    int minutes;
    
    // Private constructor to enforce creation through at method
    clock(int total_minutes);
    
public:
    // Create a clock at the specified hour and minute
    static clock at(int hour, int minute);
    
    // Add minutes to the clock
    clock plus(int minutes_to_add) const;
    
    // Subtract minutes from the clock (can use plus with negative)
    // But the instructions may want a separate method
    // Let's implement minus as well to be clear
    clock minus(int minutes_to_subtract) const;
    
    // Convert to string representation
    operator std::string() const;
    
    // Comparison operators
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;
};

}  // namespace date_independent

#endif // CLOCK_H
