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
  int balance() const;

 private:
  bool open_;
  int balance_;
  mutable std::mutex mtx_;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
