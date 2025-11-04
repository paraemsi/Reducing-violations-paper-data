#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace {

// Thread-safe RNG
std::mt19937& rng() {
    static std::mt19937 gen{std::random_device{}()};
    return gen;
}

// Global registry of used names to ensure uniqueness across all existing robots and resets.
std::unordered_set<std::string>& used_names() {
    static std::unordered_set<std::string> s;
    return s;
}

std::mutex& names_mutex() {
    static std::mutex m;
    return m;
}

std::string generate_name() {
    auto& gen = rng();
    std::uniform_int_distribution<int> letter_dist(0, 25);
    std::uniform_int_distribution<int> digit_dist(0, 9);

    for (;;) {
        std::string name;
        name.reserve(5);
        name.push_back(static_cast<char>('A' + letter_dist(gen)));
        name.push_back(static_cast<char>('A' + letter_dist(gen)));
        name.push_back(static_cast<char>('0' + digit_dist(gen)));
        name.push_back(static_cast<char>('0' + digit_dist(gen)));
        name.push_back(static_cast<char>('0' + digit_dist(gen)));

        std::lock_guard<std::mutex> lock(names_mutex());
        if (used_names().insert(name).second) {
            return name;
        }
    }
}

}  // namespace

namespace robot_name {

robot::robot()
    : m_name(generate_name())
{
}

std::string robot::name() const {
    return m_name;
}

void robot::reset() {
    m_name = generate_name();
}

}  // namespace robot_name
