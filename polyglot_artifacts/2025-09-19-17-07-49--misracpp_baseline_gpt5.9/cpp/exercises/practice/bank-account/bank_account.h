#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {
class Bankaccount {  // class Bankaccount
 public:
  Bankaccount() noexcept;
  void open();
  void close();
  void deposit(int amount);
  void withdraw(int amount);
  int balance() const;

 private:
  mutable std::mutex m_mutex;
  bool m_is_open{false};
  int m_balance{0};
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
