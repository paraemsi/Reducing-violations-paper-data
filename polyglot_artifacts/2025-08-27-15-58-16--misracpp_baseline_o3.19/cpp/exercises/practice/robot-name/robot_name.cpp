#include "robot_name.h"

#include <random>
#include <unordered_set>
#include <mutex>
#include <array>

namespace {

std::mt19937& rng() {
    static std::mt19937 engine{std::random_device{}()};
    return engine;
}

std::unordered_set<std::string>& used_names() {
    static std::unordered_set<std::string> names;
    return names;
}

std::mutex& names_mutex() {
    static std::mutex mtx;
    return mtx;
}

std::string generate_name_internal() {
    std::uniform_int_distribution<int> letter_dist('A', 'Z');
    std::uniform_int_distribution<int> digit_dist(0, 9);
    std::array<char, 6> buf{};
    buf[0] = static_cast<char>(letter_dist(rng()));
    buf[1] = static_cast<char>(letter_dist(rng()));
    buf[2] = static_cast<char>('0' + digit_dist(rng()));
    buf[3] = static_cast<char>('0' + digit_dist(rng()));
    buf[4] = static_cast<char>('0' + digit_dist(rng()));
    buf[5] = '\0';
    return std::string(buf.data());
}

} // anonymous namespace

namespace robot_name {

Robot::Robot() = default;

const std::string& Robot::name() const {
    if (m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void Robot::reset() {
    std::lock_guard<std::mutex> lock(names_mutex());
    if (!m_name.empty()) {
        used_names().erase(m_name);
        m_name.clear();
    }
}

std::string Robot::generate_unique_name() {
    std::string candidate;
    std::lock_guard<std::mutex> lock(names_mutex());
    do {
        candidate = generate_name_internal();
    } while (used_names().find(candidate) != used_names().end());
    used_names().insert(candidate);
    return candidate;
}

}  // namespace robot_name
