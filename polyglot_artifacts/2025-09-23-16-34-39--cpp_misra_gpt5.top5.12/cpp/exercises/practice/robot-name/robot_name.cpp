#include "robot_name.h"

#include <array>
#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>
#include <utility>

namespace robot_name {

namespace {
std::string generate_unique_name() {
    static std::mutex mtx{};
    static std::unordered_set<std::string> used_names{};
    static std::random_device rd{};
    static std::mt19937 engine(rd());
    static const std::string letters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    static const std::string digits("0123456789");
    static std::uniform_int_distribution<std::size_t> letter_dist(static_cast<std::size_t>(0U), (letters.size() - static_cast<std::size_t>(1U)));
    static std::uniform_int_distribution<std::size_t> digit_dist(static_cast<std::size_t>(0U), (digits.size() - static_cast<std::size_t>(1U)));

    std::lock_guard<std::mutex> lock(mtx);

    for (;;) {
        std::array<char, static_cast<std::size_t>(5U)> arr{};

        arr.at(static_cast<std::size_t>(0U)) = letters.at(letter_dist(engine));
        arr.at(static_cast<std::size_t>(1U)) = letters.at(letter_dist(engine));
        arr.at(static_cast<std::size_t>(2U)) = digits.at(digit_dist(engine));
        arr.at(static_cast<std::size_t>(3U)) = digits.at(digit_dist(engine));
        arr.at(static_cast<std::size_t>(4U)) = digits.at(digit_dist(engine));

        const std::string candidate(arr.data(), arr.size());

        const auto insertion = used_names.insert(candidate);
        if ((insertion.second) == true) {
            return candidate;
        }
    }
}
}  // namespace

robot::robot()
    : name_(generate_unique_name()) {
}

const std::string& robot::name() const {
    return name_;
}

void robot::reset() {
    name_ = generate_unique_name();
}

}  // namespace robot_name
