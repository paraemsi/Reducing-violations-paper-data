#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
// Global registry of names currently in use.
std::unordered_set<std::string> used_names;
// Mutex to protect access to the registry.
std::mutex used_names_mutex;

// Thread-local RNG seeded with entropy.
std::mt19937& rng_engine() {
    thread_local std::mt19937 rng([] {
        std::random_device rd;
        std::seed_seq seed{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
        return std::mt19937(seed);
    }());
    return rng;
}

char random_upper_letter(std::mt19937& rng) {
    static std::uniform_int_distribution<int> dist(0, 25);
    return static_cast<char>('A' + dist(rng));
}

char random_digit(std::mt19937& rng) {
    static std::uniform_int_distribution<int> dist(0, 9);
    return static_cast<char>('0' + dist(rng));
}

}  // namespace

const std::string& robot::name() const {
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void robot::reset() {
    std::lock_guard<std::mutex> guard(m_mutex);
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        used_names.erase(m_name);
        m_name.clear();
    }
}

std::string robot::generate_candidate_name() {
    auto& rng = rng_engine();
    std::string s;
    s.reserve(5);
    s.push_back(random_upper_letter(rng));
    s.push_back(random_upper_letter(rng));
    s.push_back(random_digit(rng));
    s.push_back(random_digit(rng));
    s.push_back(random_digit(rng));
    return s;
}

std::string robot::generate_unique_name() {
    for (;;) {
        std::string candidate = generate_candidate_name();
        std::lock_guard<std::mutex> lock(used_names_mutex);
        auto [it, inserted] = used_names.insert(candidate);
        if (inserted) {
            return candidate;
        }
        // Otherwise, loop and try another candidate.
    }
}

}  // namespace robot_name
