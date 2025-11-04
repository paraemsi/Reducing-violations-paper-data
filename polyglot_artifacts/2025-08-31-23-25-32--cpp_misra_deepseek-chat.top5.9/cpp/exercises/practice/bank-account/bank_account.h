#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>

namespace Bankaccount {

// Define a type alias for the balance to comply with MISRA rules
using BalanceType = std::int64_t;

class Bankaccount {
private:
    BalanceType balance_;
    bool is_open_;
    mutable std::mutex mutex_;
    
public:
    Bankaccount();
    void open();
    void close();
    void deposit(BalanceType amount);
    void withdraw(BalanceType amount);
    BalanceType balance() const;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
