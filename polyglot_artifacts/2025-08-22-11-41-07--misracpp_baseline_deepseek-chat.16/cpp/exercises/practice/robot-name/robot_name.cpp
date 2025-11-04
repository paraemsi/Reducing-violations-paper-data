#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <stdexcept>

namespace robot_name {

// Define the static member
std::unordered_set<std::string> robot::used_names;

// Helper function to generate a random name
std::string robot::generate_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> letter_dist(0, 25);
    static std::uniform_int_distribution<int> digit_dist(0, 9);
    
    std::string new_name;
    while (true) {
        new_name.clear();
        // Generate two random letters
        new_name += 'A' + letter_dist(gen);
        new_name += 'A' + letter_dist(gen);
        // Generate three random digits as characters
        new_name += '0' + digit_dist(gen);
        new_name += '0' + digit_dist(gen);
        new_name += '0' + digit_dist(gen);
        
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
    used_names.erase(robot_name);
    // Generate a new unique name
    robot_name = generate_name();
}

}  // namespace robot_name
