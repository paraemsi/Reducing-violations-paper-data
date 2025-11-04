#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
// Helpers to generate random components
inline char random_letter(std::mt19937& eng) {
    static thread_local std::uniform_int_distribution<int> dist(0, 25);
    return static_cast<char>('A' + dist(eng));
}

inline char random_digit(std::mt19937& eng) {
    static thread_local std::uniform_int_distribution<int> dist(0, 9);
    return static_cast<char>('0' + dist(eng));
}

} // namespace

std::mt19937& robot::rng() {
    static std::mt19937 eng{std::random_device{}()};
    return eng;
}

std::unordered_set<std::string>& robot::allocated_names() {
    static std::unordered_set<std::string> names;
    return names;
}

std::mutex& robot::allocated_mutex() {
    static std::mutex m;
    return m;
}

std::string robot::generate_unique_name() {
    auto& eng = rng();
    for (;;) {
        std::string candidate;
        candidate.reserve(5);
        candidate.push_back(random_letter(eng));
        candidate.push_back(random_letter(eng));
        candidate.push_back(random_digit(eng));
        candidate.push_back(random_digit(eng));
        candidate.push_back(random_digit(eng));

        std::lock_guard<std::mutex> lk(allocated_mutex());
        auto& names = allocated_names();
        if (names.find(candidate) == names.end()) {
            names.insert(candidate);
            return candidate;
        }
        // collision: loop and try again
    }
}

robot::robot()
    : name_(generate_unique_name()) {}

robot::~robot() {
    if (!name_.empty()) {
        std::lock_guard<std::mutex> lk(allocated_mutex());
        allocated_names().erase(name_);
    }
}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    // Release the current name back to the pool
    {
        std::lock_guard<std::mutex> lk(allocated_mutex());
        if (!name_.empty()) {
            allocated_names().erase(name_);
        }
    }
    // Acquire a new unique name
    name_ = generate_unique_name();
}

}  // namespace robot_name
