#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H
#include <cstdint>
#include <mutex>

namespace Bankaccount {
class Bankaccount {
 public:
  Bankaccount() = default;

  // Open the account. Can be called on a newly created account or after close().
  void open();

  // Close the account. After this, any operation except open() will throw.
  void close();

  // Return current balance.
  int64_t balance() const;

  // Deposit a non-negative amount.
  void deposit(int64_t amount);

  // Withdraw a non-negative amount.
  void withdraw(int64_t amount);

 private:
  mutable std::mutex m_;
  bool open_{false};
  int64_t balance_{0};
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
