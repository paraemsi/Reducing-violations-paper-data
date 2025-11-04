#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H
#include <mutex>

namespace Bankaccount {
class Bankaccount {
 public:
  // Open the bank account. Has no effect if the account is already open.
  void open();

  // Close the bank account. After closing, any operation except `open`
  // will throw std::runtime_error.
  void close();

  // Return current account balance. Throws std::runtime_error when the
  // account is closed.
  int balance() const;

  // Deposit a positive amount of money into the account.
  // Throws std::runtime_error for negative amounts or closed account.
  void deposit(int amount);

  // Withdraw a positive amount of money from the account.
  // Throws std::runtime_error if the amount is negative, the balance
  // is insufficient, or the account is closed.
  void withdraw(int amount);

 private:
  mutable std::mutex mutex_;
  bool is_open_{false};
  int balance_{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
