#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <optional>

namespace Bankaccount {

class Bankaccount {
public:
    Bankaccount();
    ~Bankaccount();

    // Open the account (reset balance to 0, mark as open)
    void open();

    // Close the account (mark as closed)
    void close();

    // Get the current balance. Throws std::runtime_error if closed.
    int balance();

    // Deposit money. Throws std::runtime_error if closed or amount < 0.
    void deposit(int amount);

    // Withdraw money. Throws std::runtime_error if closed or insufficient funds or amount < 0.
    void withdraw(int amount);

private:
    std::mutex mtx_;
    bool is_open_;
    int balance_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
