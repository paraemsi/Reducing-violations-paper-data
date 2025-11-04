#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class Robot
{
public:
    Robot();

    [[nodiscard]] const std::string& name() const noexcept;
    void reset() noexcept;

private:
    std::string m_name;
    static std::string generate_unique_name() noexcept;
};

using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
