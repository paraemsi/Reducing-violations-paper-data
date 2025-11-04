#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot final {
public:
    robot();
    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;
    robot(robot&&) = delete;
    robot& operator=(robot&&) = delete;
    std::string name() const;
    void reset();

private:
    static std::string generate_unique_name(const std::string& exclude);
    mutable std::string current_name_;
    mutable std::string last_name_to_avoid_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
