#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::mt19937 gen(std::random_device{}());
        static const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 999);
        
        while (true) {
            // Pick two letters using indices
            std::int32_t index1 = letter_dist(gen);
            std::int32_t index2 = letter_dist(gen);
            
            // Generate three digits
            std::int32_t number = digit_dist(gen);
            // Format number to three digits with leading zeros by adding 1000 and taking the last 3 digits
            std::string number_str = std::to_string(number + 1000).substr(1);
            
            // Construct the name by indexing into the letters string
            std::string name;
            name += letters[index1];
            name += letters[index2];
            name += number_str;
            
            // Check if the name is unique
            if (used_names.find(name) == used_names.end()) {
                used_names.insert(name);
                return name;
            }
            // If not unique, try again
        }
    }
}

robot::robot() : robot_name(generate_random_name()) {
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
