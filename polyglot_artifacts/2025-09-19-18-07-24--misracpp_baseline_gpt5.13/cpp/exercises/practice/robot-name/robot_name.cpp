#include "robot_name.h"

#include <mutex>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
constexpr unsigned int kMaxNames = 26u * 26u * 1000u;  // AA000 - ZZ999

std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

std::unordered_set<std::string>& used() {
    static std::unordered_set<std::string> names;
    return names;
}

std::mutex& used_mutex() {
    static std::mutex m;
    return m;
}

std::string generate_unique_name() {
    auto& gen = rng();
    std::uniform_int_distribution<int> letter_dist(0, 25);
    std::uniform_int_distribution<int> digit_dist(0, 9);

    for (;;) {
        std::string candidate;
        candidate.reserve(5);
        candidate.push_back(static_cast<char>('A' + letter_dist(gen)));
        candidate.push_back(static_cast<char>('A' + letter_dist(gen)));
        candidate.push_back(static_cast<char>('0' + digit_dist(gen)));
        candidate.push_back(static_cast<char>('0' + digit_dist(gen)));
        candidate.push_back(static_cast<char>('0' + digit_dist(gen)));

        std::lock_guard<std::mutex> lock(used_mutex());
        if (used().size() >= kMaxNames) {
            throw std::runtime_error("No more unique robot names available");
        }
        if (used().insert(candidate).second) {
            return candidate;
        }
        // collision; try again
    }
}

}  // namespace

robot::robot() = default;

std::string robot::name() const {
    if (name_.empty()) {
        name_ = generate_unique_name();
    }
    return name_;
}

void robot::reset() {
    if (!name_.empty()) {
        std::lock_guard<std::mutex> lock(used_mutex());
        used().erase(name_);
        name_.clear();
    }
}

}  // namespace robot_name
