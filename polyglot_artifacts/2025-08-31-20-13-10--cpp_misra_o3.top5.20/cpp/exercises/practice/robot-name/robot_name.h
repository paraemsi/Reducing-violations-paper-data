#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class robot
{
public:
    robot();

    const std::string& name() const noexcept;
    void reset();

    robot(const robot&) = delete;
    robot(robot&&) = delete;
    robot& operator=(const robot&) = delete;
    robot& operator=(robot&&) = delete;

private:
    std::string m_name;

    static std::string generate_unique_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
