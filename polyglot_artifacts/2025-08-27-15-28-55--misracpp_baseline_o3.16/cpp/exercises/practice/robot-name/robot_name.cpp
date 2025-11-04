#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <mutex>

namespace {

std::unordered_set<std::string> used_names;
std::mutex used_names_mutex;

// Random engine – initialized once.
std::mt19937& rng() {
    static std::mt19937 eng{std::random_device{}()};
    return eng;
}

// Produce a random uppercase letter.
char random_letter() {
    std::uniform_int_distribution<int> dist('A', 'Z');
    return static_cast<char>(dist(rng()));
}

// Produce a random digit.
char random_digit() {
    std::uniform_int_distribution<int> dist('0', '9');
    return static_cast<char>(dist(rng()));
}

} // namespace

namespace robot_name {

std::string Robot::generate_unique_name() {
    std::lock_guard<std::mutex> lock(used_names_mutex);

    std::string candidate;
    do {
        candidate.clear();
        candidate.push_back(random_letter());
        candidate.push_back(random_letter());
        candidate.push_back(random_digit());
        candidate.push_back(random_digit());
        candidate.push_back(random_digit());
    } while (used_names.find(candidate) != used_names.end());

    used_names.insert(candidate);
    return candidate;
}

const std::string& Robot::name() const {
    if (name_.empty()) {
        name_ = generate_unique_name();
    }
    return name_;
}

void Robot::reset() {
    // Keep the previous name in the global set so that it is never reused.
    name_.clear();
}

}  // namespace robot_name
