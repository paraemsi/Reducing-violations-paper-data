#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <mutex>

namespace robot_name {

class robot {
public:
    robot();
    std::string name() const;
    void reset();

private:
    static std::string generate_unique_name();
    mutable std::mutex name_mutex_;
    mutable std::string name_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
