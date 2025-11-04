#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock final {
public:
    // Factory method – create a clock set to the specified hour/minute
    static clock at(std::int32_t hour, std::int32_t minute = static_cast<std::int32_t>(0));

    // Add minutes and return a new clock instance
    clock plus(std::int32_t minutes) const;

    // Subtract minutes and return a new clock instance
    clock minus(std::int32_t minutes) const;

    // Get "HH:MM" string representation
    std::string to_string() const;

    // Implicit conversion to "HH:MM" string
    operator std::string() const;

    // Equality
    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    explicit clock(std::int32_t total_minutes);

    static std::int32_t normalize(std::int32_t total_minutes);

    std::int32_t m_total_minutes;
};  // class clock

}  // namespace date_independent

#endif // CLOCK_H
