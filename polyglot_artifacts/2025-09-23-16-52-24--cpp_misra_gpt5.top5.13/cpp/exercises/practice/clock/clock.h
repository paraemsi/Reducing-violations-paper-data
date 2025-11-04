#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock final {
public:
    // Special member functions
    clock(const clock&) = default;
    clock(clock&&) noexcept = default;
    clock& operator=(const clock&) = default;
    clock& operator=(clock&&) noexcept = default;
    ~clock() = default;

    std::string str() const;
    std::string to_string() const;
    clock plus(std::int32_t minutes) const;

    explicit operator std::string() const;

    static clock at(std::int32_t hour, std::int32_t minute);
    static clock at(std::int32_t hour);

    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    explicit clock(std::int32_t total_minutes);
    std::int32_t minutes_since_midnight;
};


clock at(std::int32_t hour, std::int32_t minute);
clock at(std::int32_t hour);

}  // namespace date_independent

#endif // CLOCK_H
