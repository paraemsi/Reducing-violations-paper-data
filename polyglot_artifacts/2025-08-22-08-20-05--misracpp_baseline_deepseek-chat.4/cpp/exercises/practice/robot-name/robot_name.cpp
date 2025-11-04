#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <stdexcept>

namespace robot_name {

// Use a function to ensure the set is always properly initialized
std::unordered_set<std::string>& get_used_names() {
    static std::unordered_set<std::string> used_names;
    return used_names;
}

robot::robot() {
    robot_name = generate_name();
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Get reference to the used names set
    auto& used_names = get_used_names();
    // Remove the current name from the used names set
    used_names.erase(robot_name);
    // Generate a new unique name
    robot_name = generate_name();
}

std::string robot::generate_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> letter_dist(0, 25);
    static std::uniform_int_distribution<int> digit_dist(0, 9);
    
    auto& used_names = get_used_names();
    std::string new_name;
    
    // Keep generating names until we find a unique one
    while (true) {
        new_name.clear();
        // Add two random letters
        new_name += static_cast<char>('A' + letter_dist(gen));
        new_name += static_cast<char>('A' + letter_dist(gen));
        // Add three random digits
        new_name += static_cast<char>('0' + digit_dist(gen));
        new_name += static_cast<char>('0' + digit_dist(gen));
        new_name += static_cast<char>('0' + digit_dist(gen));
        
        // Check if the name is unique
        if (used_names.find(new_name) == used_names.end()) {
            used_names.insert(new_name);
            return new_name;
        }
    }
}

}  // namespace robot_name
