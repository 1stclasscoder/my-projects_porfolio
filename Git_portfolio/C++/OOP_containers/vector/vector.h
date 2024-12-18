#ifndef S21_VECTOR_H_STRUCT
#define S21_VECTOR_H_STRUCT

#include <iostream>

namespace S21 {
template <typename T>
class vector {
  class VectorIterator;
  class VectorConstIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = vector<T>::VectorIterator;
  using const_iterator = vector<T>::VectorConstIterator;
  using size_type = size_t;

 public:
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector();

  vector &operator=(vector &&v);

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  T *data();

  iterator begin();
  iterator end();

  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

 private:
  value_type *node_vector;
  size_type size_;
  size_type capacity_;
};
}  // namespace S21

#include "vector_iterators.h"
#include "./vector.tpp"

#endif