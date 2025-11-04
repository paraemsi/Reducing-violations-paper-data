#include "robot_name.h"
#include <random>
#include <string>
#include <set>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

std::set<std::string>& robot::used_names() {
    static std::set<std::string> instance;
    return instance;
}

namespace {
    std::string generate_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        while (true) {
            // Generate two random letters
            char first_char = 'A' + static_cast<char>(letter_dist(gen));
            char second_char = 'A' + static_cast<char>(letter_dist(gen));
            
            // Generate three random digits as characters
            char first_digit = '0' + static_cast<char>(digit_dist(gen));
            char second_digit = '0' + static_cast<char>(digit_dist(gen));
            char third_digit = '0' + static_cast<char>(digit_dist(gen));
            
            // Construct the name
            std::string name;
            name += first_char;
            name += second_char;
            name += first_digit;
            name += second_digit;
            name += third_digit;
            
            // Check if the name is unique using the shared used_names
            auto& names = robot::used_names();
            if (names.find(name) == names.end()) {
                names.insert(name);
                return name;
            }
            // If not unique, try again
        }
    }
}

robot::robot() : robot_name(generate_name()) {
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    // Remove the current name from used_names
    auto& names = robot::used_names();
    names.erase(robot_name);
    // Generate a new unique name
    robot_name = generate_name();
}

}  // namespace robot_name
