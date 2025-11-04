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

robot::robot() : robot_name("") {
}

robot::~robot() {
    if (!robot_name.empty()) {
        used_names.erase(robot_name);
    }
}

std::string robot::name() const {
    if (robot_name.empty()) {
        robot_name = generate_name();
    }
    return robot_name;
}

void robot::reset() {
    if (!robot_name.empty()) {
        used_names.erase(robot_name);
    }
    robot_name = "";
}

std::string robot::generate_name() {
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
    static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
    
    // To prevent infinite loop in case all names are used up
    if (used_names.size() >= 26 * 26 * 10 * 10 * 10) {
        throw std::runtime_error("All possible robot names are in use");
    }
    
    std::string new_name;
    while (true) {
        new_name.clear();
        // Generate two letters
        new_name += static_cast<char>('A' + static_cast<char>(letter_dist(gen)));
        new_name += static_cast<char>('A' + static_cast<char>(letter_dist(gen)));
        // Generate three digits
        new_name += static_cast<char>('0' + static_cast<char>(digit_dist(gen)));
        new_name += static_cast<char>('0' + static_cast<char>(digit_dist(gen)));
        new_name += static_cast<char>('0' + static_cast<char>(digit_dist(gen)));
        
        if (used_names.find(new_name) == used_names.end()) {
            used_names.insert(new_name);
            break;
        }
    }
    return new_name;
}

}  // namespace robot_name
