#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

/*
 * Class Robot
 * -----------
 * Manages a robot’s unique name, ensuring that a newly-powered robot
 * receives a random two-letter/three-digit identifier that is unique
 * among all live Robot instances.  Calling reset() returns the robot
 * to factory settings – its current name is released and the next
 * call to name() will allocate a new unique identifier.
 */
class Robot {
public:
    Robot();                      /* constructs a robot with no name            */
    const std::string& name();    /* returns current name (generates if empty)  */
    void reset();                 /* wipes current name so a new one is chosen  */

private:
    std::string m_name;           /* cached robot name                           */

    static std::string generate_unique_name();

    /* Static resources shared across all robots                */
    static std::unordered_set<std::string> s_usedNames;
    static std::mt19937                        s_rng;
    static std::mutex                          s_mutex;
};
using robot = Robot;    /* alias required for tests expecting type `robot` */

}  // namespace robot_name

#endif // ROBOT_NAME_H
