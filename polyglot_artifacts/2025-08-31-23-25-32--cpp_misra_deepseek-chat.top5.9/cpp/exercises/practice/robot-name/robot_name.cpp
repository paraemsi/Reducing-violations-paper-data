#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

// Define the static member
std::set<std::string> robot::used_names;

std::string robot::generate_random_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
    static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
    
    const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits = "0123456789";
    
    std::string name;
    // Check if all possible names are used
    if (used_names.size() == 26 * 26 * 10 * 10 * 10) {
        throw std::runtime_error("All possible robot names are used");
    }
    
    while (true) {
        name.clear();
        // Generate two letters by indexing into the letters string
        std::int32_t letter_index1 = letter_dist(gen);
        std::int32_t letter_index2 = letter_dist(gen);
        name += letters[static_cast<std::size_t>(letter_index1)];
        name += letters[static_cast<std::size_t>(letter_index2)];
        // Generate three digits by indexing into the digits string
        for (std::int32_t i = 0; i < 3; i++) {
            std::int32_t digit_index = digit_dist(gen);
            name += digits[static_cast<std::size_t>(digit_index)];
        }
        
        // Check if the name is unique
        if (used_names.find(name) == used_names.end()) {
            used_names.insert(name);
            break;
        }
    }
    return name;
}

robot::robot() {
    generate_name();
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names
    robot::used_names.erase(robot_name);
    generate_name();
}

void robot::generate_name() {
    robot_name = generate_random_name();
}

}  // namespace robot_name
