#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

namespace clock {

class Clock {
public:
    // Constructor that takes hours and minutes
    Clock(std::int32_t hours, std::int32_t minutes);
    
    // Add minutes to the clock (returns a new Clock)
    Clock plus(std::int32_t minutes) const;
    
    // Subtract minutes from the clock (returns a new Clock)
    Clock minus(std::int32_t minutes) const;
    
    // Equality operator
    bool operator==(const Clock& other) const;
    
    // Inequality operator
    bool operator!=(const Clock& other) const;
    
    // Convert to string representation (HH:MM format)
    operator std::string() const;

private:
    // Store total minutes since midnight
    std::int32_t total_minutes_;
    
    // Normalize the time to ensure it's within 0-1439 minutes (24 hours)
    static std::int32_t normalize(std::int32_t minutes);
};

// Factory function to create a Clock
Clock at(std::int32_t hour, std::int32_t minute);

}  // namespace clock

}  // namespace date_independent

#endif // CLOCK_H
