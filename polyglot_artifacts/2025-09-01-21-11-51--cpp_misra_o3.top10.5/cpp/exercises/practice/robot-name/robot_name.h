#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <random>
#include <array>
#include <cstdint>
#include <cstddef>

namespace robot_name {

class Robot {
public:
    Robot();
    ~Robot() noexcept = default;

    Robot(const Robot&)            = delete;
    Robot& operator=(const Robot&) = delete;
    Robot(Robot&&)                 = delete;
    Robot& operator=(Robot&&)      = delete;

    const std::string& name() const noexcept;

    void reset();

private:
    std::string m_name;

    static std::unordered_set<std::string> s_used_names;

    static std::string generate_unique_name();

    static std::mt19937& prng();
};

/* type-alias required by test harness – keeps original class name intact */
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
