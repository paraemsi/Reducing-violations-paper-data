#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <mutex>

namespace robot_name {

class Robot {
public:
    Robot();
    const std::string& name() const;
    void reset();

private:
    std::string _name;
    static std::string generate_unique_name();
    static std::unordered_set<std::string> used_names;
    static std::mutex mutex_;
};

using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
