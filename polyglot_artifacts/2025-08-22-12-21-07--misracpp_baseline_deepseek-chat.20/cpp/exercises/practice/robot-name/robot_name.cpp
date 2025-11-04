#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <stdexcept>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
    
    std::string generate_random_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> letters_dist(0, 25);
        static std::uniform_int_distribution<> digits_dist(0, 9);
        
        std::string name;
        do {
            name.clear();
            // Add two random uppercase letters
            name += 'A' + letters_dist(gen);
            name += 'A' + letters_dist(gen);
            // Add three random digits as characters
            name += '0' + digits_dist(gen);
            name += '0' + digits_dist(gen);
            name += '0' + digits_dist(gen);
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
