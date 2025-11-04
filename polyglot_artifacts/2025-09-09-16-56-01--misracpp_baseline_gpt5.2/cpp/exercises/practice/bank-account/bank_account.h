#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <mutex>

namespace Bankaccount {

class Bankaccount {  // class Bankaccount
 public:
  Bankaccount();

  void open();
  void close();
  void deposit(int amount);
  void withdraw(int amount);
  int balance() const;

 private:
  mutable std::mutex mtx_;
  bool opened_;
  int bal_;
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
