#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    std::string generate_name_impl() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        // Lookup tables to avoid character arithmetic
        static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static const char digits[] = "0123456789";
        
        // Check if all possible names are used
        const std::int32_t max_possible_names = 26 * 26 * 10 * 10 * 10;
        if (used_names.size() >= static_cast<std::size_t>(max_possible_names)) {
            throw std::runtime_error("All possible robot names are exhausted");
        }
        
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
}

robot::robot() : robot_name(generate_name_impl()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names
    used_names.erase(robot_name);
    // Generate a new unique name
    robot_name = generate_name_impl();
}

}  // namespace robot_name
