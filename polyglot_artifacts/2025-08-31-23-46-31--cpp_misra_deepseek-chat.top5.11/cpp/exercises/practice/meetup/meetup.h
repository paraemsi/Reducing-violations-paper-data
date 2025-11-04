#if !defined(MEETUP_H)
#define MEETUP_H

#include <ctime>
#include <string>

namespace meetup {

class scheduler {
public:
    scheduler(int year, int month);
    
    // Teenth functions
    std::tm monteenth() const;
    std::tm tuesteenth() const;
    std::tm wednesteenth() const;
    std::tm thursteenth() const;
    std::tm friteenth() const;
    std::tm saturteenth() const;
    std::tm sunteenth() const;
    
    // First functions
    std::tm first_monday() const;
    std::tm first_tuesday() const;
    std::tm first_wednesday() const;
    std::tm first_thursday() const;
    std::tm first_friday() const;
    std::tm first_saturday() const;
    std::tm first_sunday() const;
    
    // Second functions
    std::tm second_monday() const;
    std::tm second_tuesday() const;
    std::tm second_wednesday() const;
    std::tm second_thursday() const;
    std::tm second_friday() const;
    std::tm second_saturday() const;
    std::tm second_sunday() const;
    
    // Third functions
    std::tm third_monday() const;
    std::tm third_tuesday() const;
    std::tm third_wednesday() const;
    std::tm third_thursday() const;
    std::tm third_friday() const;
    std::tm third_saturday() const;
    std::tm third_sunday() const;
    
    // Fourth functions
    std::tm fourth_monday() const;
    std::tm fourth_tuesday() const;
    std::tm fourth_wednesday() const;
    std::tm fourth_thursday() const;
    std::tm fourth_friday() const;
    std::tm fourth_saturday() const;
    std::tm fourth_sunday() const;
    
    // Last functions
    std::tm last_monday() const;
    std::tm last_tuesday() const;
    std::tm last_wednesday() const;
    std::tm last_thursday() const;
    std::tm last_friday() const;
    std::tm last_saturday() const;
    std::tm last_sunday() const;
    
private:
    int year_;
    int month_;
    std::tm find(const std::string& week, const std::string& weekday) const;
};

}  // namespace meetup

#endif // MEETUP_H
