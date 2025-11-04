#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <cstdint>
#include <stdexcept>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    std::string generate_unique_name() {
        static std::mt19937 gen(std::random_device{}());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        // Maximum number of attempts to prevent infinite loop
        const std::int32_t max_attempts = 676000; // Total possible names
        std::string new_name;
        
        for (std::int32_t attempt = 0; attempt < max_attempts; attempt++) {
            new_name.clear();
            // Generate two letters
            new_name += static_cast<char>(('A' + letter_dist(gen)));
            new_name += static_cast<char>(('A' + letter_dist(gen)));
            // Generate three digits
            for (std::int32_t i = 0; i < 3; i++) {
                new_name += static_cast<char>(('0' + digit_dist(gen)));
            }
            
            // Check if the name is unique
            if (used_names.find(new_name) == used_names.end()) {
                used_names.insert(new_name);
                return new_name;
            }
        }
        throw std::runtime_error("All possible robot names are used");
    }
}

robot::robot() : robot_name(generate_unique_name()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Generate the new name first
    std::string new_name = generate_unique_name();
    // Remove the old name from used_names
    used_names.erase(robot_name);
    // Update to the new name
    robot_name = new_name;
}

}  // namespace robot_name
