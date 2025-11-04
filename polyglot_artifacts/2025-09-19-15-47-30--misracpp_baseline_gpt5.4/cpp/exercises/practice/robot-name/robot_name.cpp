#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
std::unordered_set<std::string> used_names;
std::mutex used_mutex;

std::string make_candidate(std::mt19937& rng) {
    static std::uniform_int_distribution<int> letter_dist(0, 25);
    static std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string s;
    s.reserve(5);
    s.push_back(static_cast<char>('A' + letter_dist(rng)));
    s.push_back(static_cast<char>('A' + letter_dist(rng)));
    s.push_back(static_cast<char>('0' + digit_dist(rng)));
    s.push_back(static_cast<char>('0' + digit_dist(rng)));
    s.push_back(static_cast<char>('0' + digit_dist(rng)));
    return s;
}

std::string generate_unique_name() {
    static std::random_device rd;
    static std::mt19937 rng(rd());

    std::unique_lock<std::mutex> lock(used_mutex);
    std::string candidate;
    do {
        candidate = make_candidate(rng);
    } while (used_names.find(candidate) != used_names.end());

    used_names.insert(candidate);
    return candidate;
}
}  // namespace

robot::robot() : name_(generate_unique_name()) {}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    name_ = generate_unique_name();
}

}  // namespace robot_name
