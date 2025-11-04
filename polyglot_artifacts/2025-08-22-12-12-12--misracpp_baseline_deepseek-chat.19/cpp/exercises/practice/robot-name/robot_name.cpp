#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <stdexcept>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;

    std::string generate_name() {
        // Generate two random uppercase letters
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> letter_dist(0, 25);
        static std::uniform_int_distribution<> digit_dist(0, 9);
        
        std::string name;
        do {
            name.clear();
            // Add two letters
            name += 'A' + letter_dist(gen);
            name += 'A' + letter_dist(gen);
            // Add three digits
            name += std::to_string(digit_dist(gen));
            name += std::to_string(digit_dist(gen));
            name += std::to_string(digit_dist(gen));
        } while (used_names.find(name) != used_names.end());
        
        used_names.insert(name);
        return name;
    }
}

robot::robot() : robot_name_(generate_name()) {
}

std::string robot::name() const {
    return robot_name_;
}

void robot::reset() {
    // Remove the old name from used_names
    used_names.erase(robot_name_);
    // Generate a new name
    robot_name_ = generate_name();
}

}  // namespace robot_name
