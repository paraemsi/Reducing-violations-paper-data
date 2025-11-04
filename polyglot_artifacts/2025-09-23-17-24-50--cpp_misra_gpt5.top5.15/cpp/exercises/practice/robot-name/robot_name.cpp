#include "robot_name.h"

#include <array>
#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace {
    std::unordered_set<std::string>& used_names() {
        static std::unordered_set<std::string> set;
        return set;
    }

    std::mutex& names_mutex() {
        static std::mutex m;
        return m;
    }

    std::mt19937& rng() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    std::uniform_int_distribution<std::uint32_t>& letter_dist() {
        static std::uniform_int_distribution<std::uint32_t> dist(0U, 25U);
        return dist;
    }

    std::uniform_int_distribution<std::uint32_t>& digit_dist() {
        static std::uniform_int_distribution<std::uint32_t> dist(0U, 9U);
        return dist;
    }

    std::string make_random_name_locked() {
        // Precondition: caller holds names_mutex()
        static const char letters_data[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        static const char digits_data[11] = "0123456789";

        std::string s;
        s.reserve(5U);

        s.push_back(letters_data[static_cast<std::size_t>(letter_dist()(rng()))]);
        s.push_back(letters_data[static_cast<std::size_t>(letter_dist()(rng()))]);

        for (std::uint32_t i = 0U; (i < 3U); ++i) {
            s.push_back(digits_data[static_cast<std::size_t>(digit_dist()(rng()))]);
        }

        return s;
    }

    std::string allocate_unique_name() {
        for (;;) {
            std::lock_guard<std::mutex> lock(names_mutex());

            std::string candidate = make_random_name_locked();
            auto& set = used_names();
            const auto insert_result = set.insert(candidate);

            if (insert_result.second) {
                return candidate;
            }
        }
    }

    void release_name(const std::string& name) {
        std::lock_guard<std::mutex> lock(names_mutex());
        auto& set = used_names();
        const auto it = set.find(name);
        if ((it != set.end())) {
            (void)set.erase(it);
        }
    }
}  // unnamed namespace

namespace robot_name {

robot::robot() : m_name(allocate_unique_name()) { }

robot::~robot() noexcept {
    if ((!m_name.empty())) {
        release_name(m_name);
    }
}

std::string robot::name() const {
    return m_name;
}

void robot::reset() {
    if ((!m_name.empty())) {
        release_name(m_name);
    }
    m_name = allocate_unique_name();
}

}  // namespace robot_name
