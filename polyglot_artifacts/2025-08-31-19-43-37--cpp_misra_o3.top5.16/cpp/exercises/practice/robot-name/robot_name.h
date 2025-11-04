#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <random>
#include <cstdint>
#include <mutex>

namespace robot_name {

class robot {
public:
    robot();

    const std::string& name() const;

    void reset();

private:
    mutable std::string m_name;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
