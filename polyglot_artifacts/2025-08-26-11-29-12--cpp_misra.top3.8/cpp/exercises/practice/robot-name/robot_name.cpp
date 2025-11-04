#include "robot_name.h"
#include <random>
#include <mutex>

namespace robot_name {

std::unordered_set<std::string> robot::s_used_names;

namespace {
    // Use a function-local static to ensure thread-safe initialization
    std::mt19937& get_rng() {
        static std::random_device rd;
        static std::mt19937 rng(rd());
        return rng;
    }

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
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(get_mutex());
        (void)s_used_names.erase(m_name);
    }
}

std::string robot::name(void)
{
    if (m_name.empty()) {
        generate_name();
    }
    return m_name;
}

void robot::reset(void)
{
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(get_mutex());
        (void)s_used_names.erase(m_name);
        m_name.clear();
    }
}

void robot::generate_name(void)
{
    static const char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::uint32_t num_letters = 26U;
    static const std::uint32_t num_digits = 10U;

    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, num_letters - 1U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, num_digits - 1U);

    std::string new_name;
    bool unique = false;

    while (!unique) {
        new_name.clear();
        new_name += letters[static_cast<std::size_t>(letter_dist(get_rng()))];
        new_name += letters[static_cast<std::size_t>(letter_dist(get_rng()))];
        new_name += static_cast<char>('0' + static_cast<char>(digit_dist(get_rng())));
        new_name += static_cast<char>('0' + static_cast<char>(digit_dist(get_rng())));
        new_name += static_cast<char>('0' + static_cast<char>(digit_dist(get_rng())));

        std::lock_guard<std::mutex> lock(get_mutex());
        if (s_used_names.find(new_name) == s_used_names.end()) {
            s_used_names.insert(new_name);
            unique = true;
        }
    }
    m_name = new_name;
}

}  // namespace robot_name
