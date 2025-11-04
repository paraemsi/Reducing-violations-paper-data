#include "robot_name.h"
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <algorithm>

namespace robot_name {

// Define the static member
std::set<std::string> robot::used_names;

robot::robot() {
    robot_name = generate_name();
}

robot::~robot() {
    // Remove the name from used_names when the robot is destroyed
    used_names.erase(robot_name);
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the current name from used names
    used_names.erase(robot_name);
    // Generate a new unique name
    robot_name = generate_name();
}

std::string robot::generate_name() {
    // Random number generation
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> letter_dist(0, 25);
    std::uniform_int_distribution<> digit_dist(0, 9);
    
    std::string new_name;
    int attempts = 0;
    const int max_attempts = 1000; // Prevent infinite loop
    
    while (attempts < max_attempts) {
        // Generate two random letters
        new_name.clear();
        new_name += 'A' + letter_dist(gen);
        new_name += 'A' + letter_dist(gen);
        // Generate three random digits
        new_name += std::to_string(digit_dist(gen));
        new_name += std::to_string(digit_dist(gen));
        new_name += std::to_string(digit_dist(gen));
        
        // Check if the name is unique
        if (used_names.find(new_name) == used_names.end()) {
            used_names.insert(new_name);
            return new_name;
        }
        attempts++;
    }
    throw std::runtime_error("Unable to generate a unique robot name");
}

}  // namespace robot_name
