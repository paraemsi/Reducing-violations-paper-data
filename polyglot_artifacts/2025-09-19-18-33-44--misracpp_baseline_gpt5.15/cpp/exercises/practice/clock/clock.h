#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    clock(int hour, int minute = 0);
    static clock at(int hour, int minute = 0);

    clock plus(int minutes) const;
    clock minus(int minutes) const;

    int hour() const;
    int minute() const;

    explicit operator std::string() const;

    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    int minutes_; // minutes since midnight in [0, 1440)
    static int normalize(int total_minutes) noexcept;
};

// Convenience helper to get "HH:MM"
std::string to_string(const clock& c);

}  // namespace date_independent

#endif // CLOCK_H
