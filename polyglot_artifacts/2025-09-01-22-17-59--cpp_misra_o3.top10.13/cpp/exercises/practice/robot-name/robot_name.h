#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class Robot final
{
public:
    Robot();
    ~Robot();

    /* A Robot owns a unique name – copying or moving would
       require complex name-handover logic, therefore it is
       explicitly prohibited. */
    Robot(const Robot&)            = delete;
    Robot& operator=(const Robot&) = delete;
    Robot(Robot&&)                 = delete;
    Robot& operator=(Robot&&)      = delete;

    const std::string& name() const;
    void reset();

private:
    std::string m_name;
    static std::string generate_unique_name();
};

/* Provide the lowercase alias expected by the test-suite. */
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
