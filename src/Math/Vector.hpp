#pragma once

template <size_t M, typename T = float>
class Vector {
 public:
  Vector(T x, T y, T z, T w, typename std::enable_if<M == 4>::type* = 0);
  ~Vector() {}

  float x() const { return _data[0]; }

  float y() const { return _data[1]; }

  float z() const { return _data[2]; }

  float w() const { return _data[3]; }

 public:
  float _data[4];
};

template <size_t M, typename T>
inline Vector<M, T>::Vector(T x, T y, T z, T w,
                            typename std::enable_if<M == 4>::type*)
    : _data{x, y, z, w} {}
