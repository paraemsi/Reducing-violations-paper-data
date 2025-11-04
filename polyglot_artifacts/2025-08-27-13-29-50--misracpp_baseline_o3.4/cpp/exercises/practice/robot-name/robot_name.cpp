#include "robot_name.h"
#include <random>

namespace robot_name {

std::unordered_set<std::string> Robot::used_names{};

std::string Robot::generate_unique_name() {
    static std::mt19937 rng{std::random_device{}()};
    static std::uniform_int_distribution<int> letter_dist('A', 'Z');
    static std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string candidate;
    do {
        candidate.clear();
        candidate.push_back(static_cast<char>(letter_dist(rng)));
        candidate.push_back(static_cast<char>(letter_dist(rng)));
        for (int i = 0; i < 3; ++i) {
            candidate.push_back(static_cast<char>('0' + digit_dist(rng)));
        }
    } while (Robot::used_names.find(candidate) != Robot::used_names.end());

    Robot::used_names.insert(candidate);
    return candidate;
}

std::string Robot::name() const {
    if (_name.empty()) {
        _name = generate_unique_name();
    }
    return _name;
}

void Robot::reset() {
    // Keep the old name in `used_names` so no future robot can reuse it.
    _name.clear();
}

}  // namespace robot_name
