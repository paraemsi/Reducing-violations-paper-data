#include "robot_name.h"
#include <unordered_set>
#include <random>
#include <array>
#include <mutex>
#include <cstddef>

namespace
{
    // Container holding already allocated robot names
    std::unordered_set<std::string> used_names{};
    // Mutex to ensure thread-safety of the name pool
    std::mutex names_mutex{};
} // unnamed namespace

namespace robot_name {

const std::string& Robot::name() noexcept
{
    if(m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void Robot::reset()
{
    {
        std::lock_guard<std::mutex> lock{names_mutex};
        if(!m_name.empty()) {
            // erase returns a size_t; explicitly discard to satisfy MISRA rule about unused return values
            (void)used_names.erase(m_name);
        }
    }
    m_name.clear();
}

std::string Robot::generate_unique_name()
{
    static const std::array<char, 26U> letters{
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P',
        'Q','R','S','T','U','V','W','X','Y','Z'};
    static const std::array<char, 10U> digits{
        '0','1','2','3','4','5','6','7','8','9'};

    static std::random_device rd{};
    static std::mt19937 engine{rd()};
    static std::uniform_int_distribution<std::size_t> letter_dist{0U, 25U};
    static std::uniform_int_distribution<std::size_t> digit_dist{0U, 9U};

    std::string candidate{};

    while(true) {
        candidate.clear();

        for(std::uint32_t i{0U}; i < static_cast<std::uint32_t>(2U); ++i) {
            candidate.push_back(letters[letter_dist(engine)]);
        }

        for(std::uint32_t i{0U}; i < static_cast<std::uint32_t>(3U); ++i) {
            candidate.push_back(digits[digit_dist(engine)]);
        }

        std::lock_guard<std::mutex> lock{names_mutex};
        // attempt to insert; if successful, candidate is unique
        if(used_names.insert(candidate).second) {
            break;
        }
    }

    return candidate;
}

}  // namespace robot_name
