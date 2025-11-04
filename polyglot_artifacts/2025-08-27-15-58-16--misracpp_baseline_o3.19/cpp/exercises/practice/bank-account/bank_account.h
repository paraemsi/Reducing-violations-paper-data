#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <stdexcept>

namespace Bankaccount {

class Bankaccount {
 public:
  // Constructed in a closed state.
  Bankaccount() = default;

  // Open the account. Resets balance to 0.
  // Throws std::runtime_error if the account is already open.
  void open();

  // Close the account. Balance becomes inaccessible.
  // Throws std::runtime_error if the account is already closed.
  void close();

  // Return current balance.
  // Throws std::runtime_error if the account is closed.
  int balance() const;

  // Increase balance by 'amount'.
  // Throws std::runtime_error if the account is closed or amount is negative.
  void deposit(int amount);

  // Decrease balance by 'amount'.
  // Throws std::runtime_error if the account is closed, amount is negative,
  // or amount exceeds current balance.
  void withdraw(int amount);

 private:
  mutable std::mutex mtx_;
  bool open_{false};
  int balance_{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
