#include "clock.h"
#include <string>
#include <sstream>
#include <iomanip>

namespace date_independent {
    clock::clock(std::int32_t minutes) : total_minutes(minutes) {
        normalize();
    }
    
    void clock::normalize() {
        // Handle cases where total_minutes is negative by adding enough days
        // First, make sure total_minutes is positive by adding sufficient multiples of 1440
        if (total_minutes < 0) {
            std::int32_t days_to_add = ((-total_minutes) / 1440) + 1;
            total_minutes += (days_to_add * 1440);
        }
        // Now take modulo to get within 0-1439
        total_minutes %= 1440;
    }
    
    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert to total minutes first
        std::int32_t total = (hours * 60) + minutes;
        return clock(total);
    }
    
    clock clock::plus(std::int32_t minutes) const {
        return clock(total_minutes + minutes);
    }
    
    clock clock::minus(std::int32_t minutes) const {
        return clock(total_minutes - minutes);
    }
    
    clock::operator std::string() const {
        std::int32_t hours = total_minutes / 60;
        std::int32_t mins = total_minutes % 60;
        // Since normalize() ensures total_minutes is between 0-1439, hours will be between 0-23
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << mins;
        return oss.str();
    }
    
    bool clock::operator==(const clock& other) const {
        return (total_minutes == other.total_minutes);
    }
    
    bool clock::operator!=(const clock& other) const {
        return (total_minutes != other.total_minutes);
    }
}  // namespace date_independent
