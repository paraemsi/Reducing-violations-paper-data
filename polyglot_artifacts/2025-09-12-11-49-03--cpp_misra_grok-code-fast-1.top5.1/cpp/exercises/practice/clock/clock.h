#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>

namespace date_independent {

class clock {
public:
    static clock at(std::int32_t hour, std::int32_t minute);
    clock plus(std::int32_t minutes) const;
    clock minus(std::int32_t minutes) const;
    bool operator==(const clock& other) const;
    std::int32_t get_hours() const;
    std::int32_t get_minutes() const;

private:
    clock(std::int32_t hours, std::int32_t minutes);
    std::int32_t total_minutes;
};

}  // namespace date_independent

#endif // CLOCK_H
