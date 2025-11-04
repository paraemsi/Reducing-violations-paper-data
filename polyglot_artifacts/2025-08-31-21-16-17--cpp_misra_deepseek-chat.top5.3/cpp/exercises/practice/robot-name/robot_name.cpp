#include "robot_name.h"
#include <random>
#include <string>
#include <set>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        // Define valid characters
        constexpr char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        constexpr char digits[] = "0123456789";
        
        std::string name;
        while (true) {
            name.clear();
            // Generate two letters
            name += letters[letter_dist(gen)];
            name += letters[letter_dist(gen)];
            // Generate three digits
            name += digits[digit_dist(gen)];
            name += digits[digit_dist(gen)];
            name += digits[digit_dist(gen)];
            
            // Try to insert the name, if successful, break out of the loop
            auto result = used_names.insert(name);
            if (result.second) {
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
    used_names.erase(robot_name);
    generate_name();
}

void robot::generate_name() {
    robot_name = generate_random_name();
}

}  // namespace robot_name
