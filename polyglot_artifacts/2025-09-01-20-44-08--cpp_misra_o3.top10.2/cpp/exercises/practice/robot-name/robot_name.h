#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class Robot
{
public:
    Robot();
    ~Robot();

    Robot(const Robot&) = delete;
    Robot& operator=(const Robot&) = delete;
    Robot(Robot&&) noexcept;
    Robot& operator=(Robot&&) noexcept;

    [[nodiscard]] std::string name() const;
    void reset();

private:
    std::string generate_unique_name();

    std::string m_name;
};

using robot = Robot;   // alias expected by tests

}  // namespace robot_name

#endif // ROBOT_NAME_H
