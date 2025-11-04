#include "robot_name.h"

#include <chrono>
#include <mutex>
#include <random>
#include <unordered_set>
#include <cstdint>
#include <utility>

namespace {

// PRNG seeded with multiple entropy sources for unpredictability.
inline std::mt19937& rng() {
    static std::mt19937 gen([] {
        std::random_device rd;
        std::seed_seq seq{
            rd(), rd(), rd(), rd(),
            static_cast<std::uint32_t>(
                std::chrono::high_resolution_clock::now().time_since_epoch().count())
        };
        return std::mt19937(seq);
    }());
    return gen;
}

// Global registry to ensure uniqueness across all existing robots.
std::unordered_set<std::string> used_names;
std::mutex used_names_mutex;

}  // namespace

namespace robot_name {

robot::robot() {
    name_ = generate_unique_name();
}

robot::~robot() = default;

robot::robot(const robot& other) {
    // Do not duplicate the other's name; ensure uniqueness by generating a fresh one.
    name_ = generate_unique_name(other.name_);
    last_name_.clear();
}

robot& robot::operator=(const robot& other) {
    if (this != &other) {
        // Do not release names; keep global uniqueness across the program's lifetime.
        last_name_.clear();
        // Assign a fresh unique name (avoid immediately reusing the source's current name).
        name_ = generate_unique_name(other.name_);
    }
    return *this;
}

robot::robot(robot&& other) noexcept
    : name_(std::move(other.name_)),
      last_name_(std::move(other.last_name_)) {
    // Ensure moved-from object does not release a name it no longer owns.
    other.name_.clear();
    other.last_name_.clear();
}

robot& robot::operator=(robot&& other) noexcept {
    if (this != &other) {
        // Do not release names; keep global uniqueness across the program's lifetime.
        last_name_.clear();

        name_ = std::move(other.name_);
        last_name_ = std::move(other.last_name_);

        // Prevent the source from releasing the name on destruction.
        other.name_.clear();
        other.last_name_.clear();
    }
    return *this;
}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    if (!name_.empty()) {
        // Remember last name to avoid immediately reusing it for this robot.
        last_name_ = name_;
        name_.clear();
    }
    // Generate a fresh unique name distinct from the last one and any previously used names.
    name_ = generate_unique_name(last_name_);
}

std::string robot::generate_unique_name(const std::string& avoid) {
    std::uniform_int_distribution<int> letter_dist(0, 25);
    std::uniform_int_distribution<int> digit_dist(0, 9);

    for (;;) {
        std::string candidate;
        candidate.reserve(5);

        auto& g = rng();
        candidate.push_back(static_cast<char>('A' + letter_dist(g)));
        candidate.push_back(static_cast<char>('A' + letter_dist(g)));
        candidate.push_back(static_cast<char>('0' + digit_dist(g)));
        candidate.push_back(static_cast<char>('0' + digit_dist(g)));
        candidate.push_back(static_cast<char>('0' + digit_dist(g)));

        if (!avoid.empty() && candidate == avoid) {
            continue; // ensure reset yields a different name for this robot
        }

        std::lock_guard<std::mutex> lock(used_names_mutex);
        if (used_names.insert(candidate).second) {
            return candidate; // unique
        }
        // else collision; try again
    }
}

void robot::release_name(const std::string& n) {
    if (n.empty()) return;
    std::lock_guard<std::mutex> lock(used_names_mutex);
    used_names.erase(n);
}

}  // namespace robot_name
