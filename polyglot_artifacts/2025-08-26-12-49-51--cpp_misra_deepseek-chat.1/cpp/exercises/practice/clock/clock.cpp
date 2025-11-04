#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t total_minutes) : minutes(total_minutes) {
        // Normalize to be within 0-1439
        minutes %= 1440;
        if (minutes < 0) {
            minutes += 1440;
        }
    }

    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert hours to minutes and add
        std::int32_t total_minutes = (hours * 60) + minutes;
        return clock(total_minutes);
    }

    clock clock::plus(std::int32_t add_minutes) const {
        // Add minutes and normalize
        std::int32_t new_minutes = minutes + add_minutes;
        return clock(new_minutes);
    }

    clock clock::minus(std::int32_t sub_minutes) const {
        // Subtract by adding negative minutes
        return this->plus(-sub_minutes);
    }

    clock::operator std::string() const {
        std::int32_t h = minutes / 60;
        std::int32_t m = minutes % 60;
        
        // Ensure hours are between 0 and 23 (always true due to normalization)
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << h << ":" 
            << std::setw(2) << std::setfill('0') << m;
        return oss.str();
    }

    bool clock::operator==(const clock& other) const {
        return minutes == other.minutes;
    }

    bool clock::operator!=(const clock& other) const {
        return minutes != other.minutes;
    }
}  // namespace date_independent
