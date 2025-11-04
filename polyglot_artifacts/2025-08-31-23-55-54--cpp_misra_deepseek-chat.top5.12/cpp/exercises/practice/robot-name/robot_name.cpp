#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <cstdint>

namespace robot_name {

namespace {
    // Lookup tables to avoid character arithmetic
    constexpr char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr char digits[] = "0123456789";
}

std::set<std::string>& robot::get_used_names() {
    static std::set<std::string> used_names;
    return used_names;
}

std::string robot::generate_name() {
    // Use a fixed-width type alias
    using index_type = std::int32_t;
    
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution<index_type> letter_dist(0, 25);
    static std::uniform_int_distribution<index_type> digit_dist(0, 9);
    
    std::string new_name;
    do {
        new_name.clear();
        // Generate two letters by indexing into the letters array
        for (index_type i = 0; i < 2; i++) {
            index_type index = letter_dist(gen);
            new_name += letters[index];
        }
        // Generate three digits by indexing into the digits array
        for (index_type i = 0; i < 3; i++) {
            index_type index = digit_dist(gen);
            new_name += digits[index];
        }
    } while ((get_used_names().find(new_name)) != get_used_names().end());
    
    get_used_names().insert(new_name);
    return new_name;
}

robot::robot() : robot_name(generate_name()) {
}

robot::~robot() {
    // Don't remove the name when the robot is destroyed to ensure all names are always unique
    // This matches what the test expects
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Generate a new unique name without removing the old one
    // This ensures all names ever generated are unique
    robot_name = generate_name();
}

}  // namespace robot_name
