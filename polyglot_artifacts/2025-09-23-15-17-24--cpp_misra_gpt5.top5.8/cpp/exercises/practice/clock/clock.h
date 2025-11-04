#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>
#include <iosfwd>

namespace date_independent {

class clock final {
public:
    static clock at(std::int32_t hours, std::int32_t minutes = 0);
    clock plus(std::int32_t minutes) const;
    clock minus(std::int32_t minutes) const;
    std::string str() const;
    operator std::string() const;
    bool operator==(const clock& other) const;
    bool operator!=(const clock& other) const;

private:
    explicit clock(std::int32_t total_minutes);
    static std::int32_t normalize(std::int32_t total_minutes);

    std::int32_t total_minutes_;
};

std::ostream& operator<<(std::ostream& os, const clock& c);

}  // namespace date_independent

#endif // CLOCK_H
