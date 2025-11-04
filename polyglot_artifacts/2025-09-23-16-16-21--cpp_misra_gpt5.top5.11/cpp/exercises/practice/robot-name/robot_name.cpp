#include "robot_name.h"

#include <random>
#include <mutex>
#include <unordered_set>
#include <string>

namespace robot_name {

namespace {
    thread_local std::mt19937 rng{std::random_device{}()};

    std::mutex& name_mutex() {
        static std::mutex mtx;
        return mtx;
    }

    std::unordered_set<std::string>& registry() {
        static std::unordered_set<std::string> used;
        return used;
    }

    std::string generate_candidate() {
        static const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static const std::string digits = "0123456789";

        std::uniform_int_distribution<std::size_t> dist_letter(static_cast<std::size_t>(0), (letters.size() - static_cast<std::size_t>(1)));
        std::uniform_int_distribution<std::size_t> dist_digit(static_cast<std::size_t>(0), (digits.size() - static_cast<std::size_t>(1)));

        std::string out;
        out.reserve(5U);

        for (std::uint32_t i = 0U; (i < 2U); ++i) {
            out.push_back(letters[dist_letter(rng)]);
        }
        for (std::uint32_t i = 0U; (i < 3U); ++i) {
            out.push_back(digits[dist_digit(rng)]);
        }

        return out;
    }
}  // namespace

std::string robot::generate_unique_name() {
    for (;;) {
        std::string candidate = generate_candidate();
        std::lock_guard<std::mutex> lock(name_mutex());
        auto& used = registry();
        const auto result = used.insert(candidate);
        if (result.second) {
            return *(result.first);
        }
    }
}

robot::robot()
    : m_name(generate_unique_name()) {
}

const std::string& robot::name() const {
    return m_name;
}

void robot::reset() {
    {
        std::lock_guard<std::mutex> lock(name_mutex());
        auto& used = registry();
        (void)used.erase(m_name);
    }
    m_name = generate_unique_name();
}

}  // namespace robot_name
