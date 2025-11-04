#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>
#include <cstdint>

namespace date_independent {

class clock {
private:
    std::int32_t minutes_;
    
    // Private constructor
    clock(std::int32_t minutes);
    
public:
    // Create a clock at a specific hour and minute
    static clock at(std::int32_t hours, std::int32_t minutes);
    
    // Add minutes
    clock plus(std::int32_t minutes) const;
    
    // Subtract minutes - we can implement minus by adding negative minutes
    // But to be explicit, let's have a minus function
    clock minus(std::int32_t minutes) const;
    
    // Convert to string
    operator std::string() const;
    
    // Comparison operators
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;
};

}  // namespace date_independent

#endif // CLOCK_H
