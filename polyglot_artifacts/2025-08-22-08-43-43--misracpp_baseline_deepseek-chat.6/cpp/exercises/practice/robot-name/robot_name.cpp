#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <stdexcept>
#include <cstdio>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> letters_dist(0, 25);
        static std::uniform_int_distribution<> numbers_dist(0, 999);
        
        std::string name;
        do {
            name.clear();
            // Add two random uppercase letters
            name += 'A' + letters_dist(gen);
            name += 'A' + letters_dist(gen);
            // Add three-digit number with leading zeros
            int number = numbers_dist(gen);
            char number_str[4];
            snprintf(number_str, sizeof(number_str), "%03d", number);
            name += number_str;
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
    // Remove the old name from used_names
    used_names.erase(robot_name);
    generate_name();
}

void robot::generate_name() {
    robot_name = generate_random_name();
}

}  // namespace robot_name
