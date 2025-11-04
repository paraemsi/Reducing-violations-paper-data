#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <mutex>
#include <cstdint>

namespace robot_name {

class Robot final
{
public:
    Robot();

    const std::string& name() const noexcept;

    void reset();

private:
    std::string m_name;

    static std::string generate_unique_name();
    static std::string generate_random_name();
    static bool is_name_unique(const std::string& candidate);
    static void register_name(const std::string& name);

    static std::unordered_set<std::string> s_used_names;
    static std::mutex s_mutex;
};

/* Alias required by legacy tests – do not remove. */
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
