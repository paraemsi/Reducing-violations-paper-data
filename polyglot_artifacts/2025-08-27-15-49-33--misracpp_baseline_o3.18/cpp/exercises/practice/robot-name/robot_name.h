#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <random>
#include <mutex>

namespace robot_name {

class Robot {
public:
    Robot() = default;

    // Returns the robot's current name, generating a new one on first call.
    const std::string& name() const;

    // Resets the robot to factory settings so the next call to name()
    // will provide a fresh, unique, randomly-generated name.
    void reset();

private:
    mutable std::string m_name;

    // Generates a unique robot name and registers it.
    static std::string generate_unique_name();

    // Registry of names currently in use.
    static std::unordered_set<std::string> used_names_;

    // Shared RNG engine.
    static std::mt19937 rng_;
    static std::mutex mutex_;
};

// Alias expected by the test suite
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
