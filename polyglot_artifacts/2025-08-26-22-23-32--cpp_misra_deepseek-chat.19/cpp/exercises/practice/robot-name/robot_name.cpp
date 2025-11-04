#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    // Random number generator setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
    std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
}

std::string robot::generate_name() {
    // Check if all possible names are used
    constexpr std::int32_t max_names = 26 * 26 * 10 * 10 * 10;
    if (used_names.size() >= max_names) {
        throw std::runtime_error("All possible robot names are used");
    }
    
    std::string new_name;
    while (true) {
        new_name.clear();
        // Generate two random letters
        new_name += static_cast<char>('A' + letter_dist(gen));
        new_name += static_cast<char>('A' + letter_dist(gen));
        // Generate three random digits
        new_name += static_cast<char>('0' + digit_dist(gen));
        new_name += static_cast<char>('0' + digit_dist(gen));
        new_name += static_cast<char>('0' + digit_dist(gen));
        
        // Check if the name is unique
        if (used_names.find(new_name) == used_names.end()) {
            used_names.insert(new_name);
            break;
        }
    }
    return new_name;
}

robot::robot() : robot_name(generate_name()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the current name from used_names
    if (!robot_name.empty()) {
        used_names.erase(robot_name);
    }
    // Generate a new name
    robot_name = generate_name();
}

}  // namespace robot_name
