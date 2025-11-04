#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {
 public:
  Bankaccount() = default;

  // Open the account and reset balance to zero.
  // Throws std::runtime_error if already open.
  void open();

  // Close the account. Further operations will throw.
  // Throws std::runtime_error if already closed.
  void close();

  // Return current balance.
  // Throws std::runtime_error if the account is closed.
  int balance() const;

  // Add amount to the balance.
  // Throws std::runtime_error if the account is closed or amount is negative.
  void deposit(int amount);

  // Subtract amount from the balance.
  // Throws std::runtime_error if the account is closed, amount is negative,
  // or balance is insufficient.
  void withdraw(int amount);

 private:
  int m_balance{0};
  bool m_open{false};
  mutable std::mutex m_mutex;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
