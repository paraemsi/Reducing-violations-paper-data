#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>
#include <stdexcept>

namespace Bankaccount {

class Bankaccount {
 public:
  // Open the account. If it is already open, no state is changed.
  void open();

  // Close the account. Operations on a closed account will throw.
  void close();

  // Deposit a positive amount into the account.
  void deposit(int amount);

  // Withdraw a positive amount from the account.
  void withdraw(int amount);

  // Obtain the current balance.
  int balance() const;

 private:
  mutable std::mutex m_mutex_;
  bool m_open_{false};
  int m_balance_{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
