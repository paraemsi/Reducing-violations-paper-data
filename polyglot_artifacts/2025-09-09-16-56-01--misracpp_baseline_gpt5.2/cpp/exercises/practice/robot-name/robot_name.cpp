#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {
namespace {

// Lazily initialized RNG
std::mt19937& rng() {
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

std::string random_name() {
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::uniform_int_distribution<int> letter_dist(0, 25);
    std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string n;
    n.reserve(5);
    n.push_back(letters[letter_dist(rng())]);
    n.push_back(letters[letter_dist(rng())]);
    n.push_back(static_cast<char>('0' + digit_dist(rng())));
    n.push_back(static_cast<char>('0' + digit_dist(rng())));
    n.push_back(static_cast<char>('0' + digit_dist(rng())));
    return n;
}

std::unordered_set<std::string>& used_names() {
    static std::unordered_set<std::string> s;
    return s;
}

std::mutex& used_mutex() {
    static std::mutex m;
    return m;
}

}  // namespace

robot::robot() : name_() {}

std::string robot::name() const {
    if (name_.empty()) {
        name_ = generate_unique_name();
    }
    return name_;
}

void robot::reset() {
    // Wipe current name; next call to name() will generate a new unique one.
    name_.clear();
}

std::string robot::generate_unique_name() {
    for (;;) {
        std::string candidate = random_name();
        std::lock_guard<std::mutex> lock(used_mutex());
        auto [it, inserted] = used_names().insert(candidate);
        if (inserted) {
            return candidate;
        }
    }
}

}  // namespace robot_name
