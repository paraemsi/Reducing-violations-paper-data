#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <cstdint>

#include <iostream>
namespace robot_name {

// Define type aliases to avoid using standard integer type names directly
using int32 = std::int32_t;

// Make used_names have external linkage to be shared across all translation units
std::set<std::string> used_names;

namespace {
    
    std::string generate_name() {
        static std::mt19937 gen(std::random_device{}());
        // Use our type alias
        static std::uniform_int_distribution<int32> letter_dist(0, 25);
        static std::uniform_int_distribution<int32> digit_dist(0, 9);
        
        std::string name;
        do {
            name.clear();
            // Generate two letters with proper casts
            int32 const first_letter = letter_dist(gen);
            int32 const second_letter = letter_dist(gen);
            name += static_cast<char>('A' + static_cast<char>(first_letter));
            name += static_cast<char>('A' + static_cast<char>(second_letter));
            
            // Generate three digits
            for (int32 i = 0; i < 3; ++i) {
                int32 const digit = digit_dist(gen);
                name += static_cast<char>('0' + static_cast<char>(digit));
            }
        } while (used_names.find(name) != used_names.end());
        
        used_names.insert(name);
        return name;
    }
}

robot::robot() : robot_name(generate_name()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names first
    used_names.erase(robot_name);
    // Generate a new unique name
    std::string new_name;
    do {
        new_name = generate_name();
    } while (used_names.find(new_name) != used_names.end());
    
    // Insert the new name and update the robot's name
    used_names.insert(new_name);
    robot_name = new_name;
}

}  // namespace robot_name
