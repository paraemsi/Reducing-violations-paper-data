#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H
#include <string>
#include <cstdint>

namespace robot_name {

class Robot
{
public:
    Robot() = default;

    // Returns the robot's name, generating one if necessary
    const std::string& name() noexcept;

    // Reset the robot to factory settings (clears its current name)
    void reset();

private:
    // Produce a globally-unique random name
    static std::string generate_unique_name();

    std::string m_name{};
};

// Alias to match test expectation of `robot_name::robot`
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
