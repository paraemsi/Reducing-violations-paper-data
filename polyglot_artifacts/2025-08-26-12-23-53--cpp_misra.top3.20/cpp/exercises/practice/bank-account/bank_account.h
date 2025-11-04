#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

typedef std::int64_t money_t;

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();

    // Open the account (if not already open)
    void open();

    // Close the account (no further operations allowed)
    void close();

    // Deposit money into the account
    // Throws std::runtime_error if account is closed or amount is negative
    void deposit(money_t amount);

    // Withdraw money from the account
    // Throws std::runtime_error if account is closed, amount is negative, or insufficient funds
    void withdraw(money_t amount);

    // Get the current balance
    // Throws std::runtime_error if account is closed
    money_t balance() const;

private:
    mutable std::mutex mtx_;
    money_t balance_;
    bool is_open_;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
