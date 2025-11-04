#include "robot_name.h"

#include <random>
#include <unordered_set>
#include <mutex>
#include <cstdint>
#include <cstddef>

namespace robot_name {

namespace
{
/*
 * make_random_name
 * ----------------
 * Builds a random name in the required LLDDD format using the supplied
 * PRNG engine.  No attempt is made to ensure uniqueness here – that is
 * handled by Robot::generate_unique_name().
 */
std::string make_random_name(std::mt19937& engine)
{
    static const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::string digits  = "0123456789";

    std::uniform_int_distribution<std::size_t> letter_dist(
        static_cast<std::size_t>(0U),
        letters.size() - static_cast<std::size_t>(1U));

    std::uniform_int_distribution<std::size_t> digit_dist(
        static_cast<std::size_t>(0U),
        digits.size() - static_cast<std::size_t>(1U));

    std::string result{};
    result.reserve(5U);

    result.push_back(
        letters.at(letter_dist(engine)));
    result.push_back(
        letters.at(letter_dist(engine)));

    for (std::size_t i = static_cast<std::size_t>(0U); i < static_cast<std::size_t>(3U); ++i)
    {
        result.push_back(
            digits.at(digit_dist(engine)));
    }

    return result;
}
} // unnamed namespace

/*
 * Robot – private helpers
 */
std::string robot::generate_unique_name()
{
    static std::unordered_set<std::string> used_names{};
    static std::mutex                      mtx{};
    static std::random_device              rd{};
    static std::mt19937                    engine(rd());

    std::lock_guard<std::mutex> guard(mtx);

    std::string candidate{};

    do
    {
        candidate = make_random_name(engine);
    }
    while (used_names.find(candidate) != used_names.end());

    (void)used_names.insert(candidate);   // insert & silence return value

    return candidate;
}

/*
 * Robot – public interface
 */
robot::robot() :
    m_name(generate_unique_name())
{
}

const std::string& robot::name() const
{
    return m_name;
}

void robot::reset()
{
    m_name = generate_unique_name();
}

}  // namespace robot_name
