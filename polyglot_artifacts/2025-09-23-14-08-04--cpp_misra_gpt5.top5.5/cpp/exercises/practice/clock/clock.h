#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock final {
public:
    static clock at(std::int32_t hour, std::int32_t minute = 0);
    clock plus(std::int32_t minute_delta) const;
    operator std::string() const;
    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;

private:
    explicit clock(std::int32_t total_minutes);
    static std::int32_t normalize_total_minutes(std::int32_t total_minutes) noexcept;

    std::int32_t total_minutes_;
};

}  // namespace date_independent

#endif // CLOCK_H
