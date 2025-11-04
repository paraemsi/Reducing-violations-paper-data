#include "robot_name.h"

#include <mutex>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace {

// Pool of names currently in use across all robots.
std::unordered_set<std::string>& used_names() {
    static std::unordered_set<std::string> s;
    return s;
}

std::mutex& used_names_mutex() {
    static std::mutex m;
    return m;
}

constexpr std::size_t max_names = 26u * 26u * 1000u;

std::string generate_candidate_name() {
    thread_local std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<int> letter_dist(0, 25);
    std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string s;
    s.reserve(5);
    s.push_back(static_cast<char>('A' + letter_dist(rng)));
    s.push_back(static_cast<char>('A' + letter_dist(rng)));
    s.push_back(static_cast<char>('0' + digit_dist(rng)));
    s.push_back(static_cast<char>('0' + digit_dist(rng)));
    s.push_back(static_cast<char>('0' + digit_dist(rng)));
    return s;
}

std::string acquire_unique_name_excluding(const std::string& avoid) {
    for (;;) {
        std::string candidate = generate_candidate_name();
        std::lock_guard<std::mutex> lock(used_names_mutex());
        if (used_names().size() >= max_names) {
            throw std::runtime_error("No more unique robot names available");
        }
        if (candidate == avoid) {
            continue;
        }
        if (used_names().find(candidate) == used_names().end()) {
            used_names().insert(candidate);
            return candidate;
        }
    }
}

void release_name(const std::string& name) {
    if (name.empty()) return;
    std::lock_guard<std::mutex> lock(used_names_mutex());
    used_names().erase(name);
}

}  // unnamed namespace

namespace robot_name {

robot::robot() = default;

std::string robot::name() const {
    if (name_.empty()) {
        name_ = acquire_unique_name_excluding(last_name_);
        last_name_ = name_;
    }
    return name_;
}

void robot::reset() {
    // Remove current name from the global set and clear local state.
    if (!name_.empty()) {
        release_name(name_);
        name_.clear();
        // Keep last_name_ so the next generated name differs from the previous one.
    }
}

}  // namespace robot_name
