#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <cstddef>

namespace robot_name {

std::set<std::string> robot::used_names;

namespace {
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::uint32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::uint32_t> digit_dist(0, 9);
        
        const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const std::string digits = "0123456789";
        
        std::string name;
        while (true) {
            name.clear();
            // Generate two letters
            for (std::uint32_t i = 0; i < 2; i++) {
                name += letters[static_cast<std::size_t>(letter_dist(gen))];
            }
            // Generate three digits
            for (std::uint32_t i = 0; i < 3; i++) {
                name += digits[static_cast<std::size_t>(digit_dist(gen))];
            }
            
            // Check if the name is unique
            if (robot::used_names.find(name) == robot::used_names.end()) {
                robot::used_names.insert(name);
                break;
            }
        }
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
    // Remove the current name from used_names
    robot::used_names.erase(robot_name);
    generate_name();
}

void robot::generate_name() {
    robot_name = generate_random_name();
}

}  // namespace robot_name
