#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {
public:
    Bankaccount();

    // Open the account with 0 balance. Throws if already open.
    void open();

    // Close the account. Throws if already closed.
    void close();

    // Current balance. Throws if account is closed.
    int balance() const;

    // Deposit non-negative amount. Throws if account closed or amount negative.
    void deposit(int amount);

    // Withdraw non-negative amount. Throws if account closed, amount negative,
    // or insufficient funds.
    void withdraw(int amount);

private:
    bool is_open_{false};
    int balance_{0};
    mutable std::mutex mtx_;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
