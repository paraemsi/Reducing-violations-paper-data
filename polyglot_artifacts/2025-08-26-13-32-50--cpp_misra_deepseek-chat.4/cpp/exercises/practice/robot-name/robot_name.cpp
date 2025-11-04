#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
}

std::string robot::generate_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
    static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
    
    std::string new_name;
    while (true) {
        new_name.clear();
        // Generate two letters
        new_name += static_cast<char>('A' + letter_dist(gen));
        new_name += static_cast<char>('A' + letter_dist(gen));
        // Generate three digits
        new_name += static_cast<char>('0' + digit_dist(gen));
        new_name += static_cast<char>('0' + digit_dist(gen));
        new_name += static_cast<char>('0' + digit_dist(gen));
        
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
    // Remove the old name from used_names
    used_names.erase(robot_name);
    // Generate a new unique name
    robot_name = generate_name();
}

}  // namespace robot_name
