#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H
#include <mutex>

namespace Bankaccount {
class Bankaccount {
 public:
  Bankaccount();

  // Opens the account; must be called before any other operation.
  void open();

  // Closes the account; further operations will throw.
  void close();

  // Returns the current balance.
  int balance() const;

  // Deposits a positive amount into the account.
  void deposit(int amount);

  // Withdraws a positive amount, fails if insufficient funds.
  void withdraw(int amount);

 private:
  mutable std::mutex m_mutex{};
  bool m_open{false};
  int m_balance{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
