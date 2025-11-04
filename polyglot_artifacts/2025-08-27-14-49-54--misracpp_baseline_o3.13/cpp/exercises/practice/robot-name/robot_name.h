#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H
#include <string>

namespace robot_name {

class Robot {
public:
    Robot();
    ~Robot();

    // Disallow copying to maintain unique names
    Robot(const Robot&) = delete;
    Robot& operator=(const Robot&) = delete;

    // Returns the robot's current name. Generates one on first call.
    const std::string& name() const;

    // Reset to factory settings – discard current name and assign a new, unique one.
    void reset();

private:
    std::string name_;
    static std::string generate_unique_name();
};

using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
