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
  ~Bankaccount() = default;

  Bankaccount(const Bankaccount&) = delete;
  Bankaccount& operator=(const Bankaccount&) = delete;
  Bankaccount(Bankaccount&&) = delete;
  Bankaccount& operator=(Bankaccount&&) = delete;

 private:
  mutable std::mutex mtx_;
  bool is_open_;
  int balance_;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
