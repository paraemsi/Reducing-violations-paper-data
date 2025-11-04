#include "robot_name.h"
#include <random>
#include <functional>
#include <stdexcept>
#include <unordered_set>
#include <string>

namespace robot_name {

std::unordered_set<std::string> robot::used_names_;

robot::robot() : robot_name_(generate_name()) {
}

std::string robot::name() const {
    return robot_name_;
}

void robot::reset() {
    used_names_.erase(robot_name_);
    robot_name_ = generate_name();
}

std::string robot::generate_name() {
    // Random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> letter_dist(0, 25);
    std::uniform_int_distribution<> digit_dist(0, 9);
    
    std::string new_name;
    int attempts = 0;
    const int max_attempts = 1000;  // Prevent infinite loop
    
    do {
        // Generate two random letters
        new_name.clear();
        new_name += 'A' + letter_dist(gen);
        new_name += 'A' + letter_dist(gen);
        
        // Generate three random digits
        new_name += std::to_string(digit_dist(gen));
        new_name += std::to_string(digit_dist(gen));
        new_name += std::to_string(digit_dist(gen));
        
        // Check if we've tried too many times
        if (++attempts > max_attempts) {
            throw std::runtime_error("Unable to generate a unique robot name");
        }
    } while (used_names_.find(new_name) != used_names_.end());
    
    used_names_.insert(new_name);
    return new_name;
}

}  // namespace robot_name
