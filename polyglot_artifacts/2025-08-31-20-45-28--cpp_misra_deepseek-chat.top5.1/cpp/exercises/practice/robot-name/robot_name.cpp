#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string digits = "0123456789";
    
    std::string generate_random_name() {
        static std::mt19937 gen(std::random_device{}());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, (static_cast<std::int32_t>(letters.size()) - 1));
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, (static_cast<std::int32_t>(digits.size()) - 1));
        
        std::string name;
        do {
            name.clear();
            // Generate two letters
            for (std::int32_t i = 0; i < 2; i++) {
                name += letters[static_cast<std::size_t>(letter_dist(gen))];
            }
            // Generate three digits
            for (std::int32_t i = 0; i < 3; i++) {
                name += digits[static_cast<std::size_t>(digit_dist(gen))];
            }
        } while (used_names.find(name) != used_names.end());
        
        used_names.insert(name);
        return name;
    }
}

robot::robot() {
    generate_name();
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    used_names.erase(robot_name);
    generate_name();
}

void robot::generate_name() {
    robot_name = generate_random_name();
    used_names.insert(robot_name);
}

}  // namespace robot_name
