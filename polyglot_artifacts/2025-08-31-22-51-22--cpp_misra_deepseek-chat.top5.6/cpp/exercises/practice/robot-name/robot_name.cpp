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
        static std::mt19937 gen(std::random_device{}());
        static std::uniform_int_distribution<std::int32_t> letter_dist(0, 25);
        static std::uniform_int_distribution<std::int32_t> digit_dist(0, 999);
        
        // Check if all names are used
        if (used_names.size() >= 676000) {
            throw std::runtime_error("All possible robot names are used");
        }
        
        std::string new_name;
        while (true) {
            // Generate two letters
            new_name.clear();
            static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            for (std::int32_t i = 0; i < 2; i++) {
                std::int32_t index = letter_dist(gen);
                new_name += letters[index];
            }
            
            // Generate three digits and always format to three digits
            std::int32_t number = digit_dist(gen);
            // Format the number to always have three digits
            std::string num_str = std::to_string(number);
            if (number < 10) {
                new_name += "00" + num_str;
            } else if (number < 100) {
                new_name += "0" + num_str;
            } else {
                new_name += num_str;
            }
            
            // Check if the name is unique
            if (used_names.find(new_name) == used_names.end()) {
                used_names.insert(new_name);
                break;
            }
            // If not unique, continue the loop to generate another name
        }
        return new_name;
    }
}

robot::robot() : name_(generate_name()) {
}

std::string robot::name() const {
    return name_;
}

void robot::reset() {
    // Remove the current name from used_names
    if (!name_.empty()) {
        used_names.erase(name_);
    }
    name_ = generate_name();
}

}  // namespace robot_name
