#ifndef S21_ITERATORS_VECTOR
#define S21_ITERATORS_VECTOR

#include <iostream>

namespace S21 {

template <typename T>
class vector<T>::VectorIterator {
 public:
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;

  VectorIterator() = default;
  VectorIterator(pointer iter) : iter_(iter) {}
  ~VectorIterator() { iter_ = nullptr; }

  VectorIterator &operator++() {
    ++iter_;
    return *this;
  }

  VectorIterator operator++(int) {
    VectorIterator buf(*this);
    ++iter_;
    return buf;
  }

  VectorIterator &operator--() {
    --iter_;
    return *this;
  }
  VectorIterator operator--(int) {
    VectorIterator buf(*this);
    --iter_;
    return buf;
  }

  reference operator*() const { return *iter_; }

  bool operator==(const VectorIterator &other) const {
    return iter_ == other.iter_;
  }
  bool operator!=(const VectorIterator &other) const {
    return iter_ != other.iter_;
  }

  VectorIterator operator+(int n) const {
    VectorIterator buf(*this);
    for (int i = 0; i < n; i++) {
      buf++;
    }
    return buf;
  }

  VectorIterator operator-(int n) const {
    VectorIterator buf(*this);
    for (int i = 0; i < n; i++) {
      buf--;
    }
    return buf;
  }

  ptrdiff_t operator-(const VectorIterator &other) const {
    return iter_ - other.iter_;
  }

 protected:
  pointer iter_;
};

template <typename T>
class vector<T>::VectorConstIterator : public VectorIterator {
  using reference = T &;
  using const_reference = const T &;
  using const_pointer = const T *;

  VectorConstIterator() = default;
  VectorConstIterator(const_pointer iter) : iter_(iter) {}
  ~VectorConstIterator() { iter_ = nullptr; }

  VectorConstIterator &operator++() {
    ++iter_;
    return *this;
  }

  VectorConstIterator operator++(int) {
    VectorConstIterator buf(*this);
    ++iter_;
    return buf;
  }

  VectorConstIterator &operator--() {
    --iter_;
    return *this;
  }
  VectorConstIterator operator--(int) {
    VectorConstIterator buf(*this);
    --iter_;
    return buf;
  }

  reference operator*() const { return *iter_; }

  bool operator==(const VectorConstIterator &other) const {
    return iter_ == other.iter_;
  }
  bool operator!=(const VectorConstIterator &other) const {
    return iter_ != other.iter_;
  }

  VectorConstIterator operator+(int n) const {
    VectorConstIterator buf(*this);
    for (int i = 0; i < n; i++) {
      buf++;
    }
    return buf;
  }

  VectorConstIterator operator-(int n) const {
    VectorConstIterator buf(*this);
    for (int i = 0; i < n; i++) {
      buf--;
    }
    return buf;
  }

  ptrdiff_t operator-(const VectorConstIterator &other) const {
    return iter_ - other.iter_;
  }

 protected:
  const_pointer iter_;
};
}  // namespace S21
#endif