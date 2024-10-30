#include "./iterators.h"

namespace S21 {
template <typename T, typename V>
iterator<T, V>::iterator(tree_node<T, V> *node) {
  node_ = node;
}

template <typename T, typename V>
iterator<T, V>::iterator(tree_node<T, V> *nil, tree_node<T, V> *root) {
  node_ = nil;
  root_ = root;
}

template <typename T, typename V>
iterator<T, V> iterator<T, V>::operator+(const int value) {
  iterator buf = *this;
  for (int i = 0; i < value; i++) {
    buf++;
  }
  return buf;
}

template <typename T, typename V>
bool iterator<T, V>::operator==(const iterator &other) const {
  return other.node_ == node_;
}

template <typename T, typename V>
bool iterator<T, V>::operator!=(const iterator &other) const {
  return other.node_ != node_;
}

template <typename T, typename V>
iterator<T, V> &iterator<T, V>::operator++() {
  if (node_ != nullptr) {
    if (node_->right != nullptr) {
      node_ = node_->right;
      while (node_->left != nullptr) {
        node_ = node_->left;
      }
    } else {
      tree_node<T, V> *parent = node_->parent;
      while (parent != nullptr && node_ == parent->right) {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
    return *this;
    ;
  }
  return *this;
}

template <typename T, typename V>
iterator<T, V> iterator<T, V>::operator++(int) {
  iterator buf = *this;
  ++(*this);
  return buf;
}

template <typename T, typename V>
iterator<T, V> &iterator<T, V>::help_minus_minus() {
  if (node_ != nullptr) {
    if (node_->left != nullptr) {
      node_ = node_->left;
      while (node_->right != nullptr) {
        node_ = node_->right;
      }
    } else {
      tree_node<T, V> *parent = node_->parent;
      while (parent != nullptr && node_ == parent->left) {
        node_ = parent;
        parent = parent->parent;
      }
      node_ = parent;
    }
    return *this;
  }
  return *this;
}

template <typename T, typename V>
tree_node<T, V> *iterator<T, V>::max_key(tree_node<T, V> *node) {
  if (node != nullptr) {
    if (node->right != nullptr) {
      return max_key(node->right);
    } else {
      return node;
    }
  }
  return nullptr;
}

template <typename T, typename V>
iterator<T, V> iterator<T, V>::operator--(int) {
  iterator buf = *this;
  --(*this);
  return buf;
}

template <typename T, typename V>
int iterator<T, V>::size_tree(tree_node<T, V> *node) {
  int buf = 0;
  if (node != nullptr) {
    buf = node->size;
  } else {
    buf = 0;
  }
  return buf;
}

template <typename T, typename V>
iterator<T, V> &iterator<T, V>::operator--() {
  if (size_tree(root_) > 0) {
    if (node_ != nullptr) {
      return help_minus_minus();
    }
    node_ = max_key(root_);
    return *this;
  }
  return help_minus_minus();
}

template <typename T, typename V>
typename iterator<T, V>::reference iterator<T, V>::operator*() const {
  if (node_ == nullptr) {
    static T default_value = T{};
    return default_value;
  }
  return node_->key;
}

template <typename T, typename V>
typename iterator<T, V>::pointer iterator<T, V>::operator->() const {
  return &(node_->key);
}

}  // namespace S21