#ifndef S21_AVL_TREE
#define S21_AVL_TREE
#include <iostream>

namespace S21 {
template <typename T, typename V>
class tree_node {
 public:
  mutable T key;
  int height;
  int size;
  tree_node<T, V> *left;
  tree_node<T, V> *right;
  tree_node<T, V> *parent;
  tree_node(const T &a);
  tree_node(T &a);
};

template <typename T, typename V>
class AVL_tree {
 public:
  AVL_tree();
  AVL_tree(const AVL_tree &other);
  ~AVL_tree();
  tree_node<T, V> *getroot() const;
  void delete_key(T k);
  tree_node<T, V> *search(T k);
  tree_node<T, V> *insert_avl(T k);
  void swap_avl(AVL_tree &other);
  void setroot(tree_node<T, V> *node);
  bool get_insert();
  AVL_tree<T, V> &operator=(AVL_tree &&other) noexcept;
  void delete_class(tree_node<T, V> *node);
  void refresh_size(tree_node<T, V> *node);

 private:
  bool inserted;
  tree_node<T, V> *root;
  tree_node<T, V> *nil;
  int take_height(tree_node<T, V> *node);
  int size_of_node(tree_node<T, V> *node);
  // void delete_class(tree_node<T, V> *node);
  tree_node<T, V> *copy_tree(tree_node<T, V> *node);
  int bfactor(tree_node<T, V> *node);
  void fixheight(tree_node<T, V> *node);
  tree_node<T, V> *right_move(tree_node<T, V> *node);
  tree_node<T, V> *left_move(tree_node<T, V> *node);
  tree_node<T, V> *balance(tree_node<T, V> *node);
  tree_node<T, V> *insert_avl(tree_node<T, V> *node, T k,
                              tree_node<T, V> *parent);
  tree_node<T, V> *find_min(tree_node<T, V> *node);
  tree_node<T, V> *delete_min(tree_node<T, V> *node);
  tree_node<T, V> *delete_key(tree_node<T, V> *node, T k);
  tree_node<T, V> *search(tree_node<T, V> *node, T k);
};
}  // namespace S21

#include "./S21_tree.tpp"
#endif