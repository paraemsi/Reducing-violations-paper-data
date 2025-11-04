#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    std::string generate_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        // Use a fixed-width type that's at least 32 bits
        // Let's use uint32_t to be safe
        static std::uniform_int_distribution<std::uint32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::uint32_t> digit_dist(0, 9);
        
        std::string name;
        do {
            name.clear();
            // Generate two letters - ensure proper precedence with parentheses
            name += static_cast<char>(('A' + (letter_dist(gen))));
            name += static_cast<char>(('A' + (letter_dist(gen))));
            // Generate three digits
            // Ensure each digit is properly converted
            name += std::to_string(static_cast<int>(digit_dist(gen)));
            name += std::to_string(static_cast<int>(digit_dist(gen)));
            name += std::to_string(static_cast<int>(digit_dist(gen)));
        } while ((used_names.find(name)) != (used_names.end()));
        
        used_names.insert(name);
        return name;
    }
}

robot::robot() : name_(generate_name()) {
}

std::string robot::name() const {
    return name_;
}

void robot::reset() {
    // Remove the old name from used_names
    used_names.erase(name_);
    // Generate a new name
    name_ = generate_name();
}

}  // namespace robot_name
