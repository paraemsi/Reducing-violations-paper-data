#if !defined(MEETUP_H)
#define MEETUP_H

#include <string>
#include <cstdint>

namespace meetup {

class scheduler {
public:
    scheduler(std::int32_t year, std::int32_t month);
    
    // Teenth days
    std::int32_t monteenth() const;
    std::int32_t tuesteenth() const;
    std::int32_t wednesteenth() const;
    std::int32_t thursteenth() const;
    std::int32_t friteenth() const;
    std::int32_t saturteenth() const;
    std::int32_t sunteenth() const;
    
    // First week days
    std::int32_t first_monday() const;
    std::int32_t first_tuesday() const;
    std::int32_t first_wednesday() const;
    std::int32_t first_thursday() const;
    std::int32_t first_friday() const;
    std::int32_t first_saturday() const;
    std::int32_t first_sunday() const;
    
    // Second week days
    std::int32_t second_monday() const;
    std::int32_t second_tuesday() const;
    std::int32_t second_wednesday() const;
    std::int32_t second_thursday() const;
    std::int32_t second_friday() const;
    std::int32_t second_saturday() const;
    std::int32_t second_sunday() const;
    
    // Third week days
    std::int32_t third_monday() const;
    std::int32_t third_tuesday() const;
    std::int32_t third_wednesday() const;
    std::int32_t third_thursday() const;
    std::int32_t third_friday() const;
    std::int32_t third_saturday() const;
    std::int32_t third_sunday() const;
    
    // Fourth week days
    std::int32_t fourth_monday() const;
    std::int32_t fourth_tuesday() const;
    std::int32_t fourth_wednesday() const;
    std::int32_t fourth_thursday() const;
    std::int32_t fourth_friday() const;
    std::int32_t fourth_saturday() const;
    std::int32_t fourth_sunday() const;
    
    // Last week days
    std::int32_t last_monday() const;
    std::int32_t last_tuesday() const;
    std::int32_t last_wednesday() const;
    std::int32_t last_thursday() const;
    std::int32_t last_friday() const;
    std::int32_t last_saturday() const;
    std::int32_t last_sunday() const;

private:
    std::int32_t year_;
    std::int32_t month_;
    std::int32_t find_day(const std::string& week, const std::string& weekday) const;
};

}  // namespace meetup

#endif // MEETUP_H
