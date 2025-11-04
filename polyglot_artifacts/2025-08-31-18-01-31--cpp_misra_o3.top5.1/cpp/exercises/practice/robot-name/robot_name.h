#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class robot {
public:
    robot();

    // Return the current robot name
    [[nodiscard]] const std::string& name() const noexcept;

    // Reset the robot to factory settings – creates a new unique name
    void reset();

private:
    std::string m_name;

    static std::string generate_unique_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
