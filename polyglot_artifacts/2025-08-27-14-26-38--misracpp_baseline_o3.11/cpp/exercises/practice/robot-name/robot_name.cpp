#include "robot_name.h"

namespace robot_name {

std::unordered_set<std::string> Robot::used_names_{};
std::mt19937 Robot::rng_{std::random_device{}()};

Robot::Robot() = default;

const std::string& Robot::name() const {
    if (name_.empty()) {
        name_ = generate_name();
    }
    return name_;
}

void Robot::reset() {
    // Do not erase the previous name from used_names_ to guarantee global uniqueness.
    name_.clear();
}

std::string Robot::generate_name() {
    std::uniform_int_distribution<int> letter_dist('A', 'Z');
    std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string candidate;
    do {
        candidate.clear();
        candidate += static_cast<char>(letter_dist(rng_));
        candidate += static_cast<char>(letter_dist(rng_));
        for (int i = 0; i < 3; ++i) {
            candidate += static_cast<char>('0' + digit_dist(rng_));
        }
    } while (!used_names_.insert(candidate).second);

    return candidate;
}

}  // namespace robot_name
