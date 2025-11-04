#include "robot_name.h"
#include <random>
#include <set>
#include <stdexcept>
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
        
        // To prevent infinite loop in case all names are used
        // This should never happen if the number of active robots is less than 676,000
        if (used_names.size() >= 676000) {
            throw std::runtime_error("All possible robot names are used");
        }
        
        std::string name;
        do {
            name.clear();
            // Generate two letters
            name += static_cast<char>('A' + letter_dist(gen));
            name += static_cast<char>('A' + letter_dist(gen));
            // Generate three digits
            for (std::int32_t i = 0; i < 3; ++i) {
                name += static_cast<char>('0' + digit_dist(gen));
            }
        } while (used_names.find(name) != used_names.end());
        
        return name;
    }
}

robot::robot() {
    // Generate a unique name and add it to used_names
    robot_name = generate_random_name();
    used_names.insert(robot_name);
}

const std::string& robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names
    used_names.erase(robot_name);
    // Generate a new unique name and add it to used_names
    robot_name = generate_random_name();
    used_names.insert(robot_name);
}

}  // namespace robot_name
