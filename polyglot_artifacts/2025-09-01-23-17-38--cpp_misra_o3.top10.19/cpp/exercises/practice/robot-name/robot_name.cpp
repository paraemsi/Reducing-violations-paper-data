#include "robot_name.h"

#include <array>
#include <random>
#include <unordered_set>
#include <mutex>

namespace robot_name {

namespace {

/* Alphabet and digit lookup tables – avoid arithmetic on char */
constexpr std::array<char, 26U> alphabet {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

constexpr std::array<char, 10U> decimal_digits {
    '0','1','2','3','4','5','6','7','8','9'
};

/* Shared resources for name generation */
std::unordered_set<std::string> used_names {};
std::mutex                                          used_names_mutex {};

/* Random engine and distributions */
std::mt19937& rng()
{
    static thread_local std::mt19937 engine { std::random_device {}() };
    return engine;
}

std::string build_name()
{
    std::uniform_int_distribution<std::uint32_t> letter_dist { 0U, 25U };
    std::uniform_int_distribution<std::uint32_t> digit_dist  { 0U, 9U };

    std::string candidate {};
    candidate.reserve(5U);

    /* Two letters */
    for(std::uint32_t i { 0U }; i < 2U; ++i) {
        const std::uint32_t idx { letter_dist(rng()) };
        candidate.push_back(alphabet.at(static_cast<std::size_t>(idx)));
    }

    /* Three digits */
    for(std::uint32_t i { 0U }; i < 3U; ++i) {
        const std::uint32_t idx { digit_dist(rng()) };
        candidate.push_back(decimal_digits.at(static_cast<std::size_t>(idx)));
    }

    return candidate;
}

} // unnamed namespace

std::string robot::generate_unique_name()
{
    std::string new_name {};

    while(true) {
        new_name = build_name();

        /* lock guard ensures unique insertion */
        {
            std::lock_guard<std::mutex> lock { used_names_mutex };
            const auto inserted = used_names.insert(new_name);
            if(inserted.second) {
                break;
            }
        }
    }

    return new_name;
}

const std::string& robot::name() const
{
    if(m_name.empty()) {
        m_name = generate_unique_name();
    }

    return m_name;
}

void robot::reset()
{
    if(!m_name.empty()) {
        {
            std::lock_guard<std::mutex> lock { used_names_mutex };
            (void)used_names.erase(m_name); /* discard erase count */
        }
        m_name.clear();
    }
}

}  // namespace robot_name
