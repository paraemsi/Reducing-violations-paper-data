#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <cstddef>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        
        // Define valid characters
        static const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static const std::string digits = "0123456789";
        
        // Distributions
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, (static_cast<std::int32_t>((letters.size()) - 1)));
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, (static_cast<std::int32_t>((digits.size()) - 1)));
        
        std::string name;
        // To prevent infinite loop in case all names are used
        const std::int32_t max_attempts = 1000;
        std::int32_t attempts = 0;
        
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
            attempts++;
            if (attempts > max_attempts) {
                throw std::runtime_error("Unable to generate a unique robot name");
            }
        } while ((used_names.find(name)) != used_names.end());
        
        used_names.insert(name);
        return name;
    }
}

robot::robot() : robot_name(generate_random_name()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the current name from used_names first
    used_names.erase(robot_name);
    // Generate a new unique name
    robot_name = generate_random_name();
    // The new name is already added to used_names in generate_random_name()
}

}  // namespace robot_name
