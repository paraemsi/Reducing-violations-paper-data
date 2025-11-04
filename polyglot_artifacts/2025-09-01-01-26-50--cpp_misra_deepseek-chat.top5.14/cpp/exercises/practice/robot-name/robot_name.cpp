#include "robot_name.h"
#include <random>
#include <string>
#include <set>
#include <cstdint>
#include <stdexcept>
#include <array>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        
        // Define possible letters and digits
        static const std::array<char, 26> letters = {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
        };
        static const std::array<char, 10> digits = {
            '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
        };
        
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        std::string name;
        while (true) {
            name.clear();
            // Add two random letters
            name += letters[letter_dist(gen)];
            name += letters[letter_dist(gen)];
            // Add three random digits
            name += digits[digit_dist(gen)];
            name += digits[digit_dist(gen)];
            name += digits[digit_dist(gen)];
            
            // Check if the name is unique
            if (used_names.find(name) == used_names.end()) {
                used_names.insert(name);
                break;
            }
        }
        return name;
    }
}

robot::robot() {
    generate_name();
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Generate a new name without removing the old one from used_names
    // This ensures all names ever assigned are unique
    generate_name();
}

void robot::generate_name() {
    robot_name = generate_random_name();
}

}  // namespace robot_name
