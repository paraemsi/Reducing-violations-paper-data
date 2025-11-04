#include "robot_name.h"

#include <array>
#include <unordered_set>
#include <random>
#include <mutex>
#include <cstdint>

namespace
{
using NameSet = std::unordered_set<std::string>;

auto& get_used_names() -> NameSet&
{
    static NameSet used_names{};
    return used_names;
}

auto& get_rng() -> std::mt19937&
{
    static std::random_device rd{};
    static std::mt19937 engine{ rd() };
    return engine;
}

auto& get_mutex() -> std::mutex&
{
    static std::mutex mtx{};
    return mtx;
}

constexpr std::array<char, 26U> letters{
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

constexpr std::array<char, 10U> digits{
    '0','1','2','3','4','5','6','7','8','9'
};

} // anonymous namespace

namespace robot_name {

robot::robot() : m_name(generate_unique_name())
{
}

void robot::reset()
{
    std::lock_guard<std::mutex> lock(::get_mutex());
    (void)::get_used_names().erase(m_name);
    m_name = generate_unique_name();
}

std::string robot::name() const
{
    return m_name;
}

std::string robot::generate_unique_name()
{
    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::string candidate{};
    candidate.resize(5U);

    for (;;)
    {
        candidate[0U] = ::letters[letter_dist(::get_rng())];
        candidate[1U] = ::letters[letter_dist(::get_rng())];
        candidate[2U] = ::digits[digit_dist(::get_rng())];
        candidate[3U] = ::digits[digit_dist(::get_rng())];
        candidate[4U] = ::digits[digit_dist(::get_rng())];

        std::lock_guard<std::mutex> lock(::get_mutex());
        auto& names = ::get_used_names();
        if (names.insert(candidate).second)
        {
            return candidate;
        }
    }
}

}  // namespace robot_name
