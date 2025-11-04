#include "robot_name.h"

#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
    std::string generate_name(std::mt19937& rng) {
        static std::uniform_int_distribution<int> letter_dist('A', 'Z');
        static std::uniform_int_distribution<int> digit_dist('0', '9');

        std::string name;
        name.reserve(5);
        name.push_back(static_cast<char>(letter_dist(rng)));
        name.push_back(static_cast<char>(letter_dist(rng)));
        for (int i = 0; i < 3; ++i) {
            name.push_back(static_cast<char>(digit_dist(rng)));
        }
        return name;
    }

    std::unordered_set<std::string>& used_names() {
        static std::unordered_set<std::string> names;
        return names;
    }
} // namespace

robot::robot() {
    allocate_unique_name();
}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    const std::string old_name = name_;
    used_names().erase(old_name);

    // Ensure the new name differs from the previous one
    do {
        allocate_unique_name();
    } while (name_ == old_name);
}

void robot::allocate_unique_name() {
    static std::mt19937 rng{std::random_device{}()};
    do {
        name_ = generate_name(rng);
    } while (!used_names().insert(name_).second);
}

}  // namespace robot_name
