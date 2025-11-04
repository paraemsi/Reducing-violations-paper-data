#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();
    
    // Open a new account with zero balance
    void open();
    
    // Close the account
    void close();
    
    // Deposit money into the account
    // Throws std::runtime_error if account is closed or amount is negative
    void deposit(std::int32_t amount);
    
    // Withdraw money from the account
    // Throws std::runtime_error if account is closed, amount is negative, or insufficient funds
    void withdraw(std::int32_t amount);
    
    // Get the current balance
    // Throws std::runtime_error if account is closed
    std::int32_t balance() const;

private:
    mutable std::mutex account_mutex;
    std::int32_t account_balance;
    bool is_open;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
