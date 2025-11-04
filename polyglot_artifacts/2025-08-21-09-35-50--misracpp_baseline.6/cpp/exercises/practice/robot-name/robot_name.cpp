#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <mutex>
#include <cctype>
#include <chrono>

namespace robot_name {

namespace {
    // Thread-safe set of used names
    std::unordered_set<std::string> used_names;
    std::mutex used_names_mutex;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> letter_dist('A', 'Z');
    std::uniform_int_distribution<> digit_dist(0, 9);

    std::string random_name() {
        std::string name;
        name += static_cast<char>(letter_dist(gen));
        name += static_cast<char>(letter_dist(gen));
        for (int i = 0; i < 3; ++i) {
            name += static_cast<char>('0' + digit_dist(gen));
        }
        return name;
    }
}

class NameRegistry {
public:
    static bool is_name_taken(const std::string& name) {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        return used_names.find(name) != used_names.end();
    }

    static void register_name(const std::string& name) {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        used_names.insert(name);
    }

    static void unregister_name(const std::string& name) {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        used_names.erase(name);
    }

private:
    static std::unordered_set<std::string> used_names;
    static std::mutex used_names_mutex;
};

std::unordered_set<std::string> NameRegistry::used_names;
std::mutex NameRegistry::used_names_mutex;

Robot::Robot() : m_name("") {}

const std::string& Robot::name() {
    if (m_name.empty()) {
        generate_name();
    }
    return m_name;
}

void Robot::reset() {
    if (!m_name.empty()) {
        NameRegistry::unregister_name(m_name);
        m_name.clear();
    }
}

void Robot::generate_name() {
    std::string new_name;
    do {
        new_name = random_name();
    } while (NameRegistry::is_name_taken(new_name));
    m_name = new_name;
    NameRegistry::register_name(m_name);
}

}  // namespace robot_name
