#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class Robot final
{
public:
    Robot();
    ~Robot() noexcept;

    Robot(const Robot&) = delete;
    Robot(Robot&&) = delete;
    Robot& operator=(const Robot&) = delete;
    Robot& operator=(Robot&&) = delete;

    const std::string& name() const;  // lazily generates a unique name on first call
    void reset();               // forget current name, will generate new one next time

private:
    static std::string generate_name();  // helper: create random name candidate

    mutable std::string name_;  // cached robot name (mutable to allow lazy init in const member)
};

// Alias to match expected test type name
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
