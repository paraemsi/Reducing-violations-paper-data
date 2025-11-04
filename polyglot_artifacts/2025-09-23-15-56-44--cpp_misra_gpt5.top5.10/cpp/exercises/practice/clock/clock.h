#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock {
public:
    explicit clock(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0));

    static clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0));

    clock plus(std::int32_t minutes) const;

    clock minus(std::int32_t minutes) const;

    std::string str() const;

    operator std::string() const;

    bool operator==(const clock& other) const;

    bool operator!=(const clock& other) const;

private:
    std::int32_t minutes_;

    static std::int32_t normalize(std::int32_t minutes);
};

clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0));

}  // namespace date_independent

#endif // CLOCK_H
