#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <utility>
#include <unordered_set>

namespace robot_name {

namespace {

// Global registry of allocated names and a mutex for thread-safety
std::unordered_set<std::string> used_names;
std::mutex used_names_mutex;

// PRNG seeded once with entropy
std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

std::string generate_name() {
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::uniform_int_distribution<int> letter_dist(0, 25);
    std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string candidate;
    candidate.reserve(5);

    for (;;) {
        candidate.clear();
        candidate.push_back(letters[letter_dist(rng())]);
        candidate.push_back(letters[letter_dist(rng())]);
        candidate.push_back(static_cast<char>('0' + digit_dist(rng())));
        candidate.push_back(static_cast<char>('0' + digit_dist(rng())));
        candidate.push_back(static_cast<char>('0' + digit_dist(rng())));

        std::lock_guard<std::mutex> lock(used_names_mutex);
        if (used_names.insert(candidate).second) {
            return candidate;
        }
        // Collision: try again
    }
}

}  // namespace

robot::robot()
    : name_(generate_name()) {}

robot::~robot() {
    if (!name_.empty()) {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        used_names.erase(name_);
    }
}

robot::robot(robot&& other) noexcept {
    std::lock_guard<std::mutex> lock(used_names_mutex);
    name_ = std::move(other.name_);
    other.name_.clear();
}

robot& robot::operator=(robot&& other) noexcept {
    if (this != &other) {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        if (!name_.empty()) {
            used_names.erase(name_);
        }
        name_ = std::move(other.name_);
        other.name_.clear();
    }
    return *this;
}

std::string robot::name() const {
    return name_;
}

void robot::reset() {
    {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        if (!name_.empty()) {
            used_names.erase(name_);
        }
    }
    name_ = generate_name();
}

}  // namespace robot_name
