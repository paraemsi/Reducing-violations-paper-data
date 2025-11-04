#if !defined(CLOCK_H)
#define CLOCK_H
#include <cstdint>
#include <string>
#include <ostream>

namespace date_independent {

class clock
{
public:
    // Construct a clock representing the given hour/minute
    static clock at(std::int32_t hour,
                    std::int32_t minute = static_cast<std::int32_t>(0));

    // Return a new clock advanced by the supplied number of minutes
    clock plus(std::int32_t minutes) const;

    // Return a new clock moved backwards by the supplied number of minutes
    clock minus(std::int32_t minutes) const;

    // Equality / inequality
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

    // Formatted "HH:MM" representation
    std::string to_string() const;
    operator std::string() const;

private:
    explicit clock(std::int32_t total_minutes);

    static std::int32_t normalize(std::int32_t minutes);

    std::int32_t minutes_;
};

std::ostream& operator<<(std::ostream& os, const clock& clk);

}  // namespace date_independent

#endif // CLOCK_H
