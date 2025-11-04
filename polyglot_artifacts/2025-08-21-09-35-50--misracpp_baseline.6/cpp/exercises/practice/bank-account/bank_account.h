#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <optional>

namespace Bankaccount {

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();

    // Open the account (if not already open)
    void open();

    // Close the account. After closing, all operations fail.
    void close();

    // Deposit money. Throws std::runtime_error on error.
    void deposit(int amount);

    // Withdraw money. Throws std::runtime_error on error.
    void withdraw(int amount);

    // Get current balance. Throws std::runtime_error if account is closed.
    int balance();

private:
    mutable std::mutex mtx_;
    bool is_open_ = false;
    int balance_ = 0;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
