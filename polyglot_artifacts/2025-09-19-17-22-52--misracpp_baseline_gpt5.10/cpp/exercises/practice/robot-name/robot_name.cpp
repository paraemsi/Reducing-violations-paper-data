#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
    std::mt19937& prng() {
        static std::mt19937 gen(std::random_device{}());
        return gen;
    }

    std::uniform_int_distribution<int>& letter_dist() {
        static std::uniform_int_distribution<int> dist('A', 'Z');
        return dist;
    }

    std::uniform_int_distribution<int>& digit_dist() {
        static std::uniform_int_distribution<int> dist('0', '9');
        return dist;
    }

    std::mutex& names_mutex() {
        static std::mutex m;
        return m;
    }

    std::unordered_set<std::string>& used_names() {
        static std::unordered_set<std::string> s;
        return s;
    }

    std::string make_name() {
        std::string n;
        n.reserve(5);
        n.push_back(static_cast<char>(letter_dist()(prng())));
        n.push_back(static_cast<char>(letter_dist()(prng())));
        n.push_back(static_cast<char>(digit_dist()(prng())));
        n.push_back(static_cast<char>(digit_dist()(prng())));
        n.push_back(static_cast<char>(digit_dist()(prng())));
        return n;
    }
}  // namespace

robot::robot() : name_(generate_unique_name()) {}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    std::lock_guard<std::mutex> lock(names_mutex());

    // Free the current name
    used_names().erase(name_);

    // Generate a new unique name that is not equal to the old one
    std::string candidate;
    do {
        candidate = make_name();
    } while (candidate == name_ || used_names().find(candidate) != used_names().end());

    name_ = std::move(candidate);
    used_names().insert(name_);
}

std::string robot::generate_unique_name() {
    std::lock_guard<std::mutex> lock(names_mutex());
    std::string candidate;
    do {
        candidate = make_name();
    } while (used_names().find(candidate) != used_names().end());
    used_names().insert(candidate);
    return candidate;
}

}  // namespace robot_name
