#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <cstdint>
#include <stdexcept>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        // To prevent infinite loop in case all names are used
        const std::int32_t max_attempts = 1000;
        std::int32_t attempts = 0;
        
        std::string name;
        do {
            name.clear();
            // Add first letter
            name += static_cast<char>('A' + static_cast<char>(letter_dist(gen)));
            // Add second letter
            name += static_cast<char>('A' + static_cast<char>(letter_dist(gen)));
            // Add three digits
            for (std::int32_t i = 0; i < 3; ++i) {
                name += static_cast<char>('0' + static_cast<char>(digit_dist(gen)));
            }
            attempts++;
            if (attempts > max_attempts) {
                throw std::runtime_error("Could not generate a unique robot name");
            }
        } while (used_names.find(name) != used_names.end());
        
        used_names.insert(name);
        return name;
    }
}

robot::robot() : robot_name(generate_random_name()) {
}

robot::~robot() {
    if (!robot_name.empty()) {
        used_names.erase(robot_name);
    }
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names if it exists
    if (!robot_name.empty()) {
        used_names.erase(robot_name);
    }
    // Generate a new name
    robot_name = generate_random_name();
}

}  // namespace robot_name
