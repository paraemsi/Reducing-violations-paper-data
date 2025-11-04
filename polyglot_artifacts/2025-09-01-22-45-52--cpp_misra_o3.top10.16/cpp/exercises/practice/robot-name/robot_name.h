#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

/*
 * Robot
 * -----
 * Each Robot instance owns a unique name in the form LLDDD
 * (two upper-case ASCII letters followed by three decimal digits).
 * Creating or resetting a robot generates a new unique name.
 */
class robot final
{
public:
    robot();                                   // default construction

    robot(const robot&)            = delete;   // non-copyable
    robot& operator=(const robot&) = delete;

    robot(robot&&)            = default;       // movable
    robot& operator=(robot&&) = default;

    ~robot() = default;

    // Obtain the current robot name (guaranteed non-empty).
    [[nodiscard]] const std::string& name() const;

    // Reset the robot to factory settings – assigns a new unique name.
    void reset();

private:
    std::string m_name;

    // Generate a unique name that is not currently in use.
    static std::string generate_unique_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
