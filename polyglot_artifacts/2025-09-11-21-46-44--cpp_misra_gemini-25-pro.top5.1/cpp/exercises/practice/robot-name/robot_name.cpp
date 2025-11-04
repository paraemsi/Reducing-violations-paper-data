#include "robot_name.h"

#include <cstdint>
#include <random>
#include <set>
#include <string>

namespace robot_name {

namespace {

// Using a static set to keep track of names in use.
static std::set<std::string> names_in_use{};

// Random number generation setup.
std::mt19937& get_engine() {
    static std::random_device rd{};
    static std::mt19937 engine{rd()};
    return engine;
}

std::string generate_name() {
    constexpr char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    constexpr char digits[] = "0123456789";

    // The range for a distribution is inclusive, so [0, length-1].
    // For letters, sizeof is 27 (includes null terminator), so length is 26.
    // The range should be [0, 25], which is sizeof - 2.
    std::uniform_int_distribution<std::uint8_t> letter_dist(
        0, (sizeof(letters) - 2));
    std::uniform_int_distribution<std::uint8_t> digit_dist(
        0, (sizeof(digits) - 2));

    std::string name;
    name.resize(5);
    name[0] = letters[letter_dist(get_engine())];
    name[1] = letters[letter_dist(get_engine())];
    name[2] = digits[digit_dist(get_engine())];
    name[3] = digits[digit_dist(get_engine())];
    name[4] = digits[digit_dist(get_engine())];

    return name;
}

std::string get_unique_name() {
    std::string name;
    do {
        name = generate_name();
    } while ((names_in_use.count(name) > 0));

    return name;
}

}  // namespace

robot::robot() : name_{get_unique_name()} {
    static_cast<void>(names_in_use.insert(name_));
}

std::string const& robot::name() const {
    return name_;
}

void robot::reset() {
    const std::string old_name{name_};
    static_cast<void>(names_in_use.erase(old_name));

    do {
        name_ = get_unique_name();
    } while (name_ == old_name);

    static_cast<void>(names_in_use.insert(name_));
}

}  // namespace robot_name
