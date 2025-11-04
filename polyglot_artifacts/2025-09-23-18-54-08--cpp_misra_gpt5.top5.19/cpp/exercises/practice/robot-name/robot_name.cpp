#include "robot_name.h"

#include <array>
#include <cstdint>
#include <cstddef>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>
#include <utility>

namespace {

using robot_name::robot;

class NameUniquer final {
public:
    NameUniquer() = default;
    NameUniquer(const NameUniquer&) = delete;
    NameUniquer& operator=(const NameUniquer&) = delete;

    std::string next_unique()
    {
        for (;;) {
            std::string candidate = generate();
            {
                std::lock_guard<std::mutex> lock(mutex_);
                const auto insert_result = used_.insert(candidate);
                if (insert_result.second) {
                    return *(insert_result.first);
                }
            }
        }
    }

    void release(const std::string& name)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        (void)used_.erase(name);
    }

private:
    static std::mt19937& rng()
    {
        static std::mt19937 eng((std::random_device()()));
        return eng;
    }

    static std::uint32_t random_index(const std::uint32_t max_exclusive)
    {
        // Precondition: max_exclusive > 0
        std::uniform_int_distribution<std::uint32_t> dist(0U, (max_exclusive - 1U));
        return dist(rng());
    }

    static std::string generate()
    {
        static constexpr std::array<char, 26U> letters = {
            'A','B','C','D','E','F','G','H','I','J','K','L','M',
            'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
        };
        static constexpr std::array<char, 10U> digits = {
            '0','1','2','3','4','5','6','7','8','9'
        };
        static constexpr std::uint32_t letter_count = 26U;
        static constexpr std::uint32_t digit_count = 10U;

        std::string out;
        out.reserve(5U);

        const std::uint32_t i0 = random_index(letter_count);
        const std::uint32_t i1 = random_index(letter_count);
        out.push_back(letters[static_cast<std::size_t>(i0)]);
        out.push_back(letters[static_cast<std::size_t>(i1)]);

        const std::uint32_t d0 = random_index(digit_count);
        const std::uint32_t d1 = random_index(digit_count);
        const std::uint32_t d2 = random_index(digit_count);
        out.push_back(digits[static_cast<std::size_t>(d0)]);
        out.push_back(digits[static_cast<std::size_t>(d1)]);
        out.push_back(digits[static_cast<std::size_t>(d2)]);

        return out;
    }

    std::mutex mutex_{};
    std::unordered_set<std::string> used_{};
};

NameUniquer& name_uniquer()
{
    static NameUniquer instance{};
    return instance;
}

} // unnamed namespace

namespace robot_name {

robot::robot()
    : name_(name_uniquer().next_unique())
{
}

const std::string& robot::name() const
{
    return name_;
}

void robot::reset()
{
    name_ = name_uniquer().next_unique();
}

}  // namespace robot_name
