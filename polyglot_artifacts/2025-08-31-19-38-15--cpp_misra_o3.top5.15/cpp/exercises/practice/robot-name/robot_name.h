#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H
#include <string>

namespace robot_name {

class Robot final
{
public:
    Robot() = default;
    ~Robot() noexcept;

    /* Return the robot’s name, generating it on first call */
    auto name() const -> const std::string&;

    /* Reset the robot to factory-settings (clears its name) */
    void reset();

private:
    mutable std::string m_name;

    static auto generate_unique_name() -> std::string;
};

/* Provide the lowercase alias expected by the tests */
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
