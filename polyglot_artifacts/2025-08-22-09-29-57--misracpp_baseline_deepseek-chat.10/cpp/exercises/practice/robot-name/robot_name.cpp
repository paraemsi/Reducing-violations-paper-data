#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <string>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
}

robot::robot() {
    generate_name();
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    used_names.erase(robot_name);
    generate_name();
}

void robot::generate_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> letter_dist(0, 25);
    static std::uniform_int_distribution<int> digit_dist(0, 9);
    
    std::string new_name;
    do {
        new_name.clear();
        // Add two uppercase letters
        new_name += 'A' + letter_dist(gen);
        new_name += 'A' + letter_dist(gen);
        // Add three digits
        new_name += std::to_string(digit_dist(gen));
        new_name += std::to_string(digit_dist(gen));
        new_name += std::to_string(digit_dist(gen));
    } while (used_names.find(new_name) != used_names.end());
    
    used_names.insert(new_name);
    robot_name = new_name;
}

}  // namespace robot_name
