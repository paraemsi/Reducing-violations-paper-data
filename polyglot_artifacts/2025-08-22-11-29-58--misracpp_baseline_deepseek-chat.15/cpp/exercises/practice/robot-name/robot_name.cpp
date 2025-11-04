#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <stdexcept>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int> letter_dist(0, 25);
        static std::uniform_int_distribution<int> digit_dist(0, 9);
        
        std::string name;
        do {
            name.clear();
            // Add two random letters
            name += static_cast<char>('A' + letter_dist(gen));
            name += static_cast<char>('A' + letter_dist(gen));
            // Add three random digits as characters
            name += static_cast<char>('0' + digit_dist(gen));
            name += static_cast<char>('0' + digit_dist(gen));
            name += static_cast<char>('0' + digit_dist(gen));
        } while (used_names.find(name) != used_names.end());
        
        used_names.insert(name);
        return name;
    }
}

robot::robot() {
    robot_name = generate_random_name();
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names
    used_names.erase(robot_name);
    // Generate a new unique name
    robot_name = generate_random_name();
}

}  // namespace robot_name
