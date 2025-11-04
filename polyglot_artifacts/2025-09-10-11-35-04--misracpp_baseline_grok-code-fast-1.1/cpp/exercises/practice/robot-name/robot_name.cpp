#include "robot_name.h"
#include <random>
#include <string>
#include <set>

namespace robot_name {

std::set<std::string> robot::used_names_;

robot::robot() {
    name_ = generate_name();
    used_names_.insert(name_);
}

std::string robot::name() const {
    return name_;
}

void robot::reset() {
    used_names_.erase(name_);
    name_ = generate_name();
    used_names_.insert(name_);
}

std::string robot::generate_name() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> letter_dist(0, 25);
    std::uniform_int_distribution<> digit_dist(0, 9);
    std::string name;
    do {
        name = "";
        name += 'A' + letter_dist(gen);
        name += 'A' + letter_dist(gen);
        name += '0' + digit_dist(gen);
        name += '0' + digit_dist(gen);
        name += '0' + digit_dist(gen);
    } while (used_names_.count(name));
    return name;
}

}  // namespace robot_name
