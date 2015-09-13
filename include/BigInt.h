#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
using namespace std;

class BigInt {
  static const uint64_t MAX = 1000000000;
  
public:
  BigInt() : value_(0), tail_(nullptr) {}

  BigInt(uint64_t value) : value_(value), tail_(nullptr) {
  	// cout << __PRETTY_FUNCTION__ << " value:" << value << endl;
  	handle_overflow(value_);
  }
  
  BigInt(const BigInt &bi) : value_(0), tail_(nullptr) {
  	*this = bi;
  }

  BigInt& operator=(const BigInt &rhs) {
    if (this != &rhs) {
      value_ = rhs.value_;
      if (rhs.tail_)
      	tail_ = make_shared<BigInt>(*rhs.tail_);
    }
    return *this;
  }

  BigInt& operator+=(const BigInt &rhs) {
    handle_overflow(value_ += rhs.value_);
    if (rhs.tail_) {
    	if (!tail_)
    		tail_ = make_shared<BigInt>();
    	*tail_ += *rhs.tail_;
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
  	if (value_ != rhs.value_)
  		return false;
  	if (!tail_ && !rhs.tail_)
  		return true;
  	if (!tail_ || !rhs.tail_)
  		return false;
  	return *tail_ == *rhs.tail_;
  }

  friend ostream& operator<<(ostream& os, const BigInt& bi);

private:
  void overflow(uint64_t value) {
    if (!tail_) {
      tail_ = make_shared<BigInt>();
    }
    *tail_ += BigInt(value);
  }

  void handle_overflow(uint64_t &value) {
    if (value >= MAX) {
      overflow(value / MAX);
      value %= MAX;
    }
  }

  uint64_t value_;
  shared_ptr<BigInt> tail_;
};

ostream& operator<<(ostream& os, const BigInt& bi) {
	char fill = os.fill();
	streamsize width = os.width();
	if (bi.tail_) {
		os << *bi.tail_ << setw(9) << setfill('0');
	}
	return os << bi.value_ << setw(width) << setfill(fill);
}

