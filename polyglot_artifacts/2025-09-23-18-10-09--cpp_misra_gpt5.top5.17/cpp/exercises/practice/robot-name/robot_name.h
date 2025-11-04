#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot final {
public:
    robot();
    std::string name() const;
    void reset();

private:
    static std::string allocate_unique_name();
    static std::string make_random_name();

    mutable std::string m_name{};
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
