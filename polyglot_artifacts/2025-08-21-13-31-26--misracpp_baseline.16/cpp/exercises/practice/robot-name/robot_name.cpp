#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <mutex>
#include <cctype>

namespace robot_name {

namespace {
    // Thread-safe set of assigned names
    std::unordered_set<std::string> assigned_names;
    std::mutex assigned_names_mutex;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> letter_dist('A', 'Z');
    std::uniform_int_distribution<> digit_dist(0, 9);

    std::string generate_random_name() {
        std::string name;
        name += static_cast<char>(letter_dist(gen));
        name += static_cast<char>(letter_dist(gen));
        for (int i = 0; i < 3; ++i) {
            name += static_cast<char>('0' + digit_dist(gen));
        }
        return name;
    }
}

namespace {
    bool is_name_unique(const std::string& name) {
        std::lock_guard<std::mutex> lock(assigned_names_mutex);
        return assigned_names.find(name) == assigned_names.end();
    }

    void register_name(const std::string& name) {
        std::lock_guard<std::mutex> lock(assigned_names_mutex);
        assigned_names.insert(name);
    }

    void unregister_name(const std::string& name) {
        std::lock_guard<std::mutex> lock(assigned_names_mutex);
        assigned_names.erase(name);
    }
}

robot::robot() : m_name() {}

std::string robot::name() const {
    if (m_name.empty()) {
        // Cast away constness to allow lazy name generation
        const_cast<robot*>(this)->generate_name();
    }
    return m_name;
}

void robot::reset() {
    if (!m_name.empty()) {
        unregister_name(m_name);
        m_name.clear();
    }
}

void robot::generate_name() {
    std::string new_name;
    do {
        new_name = generate_random_name();
    } while (!is_name_unique(new_name));
    register_name(new_name);
    m_name = new_name;
}

}  // namespace robot_name
