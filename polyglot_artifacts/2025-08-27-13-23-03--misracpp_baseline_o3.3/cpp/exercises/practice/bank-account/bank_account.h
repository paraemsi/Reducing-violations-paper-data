#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H
#include <mutex>
#include <stdexcept>

namespace Bankaccount {
class Bankaccount {
public:
    Bankaccount() = default;

    // Open the bank account; balance starts at 0.
    void open();

    // Close the account; further operations will throw.
    void close();

    // Deposit a non-negative amount of money.
    void deposit(int amount);

    // Withdraw a non-negative amount, must not exceed current balance.
    void withdraw(int amount);

    // Obtain current balance.
    int balance() const;

private:
    mutable std::mutex mtx_;
    bool open_{false};
    int balance_{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
