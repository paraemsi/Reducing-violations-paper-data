#include "robot_name.h"

#include <array>
#include <random>
#include <stdexcept>

namespace robot_name {

namespace
{
    /* Random number engine scoped to this translation unit */
    inline std::mt19937& rng()
    {
        static std::random_device rd {};
        static std::mt19937 engine {rd()};
        return engine;
    }
} // unnamed namespace

std::unordered_set<std::string> robot::s_usedNames {};

robot::robot() : m_name {generateName()}
{
    /* Intentionally empty */
}

std::string robot::name() const
{
    return m_name;    /* return by value to preserve pre-reset name copies */
}

void robot::reset()
{
    /* Remove the current name from the registry */
    (void)s_usedNames.erase(m_name);

    m_name = generateName();
}

std::string robot::generateName()
{
    static constexpr std::array<char, 26U> kLetters {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    static constexpr std::array<char, 10U> kDigits {
        '0','1','2','3','4','5','6','7','8','9'
    };

    std::uniform_int_distribution<std::uint32_t> letterDist {0U, 25U};
    std::uniform_int_distribution<std::uint32_t> digitDist {0U, 9U};

    std::string candidate {};
    candidate.reserve(5U);

    /* Total possible unique names: 26 letters × 26 letters × 1000 digits */
    static constexpr std::uint32_t kTotalNames { (26U * 26U * 1000U) };

    if (s_usedNames.size() >= static_cast<std::size_t>(kTotalNames))
    {
        throw std::runtime_error("All robot names exhausted");
    }

    while (true)
    {
        candidate.clear();

        candidate.push_back(kLetters.at(letterDist(rng())));
        candidate.push_back(kLetters.at(letterDist(rng())));

        for (std::uint32_t i = 0U; i < 3U; ++i)
        {
            candidate.push_back(kDigits.at(digitDist(rng())));
        }

        const auto [it, inserted] = s_usedNames.insert(candidate);
        if (inserted)
        {
            return *it;
        }
    }
}

}  // namespace robot_name
