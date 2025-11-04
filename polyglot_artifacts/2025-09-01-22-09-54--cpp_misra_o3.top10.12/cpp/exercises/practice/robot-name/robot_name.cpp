#include "robot_name.h"

#include <array>
#include <cstdint>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

std::unordered_set<std::string> robot::used_names_{};

std::string robot::generate_unique_name()
{
    static const std::array<char, 26U> letters = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    static const std::array<char, 10U> digits = {
        '0','1','2','3','4','5','6','7','8','9'
    };

    static std::random_device random_source{};
    static std::mt19937 engine{random_source()};

    static std::uniform_int_distribution<std::uint32_t> dist_letter(0U, 25U);
    static std::uniform_int_distribution<std::uint32_t> dist_digit(0U, 9U);

    std::string candidate{};
    do {
        candidate.clear();
        candidate.push_back(letters[(dist_letter(engine))]);
        candidate.push_back(letters[(dist_letter(engine))]);
        candidate.push_back(digits[(dist_digit(engine))]);
        candidate.push_back(digits[(dist_digit(engine))]);
        candidate.push_back(digits[(dist_digit(engine))]);
    } while (used_names_.find(candidate) != used_names_.end());

    used_names_.insert(candidate);
    return candidate;
}

[[nodiscard]] std::string robot::name() const
{
    if (name_.empty()) {
        name_ = generate_unique_name();
    }
    return name_;
}

void robot::reset()
{
    if (!name_.empty()) {
        (void)used_names_.erase(name_);
        name_.clear();
    }
}

}  // namespace robot_name
