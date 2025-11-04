#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

class Bankaccount {  // class Bankaccount
 public:
  Bankaccount();

  void open();
  void close();
  void deposit(std::int64_t amount);
  void withdraw(std::int64_t amount);
  std::int64_t balance() const;

 private:
  mutable std::mutex mtx_;
  bool is_open_{false};
  std::int64_t balance_{static_cast<std::int64_t>(0)};
};

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
