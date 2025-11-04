#include "robot_name.h"

#include <random>
#include <unordered_set>

namespace robot_name {

std::unordered_set<std::string> robot::used_names_{};

std::string robot::generate_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> letter_dist('A', 'Z');
    static std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string candidate;
    candidate.reserve(5);
    candidate.push_back(static_cast<char>(letter_dist(gen)));
    candidate.push_back(static_cast<char>(letter_dist(gen)));
    for (int i = 0; i < 3; ++i) {
        candidate.push_back(static_cast<char>('0' + digit_dist(gen)));
    }
    return candidate;
}

bool robot::is_name_unique(const std::string& candidate) {
    return used_names_.find(candidate) == used_names_.end();
}

robot::robot() {
    do {
        name_ = generate_name();
    } while (!is_name_unique(name_));
    used_names_.insert(name_);
}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    do {
        name_ = generate_name();
    } while (!is_name_unique(name_));
    used_names_.insert(name_);
}

}  // namespace robot_name
