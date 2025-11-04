#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

namespace {
    // Track all names ever used to ensure every new name is unique across all time
    std::set<std::string> all_names_ever_used;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        // If all possible names are used, we can't generate a new unique one
        if (all_names_ever_used.size() == 26 * 26 * 10 * 10 * 10) {
            throw std::runtime_error("All possible robot names are used");
        }
        
        std::string name;
        do {
            name.clear();
            // Add two random uppercase letters
            name += static_cast<char>('A' + letter_dist(gen));
            name += static_cast<char>('A' + letter_dist(gen));
            // Add three random digits
            for (std::int32_t i = 0; i < 3; i++) {
                name += static_cast<char>('0' + digit_dist(gen));
            }
        } while (all_names_ever_used.find(name) != all_names_ever_used.end());
        
        all_names_ever_used.insert(name);
        return name;
    }
}

robot::robot() : robot_name(generate_random_name()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Generate a new name which is unique across all names ever used
    // The old name remains in all_names_ever_used to ensure it's not reused
    // This matches the test's expectation that new names are always different from all previous ones
    robot_name = generate_random_name();
}

void robot::generate_name() {
    robot_name = generate_random_name();
}

}  // namespace robot_name
