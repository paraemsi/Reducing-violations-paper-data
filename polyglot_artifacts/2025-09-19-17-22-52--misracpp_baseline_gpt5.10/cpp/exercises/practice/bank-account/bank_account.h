#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {

class Bankaccount {
 public:
  Bankaccount();
  void open();
  void close();
  void deposit(int amount);
  void withdraw(int amount);
  [[nodiscard]] int balance() const;

 private:
  mutable std::mutex mutex_;
  bool open_{false};
  int balance_{0};
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
