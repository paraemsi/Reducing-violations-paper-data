#include "robot_name.h"

#include <unordered_set>
#include <random>
#include <mutex>
#include <chrono>
#include <stdexcept>

namespace robot_name {

namespace {
std::unordered_set<std::string> used_names;
std::mutex used_names_mutex;

std::mt19937& rng() {
    thread_local std::mt19937 gen([] {
        std::random_device rd;
        std::seed_seq seed{
            rd(), rd(), rd(),
            static_cast<unsigned>(std::chrono::high_resolution_clock::now().time_since_epoch().count())
        };
        return std::mt19937(seed);
    }());
    return gen;
}

char random_upper() {
    static std::uniform_int_distribution<int> dist('A', 'Z');
    return static_cast<char>(dist(rng()));
}

char random_digit() {
    static std::uniform_int_distribution<int> dist('0', '9');
    return static_cast<char>(dist(rng()));
}

std::string make_random_name() {
    std::string s;
    s.reserve(5);
    s.push_back(random_upper());
    s.push_back(random_upper());
    s.push_back(random_digit());
    s.push_back(random_digit());
    s.push_back(random_digit());
    return s;
}

}  // unnamed namespace

robot::robot()
    : name_(generate_unique_name()) {}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    // Preserve the current name in the used set while we acquire a new one to
    // ensure the new name cannot be the same as the old name.
    std::string old_name;
    {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        old_name = name_;
    }

    // Acquire a new unique name (old_name is still reserved).
    std::string new_name = generate_unique_name();

    // Now release the old name back to the pool.
    {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        if (!old_name.empty()) {
            used_names.erase(old_name);
        }
    }

    name_ = std::move(new_name);
}

std::string robot::generate_unique_name() {
    for (size_t i = 0; i < 1000000; ++i) {
        auto candidate = make_random_name();
        std::lock_guard<std::mutex> lock(used_names_mutex);
        if (used_names.insert(candidate).second) {
            return candidate;
        }
    }
    throw std::runtime_error("Unable to generate a unique robot name");
}

}  // namespace robot_name
