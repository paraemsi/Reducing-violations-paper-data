#include "robot_name.h"
#include <random>
#include <string>
#include <set>

namespace robot_name {

std::set<std::string> robot::used_names_;

robot::robot() : name_("") {
}

std::string robot::name() const {
    if ((name_.empty())) {
        name_ = (generate_unique_name());
    }
    return name_;
}

void robot::reset() {
    if ((!name_.empty())) {
        used_names_.erase(name_);
        name_.clear();
    }
}

std::string robot::generate_unique_name() {
    static std::mt19937 rng(std::random_device{}());
    static const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::string digits = "0123456789";
    std::string candidate;
    do {
        candidate.clear();
        std::uniform_int_distribution<std::uint32_t> letter_dist(0, 25);
        std::uniform_int_distribution<std::uint32_t> digit_dist(0, 9);
        candidate += (letters[static_cast<std::size_t>((letter_dist(rng)))]);
        candidate += (letters[static_cast<std::size_t>((letter_dist(rng)))]);
        candidate += (digits[static_cast<std::size_t>((digit_dist(rng)))]);
        candidate += (digits[static_cast<std::size_t>((digit_dist(rng)))]);
        candidate += (digits[static_cast<std::size_t>((digit_dist(rng)))]);
    } while ((used_names_.find(candidate) != used_names_.end()));
    used_names_.insert(candidate);
    return candidate;
}

}  // namespace robot_name
