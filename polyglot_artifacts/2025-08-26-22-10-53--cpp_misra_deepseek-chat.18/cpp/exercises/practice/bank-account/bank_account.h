#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>
#include <stdexcept>

namespace Bankaccount {

// Alias for fixed-width integer type
using AccountValue = std::int64_t;

class Bankaccount {
private:
    AccountValue balance;
    bool is_open;
    mutable std::mutex mtx;
    
public:
    Bankaccount();
    void open();
    void deposit(AccountValue amount);
    void withdraw(AccountValue amount);
    AccountValue get_balance() const;
    void close();
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
