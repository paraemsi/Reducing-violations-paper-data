#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <mutex>
#include <stdexcept>

namespace Bankaccount {
class Bankaccount {
 public:
  Bankaccount() = default;

  void open();
  void close();
  int balance() const;
  void deposit(int amount);
  void withdraw(int amount);

 private:
  mutable std::mutex m_mutex{};
  bool m_open{false};
  int m_balance{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
