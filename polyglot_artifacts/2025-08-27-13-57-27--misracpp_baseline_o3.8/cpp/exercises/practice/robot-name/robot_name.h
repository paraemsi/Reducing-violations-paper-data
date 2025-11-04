#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

// A robot has a unique, randomly generated name.
// Format: two capital letters followed by three digits, e.g. "RX837".
class Robot {
public:
    Robot();
    ~Robot();

    Robot(const Robot&) = delete;
    Robot& operator=(const Robot&) = delete;
    Robot(Robot&&) = delete;
    Robot& operator=(Robot&&) = delete;

    // Return the current name. Guaranteed to be unique among all live robots.
    const std::string& name() const;

    // Reset the robot to factory settings. The next call to name() will return
    // a new, unique, randomly generated identifier.
    void reset();

private:
    std::string _name;

    // Internal helpers for name generation and bookkeeping.
    static std::string generate_unique_name();
    static bool is_name_unique(const std::string& candidate);
    static void register_name(const std::string& new_name);
    static void unregister_name(const std::string& old_name);
};

/*
 * Provide an alias expected by the test-suite.  The tests refer to
 * `robot_name::robot`, so expose `robot` as an alias of our `Robot`
 * class while preserving the existing implementation and naming.
 */
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
