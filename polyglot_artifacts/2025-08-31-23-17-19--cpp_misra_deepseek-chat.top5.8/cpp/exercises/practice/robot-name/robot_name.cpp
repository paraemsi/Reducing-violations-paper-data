#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <cstdint>
#include <stdexcept>

namespace robot_name {

// Initialize static member
std::set<std::string> robot::used_names;

std::string robot::generate_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
    static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
    
    // Lookup tables for valid characters
    constexpr char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr char digits[] = "0123456789";
    
    std::string new_name;
    while (true) {
        new_name.clear();
        
        // Generate two letters by indexing into the letters array
        for (std::int32_t i = 0; i < 2; i++) {
            std::int32_t index = letter_dist(gen);
            new_name += letters[index];
        }
        
        // Generate three digits by indexing into the digits array
        for (std::int32_t i = 0; i < 3; i++) {
            std::int32_t index = digit_dist(gen);
            new_name += digits[index];
        }
        
        // Check if the name is unique
        if (used_names.find(new_name) == used_names.end()) {
            used_names.insert(new_name);
            break;
        }
    }
    return new_name;
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
