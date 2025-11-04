#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <mutex>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
    std::mutex used_names_mutex;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> letter_dist('A', 'Z');
    std::uniform_int_distribution<> digit_dist(0, 9);

    std::string generate_random_name() {
        std::string name;
        name += static_cast<char>(letter_dist(gen));
        name += static_cast<char>(letter_dist(gen));
        for (int i = 0; i < 3; ++i) {
            name += static_cast<char>('0' + digit_dist(gen));
        }
        return name;
    }
}

robot::robot() : robot_name_("") {}

std::string robot::name() const {
    if (robot_name_.empty()) {
        // const_cast is required to modify mutable member in const method
        const_cast<robot*>(this)->generate_name();
    }
    return robot_name_;
}

void robot::reset() {
    if (!robot_name_.empty()) {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        used_names.erase(robot_name_);
        robot_name_.clear();
    }
}

void robot::generate_name() {
    std::string new_name;
    std::lock_guard<std::mutex> lock(used_names_mutex);
    do {
        new_name = generate_random_name();
    } while (used_names.find(new_name) != used_names.end());
    robot_name_ = new_name;
    used_names.insert(new_name);
}

}  // namespace robot_name
