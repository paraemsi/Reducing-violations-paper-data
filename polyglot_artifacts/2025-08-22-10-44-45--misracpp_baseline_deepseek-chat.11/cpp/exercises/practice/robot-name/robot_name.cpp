#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <stdexcept>
#include <cctype>

namespace robot_name {

// Define the static member
std::unordered_set<std::string> robot::used_names;

std::string robot::generate_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> letter_dist(0, 25);
    static std::uniform_int_distribution<int> digit_dist(0, 9);
    
    std::string name;
    do {
        name.clear();
        // Add two random uppercase letters
        name += 'A' + letter_dist(gen);
        name += 'A' + letter_dist(gen);
        // Add three random digits as characters
        name += '0' + digit_dist(gen);
        name += '0' + digit_dist(gen);
        name += '0' + digit_dist(gen);
    } while (used_names.find(name) != used_names.end());
    
    used_names.insert(name);
    return name;
}

robot::robot() : name_(generate_name()) {
}

std::string robot::name() const {
    return name_;
}

void robot::reset() {
    // Remove the old name from used_names
    used_names.erase(name_);
    // Generate a new unique name
    name_ = generate_name();
}

}  // namespace robot_name
