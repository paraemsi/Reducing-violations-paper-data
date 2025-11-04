#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();

    const std::string& name() const;
    void reset();

private:
    std::string name_;

    static std::string generate_unique_name();
    static std::mt19937& rng();
    static std::unordered_set<std::string>& allocated_names();
    static std::mutex& allocated_mutex();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
