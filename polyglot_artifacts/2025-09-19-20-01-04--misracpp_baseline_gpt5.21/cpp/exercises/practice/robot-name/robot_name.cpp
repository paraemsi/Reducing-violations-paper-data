#include "robot_name.h"

#include <random>
#include <string>
#include <unordered_set>
#include <mutex>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
    std::mutex used_names_mutex;

    char random_upper_letter(std::mt19937& rng) {
        static std::uniform_int_distribution<int> dist(0, 25);
        return static_cast<char>('A' + dist(rng));
    }

    char random_digit(std::mt19937& rng) {
        static std::uniform_int_distribution<int> dist(0, 9);
        return static_cast<char>('0' + dist(rng));
    }

    std::string make_random_name(std::mt19937& rng) {
        std::string s;
        s.reserve(5);
        s.push_back(random_upper_letter(rng));
        s.push_back(random_upper_letter(rng));
        s.push_back(random_digit(rng));
        s.push_back(random_digit(rng));
        s.push_back(random_digit(rng));
        return s;
    }

    std::string generate_unique_name() {
        static thread_local std::mt19937 rng{std::random_device{}()};
        for (;;) {
            auto candidate = make_random_name(rng);
            std::lock_guard<std::mutex> lock(used_names_mutex);
            if (used_names.insert(candidate).second) {
                return candidate;
            }
        }
    }

    void release_name(const std::string& name) {
        if (name.empty()) return;
        std::lock_guard<std::mutex> lock(used_names_mutex);
        used_names.erase(name);
    }
} // anonymous namespace

robot::robot()
    : name_{generate_unique_name()} {}

robot::~robot() {
}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    name_ = generate_unique_name();
}

}  // namespace robot_name
