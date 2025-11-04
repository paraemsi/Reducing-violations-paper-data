#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <mutex>

namespace robot_name {

namespace {

// shared state for tracking assigned names
std::unordered_set<std::string> used_names;
std::mutex names_mutex;

// generate a random uppercase letter
char random_uppercase_letter(std::mt19937& rng) {
    static std::uniform_int_distribution<int> dist(0, 25);
    return static_cast<char>('A' + dist(rng));
}

// generate a random digit character
char random_digit(std::mt19937& rng) {
    static std::uniform_int_distribution<int> dist(0, 9);
    return static_cast<char>('0' + dist(rng));
}

// produce a new unique robot name
std::string generate_unique_name() {
    static std::random_device rd;
    static std::mt19937 rng(rd());

    std::string candidate;
    std::lock_guard<std::mutex> lock(names_mutex);

    do {
        candidate.clear();
        candidate += random_uppercase_letter(rng);
        candidate += random_uppercase_letter(rng);
        candidate += random_digit(rng);
        candidate += random_digit(rng);
        candidate += random_digit(rng);
    } while (used_names.find(candidate) != used_names.end());

    used_names.insert(candidate);
    return candidate;
}

} // namespace

robot::robot()
    : name_{generate_unique_name()} {}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    // Keep a historical record of all names ever issued to guarantee
    // global uniqueness, even after robots are reset.
    name_ = generate_unique_name();
}

}  // namespace robot_name
