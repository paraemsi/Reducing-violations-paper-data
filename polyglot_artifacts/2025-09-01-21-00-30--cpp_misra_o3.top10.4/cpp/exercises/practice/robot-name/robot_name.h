#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <cstdint>
#include <string>

namespace robot_name {

class Robot {
public:
    Robot() = default;
    Robot(const Robot&) = delete;
    Robot(Robot&&) noexcept = delete;
    Robot& operator=(const Robot&) = delete;
    Robot& operator=(Robot&&) noexcept = delete;
    ~Robot();

    const std::string& name() const;
    void reset();

private:
    static std::string generate_unique_name();

    mutable std::string m_name{};
};

using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
