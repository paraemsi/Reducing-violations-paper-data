#include "robot_name.h"

#include <random>

namespace {
char random_uppercase_letter(std::mt19937& eng) {
    static std::uniform_int_distribution<int> dist(0, 25);
    return static_cast<char>('A' + dist(eng));
}

char random_digit(std::mt19937& eng) {
    static std::uniform_int_distribution<int> dist(0, 9);
    return static_cast<char>('0' + dist(eng));
}
} // unnamed namespace

namespace robot_name {

std::unordered_set<std::string> robot::used_names_{};

static std::mt19937& rng() {
    static std::mt19937 eng(std::random_device{}());
    return eng;
}

std::string robot::generate_unique_name() {
    std::string candidate;
    auto& eng = rng();
    do {
        candidate.clear();
        candidate.push_back(random_uppercase_letter(eng));
        candidate.push_back(random_uppercase_letter(eng));
        candidate.push_back(random_digit(eng));
        candidate.push_back(random_digit(eng));
        candidate.push_back(random_digit(eng));
    } while (used_names_.find(candidate) != used_names_.end());

    used_names_.insert(candidate);
    return candidate;
}

robot::robot() = default;

const std::string& robot::name() const {
    if (name_.empty()) {
        name_ = generate_unique_name();
    }
    return name_;
}

void robot::reset() {
    // Keep the previous name reserved to guarantee global uniqueness.
    name_.clear();
}

}  // namespace robot_name
