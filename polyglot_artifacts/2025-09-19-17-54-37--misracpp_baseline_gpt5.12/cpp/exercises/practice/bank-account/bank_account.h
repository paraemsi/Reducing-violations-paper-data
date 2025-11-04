#if !defined(BANK_ACCOUNT_H)
#define BANK_ACCOUNT_H
#include <mutex>

namespace Bankaccount {
class Bankaccount {
 public:
  Bankaccount();
  ~Bankaccount() = default;

  void open();
  void close();
  void deposit(int amount);
  void withdraw(int amount);
  int balance() const;

  Bankaccount(const Bankaccount&) = delete;
  Bankaccount& operator=(const Bankaccount&) = delete;
  Bankaccount(Bankaccount&&) = delete;
  Bankaccount& operator=(Bankaccount&&) = delete;

 private:
  mutable std::mutex mutex_;
  bool is_open_;
  int balance_;
};  // class Bankaccount

}  // namespace Bankaccount

#endif  // BANK_ACCOUNT_H
