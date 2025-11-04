#include "robot_name.h"

namespace robot_name {

std::unordered_set<std::string> Robot::used_names_;

std::mt19937& Robot::rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

std::string Robot::generate_unique_name() {
    // Generate indices for letters (0-25) and digits (0-9) to avoid
    // signed/unsigned char → int conversion warnings that can be escalated
    // to errors by -Werror.
    static std::uniform_int_distribution<int> letter_dist(0, 25);
    static std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string candidate;
    do {
        candidate.clear();
        candidate.push_back(static_cast<char>('A' + letter_dist(rng())));
        candidate.push_back(static_cast<char>('A' + letter_dist(rng())));
        for (int i = 0; i < 3; ++i) {
            candidate.push_back(static_cast<char>('0' + digit_dist(rng())));
        }
    } while (used_names_.find(candidate) != used_names_.end());

    return candidate;
}

Robot::Robot() = default;

Robot::~Robot() {
    reset();    // return the name to the pool when the robot is destroyed
}

const std::string& Robot::name() const {
    if (name_.empty()) {
        name_ = generate_unique_name();
        used_names_.insert(name_);
    }
    return name_;
}

void Robot::reset() {
    if (!name_.empty()) {
        used_names_.erase(name_);
        name_.clear();
    }
}

}  // namespace robot_name
