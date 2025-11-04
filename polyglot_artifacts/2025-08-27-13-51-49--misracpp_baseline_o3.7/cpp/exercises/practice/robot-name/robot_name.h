#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <random>

namespace robot_name {

class robot {
public:
    robot();
    const std::string& name() const;
    void reset();

private:
    std::string _name;

    static std::mt19937& generator();
    static std::string generate_name();
    static std::unordered_set<std::string> used_names;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
