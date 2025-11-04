#ifndef ROBOT_NAME_H
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <mutex>
#include <array>
#include <cstdint>

namespace robot_name {

class Robot final {
public:
    Robot();
    ~Robot();

    Robot(const Robot&) = delete;
    Robot& operator=(const Robot&) = delete;
    Robot(Robot&&) = delete;
    Robot& operator=(Robot&&) = delete;

    const std::string& name() const noexcept;

    void reset();

private:
    std::string _name;

    static std::string generate_name();

    static std::unordered_set<std::string> s_used_names;
    static std::mutex s_names_mutex;
};

using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
