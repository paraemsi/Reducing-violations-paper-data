#include "robot_name.h"
#include <random>
#include <set>
#include <stdexcept>
#include <string>

namespace robot_name {
namespace {

// Keep track of used names in an unnamed namespace to ensure internal linkage
std::set<std::string> used_names;

}  // namespace

robot::robot() {
    robot_name = generate_name();
}

std::string robot::name() const {
    return robot_name;
}

void robot::reset() {
    used_names.erase(robot_name);
    robot_name = generate_name();
}

std::string robot::generate_name() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> letters_dist(0, 25);
    std::uniform_int_distribution<> digits_dist(0, 9);
    
    std::string new_name;
    while (true) {
        new_name.clear();
        // Generate two random uppercase letters
        new_name += 'A' + letters_dist(gen);
        new_name += 'A' + letters_dist(gen);
        
        // Generate three random digits
        for (int i = 0; i < 3; i++) {
            new_name += '0' + digits_dist(gen);
        }
        
        // Check if the name is unique
        if (used_names.find(new_name) == used_names.end()) {
            used_names.insert(new_name);
            break;
        }
    }
    return new_name;
}

}  // namespace robot_name
