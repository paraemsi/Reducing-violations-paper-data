#include "robot_name.h"

#include <iomanip>
#include <mutex>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {

std::unordered_set<std::string> used_names{};
static std::recursive_mutex name_mutex{};

constexpr size_t kMaxNames = 26 * 26 * 1000;

std::string generate_name() {
    static std::random_device rd{};
    static std::mt19937 gen{rd()};
    static std::uniform_int_distribution<> letter_dist('A', 'Z');
    static std::uniform_int_distribution<> digit_dist(0, 999);

    std::stringstream ss;
    ss << static_cast<char>(letter_dist(gen))
       << static_cast<char>(letter_dist(gen))
       << std::setw(3) << std::setfill('0') << digit_dist(gen);
    return ss.str();
}

std::string generate_unique_name_unlocked() {
    if (used_names.size() >= kMaxNames) {
        throw std::runtime_error("All possible robot names are in use.");
    }
    std::string name;
    do {
        name = generate_name();
    } while (used_names.count(name) > 0);
    return name;
}

} // anonymous namespace

robot::robot() {}

robot::~robot() {
    std::lock_guard<std::recursive_mutex> lock(name_mutex);
    if (!robot_name_.empty()) {
        used_names.erase(robot_name_);
    }
    if (!name_to_release_.empty()) {
        used_names.erase(name_to_release_);
    }
}

const std::string& robot::name() const {
    std::lock_guard<std::recursive_mutex> lock(name_mutex);
    if (robot_name_.empty()) {
        std::string new_name = generate_unique_name_unlocked();
        used_names.insert(new_name);

        if (!name_to_release_.empty()) {
            used_names.erase(name_to_release_);
            name_to_release_.clear();
        }
        robot_name_ = std::move(new_name);
    }
    return robot_name_;
}

void robot::reset() {
    std::lock_guard<std::recursive_mutex> lock(name_mutex);
    if (!robot_name_.empty()) {
        name_to_release_ = robot_name_;
        robot_name_.clear();
    }
}

}  // namespace robot_name
