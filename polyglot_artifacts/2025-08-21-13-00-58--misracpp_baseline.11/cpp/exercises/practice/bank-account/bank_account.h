#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <optional>

namespace Bankaccount {

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();

    // Open the account (set balance to 0, mark as open)
    void open();

    // Close the account (mark as closed)
    void close();

    // Get the current balance, or throws if closed
    int balance();

    // Deposit amount, throws if closed or invalid
    void deposit(int amount);

    // Withdraw amount, throws if closed or insufficient funds or invalid
    void withdraw(int amount);

private:
    mutable std::mutex mtx_;
    bool is_open_;
    int balance_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
