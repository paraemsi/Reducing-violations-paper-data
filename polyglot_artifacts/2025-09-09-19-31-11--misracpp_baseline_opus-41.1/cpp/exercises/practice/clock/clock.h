#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    // Static factory method to create a clock
    static clock at(int hours, int minutes);
    
    // Constructor
    clock(int hours, int minutes);
    
    // Add minutes to the clock
    clock plus(int minutes) const;
    
    // Subtract minutes from the clock
    clock minus(int minutes) const;
    
    // Equality operator
    bool operator==(const clock& other) const;
    
    // Inequality operator
    bool operator!=(const clock& other) const;
    
    // Convert to string representation (HH:MM format)
    operator std::string() const;
    
private:
    int total_minutes;
    
    // Normalize the time to ensure it's within 0-1439 minutes (24 hours)
    void normalize();
};

}  // namespace date_independent

#endif // CLOCK_H
