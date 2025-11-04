#include "robot_name.h"
#include <random>

namespace robot_name {

// static storage for already-taken names
std::unordered_set<std::string> Robot::s_used_names{};

// single RNG shared by all robots
static std::mt19937& rng() {
    static std::random_device rd;
    static std::mt19937 gen{rd()};
    return gen;
}

Robot::Robot() {
    generate_unique_name();
}

const std::string& Robot::name() const {
    return _name;
}

void Robot::reset() {
    std::string old = _name;
    do {
        generate_unique_name();      // produce a new unique name
    } while (_name == old);          // make sure it actually changed
}

Robot::~Robot() = default;

void Robot::generate_unique_name() {
    do {
        _name = generate_random_name();
    } while (!s_used_names.insert(_name).second); // repeat until unique
}

std::string Robot::generate_random_name() {
    std::uniform_int_distribution<int> letter_dist('A', 'Z');
    std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string result(5, '\0');
    result[0] = static_cast<char>(letter_dist(rng()));
    result[1] = static_cast<char>(letter_dist(rng()));
    result[2] = static_cast<char>('0' + digit_dist(rng()));
    result[3] = static_cast<char>('0' + digit_dist(rng()));
    result[4] = static_cast<char>('0' + digit_dist(rng()));
    return result;
}

}  // namespace robot_name
