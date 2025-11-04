#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

namespace {
    std::set<std::string> active_names;
    
    std::string generate_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const char digits[] = "0123456789";
        
        std::string new_name;
        while (true) {
            new_name.clear();
            // Generate two letters by indexing into the letters array
            new_name += letters[letter_dist(gen)];
            new_name += letters[letter_dist(gen)];
            // Generate three digits by indexing into the digits array
            new_name += digits[digit_dist(gen)];
            new_name += digits[digit_dist(gen)];
            new_name += digits[digit_dist(gen)];
            
            // Check if the name is unique among active names
            if (active_names.find(new_name) == active_names.end()) {
                active_names.insert(new_name);
                break;
            }
        }
        return new_name;
    }
}

robot::robot() : name_(generate_name()) {
}

robot::~robot() {
    active_names.erase(name_);
}

std::string robot::name() const {
    return name_;
}

void robot::reset() {
    // Remove the old name from active_names
    active_names.erase(name_);
    // Generate a new unique name
    name_ = generate_name();
}

// Move constructor
robot::robot(robot&& other) noexcept {
    // First, remove the other's name from active_names and take ownership
    active_names.erase(other.name_);
    name_ = std::move(other.name_);
    // Insert the name for this instance
    active_names.insert(name_);
    // Clear other's name to prevent its destructor from removing from active_names
    other.name_.clear();
}

// Move assignment operator
robot& robot::operator=(robot&& other) noexcept {
    if (this != &other) {
        // Remove current name from active_names
        active_names.erase(name_);
        // Remove other's name from active_names and take ownership
        active_names.erase(other.name_);
        name_ = std::move(other.name_);
        // Insert the name for this instance
        active_names.insert(name_);
        // Clear other's name to prevent its destructor from removing from active_names
        other.name_.clear();
    }
    return *this;
}

}  // namespace robot_name
