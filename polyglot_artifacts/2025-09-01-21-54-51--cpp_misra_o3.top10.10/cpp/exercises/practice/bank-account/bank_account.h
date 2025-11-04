#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

using money_t = std::int64_t;

class Bankaccount {
 public:
  Bankaccount() noexcept;
  ~Bankaccount() = default;

  void open();
  void close();

  void deposit(money_t amount);
  void withdraw(money_t amount);

  [[nodiscard]] money_t balance() const;
  [[nodiscard]] bool is_open() const;

 private:
  mutable std::mutex mutex_;
  money_t balance_;
  bool open_;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
