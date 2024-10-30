#ifndef S21_MAP_CONTAINER
#define S21_MAP_CONTAINER
#include <initializer_list>
#include <iostream>

#include "../iterators/iterators.h"
#include "../set/S21_set.h"

namespace S21 {
template <typename T, typename V>
class map {
 public:
  using key_type = T;
  using mapped_type = V;

  using value_type = std::pair<const key_type, mapped_type>;
  using reference = key_type &;
  using const_reference = const key_type &;
  using iterator = iterator<value_type, V>;
  using const_iterator = constiterator<value_type, V>;
  using size_type = size_t;
  using Allocator = std::allocator<T>;
  using default_value = mapped_type &;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m) = default;
  ~map();
  map<T, V> operator=(map &&m);

  mapped_type &at(const_reference key);
  mapped_type &operator[](const_reference key);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<typename map<T, V>::iterator, bool> insert(const key_type &key,
                                                       const mapped_type &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(map &other);

  bool contains(const T &key);

  bool contains_std_pair(const value_type &val);
  const AVL_tree<value_type, V> &get_tree() const;

 private:
  AVL_tree<value_type, V> tree_map;
};
}  // namespace S21
#include "./S21_map.tpp"

#endif