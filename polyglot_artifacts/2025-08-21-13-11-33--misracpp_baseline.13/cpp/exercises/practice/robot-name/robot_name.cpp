#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <string>
#include <mutex>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
    std::mutex used_names_mutex;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> letter_dist('A', 'Z');
    std::uniform_int_distribution<> digit_dist(0, 9);

    std::string random_name() {
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

std::string robot::name() {
    if (robot_name_.empty()) {
        generate_name();
    }
    return robot_name_;
}

void robot::reset() {
    if (!robot_name_.empty()) {
        unregister_name(robot_name_);
        robot_name_.clear();
    }
}

void robot::generate_name() {
    std::string new_name;
    do {
        new_name = random_name();
    } while (!is_name_unique(new_name));
    robot_name_ = new_name;
    register_name(robot_name_);
}

bool robot::is_name_unique(const std::string& name) {
    std::lock_guard<std::mutex> lock(used_names_mutex);
    return used_names.find(name) == used_names.end();
}

void robot::register_name(const std::string& name) {
    std::lock_guard<std::mutex> lock(used_names_mutex);
    used_names.insert(name);
}

void robot::unregister_name(const std::string& name) {
    std::lock_guard<std::mutex> lock(used_names_mutex);
    used_names.erase(name);
}

}  // namespace robot_name
