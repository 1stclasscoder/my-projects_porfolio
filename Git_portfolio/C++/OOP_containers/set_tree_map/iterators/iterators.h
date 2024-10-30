#ifndef S21_ITERATORS
#define S21_ITERATORS
#include "../AVL_tree/S21_tree.h"

namespace S21 {
template <typename T, typename V>
class iterator {
  // friend class AVL_tree<T, V>;
 public:
  using key_type = T;
  using reference = T &;
  using const_reference = const T &;
  using pointer = T *;

  iterator(tree_node<T, V> *node = nullptr);
  iterator(tree_node<T, V> *nil, tree_node<T, V> *root);
  iterator(const iterator &) = default;
  iterator &operator=(const iterator &) = default;
  ~iterator() = default;

  iterator operator+(const int value);
  iterator &operator++();
  iterator operator++(int);
  iterator &operator--();
  iterator operator--(int);
  bool operator==(const iterator &other) const;
  bool operator!=(const iterator &other) const;
  pointer operator->() const;

  reference operator*() const;

  tree_node<T, V> *max_key(tree_node<T, V> *node);
  iterator &help_minus_minus();
  int size_tree(tree_node<T, V> *node);

 protected:
  tree_node<T, V> *node_;
  tree_node<T, V> *root_;
};

template <typename T, typename V>
class constiterator : public iterator<const T, const V> {
 public:
  using iterator<const T, const V>::iterator;

  using typename iterator<const T, const V>::key_type;
  using typename iterator<const T, const V>::reference;
  using typename iterator<const T, const V>::const_reference;
  using typename iterator<const T, const V>::pointer;
};
};  // namespace S21
#include "./iterators.tpp"
#endif