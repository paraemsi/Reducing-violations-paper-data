#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {

// Generate a random name in the format of two uppercase letters followed by three digits
std::string generate_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> letter_dist(0, 25);
    static std::uniform_int_distribution<> digit_dist(0, 9);
    
    std::string name;
    name += 'A' + letter_dist(gen);
    name += 'A' + letter_dist(gen);
    name += '0' + digit_dist(gen);
    name += '0' + digit_dist(gen);
    name += '0' + digit_dist(gen);
    return name;
}

// Keep track of used names to ensure uniqueness
std::unordered_set<std::string>& used_names() {
    static std::unordered_set<std::string> names;
    return names;
}

} // namespace

robot::robot() {
    // Generate a unique name
    while (true) {
        robot_name_ = generate_name();
        if (used_names().insert(robot_name_).second) {
            break;
        }
    }
}

std::string robot::name() const {
    return robot_name_;
}

void robot::reset() {
    // Remove the current name from used names
    used_names().erase(robot_name_);
    
    // Generate a new unique name
    while (true) {
        robot_name_ = generate_name();
        if (used_names().insert(robot_name_).second) {
            break;
        }
    }
}

}  // namespace robot_name
