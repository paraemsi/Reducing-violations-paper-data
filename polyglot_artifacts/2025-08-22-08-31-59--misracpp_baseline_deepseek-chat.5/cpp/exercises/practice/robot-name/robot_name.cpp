#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <stdexcept>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
    
    // Helper function to generate a random number in a range
    int random_int(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
}

std::string robot::generate_name() {
    std::string new_name;
    while (true) {
        // Generate two random uppercase letters
        new_name += 'A' + random_int(0, 25);
        new_name += 'A' + random_int(0, 25);
        // Generate three random digits
        new_name += '0' + random_int(0, 9);
        new_name += '0' + random_int(0, 9);
        new_name += '0' + random_int(0, 9);
        
        // Check if the name is unique
        if (used_names.find(new_name) == used_names.end()) {
            used_names.insert(new_name);
            break;
        }
        // If not unique, reset new_name and try again
        new_name.clear();
    }
    return new_name;
}

robot::robot() : name_(generate_name()) {
}

std::string robot::name() const {
    return name_;
}

void robot::reset() {
    // Remove the old name from used_names
    used_names.erase(name_);
    // Generate a new unique name
    name_ = generate_name();
}

}  // namespace robot_name
