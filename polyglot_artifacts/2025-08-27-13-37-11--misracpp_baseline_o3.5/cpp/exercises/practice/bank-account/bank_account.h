#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {

class Bankaccount {
public:
    // Open the account. Throws if the account is already open.
    void open();

    // Close the account. Throws if the account is already closed.
    void close();

    // Deposit a non-negative amount. Throws if account is closed or amount < 0.
    void deposit(int amount);

    // Withdraw a non-negative amount.
    // Throws if account is closed, amount < 0, or balance would go negative.
    void withdraw(int amount);

    // Current balance. Throws if account is closed.
    int balance() const;

private:
    mutable std::mutex mtx_;
    bool is_open_{false};
    int balance_{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
