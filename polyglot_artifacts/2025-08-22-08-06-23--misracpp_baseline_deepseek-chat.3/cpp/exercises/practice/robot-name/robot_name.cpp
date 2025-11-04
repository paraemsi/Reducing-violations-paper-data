#include "robot_name.h"
#include <random>
#include <set>
#include <stdexcept>
#include <string>

namespace robot_name {

// Static set to keep track of used names
std::set<std::string> used_names;

// Helper function to generate a random name
std::string robot::generate_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> letter_dist(0, 25);
    std::uniform_int_distribution<> digit_dist(0, 9);
    
    std::string new_name;
    int attempts = 0;
    const int max_attempts = 1000;
    
    do {
        new_name.clear();
        // Add two random uppercase letters
        new_name += 'A' + letter_dist(gen);
        new_name += 'A' + letter_dist(gen);
        // Add three random digits as characters
        new_name += '0' + digit_dist(gen);
        new_name += '0' + digit_dist(gen);
        new_name += '0' + digit_dist(gen);
        attempts++;
        if (attempts > max_attempts) {
            throw std::runtime_error("Failed to generate a unique robot name");
        }
    } while (used_names.find(new_name) != used_names.end());
    
    used_names.insert(new_name);
    return new_name;
}

robot::robot() : robot_name(generate_name()) {
}

robot::~robot() {
    used_names.erase(robot_name);
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names
    used_names.erase(robot_name);
    // Generate a new name
    robot_name = generate_name();
}

}  // namespace robot_name
