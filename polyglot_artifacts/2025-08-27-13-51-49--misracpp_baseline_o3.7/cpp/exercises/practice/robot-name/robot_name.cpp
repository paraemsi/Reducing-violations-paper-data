#include "robot_name.h"

#include <unordered_set>
#include <random>

namespace robot_name {

std::unordered_set<std::string> robot::used_names{};

std::mt19937& robot::generator() {
    static std::random_device rd;
    static std::mt19937 gen{rd()};
    return gen;
}

std::string robot::generate_name() {
    std::uniform_int_distribution<int> letter_dist('A', 'Z');
    std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string name(5, '\0');
    name[0] = static_cast<char>(letter_dist(generator()));
    name[1] = static_cast<char>(letter_dist(generator()));
    name[2] = static_cast<char>('0' + digit_dist(generator()));
    name[3] = static_cast<char>('0' + digit_dist(generator()));
    name[4] = static_cast<char>('0' + digit_dist(generator()));
    return name;
}

robot::robot() {
    reset();
}

const std::string& robot::name() const {
    return _name;
}

void robot::reset() {
    if (!_name.empty()) {
        used_names.erase(_name);
    }

    std::string candidate;
    do {
        candidate = generate_name();
    } while (used_names.find(candidate) != used_names.end());

    _name = candidate;
    used_names.insert(_name);
}

}  // namespace robot_name
