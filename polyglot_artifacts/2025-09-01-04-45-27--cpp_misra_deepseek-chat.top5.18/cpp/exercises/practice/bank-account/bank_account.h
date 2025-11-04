#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>

namespace Bankaccount {

// Alias for amount type to comply with MISRA rules
using Amount = std::int64_t;

class Bankaccount {
private:
    Amount balance_;
    bool is_open_;
    mutable std::mutex mutex_;
    
public:
    Bankaccount();
    void open();
    void close();
    void deposit(Amount amount);
    void withdraw(Amount amount);
    Amount balance() const;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
