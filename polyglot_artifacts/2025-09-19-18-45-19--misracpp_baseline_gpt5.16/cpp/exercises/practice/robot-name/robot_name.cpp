#include "robot_name.h"

#include <mutex>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {
constexpr std::size_t kCapacity = 26u * 26u * 1000u;

std::unordered_set<std::string> g_used;
std::mutex g_mutex;

char random_upper(std::mt19937& gen) {
  std::uniform_int_distribution<int> dist(0, 25);
  return static_cast<char>('A' + dist(gen));
}

char random_digit(std::mt19937& gen) {
  std::uniform_int_distribution<int> dist(0, 9);
  return static_cast<char>('0' + dist(gen));
}

std::mt19937& rng() {
  thread_local std::mt19937 gen(std::random_device{}());
  return gen;
}

std::string generate_candidate(std::mt19937& gen) {
  std::string s;
  s.reserve(5);
  s.push_back(random_upper(gen));
  s.push_back(random_upper(gen));
  s.push_back(random_digit(gen));
  s.push_back(random_digit(gen));
  s.push_back(random_digit(gen));
  return s;
}

std::string acquire_unique_name(const std::string& avoid) {
  auto& gen = rng();
  for (;;) {
    std::string candidate = generate_candidate(gen);
    if (!avoid.empty() && candidate == avoid) {
      continue;
    }
    std::lock_guard<std::mutex> lock(g_mutex);
    if (g_used.size() >= kCapacity) {
      throw std::runtime_error("All robot names have been exhausted");
    }
    if (g_used.insert(candidate).second) {
      return candidate;
    }
  }
}

void release_name(const std::string& name) {
  if (name.empty()) return;
  std::lock_guard<std::mutex> lock(g_mutex);
  g_used.erase(name);
}
}  // namespace

robot::robot()
    : name_(acquire_unique_name("")) {}

robot::~robot() = default;

std::string robot::name() const {
  return name_;
}

void robot::reset() {
  const std::string old = name_;
  name_ = acquire_unique_name(old);
}

}  // namespace robot_name
