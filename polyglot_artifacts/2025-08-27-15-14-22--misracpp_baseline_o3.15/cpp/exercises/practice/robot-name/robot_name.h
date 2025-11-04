#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    const std::string& name() const;
    void reset();

private:
    void allocate_unique_name();
    std::string name_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
