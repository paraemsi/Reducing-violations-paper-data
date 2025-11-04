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
        static std::random_device rd;
        static std::mt19937 gen(rd());
        // Generate distributions with the correct bounds
        // Since letters.size() and digits.size() return size_t which is unsigned, cast to uint32_t
        std::uint32_t letters_size = static_cast<std::uint32_t>(letters.size());
        std::uint32_t digits_size = static_cast<std::uint32_t>(digits.size());
        
        // Create distributions each time to ensure they're always valid
        // Ensure the maximum index is valid
        std::uint32_t letter_max = (letters_size > 0U) ? (letters_size - 1U) : 0U;
        std::uint32_t digit_max = (digits_size > 0U) ? (digits_size - 1U) : 0U;
        
        std::uniform_int_distribution<std::uint32_t> letter_dist(0, letter_max);
        std::uniform_int_distribution<std::uint32_t> digit_dist(0, digit_max);
        
        std::string name;
        while (true) {
            name.clear();
            // Add two random letters
            // Ensure indices are valid by using the distributions
            std::uint32_t letter_index1 = letter_dist(gen);
            std::uint32_t letter_index2 = letter_dist(gen);
            name += letters[static_cast<std::size_t>(letter_index1)];
            name += letters[static_cast<std::size_t>(letter_index2)];
            
            // Add three random digits
            for (std::int32_t i = 0; i < 3; i++) {
                std::uint32_t digit_index = digit_dist(gen);
                name += digits[static_cast<std::size_t>(digit_index)];
            }
            
            // Check if the name is unique
            if (used_names.find(name) == used_names.end()) {
                used_names.insert(name);
                break;
            }
        }
        return name;
    }
}

robot::robot() : robot_name() {
    generate_name();
}

const std::string& robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the old name from used_names
    if (!robot_name.empty()) {
        used_names.erase(robot_name);
    }
    generate_name();
}

void robot::generate_name() {
    robot_name = generate_random_name();
}

}  // namespace robot_name
