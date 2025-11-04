#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {
class Bankaccount {
 public:
  Bankaccount();

  void open();
  void close();
  void deposit(std::int64_t amount);
  void withdraw(std::int64_t amount);
  std::int64_t balance() const;

 private:
  bool open_{false};
  std::int64_t account_balance_{0};
  mutable std::mutex mutex_{};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
