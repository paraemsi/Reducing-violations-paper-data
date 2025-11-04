#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
private:
    int minutes;
    
    // Private constructor
    clock(int total_minutes);
    
public:
    // Create a clock at a specific time
    static clock at(int hours, int minutes);
    
    // Add minutes
    clock plus(int minutes_to_add) const;
    
    // Subtract minutes - we can implement minus by adding negative minutes
    // But to match the problem statement, let's have a minus function
    clock minus(int minutes_to_subtract) const;
    
    // Convert to string representation
    operator std::string() const;
    
    // Comparison operators
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;
};

}  // namespace date_independent

#endif // CLOCK_H
