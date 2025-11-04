#include "robot_name.h"

#include <unordered_set>
#include <random>
#include <mutex>
#include <string>
#include <cstdint>
#include <cstddef>

namespace robot_name {

namespace
{
    using string = std::string;

    static std::unordered_set<string> used_names {};
    static std::mutex registry_mutex {};
    static std::random_device rd {};
    static std::mt19937 engine { rd() };

    static constexpr char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static constexpr char digits[] = "0123456789";

    std::string generate_random_name()
    {
        std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
        std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

        string name {};
        name.reserve(5U);

        for (std::uint32_t i = 0U; i < 2U; ++i)
        {
            name.push_back(
                letters[static_cast<std::size_t>(letter_dist(engine))]);
        }

        for (std::uint32_t i = 0U; i < 3U; ++i)
        {
            name.push_back(
                digits[static_cast<std::size_t>(digit_dist(engine))]);
        }

        return name;
    }

    string acquire_unique_name()
    {
        std::lock_guard<std::mutex> lock(registry_mutex);

        string candidate {};

        do
        {
            candidate = generate_random_name();
        } while (used_names.find(candidate) != used_names.end());

        (void)used_names.insert(candidate);

        return candidate;
    }

    void release_name(const string& old_name)
    {
        std::lock_guard<std::mutex> lock(registry_mutex);
        (void)used_names.erase(old_name);
    }

} // unnamed namespace

robot::robot() :
    m_name { acquire_unique_name() }
{
}

[[nodiscard]] const std::string& robot::name() const
{
    return m_name;
}

void robot::reset()
{
    const std::string old_name { m_name };
    release_name(old_name);

    std::string new_name {};

    do
    {
        new_name = acquire_unique_name();
    } while (new_name == old_name);

    m_name = new_name;
}

}  // namespace robot_name
