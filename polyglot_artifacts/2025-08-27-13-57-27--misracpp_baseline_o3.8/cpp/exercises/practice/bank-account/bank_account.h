#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <mutex>
#include <stdexcept>

#if __cplusplus >= 201703L
#define BANK_NODISCARD [[nodiscard]]
#else
#define BANK_NODISCARD
#endif

namespace Bankaccount {
class Bankaccount {
 public:
  Bankaccount();

  // Reactivate the account with zero balance.
  // Throws std::runtime_error if the account is already open.
  void open();

  // Close the account and reset balance to zero.
  // Throws std::runtime_error if the account is already closed.
  void close();

  // Add `amount` to the current balance.
  // Throws std::runtime_error if the account is closed or `amount` is negative.
  void deposit(int amount);

  // Subtract `amount` from the current balance.
  // Throws std::runtime_error if the account is closed,
  // `amount` is negative, or insufficient funds are available.
  void withdraw(int amount);

  // Return current balance.
  // Throws std::runtime_error if the account is closed.
  BANK_NODISCARD int balance() const;

 private:
  bool m_open{false};
  int m_balance{0};
  mutable std::mutex m_mutex;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
