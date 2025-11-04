#include "robot_name.h"

#include <chrono>
#include <random>
#include <string>
#include <unordered_set>
#include <utility>   // std::move

namespace robot_name {

// static storage for already-allocated names
std::unordered_set<std::string> robot::allocated_;

// ---- internal helpers -----------------------------------------------------

// single random engine reused for all name generations
static std::mt19937& rng() {
    static std::mt19937 gen(static_cast<unsigned>(
        std::chrono::system_clock::now().time_since_epoch().count()));
    return gen;
}

static std::uniform_int_distribution<int>& letter_dist() {
    static std::uniform_int_distribution<int> dist('A', 'Z');
    return dist;
}

static std::uniform_int_distribution<int>& digit_dist() {
    static std::uniform_int_distribution<int> dist(0, 9);
    return dist;
}

// create a name of form [A-Z][A-Z][0-9][0-9][0-9] that is not already in use
std::string robot::generate_unique_name() {
    std::string candidate;
    do {
        candidate.clear();
        candidate += static_cast<char>(letter_dist()(rng()));
        candidate += static_cast<char>(letter_dist()(rng()));
        for (int i = 0; i < 3; ++i) {
            candidate += static_cast<char>('0' + digit_dist()(rng()));
        }
    } while (allocated_.find(candidate) != allocated_.end());

    allocated_.insert(candidate);
    return candidate;
}

// ---- public interface ------------------------------------------------------

robot::robot() : name_{generate_unique_name()} {}

robot::~robot() {
    if (!name_.empty()) {
        allocated_.erase(name_);
    }
}

robot::robot(robot&& other) noexcept : name_{std::move(other.name_)} {
    other.name_.clear(); // moved-from robot relinquishes its name
}

robot& robot::operator=(robot&& other) noexcept {
    if (this != &other) {
        // release any name currently held
        if (!name_.empty()) {
            allocated_.erase(name_);
        }
        // transfer ownership of the new name
        name_ = std::move(other.name_);
        other.name_.clear();
    }
    return *this;
}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    if (!name_.empty()) {
        allocated_.erase(name_);
    }
    name_ = generate_unique_name();
}

}  // namespace robot_name
