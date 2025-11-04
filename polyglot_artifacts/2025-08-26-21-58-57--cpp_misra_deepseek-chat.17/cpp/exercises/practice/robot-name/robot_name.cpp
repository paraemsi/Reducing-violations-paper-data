#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        std::string name;
        do {
            name.clear();
            // Generate two letters
            name += static_cast<char>('A' + letter_dist(gen));
            name += static_cast<char>('A' + letter_dist(gen));
            // Generate three digits
            name += static_cast<char>('0' + digit_dist(gen));
            name += static_cast<char>('0' + digit_dist(gen));
            name += static_cast<char>('0' + digit_dist(gen));
        } while (used_names.find(name) != used_names.end());
        
        used_names.insert(name);
        return name;
    }
}

robot::robot() {
    generate_name();
}

// Since we never remove names from used_names, the destructor doesn't need to do anything
robot::~robot() {
    // Do nothing - names are never reused
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Generate a new name without removing the old one from used_names
    // This ensures the old name remains in used_names and won't be reused
    generate_name();
}

void robot::generate_name() {
    robot_name = generate_random_name();
}

}  // namespace robot_name
