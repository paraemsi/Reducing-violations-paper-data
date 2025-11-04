#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <cstdint>

namespace Bankaccount {

using AccountValue = std::int64_t;

class Bankaccount {
private:
    AccountValue balance_;
    bool is_open_;
    mutable std::mutex mutex_;
    
public:
    Bankaccount();
    void open();
    void deposit(AccountValue amount);
    void withdraw(AccountValue amount);
    void close();
    AccountValue balance() const;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
