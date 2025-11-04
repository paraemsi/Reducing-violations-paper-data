#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <mutex>
#include <utility>

namespace robot_name {

namespace {
    // Global registry of assigned names and PRNG, protected by a mutex.
    std::unordered_set<std::string> g_used_names;

    std::mt19937& rng() {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }

    std::mutex& registry_mutex() {
        static std::mutex m;
        return m;
    }
}

robot::robot() = default;

robot::~robot() {
    if (!name_.empty()) {
        release_name(name_);
    }
}

robot::robot(robot&& other) noexcept {
    name_ = std::move(other.name_);
    other.name_.clear();
}

robot& robot::operator=(robot&& other) noexcept {
    if (this != &other) {
        if (!name_.empty()) {
            release_name(name_);
        }
        name_ = std::move(other.name_);
        other.name_.clear();
    }
    return *this;
}

const std::string& robot::name() const {
    if (name_.empty()) {
        name_ = generate_unique_name();
    }
    return name_;
}

void robot::reset() {
    if (!name_.empty()) {
        release_name(name_);
        name_.clear();
    }
}

std::string robot::generate_unique_name() {
    static std::uniform_int_distribution<int> letter_dist(0, 25);
    static std::uniform_int_distribution<int> digit_dist(0, 9);

    std::lock_guard<std::mutex> lock(registry_mutex());
    std::string candidate;
    do {
        candidate.clear();
        candidate.push_back(static_cast<char>('A' + letter_dist(rng())));
        candidate.push_back(static_cast<char>('A' + letter_dist(rng())));
        candidate.push_back(static_cast<char>('0' + digit_dist(rng())));
        candidate.push_back(static_cast<char>('0' + digit_dist(rng())));
        candidate.push_back(static_cast<char>('0' + digit_dist(rng())));
    } while (g_used_names.find(candidate) != g_used_names.end());

    g_used_names.insert(candidate);
    return candidate;
}

void robot::release_name(const std::string& name) {
    std::lock_guard<std::mutex> lock(registry_mutex());
    g_used_names.erase(name);
}

}  // namespace robot_name
