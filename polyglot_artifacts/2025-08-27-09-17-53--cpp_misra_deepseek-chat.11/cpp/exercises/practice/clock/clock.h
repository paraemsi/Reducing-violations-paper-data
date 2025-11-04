#if !defined(CLOCK_H)
#define CLOCK_H

#include <cstdint>
#include <string>

namespace date_independent {
    class clock {
    private:
        std::int32_t minutes_since_midnight;
        clock(std::int32_t minutes);
    public:
        static clock at(std::int32_t hours, std::int32_t minutes);
        clock plus(std::int32_t minutes_to_add) const;
        clock minus(std::int32_t minutes_to_subtract) const;
        operator std::string() const;
        bool operator==(const clock& other) const;
        bool operator!=(const clock& other) const;
    };
}  // namespace date_independent

#endif // CLOCK_H
