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

robot::robot() : name_("") {}

std::string robot::name() {
    if (name_.empty()) {
        generate_name();
    }
    return name_;
}

void robot::reset() {
    if (!name_.empty()) {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        used_names.erase(name_);
        name_.clear();
    }
}

void robot::generate_name() {
    std::string candidate;
    while (true) {
        candidate = random_name();
        std::lock_guard<std::mutex> lock(used_names_mutex);
        if (used_names.find(candidate) == used_names.end()) {
            used_names.insert(candidate);
            name_ = candidate;
            break;
        }
    }
}

}  // namespace robot_name
