#include <cstring>
#include <iostream>

class String {
 public:
  String() : size_(0), str_(new char[1]), bytes_size_(1) {}
  String(const char* k_str)
      : size_(strlen(k_str)), str_(new char[size_]), bytes_size_(size_) {
    memcpy(str_, k_str, size_);
  }
  String(size_t n) : size_(n), str_(new char[n]), bytes_size_(n) {}
  String(const String& k_str) : String(k_str.size_) {
    memcpy(str_, k_str.str_, size_);
  }
  String(size_t n, char c) : size_(n), str_(new char[n]), bytes_size_(n) {
    memset(str_, c, n);
  }
  String(char c) : size_(1), str_(new char[1]), bytes_size_(1) { str_[0] = c; }
  ~String() { delete[] str_; }
  char& operator[](size_t index);
  const char& operator[](size_t index) const;
  String& operator+=(const String& k_str);
  String& operator=(const String& k_str);
  void push_back(char c);
  void pop_back();
  void clear();
  bool empty() const;
  char& front();
  const char& front() const;
  char& back();
  const char& back() const;
  String substr(size_t start, size_t count) const;
  size_t find(const String& k_str) const;
  size_t rfind(const String& k_str) const;
  size_t length() const;

 private:
  void swap(String& str);
  void alloc_memory(size_t old_size, size_t new_size);
  size_t size_;
  char* str_;
  size_t bytes_size_;
};

size_t String::length() const { return size_; }

char& String::operator[](size_t index) { return str_[index]; }

const char& String::operator[](size_t index) const { return str_[index]; }

String& String::operator=(const String& k_str) {
  String copy(k_str);
  swap(copy);
  return *this;
}

std::istream& operator>>(std::istream& in, String& str) {
  char c;
  str.clear();
  while (in.get(c) && c != '\n' && c != ' ') {
    str.push_back(c);
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const String& k_str) {
  size_t it = 0;
  while (it < k_str.length()) {
    out << k_str[it];
    it++;
  }
  return out;
}

void String::alloc_memory(size_t old_size, size_t new_size) {
  char* new_str = new char[new_size];
  memcpy(new_str, str_, old_size);
  delete[] str_;
  str_ = new_str;
  bytes_size_ = new_size;
}

void String::push_back(char c) {
  if (bytes_size_ < size_ + 1) {
    alloc_memory(size_, 2 * size_);
  }
  str_[size_] = c;
  size_++;
}

void String::pop_back() { size_--; }

void String::swap(String& str) {
  std::swap(str_, str.str_);
  std::swap(size_, str.size_);
  std::swap(bytes_size_, str.bytes_size_);
}

void String::clear() {
  delete[] str_;
  str_ = new char[1];
  bytes_size_ = 1;
  size_ = 0;
}

bool operator==(const String& k_first_str, const String& k_second_str) {
  if (k_first_str.length() != k_second_str.length()) {
    return false;
  }
  for (size_t i = 0; i < k_second_str.length(); i++) {
    if (k_first_str[i] != k_second_str[i]) {
      return false;
    }
  }
  return true;
}

bool String::empty() const { return size_ == 0; }

char& String::front() { return str_[0]; }

const char& String::front() const { return str_[0]; }

char& String::back() { return str_[size_ - 1]; }

const char& String::back() const { return str_[size_ - 1]; }

String String::substr(size_t start, size_t count) const {
  String s(count);
  memcpy(s.str_, str_ + start, count);
  return s;
}

String operator+(const String& k_first_str, const String& k_second_str) {
  String new_str(k_first_str);
  new_str += k_second_str;
  return new_str;
}

String& String::operator+=(const String& k_str) {
  alloc_memory(size_, size_ + k_str.size_);
  for (size_t i = 0; i < k_str.size_; i++) {
    push_back(k_str[i]);
  }
  return *this;
}

size_t String::find(const String& k_str) const {
  size_t len = k_str.length();
  size_t first_sub = size_;
  bool find_substr = false;
  for (size_t main_it = 0; main_it <= size_ - len && !find_substr; main_it++) {
    for (size_t sub_it = 0; sub_it < len; sub_it++) {
      if (str_[main_it + sub_it] != k_str[sub_it]) {
        break;
      }
      if (sub_it == len - 1) {
        first_sub = main_it;
        find_substr = true;
        break;
      }
    }
  }
  return first_sub;
}

size_t String::rfind(const String& k_str) const {
  size_t len = k_str.length();
  size_t first_sub = size_;
  bool find_substr = false;
  for (size_t main_it = size_ - 1; !find_substr; main_it--) {
    for (size_t sub_it = len - 1;; sub_it--) {
      if (str_[main_it + sub_it - len + 1] != k_str[sub_it]) {
        break;
      }
      if (sub_it == 0 && str_[main_it + sub_it - len + 1] == k_str[sub_it]) {
        first_sub = main_it + sub_it - len + 1;
        find_substr = true;
      }
      if (sub_it == 0) {
        break;
      }
    }
    if (main_it == 0) {
      break;
    }
  }
  return first_sub;
}
