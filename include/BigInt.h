#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
using namespace std;

class BigInt {
  static const uint64_t MAX = 1000000000;
  
public:
  BigInt() : value_() {}

  BigInt(uint64_t value) : value_(1, value) {
  	handle_overflow(value_.begin());
  }
  
  BigInt(const BigInt &bi) : value_() {
  	*this = bi;
  }

  BigInt& operator=(const BigInt &rhs) {
    if (this != &rhs) {
      value_ = rhs.value_;
    }
    return *this;
  }

  BigInt& operator+=(const BigInt &rhs) {
    uint64_t carry = 0;
    for (size_t i = 0; i < rhs.value_.size(); ++i) {
      if (i == value_.size()) {
        value_.push_back(0);
      }
      value_[i] += rhs.value_[i] + carry;
      carry = value_[i] / MAX;
      value_[i] %= MAX;
    }
    if (carry > 0) {
      value_.push_back(carry);
    }
    return *this;
  }

  const BigInt operator+(const BigInt& other) const {
    return BigInt(*this) += other;
  }
  
  BigInt& operator*=(const BigInt &rhs) {
  	// TODO
    return *this;
  }
  
  const BigInt operator*(const BigInt& rhs) const {
  	// TODO
    return BigInt(*this);
  }
  
  bool operator!=(const BigInt& rhs) const {
  	return !(*this == rhs);
  }
  
  bool operator==(const BigInt& rhs) const {
    return value_ == rhs.value_;
  }

  friend ostream& operator<<(ostream& os, const BigInt& bi);

private:
  void overflow(uint64_t value, vector<uint64_t>::iterator it) {
    if (++it == value_.end()) {
      value_.push_back(value);
      it = --value_.end();
    } else {
      *it += value;
    }
    handle_overflow(it);
  }

  void handle_overflow(vector<uint64_t>::iterator it) {
    uint64_t &value = *it;
    if (value >= MAX) {
      uint64_t carry = value / MAX;
      value %= MAX;
      overflow(carry, it);
    }
  }

  vector<uint64_t> value_;
};

ostream& operator<<(ostream& os, const BigInt& bi) {
  auto it = bi.value_.crbegin();
  if (it != bi.value_.crend()) {
    os << *(it++);
  }

  for_each(it, bi.value_.crend(), [&os](const uint64_t &value) {
      os << setw(9) << setfill('0') << value;
      });
	return os;
}

