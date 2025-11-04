#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    clock(int hour = 0, int minute = 0);
    static clock at(int hour, int minute);

    clock plus(int minutes) const;
    clock minus(int minutes) const;

    std::string to_string() const;
    explicit operator std::string() const { return to_string(); }

    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);

private:
    int minutes_{0};
    static int normalize_minutes(int total_minutes);
};

}  // namespace date_independent

#endif // CLOCK_H
