#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>

namespace robot_name {

// Define the static member
std::set<std::string> robot::used_names;

robot::robot() {
    generate_name();
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the current name from used_names
    used_names.erase(robot_name);
    generate_name();
}

void robot::generate_name() {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> letter_dist(0, 25);
    std::uniform_int_distribution<int> digit_dist(0, 9);
    
    while (true) {
        // Generate a new name
        std::string new_name;
        new_name += 'A' + letter_dist(gen);
        new_name += 'A' + letter_dist(gen);
        new_name += '0' + digit_dist(gen);
        new_name += '0' + digit_dist(gen);
        new_name += '0' + digit_dist(gen);
        
        // Check if it's unique
        if (used_names.find(new_name) == used_names.end()) {
            used_names.insert(new_name);
            robot_name = new_name;
            break;
        }
    }
}

}  // namespace robot_name
