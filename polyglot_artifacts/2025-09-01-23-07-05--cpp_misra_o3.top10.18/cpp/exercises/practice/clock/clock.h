#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock
{
public:
    static clock at(std::int32_t hour,
                    std::int32_t minute = static_cast<std::int32_t>(0));

    clock plus(std::int32_t minute_delta) const;
    clock minus(std::int32_t minute_delta) const;

    friend bool operator==(const clock &lhs, const clock &rhs);
    friend bool operator!=(const clock &lhs, const clock &rhs);

    explicit operator std::string() const;

private:
    explicit clock(std::int32_t total_minutes);

    std::int32_t m_total_minutes;
};

}  // namespace date_independent

#endif // CLOCK_H
