#include "./S21_map.h"

namespace S21 {
template <typename T, typename V>
map<T, V>::map() : tree_map() {}

template <typename T, typename V>
map<T, V>::map(std::initializer_list<value_type> const &items) {
  for (auto k = items.begin(); k != items.end(); ++k) {
    this->insert(*k);
  }
}

template <typename T, typename V>
map<T, V>::map(const map &m) : tree_map(m.get_tree()) {}
template <typename T, typename V>
map<T, V>::~map() {}

template <typename T, typename V>
map<T, V> map<T, V>::operator=(map &&m) {
  if (this != &m) {
    tree_map = std::move(m.tree_map);
  }
  return *this;
}
template <typename T, typename V>
bool map<T, V>::empty() {
  bool buf = false;
  if (tree_map.getroot() == nullptr || tree_map.getroot()->size == 0) {
    buf = true;
  }
  return buf;
}

template <typename T, typename V>
typename map<T, V>::size_type map<T, V>::size() {
  size_type buf = 0;
  if (tree_map.getroot() != nullptr) {
    buf = size_type(tree_map.getroot()->size);
  }
  return buf;
}

template <typename T, typename V>
typename map<T, V>::size_type map<T, V>::max_size() {
  return pow(2, (64 - log(sizeof(T)) / log(2))) - 1;
}

template <typename T, typename V>
void map<T, V>::erase(typename map<T, V>::iterator pos) {
  if (pos != nullptr) {
    tree_map.delete_key(*pos);
  }
}

template <typename T, typename V>
void map<T, V>::swap(map &other) {
  tree_map.swap_avl(other.tree_map);
}

template <typename T, typename V>
typename map<T, V>::iterator map<T, V>::begin() {
  tree_node<value_type, V> *buf_tree = tree_map.getroot();
  if (buf_tree == nullptr) {
    return iterator(nullptr);
  } else {
    while (buf_tree->left != nullptr) {
      buf_tree = buf_tree->left;
    }
    return iterator(buf_tree);
  }
}

template <typename T, typename V>
typename map<T, V>::iterator map<T, V>::end() {
  return iterator(nullptr, this->tree_map.getroot());
}

template <typename T, typename V>
void map<T, V>::clear() {
  if (tree_map.getroot() != nullptr) {
    for (auto k = this->begin(); k != this->end(); ++k) {
      erase(k);
    }
    if (tree_map.getroot() != nullptr) {
      tree_map.delete_class(tree_map.getroot());
    }
  }
}

template <typename T, typename V>
bool map<T, V>::contains(const T &key) {
  if (tree_map.getroot() != nullptr) {
    for (iterator i = this->begin(); i != this->end(); ++i) {
      if (i->first == key) {
        return true;
      }
    }
  }
  return false;
}

template <typename T, typename V>
bool map<T, V>::contains_std_pair(const value_type &val) {
  if (tree_map.getroot() != nullptr) {
    for (auto i = this->begin(); i != this->end(); ++i) {
      if (i->first == val.first) {
        return true;
      }
    }
  }
  return false;
}

template <typename T, typename V>
std::pair<typename map<T, V>::iterator, bool> map<T, V>::insert(
    const value_type &value) {
  if (contains_std_pair(value)) {
    auto iter = this->tree_map.search(value);
    return std::make_pair(iterator(iter), false);
  } else {
    tree_map.insert_avl(value);
    auto iter = tree_map.search(value);
    if (tree_map.get_insert()) {
      return std::make_pair(iterator(iter), true);
    } else {
      return std::make_pair(iterator(iter), false);
    }
  }
}

template <typename T, typename V>
std::pair<typename map<T, V>::iterator, bool> map<T, V>::insert(
    const key_type &key, const mapped_type &obj) {
  return insert(std::make_pair(key, obj));
}

template <typename T, typename V>
std::pair<typename map<T, V>::iterator, bool> map<T, V>::insert_or_assign(
    const key_type &key, const mapped_type &obj) {
  if (this->empty()) {
    return insert(std::make_pair(key, obj));
  } else {
    for (auto k = this->begin(); k != this->end(); ++k) {
      if (k->first == key) {
        k->second = obj;
        return std::make_pair(k, false);
      }
    }
  }
  return insert(std::make_pair(key, obj));
}

template <typename T, typename V>
void map<T, V>::merge(map &other) {
  std::pair<typename map<T, V>::iterator, bool> res;
  auto i = other.begin();
  while (i != other.end()) {
    res = this->insert(*i);
    if (res.second) {
      other.erase(i);
    }
    i++;
  }
}

template <typename T, typename V>
typename map<T, V>::mapped_type &map<T, V>::at(const_reference key) {
  if (this->begin() != nullptr) {
    for (iterator i = this->begin(); i != this->end(); ++i) {
      if (i->first == key) {
        return i->second;
      }
      throw std::out_of_range(
          "Container does not have an element with the specified key");
    }
  }
  static mapped_type default_value;
  return default_value;
}

template <typename T, typename V>
typename map<T, V>::mapped_type &map<T, V>::operator[](const_reference key) {
  if (this->begin() != nullptr) {
    for (auto i = this->begin(); i != this->end(); ++i) {
      if (i->first == key) {
        return i->second;
      }
    }
    auto res = insert(value_type(key, mapped_type()));
    return res.first->second;
  }
  static mapped_type default_value;
  return default_value;
}
template <typename T, typename V>
const AVL_tree<typename map<T, V>::value_type, V> &map<T, V>::get_tree() const {
  return tree_map;
}

}  // namespace S21
