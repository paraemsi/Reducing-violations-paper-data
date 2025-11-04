#ifndef ROBOT_NAME_H
#define ROBOT_NAME_H

#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

class Robot {
public:
    Robot();

    // Return robot's name, generating a unique one on first call (or after reset).
    const std::string& name() const;

    // Reset to factory settings; the next call to name() produces a new one.
    void reset();

private:
    mutable std::string name_;

    static std::string generate_name();

    static std::unordered_set<std::string> used_names_;
    static std::mt19937 rng_;
};

using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
