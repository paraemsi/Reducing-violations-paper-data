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
    std::string name() const;

    // Resets the robot to factory settings (wipes the name)
    void reset();

private:
    std::string m_name;
    static bool is_name_used(const std::string& candidate); // NOLINT(readability-convert-member-functions-to-static)
    static void register_name(const std::string& name);     // NOLINT(readability-convert-member-functions-to-static)
    static void unregister_name(const std::string& name);   // NOLINT(readability-convert-member-functions-to-static)
    static std::string generate_unique_name();              // NOLINT(readability-convert-member-functions-to-static)
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
