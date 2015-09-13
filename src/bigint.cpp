#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
using namespace std;

class bigint {
  static const uint64_t MAX = 1000000000;
  
public:
  bigint() : value_(0), tail_(nullptr) {}

  bigint(uint64_t value) : value_(value), tail_(nullptr) {
  	// cout << __PRETTY_FUNCTION__ << " value:" << value << endl;
  	handle_overflow(value_);
  }
  
  bigint(const bigint &bi) : value_(0), tail_(nullptr) {
  	*this = bi;
  }

  bigint& operator=(const bigint &rhs) {
    if (this != &rhs) {
      value_ = rhs.value_;
      if (rhs.tail_)
      	tail_ = make_shared<bigint>(*rhs.tail_);
    }
    return *this;
  }

  bigint& operator+=(const bigint &rhs) {
    handle_overflow(value_ += rhs.value_);
    if (rhs.tail_) {
    	if (!tail_)
    		tail_ = make_shared<bigint>();
    	*tail_ += *rhs.tail_;
    }
    return *this;
  }

  const bigint operator+(const bigint& other) const {
    return bigint(*this) += other;
  }
  
  bigint& operator*=(const bigint &rhs) {
  	// TODO
	return *this;
  }
  
  const bigint operator*(const bigint& rhs) const {
  	// TODO
    return bigint(*this);
  }
  
  bool operator!=(const bigint& rhs) const {
  	return !(*this == rhs);
  }
  
  bool operator==(const bigint& rhs) const {
  	if (value_ != rhs.value_)
  		return false;
  	if (!tail_ && !rhs.tail_)
  		return true;
  	if (!tail_ || !rhs.tail_)
  		return false;
  	return *tail_ == *rhs.tail_;
  }

  friend ostream& operator<<(ostream& os, const bigint& bi);

private:
  void overflow(uint64_t value) {
    if (!tail_) {
      tail_ = make_shared<bigint>();
    }
    *tail_ += bigint(value);
  }

  void handle_overflow(uint64_t &value) {
    if (value >= MAX) {
      overflow(value / MAX);
      value %= MAX;
    }
  }

  uint64_t value_;
  shared_ptr<bigint> tail_;
};

ostream& operator<<(ostream& os, const bigint& bi) {
	char fill = os.fill();
	streamsize width = os.width();
	if (bi.tail_) {
		os << *bi.tail_ << setw(9) << setfill('0');
	}
	return os << bi.value_ << setw(width) << setfill(fill);
}
  
int main(int, char**) {
  cout << bigint(1) + bigint(2) << endl;
  cout << bigint(1000000000000000000) << endl;
  cout << bigint(1000000000000000000) + bigint(1000000000000000000) << endl;
  cout << boolalpha << (bigint(1000000000000000000) == bigint(2000000000000000000)) << endl;
  cout << boolalpha << (bigint(2000000000000000000) == bigint(2000000000000000000)) << endl;
  //cout << bigint(10000000000000000000) * bigint(2) << endl;
  return 0;
}

