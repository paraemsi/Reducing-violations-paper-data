#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
    // Keep track of all used names to ensure uniqueness
    std::unordered_set<std::string> used_names;
    
    // Generate a random name
    std::string generate_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> letter_dist(0, 25);
        static std::uniform_int_distribution<> digit_dist(0, 9);
        
        std::string name;
        while (true) {
            // Generate two random letters
            name += 'A' + letter_dist(gen);
            name += 'A' + letter_dist(gen);
            
            // Generate three random digits
            for (int i = 0; i < 3; ++i) {
                name += '0' + digit_dist(gen);
            }
            
            // Check if the name is unique
            if (used_names.find(name) == used_names.end()) {
                used_names.insert(name);
                break;
            }
            // If not unique, reset and try again
            name.clear();
        }
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
    // Generate a new unique name
    robot_name_ = generate_name();
}

}  // namespace robot_name
