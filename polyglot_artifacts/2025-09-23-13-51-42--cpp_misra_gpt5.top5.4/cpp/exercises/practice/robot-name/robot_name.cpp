#include "robot_name.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
    using name_set = std::unordered_set<std::string>;

    static name_set g_allocated_names{};
    static std::mutex g_mutex{};

    static std::random_device g_rd{};
    static std::mt19937 g_engine{g_rd()};

    static constexpr std::array<char, 26U> LETTERS = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    static constexpr std::array<char, 10U> DIGITS = {
        '0','1','2','3','4','5','6','7','8','9'
    };

    static std::uniform_int_distribution<std::uint32_t> dist_letter(0U, 25U);
    static std::uniform_int_distribution<std::uint32_t> dist_digit(0U, 9U);

    static std::string build_random_name()
    {
        std::string s{};
        s.reserve(5U);
        s.push_back(LETTERS.at(dist_letter(g_engine)));
        s.push_back(LETTERS.at(dist_letter(g_engine)));
        s.push_back(DIGITS.at(dist_digit(g_engine)));
        s.push_back(DIGITS.at(dist_digit(g_engine)));
        s.push_back(DIGITS.at(dist_digit(g_engine)));
        return s;
    }
}  // anonymous namespace

robot::robot() = default;

robot::~robot() noexcept
{
    // Do not release the name; keep global uniqueness across resets and lifetimes
}

const std::string& robot::name() const
{
    if ((name_.empty())) {
        name_ = generate_unique_name();
    } else {
        // no action required
    }

    return name_;
}

void robot::reset() noexcept
{
    if ((name_.empty())) {
        return;
    } else {
        name_.clear();
    }
}

std::string robot::generate_unique_name()
{
    std::string candidate{};
    bool inserted = false;

    while (!inserted) {
        std::lock_guard<std::mutex> lock(g_mutex);
        candidate = build_random_name();
        auto insert_result = g_allocated_names.insert(candidate);
        inserted = insert_result.second;
    }

    return candidate;
}


}  // namespace robot_name
