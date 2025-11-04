#ifndef ROBOT_NAME_H
#define ROBOT_NAME_H
#include <string>

namespace robot_name {

class Robot
{
public:
    Robot();
    const std::string& name() const;
    void reset();

private:
    static std::string generate_unique_name();
    std::string m_name;
};

/*  Alias expected by the unit-tests.
 *  The tests instantiate a `robot_name::robot`, so expose a
 *  lowercase alias that refers to the canonical `Robot` class.
 */
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
