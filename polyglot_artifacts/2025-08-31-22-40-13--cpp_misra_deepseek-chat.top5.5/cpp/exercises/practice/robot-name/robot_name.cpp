#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
}

robot::robot() : robot_name(generate_name()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names
    used_names.erase(robot_name);
    // Generate a new unique name
    robot_name = generate_name();
}

std::string robot::generate_name() {
    static std::mt19937 gen(std::random_device{}());
    // Distributions for indices
    static constexpr std::int32_t num_letters = 26;
    static std::uniform_int_distribution<std::int32_t> letter_dist(0, (num_letters - 1));
    static constexpr std::int32_t num_digits = 10;
    static std::uniform_int_distribution<std::int32_t> digit_dist(0, (num_digits - 1));
    
    // Lookup tables
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const char digits[] = "0123456789";
    
    std::string new_name;
    while (true) {
        new_name.clear();
        // Generate two letters by indexing into the letters array
        new_name += letters[letter_dist(gen)];
        new_name += letters[letter_dist(gen)];
        // Generate three digits by indexing into the digits array
        for (std::int32_t i = 0; i < 3; i++) {
            new_name += digits[digit_dist(gen)];
        }
        
        // Check if the name is unique
        if (used_names.find(new_name) == used_names.end()) {
            used_names.insert(new_name);
            break;
        }
    }
    return new_name;
}

}  // namespace robot_name
