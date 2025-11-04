#include "robot_name.h"
#include <random>
#include <mutex>
#include <array>
#include <algorithm>

namespace robot_name {

namespace {
    // Use a mutex to protect the static set of used names
    std::mutex& get_mutex() {
        static std::mutex mtx;
        return mtx;
    }
}

robot::robot()
    : m_name("")
{
}

robot::~robot()
{
    // Remove the name from the set of used names on destruction
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(get_mutex());
        (void)used_names().erase(m_name);
    }
}

std::string robot::name()
{
    if (m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void robot::reset()
{
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(get_mutex());
        (void)used_names().erase(m_name);
        m_name.clear();
    }
}

std::unordered_set<std::string>& robot::used_names()
{
    static std::unordered_set<std::string> s;
    return s;
}

std::string robot::generate_unique_name()
{
    std::string candidate;
    std::lock_guard<std::mutex> lock(get_mutex());
    do {
        candidate = generate_name_candidate();
    } while (used_names().find(candidate) != used_names().end());
    used_names().insert(candidate);
    return candidate;
}

std::string robot::generate_name_candidate()
{
    // Use random_device and mt19937 for randomness
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());

    static constexpr std::array<char, 26> letters = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    std::uniform_int_distribution<std::uint8_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint16_t> digit_dist(0U, 9U);

    std::string result;
    result += letters.at(static_cast<std::size_t>(letter_dist(gen)));
    result += letters.at(static_cast<std::size_t>(letter_dist(gen)));
    for (std::uint8_t i = 0U; (i < 3U); ++i) {
        result += static_cast<char>('0' + static_cast<char>(digit_dist(gen)));
    }
    return result;
}

}  // namespace robot_name
