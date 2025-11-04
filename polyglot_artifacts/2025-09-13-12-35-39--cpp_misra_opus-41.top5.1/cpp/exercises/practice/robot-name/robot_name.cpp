#include "robot_name.h"
#include <random>
#include <cstdint>

namespace robot_name {

// Initialize the static member
std::unordered_set<std::string> robot::used_names;

robot::robot() {
    name_ = generate_unique_name();
}

robot::~robot() {
    // Remove the name from the used set when robot is destroyed
    // This allows the name to be reused by future robots
    if (!name_.empty()) {
        used_names.erase(name_);
    }
}

std::string robot::name() const {
    return name_;
}

void robot::reset() {
    // Generate a new unique name
    // Note: We don't remove the old name from used_names here
    // This ensures that reset() always generates a completely new name
    name_ = generate_unique_name();
}

std::string robot::generate_unique_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<std::uint32_t> letter_dist(0, 25);
    static std::uniform_int_distribution<std::uint32_t> digit_dist(0, 9);
    
    // Arrays to avoid character arithmetic
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const char digits[] = "0123456789";
    
    std::string new_name;
    
    // Keep generating until we find a unique name
    // Maximum possible names: 26*26*10*10*10 = 676,000
    do {
        new_name.clear();
        
        // Generate two uppercase letters
        for (std::uint32_t i = 0; i < 2; ++i) {
            std::uint32_t letter_index = letter_dist(gen);
            new_name += letters[letter_index];
        }
        
        // Generate three digits
        for (std::uint32_t i = 0; i < 3; ++i) {
            std::uint32_t digit_index = digit_dist(gen);
            new_name += digits[digit_index];
        }
    } while (used_names.find(new_name) != used_names.end());
    
    // Add the new name to the used set
    used_names.insert(new_name);
    
    return new_name;
}

}  // namespace robot_name
