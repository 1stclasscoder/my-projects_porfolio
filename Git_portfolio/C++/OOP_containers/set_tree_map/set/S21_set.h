#ifndef S21_SET_CONTAINER
#define S21_SET_CONTAINER

#include <initializer_list>
#include <iostream>

#include "../iterators/iterators.h"
namespace S21 {
template <typename T>
class set {
  // friend class iterator<T, T>;
 public:
  using value_type = T;
  using iterator = iterator<T, T>;
  using const_iterator = constiterator<T, T>;
  using size_type = size_t;
  using Allocator = std::allocator<T>;

  set();
  set(const set &other);
  set(std::initializer_list<value_type> const &keys);
  set(set<value_type> &&other) = default;
  ~set() {}
  set<T> &operator=(set &&other);

  bool empty();
  bool contains();
  iterator find(const T &key);
  const AVL_tree<T, T> &get_tree() const;
  iterator begin();
  iterator end();
  void swap(set<T> &other);
  size_type size();
  void erase(iterator del_part);
  iterator contains(const T &key);
  void clear();
  void merge(set &other);
  std::pair<iterator, bool> insert(const value_type &value);
  size_type max_size();

 private:
  AVL_tree<T, T> tree_set;
};
}  // namespace S21
#include "./S21_set.tpp"
#endif