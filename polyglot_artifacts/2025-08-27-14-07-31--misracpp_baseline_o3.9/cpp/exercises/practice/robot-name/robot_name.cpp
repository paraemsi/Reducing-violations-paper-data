#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <string>

namespace robot_name {

std::unordered_set<std::string> robot::used_names_{};

namespace {
    std::mt19937& rng() {
        static std::mt19937 engine{std::random_device{}()};
        return engine;
    }
}

std::string robot::generate_unique_name() {
    std::uniform_int_distribution<int> letter_dist('A', 'Z');
    std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string candidate;
    do {
        candidate.clear();
        candidate.push_back(static_cast<char>(letter_dist(rng())));
        candidate.push_back(static_cast<char>(letter_dist(rng())));
        for (int i = 0; i < 3; ++i) {
            candidate.push_back(static_cast<char>('0' + digit_dist(rng())));
        }
    } while (used_names_.find(candidate) != used_names_.end());

    used_names_.insert(candidate);
    return candidate;
}

robot::robot() : name_{generate_unique_name()} {}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    // Do not allow reuse of any previously assigned name to guarantee
    // global uniqueness across the lifetime of the program.
    name_ = generate_unique_name();
}

}  // namespace robot_name
