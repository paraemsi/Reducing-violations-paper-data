#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace {

// Random engine seeded with non-deterministic random device.
std::mt19937& rng() {
    static std::mt19937 gen{std::random_device{}()};
    return gen;
}

char random_upper_letter() {
    static std::uniform_int_distribution<int> dist(0, 25);
    return static_cast<char>('A' + dist(rng()));
}

char random_digit() {
    static std::uniform_int_distribution<int> dist(0, 9);
    return static_cast<char>('0' + dist(rng()));
}

std::string make_name() {
    std::string s;
    s.reserve(5);
    s.push_back(random_upper_letter());
    s.push_back(random_upper_letter());
    s.push_back(random_digit());
    s.push_back(random_digit());
    s.push_back(random_digit());
    return s;
}

}  // namespace

namespace robot_name {

static std::unordered_set<std::string> used_names;
static std::mutex used_names_mutex;

std::string robot::name() const {
    std::lock_guard<std::mutex> lock(used_names_mutex);
    if (name_.empty()) {
        std::string candidate;
        do {
            candidate = make_name();
        } while (!used_names.insert(candidate).second);
        name_ = std::move(candidate);
    }
    return name_;
}

void robot::reset() {
    std::lock_guard<std::mutex> lock(used_names_mutex);
    if (!name_.empty()) {
        used_names.erase(name_);
        name_.clear();
    }
}


}  // namespace robot_name
