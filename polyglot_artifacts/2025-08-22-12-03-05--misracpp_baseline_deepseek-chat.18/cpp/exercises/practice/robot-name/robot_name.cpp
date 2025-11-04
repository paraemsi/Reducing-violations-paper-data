#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <string>

namespace robot_name {

namespace {
    // Use a static set to keep track of all used names
    std::unordered_set<std::string> used_names;
    
    // Helper function to generate a random name
    std::string generate_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<int> letters_dist(0, 25);
        static std::uniform_int_distribution<int> digits_dist(0, 9);
        
        std::string name;
        do {
            name.clear();
            // Add two random uppercase letters
            char letter1 = 'A' + letters_dist(gen);
            char letter2 = 'A' + letters_dist(gen);
            // Add three random digits
            char digit1 = '0' + digits_dist(gen);
            char digit2 = '0' + digits_dist(gen);
            char digit3 = '0' + digits_dist(gen);
            
            name += letter1;
            name += letter2;
            name += digit1;
            name += digit2;
            name += digit3;
        } while (used_names.count(name) > 0);
        
        used_names.insert(name);
        return name;
    }
}

robot::robot() : robot_name_(generate_name()) {
}

std::string robot::name() const {
    return robot_name_;
}

void robot::reset() {
    // Remove the current name from used_names
    used_names.erase(robot_name_);
    // Generate a new unique name
    robot_name_ = generate_name();
}

}  // namespace robot_name
