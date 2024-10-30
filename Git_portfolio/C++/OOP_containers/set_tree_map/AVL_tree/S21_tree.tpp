#include "./S21_tree.h"

namespace S21 {
template <typename T, typename V>
tree_node<T, V>::tree_node(const T &a) : key(a) {
  height = 1;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}

template <typename T, typename V>
tree_node<T, V>::tree_node(T &a) : key(a) {
  height = 1;
  left = nullptr;
  right = nullptr;
  parent = nullptr;
}

template <typename T, typename V>
AVL_tree<T, V>::AVL_tree() {
  inserted = false;
  root = nullptr;
  nil = nullptr;
}

template <typename T, typename V>
AVL_tree<T, V>::AVL_tree(const AVL_tree &other)
    : root(copy_tree(other.getroot())) {}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::getroot() const {
  return this->root;
}

template <typename T, typename V>
AVL_tree<T, V>::~AVL_tree() {
  delete_class(root);
}

template <typename T, typename V>
AVL_tree<T, V> &AVL_tree<T, V>::operator=(AVL_tree &&other) noexcept {
  if (this != &other) {
    delete_class(root);
    root = std::exchange(other.root, nullptr);
  }
  return *this;
}

template <typename T, typename V>
void AVL_tree<T, V>::delete_class(tree_node<T, V> *node) {
  if (node != nullptr) {
    delete_class(node->left);
    delete_class(node->right);
    delete node;
  }
  root = nullptr;
}

template <typename T, typename V>
int AVL_tree<T, V>::take_height(tree_node<T, V> *node) {
  if (!node)
    return 0;
  else
    return node->height;
}

template <typename T, typename V>
int AVL_tree<T, V>::size_of_node(tree_node<T, V> *node) {
  if (!node)
    return 0;
  else
    return node->size;
}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::copy_tree(tree_node<T, V> *node) {
  if (node == nullptr) {
    return nullptr;
  } else {
    tree_node<T, V> *buf_node = new tree_node<T, V>(node->key);
    buf_node->size = node->size;
    buf_node->left = copy_tree(node->left);
    buf_node->right = copy_tree(node->right);
    buf_node->parent = node->parent;
    return buf_node;
  }
}

template <typename T, typename V>
int AVL_tree<T, V>::bfactor(tree_node<T, V> *node) {
  if (!node) return 0;
  return take_height(node->left) - take_height(node->right);
}
template <typename T, typename V>
void AVL_tree<T, V>::fixheight(tree_node<T, V> *node) {
  int height_left = take_height(node->left);
  int height_right = take_height(node->right);
  if (height_left > height_right) {
    node->height = height_left + 1;
  } else {
    node->height = height_right + 1;
  }
}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::right_move(tree_node<T, V> *node) {
  tree_node<T, V> *buf_node = node->left;
  // std::cout<<"1   !!!!!!!!!!\n";
  node->left = buf_node->right;
  // std::cout<<"2   !!!!!!!!!!\n";
  if (buf_node->right) {
    buf_node->right->parent = node;
  }
  buf_node->right = node;
  buf_node->parent = node->parent;
  node->parent = buf_node;
  fixheight(buf_node);
  fixheight(node);
  return buf_node;
}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::left_move(tree_node<T, V> *node) {
  tree_node<T, V> *buf_node = node->right;
  node->right = buf_node->left;
  if (buf_node->left) {
    buf_node->left->parent = node;
  }
  buf_node->left = node;
  buf_node->parent = node->parent;
  node->parent = buf_node;
  fixheight(node);
  fixheight(buf_node);
  return buf_node;
}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::balance(tree_node<T, V> *node) {
  fixheight(node);
  if (bfactor(node) == 2) {
    if (bfactor(node->right) < -1) {
      node->left = left_move(node->left);
      refresh_size(node->left);
    }
    node = right_move(node);
    // std::cout << "1 !!!!!!!!!" << std::endl;
    refresh_size(node);
  } else if (bfactor(node) == -2) {
    if (bfactor(node->right) > 1) {
      node->right = right_move(node->right);
      refresh_size(node->right);
    }
    node = left_move(node);
    refresh_size(node);
  }
  refresh_size(node);
  return node;
}  // перепроверить тестами

template <typename T, typename V>
void AVL_tree<T, V>::refresh_size(tree_node<T, V> *node) {
  if (node != nullptr) {
    node->size = 1 + size_of_node(node->left) + size_of_node(node->right);
    refresh_size(node->left);
    refresh_size(node->right);
  }
}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::insert_avl(tree_node<T, V> *node, T k,
                                            tree_node<T, V> *parent) {
  this->inserted = false;
  if (!node) {
    node = new tree_node<T, V>(k);
    this->inserted = true;
    node->parent = parent;
    return balance(node);
  } else if (k < node->key) {
    node->left = insert_avl(node->left, k, node);
  } else if (k > node->key) {
    node->right = insert_avl(node->right, k, node);
  } else if (k == node->key) {
    this->inserted = false;
  }
  node = balance(node);
  return node;
}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::insert_avl(T k) {
  root = insert_avl(root, k, nullptr);
  return root;
}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::find_min(tree_node<T, V> *node) {
  if (!node->left) {
    return node;
  } else {
    return find_min(node->left);
  }
}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::delete_min(tree_node<T, V> *node) {
  if (!node->left) {
    return node->right;
  } else {
    node->left = delete_min(node->left);
    node = balance(node);
    return node;
  }
}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::delete_key(tree_node<T, V> *node, T k) {
  if (!node) {
    return nullptr;
  } else if (k < node->key) {
    node->left = delete_key(node->left, k);
  } else if (k > node->key) {
    node->right = delete_key(node->right, k);
  } else {
    if (!node->right) {
      return node->left;
    } else if (!node->left) {
      return node->right;
    } else {
      tree_node<T, V> *buf_l = node->left;
      tree_node<T, V> *buf_r = node->right;
      tree_node<T, V> *min = find_min(buf_r);
      min->right = delete_min(buf_r);
      min->left = buf_l;
      min->size--;
      min->parent = node->parent;
      delete node;
      fixheight(min);
      min = balance(min);
      return min;
    }
  }
  node->size--;
  fixheight(node);
  node = balance(node);
  return node;
}

template <typename T, typename V>
void AVL_tree<T, V>::delete_key(T k) {
  root = delete_key(root, k);
}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::search(tree_node<T, V> *node, T k) {
  if (!node || node->key == k) return node;
  if (k < node->key) {
    return search(node->left, k);
  } else {
    return search(node->right, k);
  }
}

template <typename T, typename V>
tree_node<T, V> *AVL_tree<T, V>::search(T k) {
  return search(root, k);
}

template <typename T, typename V>
void AVL_tree<T, V>::swap_avl(AVL_tree &other) {
  std::swap(this->root, other.root);
}

template <typename T, typename V>
void AVL_tree<T, V>::setroot(tree_node<T, V> *node) {
  root = node;
  if (root != nullptr) {
    root->parent = nullptr;
  }
}
template <typename T, typename V>
bool AVL_tree<T, V>::get_insert() {
  return inserted;
}

}  // namespace S21