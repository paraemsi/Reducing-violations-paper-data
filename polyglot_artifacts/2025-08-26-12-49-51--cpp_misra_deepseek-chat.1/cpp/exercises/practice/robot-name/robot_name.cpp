#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

// Define the static member
std::set<std::string> robot::used_names;

robot::robot() : robot_name("") {
}

std::string robot::name() const {
    if (robot_name.empty()) {
        robot_name = generate_name();
    }
    return robot_name;
}

void robot::reset() {
    if (!robot_name.empty()) {
        used_names.erase(robot_name);
        robot_name.clear();
    }
}

std::string robot::generate_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
    static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
    
    // To prevent infinite loop in case all names are used
    // Since the test wants all names to be unique across all time, not just active robots
    // We need to track all generated names
    if (used_names.size() >= (26 * 26 * 10 * 10 * 10)) {
        throw std::runtime_error("All possible robot names are used");
    }
    
    std::string name;
    do {
        // Generate two random letters
        char first_char = static_cast<char>('A' + letter_dist(gen));
        char second_char = static_cast<char>('A' + letter_dist(gen));
        
        // Generate three random digits
        std::int32_t first_digit = digit_dist(gen);
        std::int32_t second_digit = digit_dist(gen);
        std::int32_t third_digit = digit_dist(gen);
        
        // Construct the name
        name.clear();
        name += first_char;
        name += second_char;
        name += std::to_string(first_digit);
        name += std::to_string(second_digit);
        name += std::to_string(third_digit);
    } while (used_names.find(name) != used_names.end());
    
    used_names.insert(name);
    return name;
}

}  // namespace robot_name
