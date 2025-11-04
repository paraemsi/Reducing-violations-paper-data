#include "robot_name.h"
#include <random>
#include <mutex>

namespace robot_name {

static std::unordered_set<std::string> s_used_names_storage;

std::unordered_set<std::string>& robot::s_used_names_ref(void)
{
    return s_used_names_storage;
}

namespace {
    // Use a function-local static to ensure thread-safe initialization
    std::mt19937& rng() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    std::mutex& name_mutex() {
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
        std::lock_guard<std::mutex> lock(name_mutex());
        (void)s_used_names_ref().erase(m_name);
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
        std::lock_guard<std::mutex> lock(name_mutex());
        (void)s_used_names_ref().erase(m_name);
        m_name.clear();
    }
}

void robot::generate_name(void)
{
    std::uniform_int_distribution<std::uint16_t> letter_dist(0, 25);
    std::uniform_int_distribution<std::uint16_t> digit_dist(0, 9);

    std::string new_name;
    bool unique = false;

    while (!unique) {
        new_name.clear();
        new_name += static_cast<char>('A' + static_cast<std::int32_t>(letter_dist(rng())));
        new_name += static_cast<char>('A' + static_cast<std::int32_t>(letter_dist(rng())));
        new_name += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(rng())));
        new_name += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(rng())));
        new_name += static_cast<char>('0' + static_cast<std::int32_t>(digit_dist(rng())));

        std::lock_guard<std::mutex> lock(name_mutex());
        if (s_used_names_ref().find(new_name) == s_used_names_ref().end()) {
            s_used_names_ref().insert(new_name);
            unique = true;
        }
    }
    m_name = new_name;
}

}  // namespace robot_name
