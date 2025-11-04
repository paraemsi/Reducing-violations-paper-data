#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <cstdint>

namespace robot_name {

std::set<std::string> robot::used_names;

std::string robot::generate_name() {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
    static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
    
    std::string new_name;
    do {
        new_name.clear();
        // Generate two letters
        for (std::int32_t i = 0; i < 2; i++) {
            new_name += static_cast<char>(('A' + letter_dist(gen)));
        }
        // Generate three digits
        for (std::int32_t i = 0; i < 3; i++) {
            new_name += static_cast<char>(('0' + digit_dist(gen)));
        }
    } while ((used_names.find(new_name) != used_names.end()));
    
    used_names.insert(new_name);
    return new_name;
}

robot::robot() : robot_name(generate_name()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Don't erase the old name from used_names to ensure it's never reused
    robot_name = generate_name();
}

}  // namespace robot_name
