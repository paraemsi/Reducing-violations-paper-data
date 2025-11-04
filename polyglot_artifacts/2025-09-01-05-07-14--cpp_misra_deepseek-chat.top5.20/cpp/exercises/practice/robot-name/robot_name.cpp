#include "robot_name.h"
#include <random>
#include <set>
#include <string>
#include <cstdint>
#include <stdexcept>

namespace robot_name {

namespace {
    std::set<std::string> used_names;
    
    std::string generate_name() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 9);
        
        std::string new_name;
        // Keep generating names until we find one that's not in use
        while (true) {
            new_name.clear();
            // Generate two letters
            new_name += static_cast<char>('A' + letter_dist(gen));
            new_name += static_cast<char>('A' + letter_dist(gen));
            // Generate three digits
            for (std::int32_t j = 0; j < 3; j++) {
                new_name += static_cast<char>('0' + digit_dist(gen));
            }
            // Check if the name is unique
            if ((used_names.find(new_name)) == used_names.end()) {
                used_names.insert(new_name);
                return new_name;
            }
        }
    }
}

robot::robot() : name_() {
}

robot::~robot() {
    // Remove the name from used_names when the robot is destroyed
    if (!(name_.empty())) { 
        used_names.erase(name_); 
    }
}

std::string robot::name() const {
    if (name_.empty()) { 
        name_ = generate_name(); 
    }
    return name_;
}

void robot::reset() {
    // Always remove the current name from used_names if it's not empty
    // Make sure name_ is valid before trying to erase it
    if (!(name_.empty())) { 
        // Ensure the name exists in used_names before erasing
        auto it = used_names.find(name_);
        if (it != used_names.end()) {
            used_names.erase(it);
        }
    }
    // Generate a new name and update name_
    name_ = generate_name();
}

}  // namespace robot_name
