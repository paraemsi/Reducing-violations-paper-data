#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <cstdint>

namespace robot_name {

// Initialize static member
std::set<std::string> robot::used_names;

robot::robot() : name_generated(false) {
    // Don't generate the name here, generate it when name() is first called
}

robot::~robot() {
    // When the robot is destroyed, remove its name from used_names if it was generated
    if (name_generated) {
        used_names.erase(robot_name);
    }
}

std::string robot::generate_name() {
    static std::mt19937 engine{std::random_device{}()};
    static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
    static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
    
    // To prevent infinite loop, limit the number of attempts
    const std::int32_t max_attempts = 1000;
    std::string new_name;
    
    for (std::int32_t attempt = 0; attempt < max_attempts; ++attempt) {
        new_name.clear();
        // Generate two letters
        new_name += static_cast<char>('A' + letter_dist(engine));
        new_name += static_cast<char>('A' + letter_dist(engine));
        // Generate three digits
        for (std::int32_t i = 0; i < 3; ++i) {
            new_name += static_cast<char>('0' + digit_dist(engine));
        }
        
        if (used_names.find(new_name) == used_names.end()) {
            used_names.insert(new_name);
            return new_name;
        }
    }
    
    // If we can't find a unique name after many attempts, throw an exception
    throw std::runtime_error("Could not generate a unique robot name");
}

std::string robot::name() const {
    if (!name_generated) {
        robot_name = generate_name();
        name_generated = true;
    }
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names if it was generated
    if (name_generated) {
        used_names.erase(robot_name);
    }
    // Generate a new name
    robot_name = generate_name();
    name_generated = true;
}

}  // namespace robot_name
