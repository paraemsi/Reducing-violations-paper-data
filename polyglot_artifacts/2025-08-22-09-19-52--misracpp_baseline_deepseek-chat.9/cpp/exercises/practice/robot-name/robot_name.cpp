#include "robot_name.h"
#include <random>
#include <algorithm>
#include <set>
#include <string>
#include <stdexcept>

namespace robot_name {

std::set<std::string> robot::used_names_;

std::string robot::generate_name() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> letters_dist(0, 25);
    std::uniform_int_distribution<> digits_dist(0, 9);
    
    std::string new_name;
    do {
        new_name.clear();
        // Generate two random letters
        new_name += 'A' + letters_dist(gen);
        new_name += 'A' + letters_dist(gen);
        // Generate three random digits
        new_name += std::to_string(digits_dist(gen));
        new_name += std::to_string(digits_dist(gen));
        new_name += std::to_string(digits_dist(gen));
    } while (used_names_.find(new_name) != used_names_.end());
    
    used_names_.insert(new_name);
    return new_name;
}

robot::robot() : robot_name_(generate_name()) {
}

std::string robot::name() const {
    return robot_name_;
}

void robot::reset() {
    // Remove the old name from used_names_
    used_names_.erase(robot_name_);
    // Generate a new name
    robot_name_ = generate_name();
}

}  // namespace robot_name
