#include "robot_name.h"
#include <random>
#include <mutex>

namespace robot_name {

namespace {
    // Use a mutex to protect the static set of used names
    std::mutex& get_mutex() {
        static std::mutex mtx;
        return mtx;
    }
}

std::unordered_set<std::string> robot::s_used_names;

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
        m_name = generate_unique_name();
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

std::string robot::generate_unique_name(void)
{
    using letter_index_t = std::uint8_t;
    using digit_index_t = std::uint16_t;

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<letter_index_t> letter_dist(0U, 25U);
    static std::uniform_int_distribution<digit_index_t> digit_dist(0U, 9U);

    std::string new_name;
    bool unique = false;

    while (!unique) {
        char first = static_cast<char>('A' + letter_dist(gen));
        char second = static_cast<char>('A' + letter_dist(gen));
        char third = static_cast<char>('0' + digit_dist(gen));
        char fourth = static_cast<char>('0' + digit_dist(gen));
        char fifth = static_cast<char>('0' + digit_dist(gen));

        new_name = std::string() + first + second + third + fourth + fifth;

        {
            std::lock_guard<std::mutex> lock(get_mutex());
            if (s_used_names.find(new_name) == s_used_names.end()) {
                (void)s_used_names.insert(new_name);
                unique = true;
            }
        }
    }
    return new_name;
}

}  // namespace robot_name
