#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <mutex>
#include <stdexcept>

namespace Bankaccount {

// A simple bank account that is safe to use from multiple threads.
class Bankaccount {
 public:
  // Open the account with zero balance.
  // Throws std::runtime_error if the account is already open.
  void open();

  // Close the account.
  // Throws std::runtime_error if the account is already closed.
  void close();

  // Deposit a non-negative amount of money.
  // Throws std::runtime_error if account is closed or amount is negative.
  void deposit(int amount);

  // Withdraw a non-negative amount of money.
  // Throws std::runtime_error if account is closed, amount is negative,
  // or there are insufficient funds.
  void withdraw(int amount);

  // Current balance of the account.
  // Throws std::runtime_error if the account is closed.
  int balance() const;

 private:
  mutable std::mutex m_;
  bool open_{false};
  int balance_{0};
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
