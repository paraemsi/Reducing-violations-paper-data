#include "robot_name.h"

#include <array>
#include <cstddef>
#include <mutex>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace {

using Mutex = std::mutex;

static Mutex g_mutex{};
static std::unordered_set<std::string> g_used_names{};

static constexpr std::array<char, 26U> kLetters = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

static constexpr std::array<char, 10U> kDigits = {
    '0','1','2','3','4','5','6','7','8','9'
};

static constexpr std::size_t kTotalNames =
    ((static_cast<std::size_t>(26U) * static_cast<std::size_t>(26U)) * static_cast<std::size_t>(1000U));

std::size_t uniform_index(std::random_device& rd, std::size_t bound)
{
    if (bound == static_cast<std::size_t>(0U)) {
        throw std::logic_error("bound must be > 0");
    }

    const std::size_t rmin = static_cast<std::size_t>(std::random_device::min());
    const std::size_t rmax = static_cast<std::size_t>(std::random_device::max());
    const std::size_t range = ((rmax - rmin) + static_cast<std::size_t>(1U));
    const std::size_t bucket_size = (range / bound);

    std::size_t r = static_cast<std::size_t>(0U);
    if (bucket_size == static_cast<std::size_t>(0U)) {
        // Fallback: extremely unlikely for our small bounds; degrade gracefully.
        return (static_cast<std::size_t>(rd()) % bound);
    }

    for (;;) {
        r = (static_cast<std::size_t>(rd()) - rmin);
        const std::size_t limit = (bucket_size * bound);
        if (r < limit) {
            const std::size_t idx = (r / bucket_size);
            return idx;
        }
    }
}

std::string make_candidate(std::random_device& rd)
{
    std::string s{};
    s.reserve(static_cast<std::size_t>(5U));

    const std::size_t li0 = uniform_index(rd, static_cast<std::size_t>(kLetters.size()));
    const std::size_t li1 = uniform_index(rd, static_cast<std::size_t>(kLetters.size()));
    s.push_back(kLetters.at(li0));
    s.push_back(kLetters.at(li1));

    const std::size_t di0 = uniform_index(rd, static_cast<std::size_t>(kDigits.size()));
    const std::size_t di1 = uniform_index(rd, static_cast<std::size_t>(kDigits.size()));
    const std::size_t di2 = uniform_index(rd, static_cast<std::size_t>(kDigits.size()));
    s.push_back(kDigits.at(di0));
    s.push_back(kDigits.at(di1));
    s.push_back(kDigits.at(di2));

    return s;
}

}  // anonymous namespace

namespace robot_name {

robot::robot() = default;

std::string robot::generate_unique_name(const std::string& exclude)
{
    std::random_device rd{};

    for (;;) {
        std::string candidate = make_candidate(rd);

        if ((!exclude.empty()) && (candidate == exclude)) {
            continue;
        }

        {
            std::lock_guard<Mutex> lock(g_mutex);
            if ((g_used_names.size() >= kTotalNames)) {
                throw std::runtime_error("no available robot names left");
            }

            const auto insert_result = g_used_names.insert(candidate);
            if (insert_result.second) {
                return candidate;
            }
        }
        // Collision or excluded; try again.
    }
}

std::string robot::name() const
{
    if (current_name_.empty()) {
        const std::string generated = robot::generate_unique_name(last_name_to_avoid_);
        current_name_ = generated;
        last_name_to_avoid_.clear();
    }
    return current_name_;
}

void robot::reset()
{
    if (!current_name_.empty()) {
        {
            std::lock_guard<Mutex> lock(g_mutex);
            (void)g_used_names.erase(current_name_);
        }
        last_name_to_avoid_ = current_name_;
        current_name_.clear();
    } else {
        last_name_to_avoid_.clear();
    }
}

}  // namespace robot_name
