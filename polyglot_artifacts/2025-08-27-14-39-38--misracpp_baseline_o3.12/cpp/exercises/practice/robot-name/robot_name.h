#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H
#include <string>
#include <unordered_set>
#include <random>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();

    // Robots have unique identities; disable copy and move semantics.
    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;
    robot(robot&&) = delete;
    robot& operator=(robot&&) = delete;

    // Return the robot's current name.
    const std::string& name() const;

    // Reset the robot to factory settings (clears name and assigns a new one).
    void reset();

private:
    std::string _name;

    // Static helpers/containers shared by every robot instance.
    static std::unordered_set<std::string> used_names;
    static std::mt19937 rng;

    // Generate a unique robot name (AA000-ZZ999, non-repeating among live robots).
    static std::string generate_unique_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
