#if !defined(CLOCK_H)
#define CLOCK_H
#include <cstdint>
#include <string>

namespace date_independent {

class Clock final
{
public:
    static Clock at(std::int32_t hour,
                    std::int32_t minute = static_cast<std::int32_t>(0));

    [[nodiscard]] Clock plus(std::int32_t minutes) const noexcept;
    [[nodiscard]] Clock minus(std::int32_t minutes) const noexcept;

    [[nodiscard]] std::string to_string() const;
    [[nodiscard]] operator std::string() const noexcept;

    friend bool operator==(const Clock& lhs, const Clock& rhs) noexcept;
    friend bool operator!=(const Clock& lhs, const Clock& rhs) noexcept;

private:
    explicit Clock(std::int32_t total_minutes) noexcept;

    void adjust(std::int32_t delta) noexcept;

    static constexpr std::int32_t kMinutesPerDay =
        static_cast<std::int32_t>(1440);

    std::int32_t minutes_;
};

}  // namespace date_independent

/* Provide API expected by tests: date_independent::clock::at(...) */

namespace date_independent::clock
{
using Clock = date_independent::Clock;

inline Clock at(std::int32_t hour,
                std::int32_t minute = static_cast<std::int32_t>(0))
{
    return Clock::at(hour, minute);
}
} // namespace date_independent::clock

#endif // CLOCK_H
