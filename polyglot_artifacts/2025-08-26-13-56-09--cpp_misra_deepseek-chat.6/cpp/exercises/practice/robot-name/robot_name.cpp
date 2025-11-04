#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <cstdio>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    // Random number generator setup
    std::random_device rd;
    std::mt19937 gen(rd());
    // Use appropriate fixed-width types
    std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
    // For digits, we need numbers from 0 to 999
    std::uniform_int_distribution<std::int32_t> digit_dist(0, 999);
}

std::string robot::generate_name() {
    std::string new_name;
    while (true) {
        // Generate two random letters with proper casting
        char first_letter = static_cast<char>('A' + static_cast<char>(letter_dist(gen)));
        char second_letter = static_cast<char>('A' + static_cast<char>(letter_dist(gen)));
        
        // Generate three random digits, ensuring they are formatted with leading zeros
        std::int32_t number = digit_dist(gen);
        // Format number to three digits with leading zeros
        char digits[4];
        // Use snprintf to format the number
        // The cast ensures we're using the right type
        std::snprintf(digits, sizeof(digits), "%03d", static_cast<std::int32_t>(number));
        
        // Build the name
        new_name = std::string() + first_letter + second_letter + digits;
        
        // Check if the name is unique with proper parentheses
        if ((used_names.find(new_name)) == (used_names.end())) {
            break;
        }
    }
    return new_name;
}

robot::robot() : robot_name(generate_name()) {
    used_names.insert(robot_name);
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the current name from used_names
    used_names.erase(robot_name);
    // Generate a new unique name
    std::string new_name = generate_name();
    // Insert the new name
    used_names.insert(new_name);
    robot_name = new_name;
}

}  // namespace robot_name
