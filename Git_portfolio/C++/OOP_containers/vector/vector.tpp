#include "./vector.h"
namespace S21 {

template <typename T>
vector<T>::vector() : node_vector(nullptr), size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(size_type n)
    : node_vector(new value_type[n]), size_(n), capacity_(n) {}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : node_vector(new value_type[items.size()]),
      size_(items.size()),
      capacity_(items.size()) {
  auto a = items.begin();
  for (size_type i = 0; i < items.size(); ++i) {
    node_vector[i] = *a;
    a++;
  }
}

template <typename T>
vector<T>::vector(const vector &v)
    : node_vector(new value_type[v.capacity_]),
      size_(v.size_),
      capacity_(v.capacity_) {
  std::copy(v.node_vector, v.node_vector + v.size_, node_vector);
}

template <typename T>
vector<T>::vector(vector &&v) noexcept
    : node_vector(new value_type[v.capacity_]),
      size_(v.size_),
      capacity_(v.capacity_) {
  std::copy(v.node_vector, v.node_vector + v.size_, node_vector);
  delete[] v.node_vector;
  v.node_vector = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] node_vector;
  node_vector = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&v) {
  if (this != &v) {
    this->swap(v);
    delete[] v.node_vector;
    v.node_vector = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

template <typename T>
typename vector<T>::size_type vector<T>::size() const {
  return size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size >= max_size()) {
    throw std::length_error("Mistake");
  } else if (size > size_) {
    T *buf = new T[size];
    std::copy(node_vector, node_vector + size_, buf);
    // for (int i = 0; i < size_; ++i){
    //     buf[i] = node_vector[i];
    // }
    delete[] node_vector;
    node_vector = buf;
    capacity_ = size;
  }
}
template <typename T>
typename vector<T>::size_type vector<T>::max_size() const {
  return pow(2, (64 - log(sizeof(T)) / log(2))) - 1;
}

template <typename T>
bool vector<T>::empty() const {
  bool buf = false;
  if (size_ == 0) {
    buf = true;
  }
  return buf;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (capacity_ == size_) {
    if (capacity_) {
      this->reserve(2 * size_);
    } else {
      this->reserve(1);
    }
  }
  node_vector[size_] = value;
  size_++;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ > 0) {
    this->size_--;
  }
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(node_vector, other.node_vector);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
void vector<T>::clear() noexcept {
  size_ = 0;
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() const {
  if (size_ == 0) {
    throw std::length_error("Mistake");
  }
  return node_vector[0];
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() const {
  if (size_ == 0) {
    throw std::length_error("Mistake");
  }
  return node_vector[size_ - 1];
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() {
  return VectorIterator(node_vector);
}

template <typename T>
typename vector<T>::iterator vector<T>::end() {
  return VectorIterator(node_vector + size_);
}

template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_ || pos < 0) {
    throw std::out_of_range("Mistake");
  } else {
    return node_vector[pos];
  }
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  if (pos >= size_ || pos < 0) {
    throw std::out_of_range("Mistake");
  } else {
    return node_vector[pos];
  }
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  if (pos >= size_ || pos < 0) {
    throw std::out_of_range("Mistake");
  } else {
    return node_vector[pos];
  }
}

template <typename T>
T *vector<T>::data() {
  return node_vector;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    T *buf = new T[size_];
    std::copy(node_vector, node_vector + size_, buf);
    // for (int i = 0; i < size_; ++i){
    //     buf[i] = node_vector[i];
    // }
    delete[] node_vector;
    node_vector = buf;
    capacity_ = size_;
  }
}

template <typename T>
void vector<T>::erase(iterator pos) {
  size_type dif = pos - begin();
  if (dif > size_) {
    throw std::out_of_range("Mistake");
  } else {
    for (auto i = pos; i != this->end() - 1; ++i) {
      *i = *(i + 1);
    }
    --size_;
  }
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  size_type dif = pos - begin();
  if (dif > size_) {
    throw std::out_of_range("Mistake");
  }
  if (capacity_ == size_) {
    if (capacity_) {
      this->reserve(2 * size_);
    } else {
      this->reserve(1);
    }
  }
  auto pos_ = begin() + dif;
  int flag = 0;
  for (auto i = this->end(); i != pos_; --i) {
    if (flag == 0) {
      *(i + 1) = *(i);
      ++flag;
    }
    *i = *(i - 1);
  }
  *pos_ = value;
  ++size_;
  return pos_;
}
}  // namespace S21