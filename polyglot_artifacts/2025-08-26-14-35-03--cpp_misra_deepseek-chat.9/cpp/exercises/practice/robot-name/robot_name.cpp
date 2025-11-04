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
    
    std::string name;
    do {
        name.clear();
        // Generate two letters
        name += static_cast<char>('A' + letter_dist(gen));
        name += static_cast<char>('A' + letter_dist(gen));
        // Generate three digits
        for (std::int32_t i = 0; i < 3; ++i) {
            name += static_cast<char>('0' + digit_dist(gen));
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
    used_names.erase(robot_name);
    robot_name = generate_name();
}

}  // namespace robot_name
