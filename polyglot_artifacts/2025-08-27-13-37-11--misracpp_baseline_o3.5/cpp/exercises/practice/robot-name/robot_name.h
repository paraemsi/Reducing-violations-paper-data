#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>

namespace robot_name {

class robot {
public:
    robot();
    const std::string& name() const;
    void reset();

private:
    std::string name_;

    static std::string generate_name();
    static bool is_name_unique(const std::string& candidate);

    static std::unordered_set<std::string> used_names_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
