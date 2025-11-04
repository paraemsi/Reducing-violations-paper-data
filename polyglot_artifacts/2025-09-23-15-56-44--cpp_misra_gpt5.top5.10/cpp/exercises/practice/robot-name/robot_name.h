#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class robot final {
public:
    robot();

    std::string name() const;

    void reset();

private:
    std::string current_name_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
