#include "robot_name.h"

#include <unordered_set>
#include <random>
#include <array>
#include <utility>
#include <stdexcept>
#include <string>

namespace robot_name {

namespace
{
    auto engine() -> std::mt19937&
    {
        static std::random_device rd{};
        static std::mt19937 gen{ rd() };
        return gen;
    }

    auto letter_distribution() -> std::uniform_int_distribution<std::uint32_t>&
    {
        static std::uniform_int_distribution<std::uint32_t> dist{ 0U, 25U };
        return dist;
    }

    auto digit_distribution() -> std::uniform_int_distribution<std::uint32_t>&
    {
        static std::uniform_int_distribution<std::uint32_t> dist{ 0U, 9U };
        return dist;
    }

    constexpr std::array<char, 26U> letters
    {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    constexpr std::array<char, 10U> digits
    {
        '0','1','2','3','4','5','6','7','8','9'
    };

    auto used_names() -> std::unordered_set<std::string>&
    {
        static std::unordered_set<std::string> registry{};
        return registry;
    }
} // unnamed namespace

robot::robot() : m_name{ generate_unique_name() }
{
}

robot::~robot()
{
    auto& registry = used_names();
    (void)registry.erase(m_name);
}

robot::robot(robot&& other) noexcept : m_name{ std::move(other.m_name) }
{
    other.m_name.clear();
}

auto robot::operator=(robot&& other) noexcept -> robot&
{
    if (this != &other)
    {
        auto& registry = used_names();
        (void)registry.erase(m_name);

        m_name = std::move(other.m_name);
        other.m_name.clear();
        /* registry already contains m_name */
    }
    return *this;
}

auto robot::name() const -> const std::string&
{
    return m_name;
}

void robot::reset()
{
    auto& registry = used_names();
    (void)registry.erase(m_name);

    m_name = generate_unique_name();
}

auto robot::generate_unique_name() -> std::string
{
    auto& registry = used_names();

    constexpr std::uint32_t max_attempts { 10U };
    for (std::uint32_t attempt{ 0U }; attempt < max_attempts; ++attempt)
    {
        std::string candidate{};
        candidate.reserve(5U);

        auto& eng = engine();

        for (std::uint32_t i{ 0U }; i < 2U; ++i)
        {
            const char letter { letters[ letter_distribution()(eng) ] };
            candidate.push_back(letter);
        }

        for (std::uint32_t i{ 0U }; i < 3U; ++i)
        {
            const char digit { digits[ digit_distribution()(eng) ] };
            candidate.push_back(digit);
        }

        const auto insertion_result = registry.insert(candidate);
        if (insertion_result.second)
        {
            return candidate;
        }
    }

    throw std::runtime_error("Failed to generate a unique robot name");
}

}  // namespace robot_name
