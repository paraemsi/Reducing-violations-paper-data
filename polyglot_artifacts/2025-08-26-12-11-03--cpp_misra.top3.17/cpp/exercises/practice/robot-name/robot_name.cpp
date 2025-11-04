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

    // Random engine and distribution for name generation
    std::random_device& get_rd() {
        static std::random_device rd;
        return rd;
    }

    std::mt19937& get_rng() {
        static std::mt19937 rng(get_rd()());
        return rng;
    }

    std::uniform_int_distribution<std::uint16_t>& get_letter_dist() {
        static std::uniform_int_distribution<std::uint16_t> dist(0U, 25U);
        return dist;
    }

    std::uniform_int_distribution<std::uint16_t>& get_digit_dist() {
        static std::uniform_int_distribution<std::uint16_t> dist(0U, 9U);
        return dist;
    }

    std::string generate_name() {
        std::string name;
        name += static_cast<char>('A' + static_cast<std::int32_t>(get_letter_dist()(get_rng())));
        name += static_cast<char>('A' + static_cast<std::int32_t>(get_letter_dist()(get_rng())));
        for(std::uint8_t i = 0U; i < 3U; ++i) {
            name += static_cast<char>('0' + static_cast<std::int32_t>(get_digit_dist()(get_rng())));
        }
        return name;
    }
}

std::unordered_set<std::string>& robot::used_names() {
    static std::unordered_set<std::string> s_used_names{};
    return s_used_names;
}

robot::robot()
    : m_name("")
{
    assign_name();
}

robot::~robot()
{
    if(!m_name.empty()) {
        std::lock_guard<std::mutex> lock(get_mutex());
        (void)used_names().erase(m_name);
    }
}

robot::robot(robot&& other) noexcept
    : m_name(std::move(other.m_name))
{
    other.m_name.clear();
}

robot& robot::operator=(robot&& other) noexcept
{
    if(this != &other) {
        std::lock_guard<std::mutex> lock(get_mutex());
        if(!m_name.empty()) {
            (void)used_names().erase(m_name);
        }
        m_name = std::move(other.m_name);
        other.m_name.clear();
    }
    return *this;
}

std::string robot::name() const
{
    return m_name;
}

void robot::reset()
{
    std::lock_guard<std::mutex> lock(get_mutex());
    if(!m_name.empty()) {
        (void)used_names().erase(m_name);
    }
    m_name.clear();
    assign_name();
}

void robot::assign_name()
{
    std::lock_guard<std::mutex> lock(get_mutex());
    std::string new_name;
    do {
        new_name = generate_name();
    } while(used_names().find(new_name) != used_names().end());
    m_name = new_name;
    (void)used_names().insert(m_name);
}

}  // namespace robot_name
