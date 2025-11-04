#include "robot_name.h"

#include <array>
#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
    auto registry_mutex() -> std::mutex& {
        static std::mutex mtx;
        return mtx;
    }

    auto used_names() -> std::unordered_set<std::string>& {
        static std::unordered_set<std::string> set;
        return set;
    }

    auto rng() -> std::mt19937& {
        static std::mt19937 engine([]() {
            std::random_device rd;
            std::array<std::uint32_t, 8U> seeds{};
            for (std::size_t i = 0U; i < seeds.size(); i++) {
                seeds[i] = static_cast<std::uint32_t>(rd());
            }
            std::seed_seq seq(seeds.begin(), seeds.end());
            return std::mt19937(seq);
        }());
        return engine;
    }

    auto generate_unique_name() -> std::string {
        static const std::array<char, 26U> letters = {
            'A','B','C','D','E','F','G','H','I','J','K','L','M',
            'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
        };
        static const std::array<char, 10U> digits = {
            '0','1','2','3','4','5','6','7','8','9'
        };

        std::uniform_int_distribution<std::uint32_t> letter_dist(
            static_cast<std::uint32_t>(0),
            static_cast<std::uint32_t>(25)
        );
        std::uniform_int_distribution<std::uint32_t> digit_dist(
            static_cast<std::uint32_t>(0),
            static_cast<std::uint32_t>(9)
        );

        for (;;) {
            std::string candidate;
            candidate.reserve(static_cast<std::size_t>(5));

            candidate.push_back(letters[letter_dist(rng())]);
            candidate.push_back(letters[letter_dist(rng())]);
            candidate.push_back(digits[digit_dist(rng())]);
            candidate.push_back(digits[digit_dist(rng())]);
            candidate.push_back(digits[digit_dist(rng())]);

            {
                std::lock_guard<std::mutex> lock(registry_mutex());
                auto& set = used_names();
                if ((set.find(candidate) == set.end())) {
                    (void)set.insert(candidate);
                    return candidate;
                } else {
                    // Collision; try again
                }
            }
        }
    }
}  // namespace

robot::robot() noexcept = default;





robot::~robot() noexcept {
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(registry_mutex());
        (void)used_names().erase(m_name);
    } else {
        // No assigned name to release
    }
}

auto robot::name() const -> const std::string& {
    if (m_name.empty()) {
        m_name = generate_unique_name();
    } else {
        // Name already assigned
    }
    return m_name;
}

void robot::reset() {
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(registry_mutex());
        (void)used_names().erase(m_name);
        m_name.clear();
    } else {
        // Nothing to reset
    }
}

}  // namespace robot_name
