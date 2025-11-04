#include "clock.h"
#include <string>
#include <iomanip>
#include <sstream>

namespace date_independent {
    clock::clock(std::int32_t total_minutes) {
        // Normalize to be within 0-1439
        total_minutes %= 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
        this->minutes = total_minutes;
    }

    clock clock::at(std::int32_t hours, std::int32_t minutes) {
        // Convert everything to total minutes and normalize
        std::int32_t total_minutes = (hours * 60) + minutes;
        // Normalize to be within 0-1439
        total_minutes %= 1440;
        if (total_minutes < 0) {
            total_minutes += 1440;
        }
        return clock(total_minutes);
    }

    clock clock::plus(std::int32_t add_minutes) const {
        // Handle large add_minutes by taking modulo 1440 to prevent overflow
        // First, convert to int64_t to prevent overflow during addition
        std::int64_t total = static_cast<std::int64_t>(this->minutes) + add_minutes;
        // Normalize to be within 0-1439
        total %= 1440;
        if (total < 0) {
            total += 1440;
        }
        return clock(static_cast<std::int32_t>(total));
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
        return this->minutes == other.minutes;
    }

    bool clock::operator!=(const clock& other) const {
        return !(*this == other);
    }
}  // namespace date_independent
