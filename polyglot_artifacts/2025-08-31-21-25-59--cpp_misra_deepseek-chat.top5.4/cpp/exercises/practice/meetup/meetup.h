#if !defined(MEETUP_H)
#define MEETUP_H

#include <string>

namespace meetup {

struct Date {
    int year;
    int month;
    int day;
};

class scheduler {
public:
    scheduler(int year, int month);
    
    // Teenth functions
    Date monteenth() const;
    Date tuesteenth() const;
    Date wednesteenth() const;
    Date thursteenth() const;
    Date friteenth() const;
    Date saturteenth() const;
    Date sunteenth() const;
    
    // First week functions
    Date first_monday() const;
    Date first_tuesday() const;
    Date first_wednesday() const;
    Date first_thursday() const;
    Date first_friday() const;
    Date first_saturday() const;
    Date first_sunday() const;
    
    // Second week functions
    Date second_monday() const;
    Date second_tuesday() const;
    Date second_wednesday() const;
    Date second_thursday() const;
    Date second_friday() const;
    Date second_saturday() const;
    Date second_sunday() const;
    
    // Third week functions
    Date third_monday() const;
    Date third_tuesday() const;
    Date third_wednesday() const;
    Date third_thursday() const;
    Date third_friday() const;
    Date third_saturday() const;
    Date third_sunday() const;
    
    // Fourth week functions
    Date fourth_monday() const;
    Date fourth_tuesday() const;
    Date fourth_wednesday() const;
    Date fourth_thursday() const;
    Date fourth_friday() const;
    Date fourth_saturday() const;
    Date fourth_sunday() const;
    
    // Last week functions
    Date last_monday() const;
    Date last_tuesday() const;
    Date last_wednesday() const;
    Date last_thursday() const;
    Date last_friday() const;
    Date last_saturday() const;
    Date last_sunday() const;
    
private:
    int year_;
    int month_;
    Date find_date(const std::string& week, const std::string& weekday) const;
};

}  // namespace meetup

#endif // MEETUP_H
