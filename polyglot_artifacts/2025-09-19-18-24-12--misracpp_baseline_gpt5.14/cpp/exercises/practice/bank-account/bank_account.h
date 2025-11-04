#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {

class Bankaccount {  // class Bankaccount
 public:
  // Construct a closed account with zero balance.
  Bankaccount();
  // Open the account and reset balance to zero.
  // Throws if the account is already open.
  void open();

  // Close the account.
  // Throws if the account is already closed.
  void close();

  // Get current balance.
  // Throws if the account is closed.
  int balance() const;

  // Deposit a non-negative amount.
  // Throws if the account is closed or amount is negative.
  void deposit(int amount);

  // Withdraw a non-negative amount.
  // Throws if the account is closed, amount is negative, or insufficient funds.
  void withdraw(int amount);

 private:
  mutable std::mutex mtx_;
  bool is_open_;
  int balance_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
