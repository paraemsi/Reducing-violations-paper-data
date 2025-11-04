#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H

#include <cstdint>
#include <mutex>

namespace Bankaccount {

using amount_t = std::int64_t;

class Bankaccount {  // class Bankaccount
 public:
  Bankaccount() noexcept;
  ~Bankaccount() noexcept = default;

  void open();
  void close();

  void deposit(amount_t amount);
  void withdraw(amount_t amount);

  amount_t balance() const;

 private:
  Bankaccount(const Bankaccount&) = delete;
  Bankaccount& operator=(const Bankaccount&) = delete;
  Bankaccount(Bankaccount&&) = delete;
  Bankaccount& operator=(Bankaccount&&) = delete;

  mutable std::mutex m_mutex;
  bool m_is_open;
  amount_t m_balance;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
