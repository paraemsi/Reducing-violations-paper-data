#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    // Lookup tables for valid characters
    constexpr char letters[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    
    constexpr char digits[] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
    };
}

robot::robot() : robot_name(generate_name()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names
    used_names.erase(robot_name);
    // Generate a new unique name
    robot_name = generate_name();
}

std::string robot::generate_name() {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<std::int32_t> letter_dist(0, (sizeof(letters) / sizeof(letters[0])) - 1);
    static std::uniform_int_distribution<std::int32_t> digit_dist(0, (sizeof(digits) / sizeof(digits[0])) - 1);
    
    std::string new_name;
    while (true) {
        new_name.clear();
        // Generate two letters by indexing into the letters array
        for (std::int32_t i = 0; i < 2; i++) {
            new_name += letters[letter_dist(gen)];
        }
        // Generate three digits by indexing into the digits array
        for (std::int32_t i = 0; i < 3; i++) {
            new_name += digits[digit_dist(gen)];
        }
        
        // Check if the name is unique
        if (used_names.find(new_name) == used_names.end()) {
            used_names.insert(new_name);
            break;
        }
        // If not unique, generate again
    }
    return new_name;
}

}  // namespace robot_name
