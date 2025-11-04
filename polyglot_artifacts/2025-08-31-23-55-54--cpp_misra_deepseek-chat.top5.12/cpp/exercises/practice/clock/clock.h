#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>
#include <cstdint>

namespace date_independent {
    // Alias for fixed-width integer type
    using minute_t = std::int32_t;
    
    class clock {
    private:
        minute_t total_minutes;
        explicit clock(minute_t minutes);
    public:
        static clock at(minute_t hours, minute_t minutes);
        clock plus(minute_t minutes) const;
        clock minus(minute_t minutes) const;
        operator std::string() const;
        bool operator==(const clock& other) const;
        bool operator!=(const clock& other) const;
    };
}  // namespace date_independent

#endif // CLOCK_H
