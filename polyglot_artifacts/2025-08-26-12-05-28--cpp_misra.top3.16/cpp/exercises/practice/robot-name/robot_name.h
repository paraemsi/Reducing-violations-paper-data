#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class robot
{
public:
    robot();
    ~robot() = default;

    // Returns the robot's name, generating a new one if needed
    [[nodiscard]] std::string name();

    // Resets the robot to factory settings (wipes the name)
    void reset();

private:
    std::string m_name;
    static bool is_name_used(const std::string& candidate);
    static void register_name(const std::string& name);
    static void unregister_name(const std::string& name);
    static std::string generate_unique_name();

    // Rule-of-five: explicitly delete copy/move constructors and assignment operators
    robot(const robot&) = delete;
    robot(robot&&) = delete;
    robot& operator=(const robot&) = delete;
    robot& operator=(robot&&) = delete;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
