#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>
#include <cstdint>

namespace date_independent {

class clock {
private:
    std::int32_t minutes;
    clock(std::int32_t total_minutes);
public:
    static clock at(std::int32_t hours, std::int32_t minutes);
    clock plus(std::int32_t add_minutes) const;
    clock minus(std::int32_t sub_minutes) const;
    operator std::string() const;
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;
};

}  // namespace date_independent

#endif // CLOCK_H
