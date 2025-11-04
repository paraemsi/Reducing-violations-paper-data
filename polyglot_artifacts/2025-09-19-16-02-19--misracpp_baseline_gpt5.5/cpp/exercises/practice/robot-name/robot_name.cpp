#include "robot_name.h"
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {

// Thread-safe PRNG seeded with std::random_device
std::mt19937& rng() {
    static thread_local std::mt19937 gen{std::random_device{}()};
    return gen;
}

std::string random_name() {
    static std::uniform_int_distribution<int> letter_dist(0, 25);
    static std::uniform_int_distribution<int> digit_dist(0, 9);
    auto& gen = rng();

    std::string n;
    n.reserve(5);
    n.push_back(static_cast<char>('A' + letter_dist(gen)));
    n.push_back(static_cast<char>('A' + letter_dist(gen)));
    n.push_back(static_cast<char>('0' + digit_dist(gen)));
    n.push_back(static_cast<char>('0' + digit_dist(gen)));
    n.push_back(static_cast<char>('0' + digit_dist(gen)));
    return n;
}

std::unordered_set<std::string>& used_names() {
    static std::unordered_set<std::string> used;
    return used;
}

std::mutex& names_mutex() {
    static std::mutex m;
    return m;
}

std::string acquire_unique() {
    for (;;) {
        std::string candidate = random_name();
        std::lock_guard<std::mutex> lock(names_mutex());
        auto [it, inserted] = used_names().insert(candidate);
        if (inserted) {
            return candidate;
        }
    }
}

void release_name(const std::string& name) {
    std::lock_guard<std::mutex> lock(names_mutex());
    used_names().erase(name);
}

} // namespace

robot::robot()
    : name_(acquire_unique()) {}

std::string robot::name() const {
    return name_;
}

void robot::reset() {
    name_ = acquire_unique();
}

}  // namespace robot_name
