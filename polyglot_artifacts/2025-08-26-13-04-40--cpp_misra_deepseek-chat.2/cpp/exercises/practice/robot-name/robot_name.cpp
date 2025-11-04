#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        // If all names are used, we can't generate a new one
        // This should not happen according to the tests, but let's be safe
        if (used_names.size() >= (26 * 26 * 10 * 10 * 10)) {
            throw std::runtime_error("All possible robot names are used");
        }
        
        std::string name;
        do {
            name.clear();
            // Generate two letters
            name += static_cast<char>(('A' + letter_dist(gen)));
            name += static_cast<char>(('A' + letter_dist(gen)));
            // Generate three digits
            name += static_cast<char>(('0' + digit_dist(gen)));
            name += static_cast<char>(('0' + digit_dist(gen)));
            name += static_cast<char>(('0' + digit_dist(gen)));
        } while ((used_names.find(name) != used_names.end()));
        
        used_names.insert(name);
        return name;
    }
}

robot::robot() {
    generate_name();
}

robot::~robot() {
    // Don't remove the name from used_names to ensure it's never reused
    // This makes all generated names unique throughout the program's lifetime
}

const std::string& robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Generate a new name without removing the old one from used_names
    // This ensures the old name is never reused
    generate_name();
}

void robot::generate_name() {
    robot_name = generate_random_name();
    // The name is already inserted into used_names by generate_random_name()
}

}  // namespace robot_name
