#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {
 public:
  // Construct a new, closed account with zero balance.
  Bankaccount();

  // Open the account; sets balance to 0. Throws if already open.
  void open();

  // Close the account. Throws if already closed.
  void close();

  // Deposit a positive amount. Throws if account is closed or amount < 0.
  void deposit(int amount);

  // Withdraw a positive amount. Throws if account is closed or amount < 0.
  // Note: Overdraft checking is outside the scope of these requirements.
  void withdraw(int amount);

  // Get current balance. Throws if account is closed.
  int balance() const;

 private:
  mutable std::mutex m_mutex;
  bool m_open;
  int m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
