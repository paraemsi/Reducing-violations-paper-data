#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <array>
#include <cstdint>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

class Robot {
public:
    Robot();

    /*--------------------------------------------------------------------
     * Return the current robot name.  Generates one on first call.
     *------------------------------------------------------------------*/
    const std::string& name() const;

    /*--------------------------------------------------------------------
     * Reset the robot to factory settings – clears the current name.
     *------------------------------------------------------------------*/
    void reset();

private:
    mutable std::string name_;

    /*--------------------------------------------------------------------
     * Helper – create a new unique name.
     *------------------------------------------------------------------*/
    static std::string generate_unique_name();

    /*--------------------------------------------------------------------
     * Global resources shared by every Robot instance.
     *------------------------------------------------------------------*/
    static std::unordered_set<std::string> used_names_;
    static std::mt19937_64                     rng_;
};

/*------------------------------------------------------------------------
 * Alias to satisfy tests that expect type `robot_name::robot`.
 *------------------------------------------------------------------------*/
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
