#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

// Define an index type to use instead of raw integer types
using index_t = std::int32_t;

namespace {
    std::set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<index_t> letter_dist(0, 25);
        static std::uniform_int_distribution<index_t> digit_dist(0, 9);
        
        // Lookup tables to avoid character arithmetic
        static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static const char digits[] = "0123456789";
        
        std::string name;
        while (true) {
            name.clear();
            // Generate two letters by indexing into the letters array
            name += letters[static_cast<index_t>(letter_dist(gen))];
            name += letters[static_cast<index_t>(letter_dist(gen))];
            // Generate three digits by indexing into the digits array
            for (index_t i = 0; i < 3; i++) {
                name += digits[static_cast<index_t>(digit_dist(gen))];
            }
            
            // Check if the name is unique (always use compound statements for if)
            if (used_names.find(name) == used_names.end()) {
                used_names.insert(name);
                break;
            }
        }
        return name;
    }
}

robot::robot() : robot_name(generate_random_name()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names (always use compound statements for if)
    if (!robot_name.empty()) {
        used_names.erase(robot_name);
    }
    // Generate a new unique name
    robot_name = generate_random_name();
}

}  // namespace robot_name
