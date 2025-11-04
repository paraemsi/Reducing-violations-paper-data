#include "robot_name.h"
#include <random>
#include <algorithm>
#include <mutex>

namespace robot_name {

// Static member to track all used names across all robot instances
std::unordered_set<std::string> robot::used_names_;

// Static mutex for thread safety when accessing used_names_
static std::mutex names_mutex;

robot::robot() {
    // Name is not generated until first access
}

robot::~robot() {
    // Release the name when robot is destroyed
    if (!name_.empty()) {
        std::lock_guard<std::mutex> lock(names_mutex);
        used_names_.erase(name_);
    }
}

std::string robot::name() const {
    // Lazy initialization - generate name on first access
    if (name_.empty()) {
        name_ = generate_unique_name();
    }
    return name_;
}

void robot::reset() {
    // Release the old name
    if (!name_.empty()) {
        std::lock_guard<std::mutex> lock(names_mutex);
        used_names_.erase(name_);
        name_.clear();
    }
    // Note: new name will be generated on next call to name()
}

std::string robot::generate_unique_name() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> letter_dist(0, 25);
    static std::uniform_int_distribution<> digit_dist(0, 9);
    
    std::string new_name;
    
    // Keep generating until we find a unique name
    std::lock_guard<std::mutex> lock(names_mutex);
    do {
        new_name.clear();
        
        // Generate two uppercase letters
        for (int i = 0; i < 2; ++i) {
            new_name += static_cast<char>('A' + letter_dist(gen));
        }
        
        // Generate three digits
        for (int i = 0; i < 3; ++i) {
            new_name += static_cast<char>('0' + digit_dist(gen));
        }
    } while (used_names_.find(new_name) != used_names_.end());
    
    // Mark this name as used
    used_names_.insert(new_name);
    
    return new_name;
}

}  // namespace robot_name
