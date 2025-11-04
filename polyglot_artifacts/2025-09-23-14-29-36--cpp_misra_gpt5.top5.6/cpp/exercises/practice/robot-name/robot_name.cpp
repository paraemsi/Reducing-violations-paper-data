#include "robot_name.h"

#include <cstddef>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
    auto used_names() -> std::unordered_set<std::string>&
    {
        static std::unordered_set<std::string> names{};
        return names;
    }

    auto name_mutex() -> std::mutex&
    {
        static std::mutex m{};
        return m;
    }

    auto random_device_instance() -> std::random_device&
    {
        static std::random_device rd{};
        return rd;
    }

    auto letter_dist() -> std::uniform_int_distribution<std::size_t>&
    {
        static std::uniform_int_distribution<std::size_t> dist(static_cast<std::size_t>(0U), static_cast<std::size_t>(25U));
        return dist;
    }

    auto digit_dist() -> std::uniform_int_distribution<std::size_t>&
    {
        static std::uniform_int_distribution<std::size_t> dist(static_cast<std::size_t>(0U), static_cast<std::size_t>(9U));
        return dist;
    }
}  // namespace

auto robot::generate_name() -> std::string
{
    static const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::string digits = "0123456789";

    std::string candidate{};
    candidate.reserve(static_cast<std::size_t>(5U));

    auto& rd = random_device_instance();

    {
        const std::size_t idx1 = letter_dist()(rd);
        const std::size_t idx2 = letter_dist()(rd);
        candidate.push_back(letters[idx1]);
        candidate.push_back(letters[idx2]);
    }
    {
        const std::size_t d1 = digit_dist()(rd);
        const std::size_t d2 = digit_dist()(rd);
        const std::size_t d3 = digit_dist()(rd);
        candidate.push_back(digits[d1]);
        candidate.push_back(digits[d2]);
        candidate.push_back(digits[d3]);
    }

    return candidate;
}

robot::robot()
    : m_name{}
{
    reset();
}

auto robot::name() const -> const std::string&
{
    return m_name;
}

void robot::reset()
{
    {
        std::lock_guard<std::mutex> lock(name_mutex());
        if ((!m_name.empty())) {
            (void)used_names().erase(m_name);
        }
    }

    std::string new_name{};
    bool inserted = false;
    do
    {
        new_name = generate_name();
        std::lock_guard<std::mutex> lock(name_mutex());
        const auto result = used_names().insert(new_name);
        inserted = result.second;
    } while ((!inserted));

    m_name = new_name;
}

}  // namespace robot_name
