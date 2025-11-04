#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {

class Bankaccount {  // class Bankaccount
 public:
  Bankaccount() = default;

  void open();
  void close();
  void deposit(int amount);
  void withdraw(int amount);
  int balance() const;

 private:
  mutable std::mutex mtx_;
  bool is_open_{false};
  int balance_{0};
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
