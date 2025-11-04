#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

class clock {
public:
    clock(int hour, int minute);
    static clock at(int hour, int minute);

    clock plus(int minutes) const;
    clock minus(int minutes) const;

    operator std::string() const;
    std::string str() const;

private:
    int minutes_from_midnight_;
    static int normalize_minutes(int minutes);

    friend bool operator==(const clock& lhs, const clock& rhs);
    friend bool operator!=(const clock& lhs, const clock& rhs);
};

}  // namespace date_independent

#endif // CLOCK_H
