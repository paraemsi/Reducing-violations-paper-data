#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    // Random number generator
    std::mt19937& get_rng() {
        static std::mt19937 rng(std::random_device{}());
        return rng;
    }
}

std::string robot::generate_name() {
    std::string name;
    do {
        name.clear();
        // Generate two random uppercase letters
        std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        name += static_cast<char>('A' + letter_dist(get_rng()));
        name += static_cast<char>('A' + letter_dist(get_rng()));
        
        // Generate three random digits, ensuring they are always three digits (including leading zeros)
        std::uniform_int_distribution<std::int32_t> digit_dist(0, 999);
        int number = digit_dist(get_rng());
        // Format the number to always be three digits
        if (number < 10) {
            name += "00" + std::to_string(number);
        } else if (number < 100) {
            name += "0" + std::to_string(number);
        } else {
            name += std::to_string(number);
        }
    } while (used_names.find(name) != used_names.end());
    
    used_names.insert(name);
    return name;
}

robot::robot() : robot_name(generate_name()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names
    used_names.erase(robot_name);
    // Generate a new name
    robot_name = generate_name();
}

}  // namespace robot_name
