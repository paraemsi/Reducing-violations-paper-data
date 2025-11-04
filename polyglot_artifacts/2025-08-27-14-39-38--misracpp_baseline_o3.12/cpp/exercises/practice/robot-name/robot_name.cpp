#include "robot_name.h"
#include <stdexcept>

namespace robot_name {

// Static member definitions
std::unordered_set<std::string> robot::used_names{};
std::mt19937 robot::rng{std::random_device{}()};

// Generate a unique random name in the format AA000-ZZ999.
std::string robot::generate_unique_name() {
    // Total possible names = 26 * 26 * 1000
    if (used_names.size() >= 26 * 26 * 1000) {
        throw std::runtime_error("Exhausted all robot names");
    }

    std::uniform_int_distribution<int> letter_dist(0, 25); // A-Z
    std::uniform_int_distribution<int> digit_dist(0, 9);   // 0-9

    std::string candidate;
    do {
        candidate.clear();
        candidate += static_cast<char>('A' + letter_dist(rng));
        candidate += static_cast<char>('A' + letter_dist(rng));
        for (int i = 0; i < 3; ++i) {
            candidate += static_cast<char>('0' + digit_dist(rng));
        }
    } while (used_names.find(candidate) != used_names.end());

    used_names.insert(candidate);
    return candidate;
}

robot::robot() : _name(generate_unique_name()) {}

robot::~robot() {
    // Release the name when a robot instance is destroyed so it can be reused.
    used_names.erase(_name);
}

const std::string& robot::name() const {
    return _name;
}

void robot::reset() {
    const std::string old_name = _name;
    used_names.erase(old_name);  // Release old name so it can be reused.

    std::string new_name;
    do {
        new_name = generate_unique_name();      // Generates and *reserves* a name.
        if (new_name == old_name) {
            // Generated the same name – free it and try again.
            used_names.erase(new_name);
        }
    } while (new_name == old_name);

    _name = new_name;
}

}  // namespace robot_name
