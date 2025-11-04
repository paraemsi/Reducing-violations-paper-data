#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {

class clock final {
public:
    using minute_t = std::int32_t;

    static clock at(minute_t hour, minute_t minute = static_cast<minute_t>(0));

    clock plus(minute_t minutes) const;

    [[nodiscard]] std::string to_string() const;

    [[nodiscard]] operator std::string() const;

    [[nodiscard]] bool operator==(const clock& other) const;

    [[nodiscard]] bool operator!=(const clock& other) const;

private:
    minute_t total_minutes_;

    explicit clock(minute_t total_minutes);

    static minute_t normalize(minute_t minutes);
};

[[nodiscard]] std::string string(const clock& c);

}  // namespace date_independent

#endif // CLOCK_H
