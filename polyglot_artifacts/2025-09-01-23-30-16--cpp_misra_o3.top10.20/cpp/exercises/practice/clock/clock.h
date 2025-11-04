#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock
{
public:
    // Construct a clock set to the given hour and minute.
    // Values outside their normal ranges are tolerated and normalised.
    [[nodiscard]] static clock at(std::int32_t hour,
                                  std::int32_t minute = static_cast<std::int32_t>(0)) noexcept;

    // Return a new clock advanced by the supplied number of minutes.
    [[nodiscard]] clock plus(std::int32_t minutes) const noexcept;

    // Format as "HH:MM".
    [[nodiscard]] std::string to_string() const;
    operator std::string() const { return to_string(); }

    // Equality – implemented as non-member friend functions to preserve symmetry.
    friend bool operator==(const clock& lhs, const clock& rhs) noexcept;
    friend bool operator!=(const clock& lhs, const clock& rhs) noexcept;

private:
    explicit clock(std::int32_t canonical_minutes) noexcept;

    // Minutes past midnight, guaranteed in the range [0, 1439].
    std::int32_t m_minutes;
};

}  // namespace date_independent

#endif // CLOCK_H
