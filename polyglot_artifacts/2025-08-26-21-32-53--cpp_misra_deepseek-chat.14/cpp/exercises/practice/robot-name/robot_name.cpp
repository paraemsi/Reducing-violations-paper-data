#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        // Use fixed-width integer types
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        std::string name;
        do {
            name.clear();
            // Generate each part with proper casting
            // Add two random uppercase letters
            std::int32_t const first_letter = letter_dist(gen);
            std::int32_t const second_letter = letter_dist(gen);
            // Add three random digits
            std::int32_t const first_digit = digit_dist(gen);
            std::int32_t const second_digit = digit_dist(gen);
            std::int32_t const third_digit = digit_dist(gen);
            
            // Build the name
            name += static_cast<char>('A' + first_letter);
            name += static_cast<char>('A' + second_letter);
            name += static_cast<char>('0' + first_digit);
            name += static_cast<char>('0' + second_digit);
            name += static_cast<char>('0' + third_digit);
        } while (used_names.find(name) != used_names.end());
        
        used_names.insert(name);
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
    // Remove the old name from used_names
    if (!robot_name.empty()) {
        used_names.erase(robot_name);
    }
    generate_name();
}

void robot::generate_name() {
    robot_name = generate_random_name();
}

}  // namespace robot_name
