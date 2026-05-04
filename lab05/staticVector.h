
#ifndef STATIC_VECTOR_H
#define STATIC_VECTOR_H


#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

template <typename T, size_t N>
class Vector;

template <typename T> class Vector<T, 0>;

template <typename T, size_t N>
class Vector{
    T data[N];

public:
    typedef T value_type;
    typedef std::size_t  size_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T& const_reference;

    Vector() {
        std::fill(std::begin(data), std::end(data),T{}); 
    }
    Vector(const Vector & v) {
        std::copy(std::begin(v.data), std::end(v.data), data);
    }
    Vector &operator=(const Vector & m) {
        if(this != &m) {
            std::copy(std::begin(m.data), std::end(m.data), data);
        }
        return *this;
    }
    Vector(const std::initializer_list<T> &list){ 
        std::copy(list.begin(), list.end(), data);
     }

    friend Vector operator+ (const  Vector & u, const Vector & v ){
        Vector res;
        for(size_type i = 0; i < N; i++) {
            res.data[i] = u.data[i] + v.data[i];
        }
        return res;
    }

    Vector(const Vector<T,0>& dynamic) {
        for(size_type i = 0; i < N; i++) data[i] = dynamic[i];
    }

    template <typename U, size_t M> friend class Vector;

    friend Vector operator+(const Vector& s, const Vector<T, 0>& d) {
        Vector res;
        for(size_t i = 0; i < N; ++i) res.data[i] = s.data[i] + d[i];
        return res;
    }

    friend Vector operator+(const Vector<T, 0>& d, const Vector& s) {
        return s + d;
    }

    constexpr size_type size() const {
        return N;
    }

    const_reference get(size_type index) const {
        return data[index];
    }

    void set(size_type index, const_reference value) {
        data[index] = value;
    }

    reference operator[](size_type index){
        return data[index];
    }
    const_reference operator[](size_type index) const{
        return data[index];
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
        for( auto elem: v.data ){
            out << elem << " ";
        }
        return out;
    }
};

#endif //STATIC_VECTOR_H