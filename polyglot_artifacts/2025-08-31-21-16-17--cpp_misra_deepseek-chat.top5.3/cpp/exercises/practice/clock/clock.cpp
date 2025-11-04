#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t total_minutes) {
        // Normalize to be within 0-1439 minutes (24 hours)
        // Handle negative values by adding enough days to make it positive
        total_minutes %= 1440;
        if (total_minutes < 0) { 
            total_minutes += 1440; 
        }
        this->minutes = total_minutes;
    }

    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        std::int32_t total_minutes = (hours * 60) + minutes;
        return clock(total_minutes);
    }

    clock clock::plus(std::int32_t add_minutes) const {
        std::int32_t new_minutes = (this->minutes + add_minutes) % 1440;
        if (new_minutes < 0) { 
            new_minutes += 1440; 
        }
        return clock(new_minutes);
    }

    clock clock::minus(std::int32_t sub_minutes) const {
        return this->plus(-sub_minutes);
    }

    clock::operator std::string() const {
        std::int32_t hours = this->minutes / 60;
        std::int32_t mins = this->minutes % 60;
        
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << mins;
        return oss.str();
    }

    bool clock::operator==(const clock& other) const {
        return (this->minutes == other.minutes);
    }

    bool clock::operator!=(const clock& other) const {
        return !((*this) == other);
    }
}  // namespace date_independent
